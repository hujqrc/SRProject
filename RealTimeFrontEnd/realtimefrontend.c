/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��realtimefrontend.h                                               */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                        */
/* �������ڣ�20120511                                                         */
/*----------------------------------------------------------------------------*/
/* �ļ�������ǰ�˴���ӿڶ���                                                 */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/CyDebug.h"
#include "../SRParamSet/datadef.h"
#include "dspAIC.h"
#include "realtimefrontend.h"
#include "common.h"
#include "vad.h"
#include "../FeatureExtraction/FeatureExtraction.h"

static volatile CyBOOL mutex = CyTRUE;   // ֻ�ܵ��߳̽����ģ��

#if (BUFFER_RECYCLING_OPT == RECYCLING_NO)   // ��ѭ�����û�����(0)��ѭ�����û�����(1)����
// ǰ��ʵʱ����������ѭ�����û���������Ҫ���ɼ������������ݴ��ݸ�ǰ�˴������
CyVOID Frontend_VoiceDataProcessing( CyINT16 *data, CyUINT16 length )
{
	CyUINT16 i;
	for(i=0;i<length;i++)
	{
		if( gVoiceBuf.bSmplFinished ) return; // �������ֱ�ӷ���

		gVoiceBuf.fData[gVoiceBuf.iSmplCounter++]=*(data++)/(CyFLOAT)32768;

		if( mutex )
		{
			mutex = CyFALSE;
			while( gVoiceBuf.iSmplCounter >= gVoiceBuf.iSmplCursor+FRAME_SIZE )   //��ʾ�Ѳ�������һ֡
			{
				//���һ֡�������ݵ�����
				CyFLOAT frmVolume = GetFrmVolume(gVoiceBuf.fData+gVoiceBuf.iSmplCursor, FRAME_SIZE);
				
				//������������������������
				gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.iFrmCounter] = frmVolume;
				
				CyTRACE("[Frame %4d]: %3.14f\n", gVoiceBuf.iFrmCounter, frmVolume);
				
				//ʵʱVAD���
				//RealTimeVAD(&gVadInfo, &gFrmIdxSeq, frmVolume, gSampleBuff.iFrmCounter);
				
				//�������֡���������ܱ�������֡�������������
				if( (++gVoiceBuf.iFrmCounter) >= MAX_FRAMES)
				{
					//�ر������ɼ�
					//StopSampling(&gVoiceBuf);
					Frontend_StopSampling();
					mutex = CyTRUE;
					//Frontend_Reset();
					return;
				}
				
				gVoiceBuf.iSmplCursor += FRAME_SHIFT;
			}

			mutex = CyTRUE;
		}
	}
}
#else   //ѭ�����û�����
// ǰ��ʵʱ��������ѭ�����û���������Ҫ���ɼ������������ݴ��ݸ�ǰ�˴������
CyVOID Frontend_VoiceDataProcessing( CyINT16 *data, CyUINT16 length )
{
	CyUINT16 i;
	//CyTRACE("[Frame %4d]\n", data[0]);
	for(i=0;i<length;i++)
	{
		if( gVoiceBuf.bSmplFinished ) return; // �������ֱ�ӷ���

		gVoiceBuf.fData[(gVoiceBuf.iSmplCounter++)%MAX_SAMPLE_NUM]=*(data++)/(CyFLOAT)32768;
		
		if( mutex )
		{
			mutex = CyFALSE;
			while( gVoiceBuf.iSmplCounter >= gVoiceBuf.iSmplCursor+FRAME_SIZE )   //��ʾ�Ѳ�������һ֡
			{
				//���һ֡�������ݵ�����
				CyFLOAT frmVolume = GetFrmVolume(gVoiceBuf.fData, gVoiceBuf.iSmplCursor, FRAME_SIZE);
				
				//������������������������
				gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.iFrmCounter] = frmVolume;
				
				//CyTRACE("[Frame %4d]: %3.14f\n", gVoiceBuf.iFrmCounter, frmVolume);
				//printf("[Frame %4d]: %3.14f\n", gVoiceBuf.iFrmCounter+1, frmVolume);
				
				//ʵʱVAD���
				RealTimeVAD(&gVoiceBuf);
				
				//�������֡���������ܱ�������֡�������������
				gVoiceBuf.iFrmCounter=(gVoiceBuf.iFrmCounter+1)%MAX_FRAMES;
				
				gVoiceBuf.iSmplCursor += FRAME_SHIFT;

				if(gVoiceBuf.iSmplCursor>=MAX_SAMPLE_NUM)
				{
					gVoiceBuf.iSmplCursor %= MAX_SAMPLE_NUM;
					gVoiceBuf.iSmplCounter %= MAX_SAMPLE_NUM;
					//AIC_Close();
					//Frontend_Reset();
				}
			}
			
			mutex = CyTRUE;
		}
	}
}
#endif

// ǰ������
CyVOID Frontend_Reset()
{
	ResetVoiceBuffer(&gVoiceBuf);
	ResetVADParam();
	ResetFeaSeq(&gFeaSeq);
}


CyVOID Frontend_Init()
{
	InitFeatureExtractionParam();

	return;
}

// ǰ�˴�������
CyVOID Frontend_Setup(CyVOID (*DeviceOpen)(), CyVOID (*DeviceClose)())
{
	AIC_Open = DeviceOpen;
	AIC_Close = DeviceClose;

	Frontend_Init();
}

CyVOID Frontend_StopSampling()
{
	StopSampling(&gVoiceBuf);
}

#if (BUFFER_RECYCLING_OPT == RECYCLING_NO)   // ��ѭ�����û�����(0)��ѭ�����û�����(1)����
// ����������ǰ�˴���������������
CyVOID Frontend_GetFeaSeq(FeatureSeq *pFeaSeq)
{
	// ����ϵͳ����
	Frontend_Reset();
	
	// ����Ƶ�豸�ɼ�
	AIC_Open();

	while( !gVoiceBuf.bSmplFinished ); //�ȴ������������

	RealTimeVAD(&gVoiceBuf);
	
	//�ȴ��˵������
	while( !gVoiceBuf.bVadFinished );
	
	// ����������ȡ
	//FeatureExtraction(pFeaSeq, &gVoiceBuf);

BlockTRACE_Begin
	printf("�˵����������\n");
	for(gVoiceBuf.uVadIdxCursor = 0; gVoiceBuf.uVadIdxCursor<gVoiceBuf.uVadIdxCount; gVoiceBuf.uVadIdxCursor++)
	{
		printf("%4c[frmIdx: %4d, frmVolume: %3.14f]\n", '\0', 
			gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor], 
			gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor]]);
	}
	printf("\n");
BlockTRACE_End		
}

#else
// ����������ǰ�˴���������������
CyVOID Frontend_GetFeaSeq(FeatureSeq *pFeaSeq)
{
	if ( pFeaSeq == CyNULL )
	{
		pFeaSeq = &gFeaSeq;
	}

	// ����ϵͳ����
	Frontend_Reset();

	// ����Ƶ�豸�ɼ�
	AIC_Open();

	//�ȴ���Ч�����ɼ����
	while( !gVoiceBuf.bVadFinished );

	// ����������ȡ
	FeatureExtraction(pFeaSeq, &gVoiceBuf);

BlockTRACE_Begin
	printf("�˵����������\n");
	for(gVoiceBuf.uVadIdxCursor = 0; gVoiceBuf.uVadIdxCursor<gVoiceBuf.uVadIdxCount; gVoiceBuf.uVadIdxCursor++)
	{
		printf("%4c[frmIdx: %4d, frmVolume: %3.14f]\n", '\0', 
			gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor], 
			gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor]]);
	}
	printf("\n");
BlockTRACE_End

}
#endif
