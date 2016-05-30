/******************************************************************************/
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��datatype.h                                                       */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                        */
/* �������ڣ�20120510                                                         */
/*----------------------------------------------------------------------------*/
/* �ļ�������һЩ���ݽṹ�Ķ���                                               */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* 2011-7-26 ��demo                                                           */
/******************************************************************************/

#include "../SRParamSet/datadef.h"
#include "dspAIC.h"
#include <string.h>

//#define RESET_MEMSET



// ��������������
void ResetVoiceBuffer(VoiceBuffer* vbuff)
{
#ifdef RESET_MEMSET
	memset(vbuff, 0, sizeof(VoiceBuffer));  //���ַ�����ʱ������ȫ
#else	
 	vbuff->iFrmCounter = 0;
 	vbuff->iSmplCounter = 0;
 	vbuff->iSmplCursor = 0;
	vbuff->bSmplFinished = CyFALSE;
	
 	vbuff->uVadIdxCount = 0;
 	vbuff->uVadIdxCursor = 0;
	vbuff->bVadFinished = CyFALSE;
#endif
}


//��ʼ����������������
void ResetFeaSeq(FeatureSeq* pFeaSeq)
{
#ifdef RESET_MEMSET
	memset(pFeaSeq, 0, sizeof(FeatureSeq));  //���ַ�����ʱ������ȫ
#else	
	pFeaSeq->dFeaCounter = 0;
#endif	
}
