/******************************************************************************/

/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��CyDebug.h                                                        */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�20120529                                                         */
/*----------------------------------------------------------------------------*/
/* DSP -- ����Ҷ�任                                                          */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */

/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/CyDebug.h"
#include "../SRParamSet/typedef.h"
#include "fft.h"
#include <math.h>
#include <stdlib.h>

#define FFT_SIZE  FRAME_SIZE             //���帵��Ҷ�任�ĵ���

static CyINT16 lfftSize;

//��������:
//lTableCos:cos(2*pi*x/N);
//lTableSin:-sin(2*pi*x/N);
//����piΪ����:3.141592;N:����Ҷ�任�ĵ���;x:0~N/2-1;  
static CyFLOAT lTableSin[FFT_SIZE/2+1];   //�������ұ�Ĵ�ſռ�
static CyFLOAT lTableCos[FFT_SIZE/2+1];   //�������ұ�Ĵ�ſռ�

/*******************************************************************
����ԭ�ͣ�struct CyComplex ComplexMulti(struct CyComplex b1,struct CyComplex b2)  
�������ܣ��������������г˷�����
��������������������嶨��ĸ���a,z2
���������a��b�ĳ˻��������������ʽ���
*******************************************************************/
static CyComplex ComplexMulti(CyComplex z1, CyComplex z2);


CyVOID InitFFT(CyINT16 fftsize)                     
{
	CyINT16 i;
	lfftSize = fftsize;

	if( fftsize!=FFT_SIZE )
	{
		CyTRACE("FFT.c InitFFT(), Size of FFT is not match!\n");
		exit(-1);
	}

	//��������:
	//lTableCos:cos(2*pi*x/N);
	//lTableSin:-sin(2*pi*x/N);
	//����piΪ����:3.141592;N:����Ҷ�任�ĵ���;x:0~N/2-1;
	for(i=0; i<=fftsize/2; i++)
	{
// 		*(lTableCos+i) =  cos( _2PI*i/fftsize );
// 		*(lTableSin+i) = -sin( _2PI*i/fftsize );
		*(lTableCos+i) =  cos( _PI/(CyFLOAT)i );
		*(lTableSin+i) = -sin( _PI/(CyFLOAT)i );
	}
}

CyVOID FFT(CyComplex *z, CyINT16 N)
{
	CyINT16 f,m,nv2,nm1,i,k,l,j=0;
	CyComplex u,w,t;
	
	nv2 = N/2;                  //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
	nm1 = N-1;  
	for(i=0;i<nm1;i++)        
	{
		if(i<j)                    //���i<j,�����б�ַ
		{
			t=z[j];           
			z[j]=z[i];
			z[i]=t;
		}
		k=nv2;                    //��j����һ����λ��
		while(k<=j)               //���k<=j,��ʾj�����λΪ1   
		{           
			j=j-k;                 //�����λ���0
			k=k/2;                 //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
		}
		j=j+k;                   //��0��Ϊ1
	}
	
	{
		CyINT16 le,lei,ip;                            //FFT����ˣ�ʹ�õ����������FFT����
		f=N;
		for(l=1;(f=f/2)!=1;l++)                  //����l��ֵ����������μ���
			;        // N=2**l;
		for(m=1;m<=l;m++)                         // ���Ƶ��νἶ��
		{                                        //m��ʾ��m�����Σ�lΪ���μ�����l=log��2��N
			le=1<<m;                            //le���ν���룬����m�����εĵ��ν����le��
			lei=le/2;                               //ͬһ���ν��вμ����������ľ���
			u.real=1.0;                             //uΪ���ν�����ϵ������ʼֵΪ1
			u.imag=0.0;
			//u = {1.0f, 0.0f};
			//w.real=cos(_PI/lei);                  //�����ò������sinֵ��cosֵ
			//w.imag=-sin(_PI/lei);
			w.real=lTableCos[lei];                  //�����ò������sinֵ��cosֵ
			w.imag=lTableSin[lei];
			for(j=0;j<=lei-1;j++)                  //���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
			{
				for(i=j;i<N;i=i+le)           //����ͬһ���ν����㣬������ϵ����ͬ���ν�
				{
					ip=i+lei;                          //i��ip�ֱ��ʾ�μӵ�������������ڵ�
					t=ComplexMulti(z[ip],u);                   //�������㣬�����ʽ
					z[ip].real=z[i].real-t.real;
					z[ip].imag=z[i].imag-t.imag;
					z[i].real=z[i].real+t.real;
					z[i].imag=z[i].imag+t.imag;
				}
				u=ComplexMulti(u,w);                          //�ı�ϵ����������һ����������
			}
		}
	}
}


CyComplex ComplexMulti(CyComplex z1, CyComplex z2)      
{
	CyComplex res;
	res.real=z1.real*z2.real-z1.imag*z2.imag;
	res.imag=z1.real*z2.imag+z1.imag*z2.real;
	return res;
}


CyVOID RealFFT(CyFLOAT *data, CyINT16 N)
{
	CyComplex fftData[FFT_SIZE];
	CyINT16 i;

	// Step 1: ת���ɸ��������鲿Ϊ0
	for (i=0; i<N; i++)
	{
		fftData[i].real = data[i];
		fftData[i].imag = 0.0f;
	}

	// Step 2: ��������Ҷ�任
	FFT(fftData, N);

	// Step 3: ��������ֵ
	for(i=0; i<N/2; i++)
	{
		data[i] = fftData[i].real*fftData[i].real+fftData[i].imag*fftData[i].imag;
	}
}