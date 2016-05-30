/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��vad.h                                                            */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                        */
/* �������ڣ�20120515                                                         */
/*----------------------------------------------------------------------------*/
/* �ļ�������ǰ�˴���-ʵʱ�˵���                                            */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/CyDebug.h"
#include "vad.h"
#include "dspAIC.h"

#ifdef RESET_MEMSET
#include <string.h>
#endif


static VADParam sVadParam;

static CyVOID VadFinished(VoiceBuffer *pVoiceBuf);


//���û��ʼ��VADParam
CyVOID ResetVADParam()
{
#ifdef RESET_MEMSET
	memset(&sVadParam, 0, sizeof(VADParam));  //���ַ�����ʱ������ȫ
#else
 	sVadParam.fThresholdVolume = 0.0f;
 	sVadParam.curStatus = VOICE_SIL;
 	sVadParam.curStatusDuration = 0;
 	sVadParam.segCount = 0;
	sVadParam.bThresholdComputed = CyFALSE;
#endif	
}

#if (BUFFER_RECYCLING_OPT == RECYCLING_NO)   // ��ѭ�����û�����(0)��ѭ�����û�����(1)����
// ��ѭ���������˵���
CyVOID RealTimeVAD(VoiceBuffer *pVoiceBuf)
{
	CyINT16 i, j;
	CyFLOAT maxVolume, minVolume;
	CyFLOAT *pVolumes;// = pVoiceBuf->fFrmEnergyBuf;

	// Step 1: ������ֵ
	pVolumes = pVoiceBuf->fFrmEnergyBuf;
	maxVolume = minVolume = *pVolumes++;
	for (i=1; i<pVoiceBuf->iFrmCounter; i++, pVolumes++)
	{
		if(maxVolume < *pVolumes) maxVolume = *pVolumes;
		else if(minVolume > *pVolumes) minVolume = *pVolumes;
	}
	
	// �趨��ֵ
	sVadParam.fThresholdVolume = maxVolume*0.08f;//(maxVolume-minVolume)*0.2f+minVolume;
	sVadParam.bThresholdComputed = CyTRUE;

	CyTRACE("Average Volume is: %3.14f. VAD Beginning ...\n", sVadParam.fThresholdVolume);

	// Step 2: �˵����о�
	pVolumes = pVoiceBuf->fFrmEnergyBuf;

	for (i=0, j=0; i < pVoiceBuf->iFrmCounter; i++, pVolumes++)
	{
		if ( *pVolumes > sVadParam.fThresholdVolume )
		{
			j++;
			continue;    // ������һ��ѭ��
		}
		else if( j >= VAD_MAX_PRENUM || 
			     (sVadParam.segCount > 0 && j>VAD_MIN_PRENUM) )
		{
			sVadParam.Segs[sVadParam.segCount].bgnFrmIdx = i - j;
			sVadParam.Segs[sVadParam.segCount].endFrmIdx = i ;
			sVadParam.Segs[sVadParam.segCount].segLength = j;
			
			if( ++sVadParam.segCount >= VAD_MAX_SEGMENT )
			{
				CyTRACE("VAD : SegCount >= 5\n");
				break;
			}
		}
		
		j = 0;
	}

	// Step 3�������������VoiceBuffer��
	for (i=0; i<sVadParam.segCount; i++)
	{
		for (j = sVadParam.Segs[i].bgnFrmIdx; 
			 j < sVadParam.Segs[i].endFrmIdx;
			 j++ )
		{
			pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = j;
		}
	}

	pVoiceBuf->bVadFinished = CyTRUE;
}

CyVOID VadFinished(VoiceBuffer *pVoiceBuf)
{
	CyTRACE("VAD : [ThresholdVolume = %3.14f]\n", sVadParam.fThresholdVolume);
	pVoiceBuf->bVadFinished = CyTRUE;
}

#else
// ѭ���������˵���
CyVOID RealTimeVAD(VoiceBuffer *pVoiceBuf)
{
	CyINT16 curFrmIdx;      //��ǰ����֡���
	CyFLOAT curFrmVolume;   //��ǰ����֡�ܲ���
	
	curFrmIdx = pVoiceBuf->iFrmCounter;
	curFrmVolume = pVoiceBuf->fFrmEnergyBuf[curFrmIdx];

	// ��ǰVAD_NOISE_FRAME֡����������ƽ����������
	if ( !sVadParam.bThresholdComputed )
	{
		sVadParam.fThresholdVolume += curFrmVolume;
		CyTRACE("VAD : Averaging Volume, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
		if( (++sVadParam.curStatusDuration)==VAD_NOISE_FRAME )
		{
			sVadParam.fThresholdVolume /= (CyFLOAT)VAD_NOISE_FRAME;
			sVadParam.fThresholdVolume *= .5f;
			sVadParam.bThresholdComputed = CyTRUE;

			CyTRACE("Average Volume is: %3.14f. VAD Beginning ...\n", sVadParam.fThresholdVolume);
		}

		return;
	}

	switch(sVadParam.curStatus)
	{
		case VOICE_SIL :
			if( curFrmVolume > sVadParam.fThresholdVolume)
			{
				//����ֵ������ֵ����������Ч����֡���ı䵱ǰ״̬
				sVadParam.curStatus = VOICE_PRE;
				//��ǰ״̬��פ��֡����1
				sVadParam.curStatusDuration = 1;
				//����ǰ֡����֡������
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;
				
				//For debug
				CyTRACE("VAD : VOICE_SIL -->  VOICE_PRE, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			else
			{
				sVadParam.curStatusDuration++;
				CyTRACE("VAD : VOICE_SIL -->  VOICE_SIL, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			break;
		case VOICE_PRE :
			if( curFrmVolume > sVadParam.fThresholdVolume )
			{
				//����ǰ֡������֡��������פ��֡������
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;
				sVadParam.curStatusDuration++;

				//For debug
				CyTRACE("VAD : VOICE_PRE -->  VOICE_PRE, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				
				//��һ�������������鳤�ȳ���5֡����Ϊ������ʼ��������һ��״̬
				if( sVadParam.curStatusDuration >= VAD_MAX_PRENUM )
				{	
					//״̬�ı䣬��������פ��֡����
					sVadParam.curStatus = VOICE_BEGIN;
					sVadParam.curStatusDuration = 0;  //��ʱ��ǰ֡���δ���VOICE_PRE״̬

					//��VOICE_SIL��VOICE_PRE�ĵ�һ����Ч֡����һ�����������ʼ֡
					sVadParam.Segs[sVadParam.segCount].bgnFrmIdx = (curFrmIdx-VAD_MAX_PRENUM+1+MAX_FRAMES)%MAX_FRAMES;
					//�趨��ǰ�����ֿ�ĳ���
					sVadParam.Segs[sVadParam.segCount].segLength = VAD_MAX_PRENUM;
					
					//For debug
					CyTRACE("VAD : VOICE_PRE -->  VOICE_BEGIN, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			// �����������С��ƽ�������������Ѿ���⵽�����Σ����뵥�ֽض�״̬
			else if( sVadParam.segCount > 0)
			{
				sVadParam.curStatus = VOICE_STOP;

				//״̬�ı䣬��������פ��֡��������������Ľ�ֹ��
				sVadParam.curStatusDuration = 1;
				sVadParam.Segs[sVadParam.segCount++].endFrmIdx = curFrmIdx;

				//For debug
				CyTRACE("VAD : VOICE_PRE -->  VOICE_STOP, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				
				//��һ�������ﵽ���ֿ���������Ϊ��������ֹ
				if( sVadParam.segCount==VAD_MAX_SEGMENT )
				{
					sVadParam.curStatus = VOICE_END;

					// �˵���������ر������ɼ�
					VadFinished(pVoiceBuf);

					//For debug
					CyTRACE("VAD : VOICE_PRE -->  VOICE_END, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			//������Ϊǰ���֡��һ����������
			else
			{
				sVadParam.curStatus = VOICE_SIL;
				//�����趨�Լ���֡��
				pVoiceBuf->uVadIdxCount = 0;
				//ResetFrmIdxSeq(pFrmIdxSeq);

				//For debug
				CyTRACE("VAD : VOICE_PRE -->  VOICE_SIL, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			break;
		case VOICE_BEGIN :
			if( curFrmVolume > sVadParam.fThresholdVolume )
			{
				//��ǰ֡��פ��֡���������鳤������
				sVadParam.curStatusDuration++;
				sVadParam.Segs[sVadParam.segCount].segLength++;

				//����ǰ֡������֡������
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;

				//For debug
				CyTRACE("VAD : VOICE_BEGIN -->  VOICE_BEGIN, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			else
			{
				//����������ֵС��ƽ������ʱ��Ϊ���ֽ�����״̬�ı䣬��������״̬פ��֡��
				sVadParam.curStatus = VOICE_STOP;
				sVadParam.curStatusDuration = 1;
				
				//����������Ľ�ֹ�㣬����Ч�������������õ�
				sVadParam.Segs[sVadParam.segCount++].endFrmIdx = curFrmIdx;
				
				//For debug
				CyTRACE("VAD : VOICE_BEGIN -->  VOICE_STOP, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);

				//��һ�������ﵽ���ֿ���������Ϊ��������ֹ
				if( sVadParam.segCount==VAD_MAX_SEGMENT )
				{
					sVadParam.curStatus = VOICE_END;

					// �˵���������ر������ɼ�
					VadFinished(pVoiceBuf);

					//For debug
					CyTRACE("VAD : VOICE_STOP -->  VOICE_END, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			break;
		case VOICE_STOP :
			if( curFrmVolume > sVadParam.fThresholdVolume )
			{
				//����ֵ������ֵ����������Ч����֡���ı䵱ǰ״̬,��ǰ״̬��פ��֡����1
				sVadParam.curStatus = VOICE_PRE;
				sVadParam.curStatusDuration = 1;

				//����ǰ֡������֡������
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;

				//For debug
				CyTRACE("VAD : VOICE_STOP -->  VOICE_PRE, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			else
			{
				CyTRACE("VAD : VOICE_STOP -->  VOICE_STOP, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				if( (++sVadParam.curStatusDuration) >= VAD_MAX_STOP )
				{
					sVadParam.curStatus = VOICE_END;
					
					// �˵���������ر������ɼ�
					VadFinished(pVoiceBuf);
					
					//For debug
					CyTRACE("VAD : VOICE_STOP -->  VOICE_END, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			break;
		case VOICE_END :
			// �˵���������ر������ɼ�
			VadFinished(pVoiceBuf);

			CyTRACE("VAD : ----End!----\n");
			break;
		default:
			//HError(-1, "Unknown VOICE_status in RealTimeVAD.\n");
			break;
	}
}

CyVOID VadFinished(VoiceBuffer *pVoiceBuf)
{
	AIC_Close();
	CyTRACE("VAD : [ThresholdVolume = %3.14f]\n", sVadParam.fThresholdVolume);
	pVoiceBuf->bVadFinished = CyTRUE;
}

#endif