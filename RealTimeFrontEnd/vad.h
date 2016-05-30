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

#ifndef _VAD_H_
#define _VAD_H_

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"

//////////////////////////////////////////////////////////////////////////
// VAD������ݽṹ����
typedef enum _VOICE_status
{
	VOICE_SIL,			//������״̬
	VOICE_PRE,			//
	VOICE_BEGIN,		//
	VOICE_STOP,			//
	VOICE_END			//������
} VOICE_status;			//������״̬


typedef struct _Segment
{
	CyUINT16			bgnFrmIdx;				//��������ʼ֡���
	CyUINT16			endFrmIdx;				//��������ֹ֡���
	CyUINT16			segLength;				//�ֶεĳ���
} Segment;			//������


typedef struct _VADInfo
{
	CyFLOAT			fThresholdVolume;				//VADƽ����ֵ
	CyBOOL			bThresholdComputed;						//����Ƿ��Ѿ����������ľ�ֵ
	
	CyUINT8			segCount;					//���������
	Segment			Segs[VAD_MAX_SEGMENT];		//������
	
	VOICE_status	curStatus;				 	//��ǰ״̬
	CyUINT8			curStatusDuration;			//��ǰ״̬פ��ʱ��
	
} VADParam; 


//���û��ʼ��VADParam
CyVOID ResetVADParam();

// ʵʱ�˵���
CyVOID RealTimeVAD(VoiceBuffer *pVoiceBuf);


#endif