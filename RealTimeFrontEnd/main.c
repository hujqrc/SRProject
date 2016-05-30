#include "../SRParamSet/datadef.h"
#include "common.h"
#include "vad.h"
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
// ʵʱǰ�˴���ģ����Դ���

int main()
{
	ResetVoiceBuffer(&gVoiceBuf);
	ResetFeaSeq(&gFeaSeq);
	ResetVADParam();

	puts("ʵʱǰ�˴���ģ�����:");
	printf("%4cgVoiceBuf:\n",'\0');
	printf("%8cgVoiceBuf.iSmplCounter=%d\n",'\0' , gVoiceBuf.iSmplCounter);
	printf("%8cgVoiceBuf.iSmplCursor=%d\n",'\0' , gVoiceBuf.iSmplCursor);
	printf("%8cgVoiceBuf.iFrmCounter=%d\n",'\0' , gVoiceBuf.iFrmCounter);
	printf("%8cgVoiceBuf.uVadIdxCount=%u\n",'\0' , gVoiceBuf.uVadIdxCount);
	printf("%8cgVoiceBuf.uVadIdxCursor=%d\n",'\0' , gVoiceBuf.uVadIdxCursor);
	printf("\n");

	printf("%4cgFeaSeq:\n",'\0');
	printf("%8cgVoiceBuf.dFeaCounter=%d\n",'\0' , gFeaSeq.dFeaCounter);
	printf("\n");

	printf("End!\n");



	
	return 0;
}
