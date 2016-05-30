#include <stdlib.h>
#include <stdio.h>
#include "typedef.h"
#include "asrconfig.h"
#include "CyDebug.h"

int main()
{
	CyINT16 iParamCount = 0;

	puts("Speech Recognition Parameter Set:");
	
	iParamCount++;
	printf("\n%4d. Parameters for Frame Block: \n", iParamCount);
	printf("%8c ֡��: FRAME_SIZE=%d\n", '\0', FRAME_SIZE);
	printf("%8c ֡���ص�: OVERLAP=%d\n", '\0', OVERLAP);
	printf("%8c ֡��: FRAME_SHIFT=FRAME_SIZE-OVERLAP=%d\n", '\0', FRAME_SHIFT);
	
	iParamCount++;
	printf("\n%4d. Parameter for wave buffer: \n", iParamCount);
	printf("%8c MAX_FRAMES=%d\n", '\0', MAX_FRAMES);
	printf("%8c MAX_SAMPLE_NUM=FRAME_SHIFT*MAX_FRAMES+OVERLAP=%d\n", '\0', MAX_SAMPLE_NUM);
	
	iParamCount++;
	printf("\n%4d. Parameters for MFCC feature extraction: \n", iParamCount);
	printf("%8c Ԥ��ǿϵ��: PRE_EM_COEF=%3.3f\n", '\0', PRE_EM_COEF);
	printf("%8c ������: WIN_OPT=%d (See options.h)\n", '\0', WIN_OPT);
	printf("%8c �����˲�������: TBF_NUM=%d\n", '\0', TBF_NUM);
	printf("%8c ������������ά��: CEPS_NUM=%d\n", '\0', CEPS_NUM);


	iParamCount++;
	printf("\n%4d. Parameters for Delta features Type: \n", iParamCount);
	printf("%8c ��̬��������: DELTA_OPT=%d (See options.h)\n", '\0', DELTA_OPT);
	printf("%8c ��̬�������뾶: DELTA_WIN=%d\n", '\0', DELTA_WIN);

	iParamCount++;
	printf("\n%4d. Parameters for Logarithmic Energy option: \n", iParamCount);
	printf("%8c ��������ѡ��: LOG_ENERGY_OPT=%d (See options.h)\n", '\0', LOG_ENERGY_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for dimension of the output feature: \n", iParamCount);
	printf("%8c �����������ά���Ļ���: FEATURE_BASE=%d\n", '\0', FEATURE_BASE);
	printf("%8c �������������ά��: FEATURE_DIM=%d\n", '\0', FEATURE_DIM);

	iParamCount++;
	printf("\n%4d. Parameters for Robust feature process: \n", iParamCount);
	printf("%8c ³������������ѡ��: ROBUST_OPT=%d (See options.h)\n", '\0', ROBUST_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for distance of two feature vectors: \n", iParamCount);
	printf("%8c �����������ѡ��: DIST_OPT=%d (See options.h)\n", '\0', DIST_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for Acoustic Modeling: \n", iParamCount);
	printf("%8c ��ѧ����ģ��ѡ��: MODEL_OPT=%d (See options.h)\n", '\0', MODEL_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for Voice Activity Detection: \n", iParamCount);
	printf("%8c �����д��ڵ����ֶ���: VAD_MAX_SEGMENT=%d\n", '\0', VAD_MAX_SEGMENT);
	printf("%8c δ��⵽����ʱ����Ч��������С����: VAD_MAX_PRENUM=%d\n", '\0', VAD_MAX_PRENUM);
	printf("%8c ��⵽����ʱ����Ч���������ٳ���: VAD_MIN_PRENUM=%d\n", '\0', VAD_MIN_PRENUM);
	printf("%8c ��������STOP״̬���פ��֡��: VAD_MAX_STOP=%d\n", '\0', VAD_MAX_STOP);

	iParamCount++;
	printf("\n%4d. Parameter for Word Information: \n", iParamCount);
	printf("%8c ���������: MAX_CMDWORD=%d\n", '\0', MAX_CMDWORD);
	printf("%8c ��֤������: MAX_VERWORD=%d\n", '\0', MAX_CMDWORD);

	iParamCount++;
	printf("\n%4d. Parameter for Volume (which is used for VAD): \n", iParamCount);
	printf("%8c ����ѡ��: VOLUME_OPT=%d (See options.h) \n", '\0', VOLUME_OPT);

	
	
	printf("\nEnd!\n");

	CyTRACE("CyTRACE Test: ERROR_TEST_CODE: %d\n", 0xFF);
}