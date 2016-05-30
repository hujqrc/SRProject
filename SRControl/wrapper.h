/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��wrapper.h                                                        */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                        */
/* �������ڣ�20120510                                                         */
/*----------------------------------------------------------------------------*/
/* �ļ���������C�����ӿڷ�װC++��д�Ĳɼ�ģ��                                 */
/*----------------------------------------------------------------------------*/
/* �����б�                                                                 */

/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��Demo                                                             */
/* 2011-7-31: Author                                                          */
/*    Content                                                                 */
/******************************************************************************/

#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include "../SRParamSet/typedef.h"

// ��ʾ�����ɼ�����
//extern "C" 
DWORD WINAPI ShowSpeechCollectionFrame(LPARAM lp);

// �����������ݲɼ��豸
extern "C" CyVOID CreateSpeechCollection();

// ��ʼ�������ɼ����ݴ�����
extern "C" CyVOID InitSpeechCollection( void (*SpeechDataProcessing)(CyINT16 *data, CyUINT16 length),
									   void (*FrontendReset)(),
										void (*FrontendStopSampling)() );

// ����������ʼ�������ݲɼ�
extern "C" CyVOID CollectionOpen();

// �ر�������ֹͣ�������ݲɼ�
extern "C" CyVOID CollectionClose();

// �����˳�ʱ����Ҫ�ͷ��豸
extern "C" CyVOID ReleaseSpeechCollection();

#endif