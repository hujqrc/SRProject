/******************************************************************************/

/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：CyDebug.h                                                        */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：20120529                                                         */
/*----------------------------------------------------------------------------*/
/* DSP -- 傅里叶变换                                                          */
/* 使用此函数只需更改宏定义FFT_N的值即可实现点数的改变，FFT_N的               */ 
/* 应该为2的N次方，不满足此条件时应在后面补0。若使用查表法计算sin值和         */
/* cos值，应在调用FFT函数前调用create_sin_tab()函数创建正弦表                 */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/* 参考链接，对FFT实现加速                                                    */
/* http://www.katjaas.nl/realFFT/realFFT2.html                                */
/******************************************************************************/

#ifndef _DSP_FFT_H_
#define _DSP_FFT_H_

#include "../SRParamSet/typedef.h"


/******************************************************************
函数原型：CyVOID InitFFT(CyINT16 fftsize);
函数功能：初始化FFT参数
输出参数：fftsize -- 傅里叶变换长度
******************************************************************/
CyVOID InitFFT(CyINT16 fftsize);


/*****************************************************************
函数原型：CyVOID FFT(CyComplex *z, CyINT16 N);
函数功能：对输入的复数组进行N点快速傅里叶变换（FFT）
输入参数：
CyComplex *z -- 需要变换的数据 
CyINT16  N -- 长度
输出参数：
CyComplex *z -- 变换后输出参数
*****************************************************************/
CyVOID FFT(CyComplex *z, CyINT16 N);


/*****************************************************************
函数原型：CyVOID RealFFT(CyFLOAT *data, CyINT16 N);
函数功能：对输入的实数序列进行N点快速傅里叶变换（FFT）
输入参数：
CyFLOAT *data -- 需要变换的数据 
CyINT16  N -- 长度
输出参数：
CyFLOAT *data -- 返回变换后的能量谱，0~N/2-1
*****************************************************************/
CyVOID RealFFT(CyFLOAT *data, CyINT16 N);

#endif