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

#ifndef _DATADEF_H_
#define _DATADEF_H_

#include "asrconfig.h"
#include "typedef.h"

//////////////////////////////////////////////////////////////////////////
/*
struct _VoiceBuffer
{
	//CyINT16	iData[MAX_SAMPLE_NUM];      //�������ݻ�������ȫ���ⲿ����
	CyFLOAT	fData[MAX_SAMPLE_NUM];      //�������ݻ�������ȫ���ⲿ����
	CyINT16	iSmplCounter;				//���������
	CyINT16	iSmplCursor;				//�����α꣬���ڼ�¼��ǰ���ڲ���֡����ʼλ��				
	
	CyINT16	iFrmCounter;				//����֡����
	//����֡������ȫ���ⲿ���������ں��ڽ�����������Ϊ�������Լ�����ƽ�������Ĺ���
	CyFLOAT	fFrmEnergyBuf[MAX_FRAMES];
	CyBOOL	bSmplFinished;				// �����������Ƿ�������������Ƿ����
	
	CyBOOL		bVadFinished;					//��ʾ�˵����Ƿ����
	CyUINT16	uVadIdxBuf[MAX_FRAMES];			//�洢��Ч����֡�������
	CyUINT16	uVadIdxCount;					//���������ݼ���	
	CyUINT16	uVadIdxCursor;					//ָʾ�Ѵ�����Ч����֡��λ�ã�����ʵʱ������ȡ
};*/
struct _VoiceBuffer;
typedef struct _VoiceBuffer VoiceBuffer;

// ��������ʸ��
struct _featureSequence;
typedef struct _featureSequence FeatureSeq; 


//////////////////////////////////////////////////////////////////////////
// VoiceBuffer data structure and its operators
struct _VoiceBuffer
{
	//CyINT16	iData[MAX_SAMPLE_NUM];      //�������ݻ�������ȫ���ⲿ����
	CyFLOAT	fData[MAX_SAMPLE_NUM];      //�������ݻ�������ȫ���ⲿ����
	CyINT16	iSmplCounter;				//���������
	CyINT16	iSmplCursor;				//�����α꣬���ڼ�¼��ǰ���ڲ���֡����ʼλ��				
	
	CyINT16	iFrmCounter;				//����֡����
	//����֡������ȫ���ⲿ���������ں��ڽ�����������Ϊ�������Լ�����ƽ�������Ĺ���
	CyFLOAT	fFrmEnergyBuf[MAX_FRAMES];
	CyBOOL	bSmplFinished;				// �����������Ƿ�������������Ƿ����
	
	CyBOOL		bVadFinished;					//��ʾ�˵����Ƿ����
	CyUINT16	uVadIdxBuf[MAX_FRAMES];			//�洢��Ч����֡�������
	CyUINT16	uVadIdxCount;					//���������ݼ���	
	CyUINT16	uVadIdxCursor;					//ָʾ�Ѵ�����Ч����֡��λ�ã�����ʵʱ������ȡ
};

// ��������������
CyVOID ResetVoiceBuffer(VoiceBuffer* vbuff);


/* Featuer Vector and Feature Sequence data structure define and their operators
Feature Vector ��������
0..FEATURE_BASE: Static MFCC
FEATURE_BASE..2*FEATURE_BASE: Delta Features
2*FEATURE_BASE..3*FEATURE_BASE: Delta Delta Features
*/
typedef CyFLOAT		FVector[FEATURE_DIM]; 

//������������
struct _featureSequence
{
	FVector			feature[MAX_FRAMES];		//����������������
	CyINT16			dFeaCounter;				//������������
	
	// �����ԷֶεĽ������NLP+1�����ʾ�� 
	// ��i�ε���ʼ����iNlpParam[i]����ֹ����iNlpParam[i+1]���������õ㣩
	// ���������
	CyINT16			iNlpParam[NLP_N+1];			
};

//��ʼ����������������
CyVOID ResetFeaSeq(FeatureSeq* pFeaSeq);

// ������������a��b�ľ���
CyFLOAT VecDistance(FVector a, FVector b);

// �����������п���
//void CopyFeaSeq(FeatureSeq* pFeaSeqDest, FeatureSeq* pFeaSeqSrc);

//��������
//void CopyVector(FVector dest, FVector src);

#endif

