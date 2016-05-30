// SRControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SRControl.h"
#include "wrapper.h"
#include "resource.h"
#include "../SpeechCollection/SpeechCollectionDlg.h"

// C����ͷ�ļ�
extern "C"
{
#include "../RealTimeFrontEnd/realtimefrontend.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/nlpgmm.h"
#include "../LoadNlpGmm/LoadNlpGmm.h"
#include "../NlpGmmModelEval/nlpgmmRecognition.h"
#include "../NonLinerPartition/nlp.h"
#include "../SRParamSet/asrconfig.h"
#include "../RealTimeFrontEnd/common.h"
};


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

// void DataProcess(short* data, int length)
// {
// 	//AfxMessageBox("�����е�������");
// 	for(int i=0;i<length;i++)
// 	{
// 		printf("[%04d]: %8d\n", i, data[i]);
// 	}
// }

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		printf("Fatal Error: MFC initialization failed");
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		NlpGmmSet* pModelSet; 

		CreateSpeechCollection();  // ���������ɼ��豸
		//CollectionOpen();                // ���豸�������ݲɼ�

		InitSpeechCollection( Frontend_VoiceDataProcessing, Frontend_Reset, Frontend_StopSampling );  // ��ʼ�����ݴ���ص�����
		Frontend_Setup(CollectionOpen, CollectionClose); // ǰ������
		Frontend_Reset();

		AfxBeginThread((AFX_THREADPROC)ShowSpeechCollectionFrame, NULL);  //��һ���µ��߳���ʾ�ɼ�����
		//ReleaseSpeechCollection();    //�ͷŲɼ��豸

		pModelSet = LoadModelSetTest();

		while(1)
		{
			int i;
			CyINT16 RecogID;
			//printf("���������ֿ�ʼ��0�˳���1-9�������������޼�⣩: ");
			//scanf("%d", &i);
			//if(i==0) exit(0);
			

			Frontend_GetFeaSeq(&gFeaSeq);

			NonLinerPartition(&gFeaSeq, NLP_N);

			RecogID = nlpgmmRecognition(&gFeaSeq, pModelSet);

			printf("<RESULT = %s>\n", pModelSet->Words[RecogID].Label);

			for (i=0; i<pModelSet->wordNum; i++)
			{
				printf("    <%d. %s Score = %4.8f>\n", 
					pModelSet->Words[i].ID,
					pModelSet->Words[i].Label,
					pModelSet->Words[i].fScore);
			}

			Sleep(2000);
		}
	}

	return nRetCode;
}


