/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��nlp.c                                                            */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�2012.05.27                                                       */
/*----------------------------------------------------------------------------*/
/* �ļ������������������з����Էֶ�                                           */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/CyMath.h"
#include "nlp.h"

CyVOID NonLinerPartition( FeatureSeq *pFeaSeq, CyINT16 partitionNum )
{
	CyINT16 i, j;
	CyFLOAT diff[MAX_FRAMES]={0};

	// ����������С��״̬��
	if( pFeaSeq->dFeaCounter < NLP_N)
	{

	}

	// Step 1: �������������仯�������ۼ�
	for (i=1; i< pFeaSeq->dFeaCounter; i++)
	{
		diff[i] = diff[i-1] + VecDistance(pFeaSeq->feature[i], pFeaSeq->feature[i-1]);
	}

	// ��diff[0]���洢ƽ���ܱ仯��
	*diff = diff[i-1]/(CyFLOAT)partitionNum;

	// Step 2: ����ÿ����ķֽ��
	pFeaSeq->iNlpParam[0] = 0;   // ��һ���ֽ���ǵ�0֡

	for (i=1, j=1; i<pFeaSeq->dFeaCounter; i++)
	{
		if ( diff[i]>diff[0]*j )    // ʽ(2.41)
		{
			pFeaSeq->iNlpParam[j++] = i;

			if(j>=partitionNum) break;
		}
	}

	// ���һ���ֽ�������һ֡
	pFeaSeq->iNlpParam[partitionNum] = pFeaSeq->dFeaCounter;
}