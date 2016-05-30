/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
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
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#include "datadef.h"
#include <string.h>
#include <math.h>
#include "CyMath.h"

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

CyFLOAT VecDistance(FVector a, FVector b)
{
	CyINT16 i;
	CyFLOAT dist = 0;

	for (i=0; i<FEATURE_DIM; i++)
	{
#if (DIST_OPT == DIST_ABS)
		dist += CyABS(a[i]-b[i]);
#elif (DIST_OPT == DIST_EUC)
		dist += (a[i]-b[i])*(a[i]-b[i]);
#endif
	}

#if (DIST_OPT == DIST_ABS)
	return dist;
#elif (DIST_OPT == DIST_EUC)
	return CySQRT(dist);
#endif
}