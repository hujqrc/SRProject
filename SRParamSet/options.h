/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��options.h                                                        */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�26/7/11                                                          */
/*----------------------------------------------------------------------------*/
/* �ļ��������Զ�����ʶ�����ò���ѡ���                                     */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#ifndef _OPINTIONS_H_
#define _OPINTIONS_H_

// The option Set for Windowing
#define WIN_HAMMING		0		//Hamming window
#define	WIN_RECT		1		//Rectangular window
#define	WIN_HANNING		2		//Hanning window

// The option Set for using delta feature
#define DELTA			0		//Delta Coefficient
#define DELTA_DELTA		1		//Delta Delta Coefficient
#define DELTA_NO		2		//Don't using DELTA

// The option Set for using Log Energy
#define LOG_ENERGY_YES	0		//Using the Log Energy
#define LOG_ENERGY_NO	1		//Not Using the Log Energy

// The option Set for Robust Features
#define ROBUST_CMS		2		//Using the (Cepstrum Mean Subtraction, Cepstrum Mean Normalization) CMS, CMN
#define ROBUST_CMVN		7		//Using the (Cepstrum Mean and Variant Normalization)
#define ROBUST_STCMVN	5		//Using the Statistical Thresholding for CMVN
#define ROBUST_NO		1
// MFCC=1;
// CMS=2;
// CMVN=3;
// MFCC_SN=4;
// STCMVN=5;
// CMVN_ALL=7;

// The option Set for Distance between two vectors
#define DIST_ABS		0		//Using the absolute distance
#define DIST_EUC		1		//Euclidean distance

// The option Set for Acoustic Modeling
#define MODEL_DTW		0
#define MODEL_VQ		1
#define MODEL_CDCPM		2
#define MODEL_HMM		3

// The option Set for Volume
#define VOLUME_AMPLITUDE 	0		// ʹ�÷���ֵ������ֵ��
#define VOLUME_ENERGY		1		// ��ʱ����
#define VOLUME_INTENSITY	2		// ��ʱǿ��

// The option Set for Buffer Recycling
#define RECYCLING_YES		1
#define RECYCLING_NO		0

#endif