/******************************************************************************/
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��debug.h                                                          */
/* ������  ���Ѹ�����pfa2008@126.com                                          */
/* �������ڣ�20120511                                                         */
/*----------------------------------------------------------------------------*/
/* �ļ�������debug.h���ڵ���                                                  */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */

/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* 2011-7-26 ��demo                                                           */
/******************************************************************************/

#ifndef _DEBUG_H__
#define _SHELL_H_

#include <stdio.h>
#include "typedef.h"


#ifdef _CQUPT_DEBUG_
//�������ʱ��ʾ�м�����ע���TRACE��֧�ֻ��У�
//��Ҫ����������߼��������ú�Ӧ�ö������У���Ҫ����������������䡣
//ʹ�÷�����printf��ȫһ��
#define TRACE printf
#define __ASSERT HError
#else
#define TRACE /\
/ //Enable by define _CQUPT_DEBUG_

#define __ASSERT /\
/   //Enable by define _CQUPT_DEBUG_
#endif


#ifdef _DSP_INTERRUPT_
#define INTERRUPT interrupt
#else
#define INTERRUPT /\
/  //Enable by define _DSP_INTERRUPT_
#endif

/* From HTK */
/* EXPORT->HError: print error message on stderr*/
void HError(CyINT16 errcode, CyCHAR *message, ...);

//void __assert(BOOL bValue, CyCHAR *message, ...);

#endif