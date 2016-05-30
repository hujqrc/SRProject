/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��nlpgmmRecognition.h                                              */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�2012.06.03                                                       */
/*----------------------------------------------------------------------------*/
/* �ļ������������������У���������                                           */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/nlpgmm.h"
#include "../SRParamSet/CyMath.h"
#include "nlpgmmRecognition.h"
#include <math.h>

#define LOG2PI	1.83787706640935f


CyINT16 nlpgmmRecognition( FeatureSeq *pFeaSeq, NlpGmmSet *pSet )
{
	CyINT16 i;
	CyFLOAT maxScore = -100000;
	CyINT16 maxID = 0xFF;

	for (i=0; i<pSet->wordNum; i++)
	{
		CyFLOAT score = nlpgmmEval(pFeaSeq, &pSet->Words[i]);
		//CyFLOAT score = nlpgmmEval(pFeaSeq, pSet->Words+i);   //for speed
		
		if (score>maxScore)
		{
			maxScore = score;
			maxID = pSet->Words[i].ID;
		}
	}

	return maxID;
}


CyFLOAT nlpgmmEval(FeatureSeq *pFeaSeq, NlpGmmItem *pItem)
{
	CyINT16 i, j;
	CyFLOAT score = 0;
	
	for (i=1; i<=NLP_N; i++)  // loop for state
	{
		for (j=pFeaSeq->iNlpParam[i-1]; 
		     j<pFeaSeq->iNlpParam[i]; j++)  // loop for features in state i
		{
			score += gmmEval(pFeaSeq->feature[j], pItem->nlpgmmParam[i-1]);
		}
	}

	return (pItem->fScore = score);
}


CyFLOAT gmmEval(FVector vec, Gmm gmmParam)
{
	CyINT16 i;
	CyDOUBLE logScore = 0;   // ����Ҳ��ҪҪ˫���ȸ����������������

	for (i=0; i<GAUSSIAN_NUM; i++)
	{
		//logScore += gaussComponentEval(vec, gmmParam+i);   // for speed
		logScore += gaussComponentEval(vec, &gmmParam[i]);
	}

	// ��ȡ�����󣬲���������������ʹ��FLOAT���洢�����Է���ֵ����Ϊfloat
	//return CyLOG(logScore+EPS);
	return (CyFLOAT)CyLOG(logScore);
}


CyDOUBLE gaussComponentEval(FVector vec, MixElem *pMixElem)
{
	// �����Ƶ�������22ҳ����
	// ע������ķ������ͣ���Ҫ��˫���ȸ����������������
	CyINT16 i;
	CyFLOAT prob = 0;

	// (x-mu)*(x-mu)T
	for (i=0; i<FEATURE_DIM; i++)
	{
		CyFLOAT tmp = vec[i] - pMixElem->gpdf.mu[i];
		prob += tmp*tmp;
	}
	//{(x-mu)*(x-mu)T}/sigma
	prob /= (pMixElem->gpdf.sigma);
	
	prob += (LOG2PI + CyLOG(pMixElem->gpdf.sigma)) * FEATURE_DIM ;
	prob *= 0.5;
	
	return (CyDOUBLE)pMixElem->weight * CyEXP( -(CyDOUBLE)prob );
}