/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��wrapper.cpp                                                      */
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

#include "StdAfx.h"
#include "wrapper.h"
#include "resource.h"
#include "../SpeechCollection/SpeechCollectionDlg.h"

CSpeechCollectionDlg *pSCDlg = NULL;

// ��ʾ�����ɼ�����
//extern "C" 
DWORD WINAPI ShowSpeechCollectionFrame(LPARAM lp)
{
	if(pSCDlg==NULL)
	{
		AfxMessageBox("���������ɼ��豸δ����!");
		exit(-1);
	}
// 	pSCDlg->Create(CSpeechCollectionDlg::IDD, CWnd::FromHandle(GetDesktopWindow()));
// 	pSCDlg->ShowWindow(SW_SHOW);
 	int nResponse = pSCDlg->DoModal();
 	if(nResponse==IDOK)
 	{
 
 	}
 	else if (nResponse == IDCANCEL)
 	{
 		//delete pSCDlg;
 	}

	return 0;
}

// �����������ݲɼ�����
extern "C" CyVOID CreateSpeechCollection()
{
	if(pSCDlg == NULL)
	{
		AfxSetResourceHandle(GetModuleHandle(NULL));
// 		//TODO: code your application's behavior here.
// 		static LPCTSTR temptitle = _T("{98C1C303-2A9E-11d4-9FF5-006067718D04}");
// 		TCHAR title[512];
// 		if(GetConsoleTitle(title, sizeof(title)/sizeof(TCHAR)) == 0)
// 			return;
// 		SetConsoleTitle(temptitle);
// 		HWND wnd = FindWindow(NULL, temptitle);
// 		SetConsoleTitle(title);
// 		pSCDlg = new CSpeechCollectionDlg(CWnd::FromHandle(wnd));
		pSCDlg = new CSpeechCollectionDlg();
	}
}

// ������ʼ�������ɼ����ݴ�����
extern "C" CyVOID InitSpeechCollection( void (*SpeechDataProcessing)(CyINT16 *data, CyUINT16 length),
									    void (*FrontendReset)(),
										void (*FrontendStopSampling)())
{
	if(pSCDlg != NULL)
	{
		glfpSpeechDataProcessing = SpeechDataProcessing;
		pSCDlg->m_fpFrontendReset = FrontendReset;
		pSCDlg->m_fpFrontendStopSampling = FrontendStopSampling;
	}
	else
	{
		AfxMessageBox("Ϊ���������ɼ��豸δ���������ܽ��г�ʼ��!");
		exit(-1);
	}
}

// ����������ʼ�������ݲɼ�
extern "C" CyVOID CollectionOpen()
{
	if(pSCDlg != NULL)
	{
		pSCDlg->OnBtnBegin();
	}
	else
	{
		AfxMessageBox("�����ɼ��豸δ����������ʧ��!");
		exit(-1);
	}
}

// �ر�������ֹͣ�������ݲɼ�
extern "C" CyVOID CollectionClose()
{
	if(pSCDlg != NULL)
	{
		pSCDlg->OnBtnStop();
	}
	else
	{
		AfxMessageBox("�����ɼ��豸δ����������ִ�иò���!");
		exit(-1);
	}
}

extern "C" CyVOID ReleaseSpeechCollection()
{
	if(pSCDlg)
	{
		delete pSCDlg;
		pSCDlg = NULL;
	}
}