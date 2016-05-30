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

#ifndef _NLP_GMM_EVALUATION_
#define _NLP_GMM_EVALUATION_

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/nlpgmm.h"


/*****************************************************************
����ԭ�ͣ�NlpGmmItem *nlpgmmRecognition(FeatureSeq *pFeaSeq, NlpGmmSet *pSet);
�������ܣ���ģ�ͼ��϶Ը�����������֣������ط�ֵ������
���������
FeatureSeq *pFeaSeq -- ��������������
NlpGmmSet *pSet -- ģ�ͼ�
���������
��������ֵ (CyINT16) ָ���ֵ����ID
*****************************************************************/
CyINT16 nlpgmmRecognition(FeatureSeq *pFeaSeq, NlpGmmSet *pSet);


/*****************************************************************
����ԭ�ͣ�CyFLOAT nlpgmmEval(FeatureSeq *pFeaSeq, NlpGmmItem *pItem);
�������ܣ���ģ�ͼ��϶Ը������������
���������
FeatureSeq *pFeaSeq -- ��������������
NlpGmmItem *pItem -- ĳ��ģ��
���������
���ص÷�ֵ (CyFLOAT Score) 
*****************************************************************/
CyFLOAT nlpgmmEval(FeatureSeq *pFeaSeq, NlpGmmItem *pItem);


/*****************************************************************
����ԭ�ͣ�CyFLOAT gmmEval(FVector vec, Gmm gmmParam);
�������ܣ�һ֡������һ��GMMģ���ϵĶ�����Ȼ��
���������
FVector vec -- ������������
Gmm gmmParam -- ��˹���ģ��
���������
���ض�����Ȼ�� (CyFLOAT Score) 
*****************************************************************/
CyFLOAT gmmEval(FVector vec, Gmm gmmParam);


/*****************************************************************
����ԭ�ͣ�CyDOUBLE gaussComponentEval(FVector vec, MixElem *pMixElem);
�������ܣ�һ֡������һ����˹����(Gaussian Component)�ϵļ�Ȩ��ֵ
���������
FVector vec -- ������������
MixElem *pMixElem -- ��˹���ģ��
���������
���ص÷�ֵ (CyDOUBLE Score) 
ע�⣺����ķ���ֵ������˫���ȸ����������������
*****************************************************************/
CyDOUBLE gaussComponentEval(FVector vec, MixElem *pMixElem);


#endif