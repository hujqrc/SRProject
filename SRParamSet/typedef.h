/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��typedef.h                                                        */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�2012-05-27                                                          */
/*----------------------------------------------------------------------------*/
/* �ļ�����������Ƕ��ʽƽ̨�ϵ�һЩ�����������Ͷ�����ڿ���ֲ                 */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* 2012-4-26 �����������ͼ���ǰ׺���Ѹ���                                     */
/******************************************************************************/

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

/* Unsigned integer definitions (32bit, 16bit, 8bit) follow... */
typedef unsigned int	CyUINT32;			//32λ�޷�����������
typedef unsigned short	CyUINT16;			//16λ�޷�����������
typedef unsigned char	CyUINT8;			//8λ�޷����������� 
typedef unsigned char	CyBYTE;			//�ֽ�����

/* Signed integer definitions (32bit, 16bit, 8bit) follow... */
typedef int				CyINT32;			//32λ�з�����������
typedef short			CyINT16;			//16λ�з�����������
typedef char			CyINT8;			//8λ�з�����������
typedef char			CyCHAR;			//�����ַ���
typedef void			CyVOID;				//�޷�������

typedef double			CyFLOAT;			//������
typedef double			CyDOUBLE;			//˫���ȸ�����

#define EPS				2E-16f				//��С�Ǹ���0������
#define _2PI			6.283185307179586f
#define _PI				3.141592653589793f

//typedef char	BOOL;			//���岼������
typedef enum _CyBOOL { CyFALSE=0, CyTRUE };
typedef char				CyBOOL;

#define CyNULL			((void*)0)   //����NULL

typedef struct _Complex 
{
	CyFLOAT real,imag;
} CyComplex; //����һ�������ṹ

#endif
