/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��NlpGmmModel.h                                                    */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�2012.06.03                                                       */
/*----------------------------------------------------------------------------*/
/* �ļ�������NLP+��˹���ģ��                                                 */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* 2012-7-26 ��demo                                                           */
/******************************************************************************/

#ifndef _NLP_GMM_MODEL_H_
#define _NLP_GMM_MODEL_H_

#include "asrconfig.h"
#include "typedef.h"
#include "datadef.h"

typedef struct _GaussPDF
{
	FVector		mu;		/* mean vector */
	CyFLOAT		sigma;	/* covariance matrix or vector */
} GaussPDF;


typedef struct _MixElement
{
	GaussPDF	gpdf;	 /* mixture pdf */
	CyFLOAT		weight;	 /* mixture weight */	
} MixElem;   /* 1 of these per mixture per stream */


// The definition of Gaussian mixture model
typedef MixElem Gmm[GAUSSIAN_NUM];

// The definition of Nonlinear Partition and Gmm
typedef Gmm		NlpGmm[NLP_N];


#define MAX_LABEL		10  // ��־����󳤶�
#define MAX_CMDDATA		8	// ���ݱ�������

// �����Էֶεĸ�˹���ģ��
typedef struct _NLP_GMM
{
	CyINT16		ID;	// ģ�ͱ��
	CyCHAR		Label[MAX_LABEL];	//��־
	CyBYTE		cmdData[MAX_CMDDATA];	//ÿ���ʶ���Ӧ����Ӧ�����������������

	//Gmm		nlpgmmParam[NLP_N];	// �����Էֶ�ģ�Ͳ���
	NlpGmm		nlpgmmParam;
	CyFLOAT     fScore;		// ������ĵ÷�
} NlpGmmItem;    // NLP+GMM item of a word. 


typedef struct _wordModel
{
	NlpGmmItem		Words[MAX_CMDWORD];
	CyINT16			wordNum;
} NlpGmmSet;    // NLP+GMM ģ�ͼ�

#endif