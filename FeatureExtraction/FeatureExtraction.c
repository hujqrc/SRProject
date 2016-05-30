/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��featureExtraction.c                                              */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�2012.05.27                                                       */
/*----------------------------------------------------------------------------*/
/* �ļ�������������ȡ                                                         */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/CyDebug.h"
#include "../SRParamSet/datadef.h"
#include "MFCC.h"
#include "DeltaFeature.h"
#include "FeatureTransform.h"

// ��ȡ�����ľ�̬��������
static CyVOID GetStaticMFCC(FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff);

// ͨ��֡��Ż��һ֡��������
static CyVOID GetFrmDataByIdx(CyFLOAT *data, VoiceBuffer *pVoiceBuff, CyINT16 idx);

CyVOID InitFeatureExtractionParam()
{
	InitMfccParam();

	// ֻ�в��Ǹ�����Ĭ�ϲ�����ִ�г�ʼ��
#if (DELTA_WIN!=2)  
	InitDeltaParam();
#endif
}

CyVOID FeatureExtraction( FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff )
{
	// ��ȡ��̬MFCC����
	GetStaticMFCC(pFeaSeq, pVoiceBuff);

#if ((DELTA_OPT == DELTA) || (DELTA_OPT == DELTA_DELTA))
	// һ�ײ�ֲ���
	Delta1Feature(pFeaSeq);
#endif

#if (DELTA_OPT == DELTA_DELTA)
	// ���ײ�ֲ���
	Delta2Feature(pFeaSeq);
#endif

#if (ROBUST_OPT == ROBUST_CMVN)
	CMVN(pFeaSeq);
#elif (ROBUST_OPT == ROBUST_CMS)
	CMS(pFeaSeq);
#endif
}


CyVOID GetStaticMFCC(FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff)
{
	CyINT16 i;   // frame index
	CyFLOAT frmData[FRAME_SIZE];

	for ( i =  pVoiceBuff->uVadIdxBuf[0];
	      i <= pVoiceBuff->uVadIdxBuf[pVoiceBuff->uVadIdxCount-1];
		  i++)
	{
		//memset(data, 0, FRAME_SIZE*sizeof(CyFLOAT));  //��ʼ����0

		// Step 1: ���һ֡����
		GetFrmDataByIdx(frmData, pVoiceBuff, i);
		
		// Step 2: ��ȡһ֡�����ľ�̬MFCC����
		GetFrmStaticMFCC(pFeaSeq->feature[pFeaSeq->dFeaCounter++], frmData, FRAME_SIZE);
	}
}


CyVOID GetFrmDataByIdx(CyFLOAT *data, VoiceBuffer *pVoiceBuff, CyINT16 idx)
{
	CyINT16 i;
	
	idx = idx*FRAME_SHIFT;  //����������λ��

	if ( idx+FRAME_SIZE < MAX_SAMPLE_NUM )
	{
		for (i=0; i<FRAME_SIZE; i++, idx++)
		{
			data[i] = pVoiceBuff->fData[idx];
		}
	}
	else
	{
		for (i=0; i<FRAME_SIZE; i++, idx++)
		{
			data[i] = pVoiceBuff->fData[idx%MAX_SAMPLE_NUM];
		}
	}
	
}