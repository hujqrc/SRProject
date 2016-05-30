/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��asrconfig.h                                                      */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�26/7/11                                                          */
/*----------------------------------------------------------------------------*/
/* �ļ��������Զ�����ʶ��������ã����ݲ�ͬ���������ɿɲü��Ĵ���             */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#ifndef _ASRCONFIG_H_
#define _ASRCONFIG_H_

#include "options.h"


// Parameter for wave data
//#define 

/************************************************************************/
/* Parameters for Frame Block                                           */
/************************************************************************/
#define FRAME_SIZE		256			//Frame Size
#define	OVERLAP			0			//Frame overlap
#define FRAME_SHIFT		256		    //Frame shift = FrameSize - Overlap

#if ((FRAME_SIZE-OVERLAP) != FRAME_SHIFT)
#error "(FRAME_SIZE-OVERLAP) != FRAME_SHIFT";
#endif

/************************************************************************/
/*  Parameter for wave                                                  */
/************************************************************************/
#define SAMPLE_RATE 8000              //������


/************************************************************************/
/*  Parameter for wave buffer                                           */
/************************************************************************/
#define MAX_FRAMES		125			//����֡������
#define MAX_SAMPLE_NUM	32000		//��������=FRAME_SHIFT*MAX_FRAMES+OVERLAP

#if ((FRAME_SHIFT*MAX_FRAMES+OVERLAP) != MAX_SAMPLE_NUM)
#error "(FRAME_SHIFT*MAX_FRAMES+OVERLAP) != MAX_SAMPLE_NUM"
#endif


/************************************************************************/
/* Parameters for MFCC feature extraction                               */
/************************************************************************/
#define PRE_EM_COEF		0.95f		//Ԥ����ϵ��
#define WIN_OPT			WIN_HAMMING	//The option of Windowing (options.h)			
#define TBF_NUM			23			//Number of triangular band-pass filters
#define CEPS_NUM		12			//Dimension of cepstrum


/************************************************************************/
/* Parameters for Delta features Type                                   */
/************************************************************************/
#define DELTA_OPT		DELTA		//Delta Coefficients (options.h)
#define DELTA_WIN		2


/************************************************************************/
/* Parameters for Logarithmic Energy option                             */
/************************************************************************/
#define LOG_ENERGY_OPT	LOG_ENERGY_NO	//Log Energy (options.h)


/************************************************************************/
/* Parameter for dimension of the output feature                        */
/************************************************************************/
#if (DELTA_OPT == DELTA)
#if LOG_ENERGY_OPT == LOG_ENERGY_NO
#define FEATURE_DIM	24		// CEPS_NUM*2
#else
#define FEATURE_DIM	26		// (CEPS_NUM+1)*2
#endif
#elif (DELTA_OPT == DELTA_DELTA)
#if (LOG_ENERGY_OPT == LOG_ENERGY_NO)
#define FEATURE_DIM	36		// CEPS_NUM*3
#else
#define FEATURE_DIM	39		// (CEPS_NUM+1)*3
#endif
#else
#if (LOG_ENERGY_OPT == LOG_ENERGY_NO)
#define FEATURE_DIM	12		// CEPS_NUM
#else
#define FEATURE_DIM	13		// (CEPS_NUM+1)
#endif
#endif

#if (LOG_ENERGY_OPT == LOG_ENERGY_NO)
#define FEATURE_BASE	12  // CEPS_NUM
#else
#define FEATURE_BASE	13  // (CEPS_NUM+1)
#endif


/************************************************************************/
/* Parameters for Robust feature process                                */
/************************************************************************/
#define ROBUST_OPT		ROBUST_CMVN	//Robust option
#define ROBUST_MAX_FRAMES	10  //���������е�֡��С��ROBUST_MAX_FRAMESʱ��ʹ��Ĭ�Ͼ�ֵ�ͷ���
//#define ROBUST_MEAN         {0.0f}  // Ĭ�Ͼ�ֵ    
//#define ROBUST_STD          {1.0f}  // Ĭ�ϱ�׼��


// Parameter for distance of two feature vectors
#define DIST_OPT		DIST_EUC


// Parameter for Acoustic Modeling
#define MODEL_OPT		MODEL_DTW


// Parameter for Voice Activity Detection
#define VAD_NOISE_FRAME		10	// ���ڼ���ƽ��������֡��	
#define VAD_MAX_SEGMENT		5	//�����д��ڵ����ֶ���
#define VAD_MAX_PRENUM		5	/* ����Ϊ����5֡��������ֵ����Ϊ��Ч����������Ϊ���������������� */
#define VAD_MIN_PRENUM		2	/* ���Ѽ����Ч������ǰ���£������� */
#define VAD_MAX_STOP		15	/* ��������STOP״̬������ʱפ��֡���ȳ���15������Ϊ��������ֹ */


// Parameter for Word Information
#define MAX_CMDWORD		20
#define MAX_VERWORD		4


// Parameter for Volume (which is used for VAD)
#define VOLUME_OPT		VOLUME_INTENSITY


// Parameter for Buffer Recycling
#define BUFFER_RECYCLING_OPT	RECYCLING_YES


// Parameter for Non-Linear Partition and Gaussian Mixture Model
#define NLP_N			4  // �����Էֶο���
#define GAUSSIAN_NUM		7  // ��˹���ģ�͵Ļ����


#endif
