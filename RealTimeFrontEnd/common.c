#include "../SRParamSet/options.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/datadef.h"
#include "common.h"
#include "dspAIC.h"
#include <math.h>

// �������ݻ����������ڶ˵����������ȡ
VoiceBuffer gVoiceBuf;

// ȫ����������
FeatureSeq	gFeaSeq;

#if BUFFER_RECYCLING_OPT==RECYCLING_NO
//���һ֡������һ���������
CyFLOAT GetFrmVolume(CyFLOAT *data, CyINT16 i)
{
#if (VOLUME_OPT == VOLUME_ENERGY)
	CyFLOAT volume = data[0]*data[0];
	
	for(--i;i;i--) //ֱ����i��Ϊѭ��������������Ҫ����ı���
		volume+=data[i]*data[i];
	
	return volume;
	
#elif (VOLUME_OPT == VOLUME_AMPLITUDE)
	CyFLOAT volume = fabs(data[0]);
	
	for(--i;i;i--) //ֱ����i��Ϊѭ��������������Ҫ����ı���
		volume+=fabs(data[i]);
	
	return volume;
	
#else
	CyFLOAT volume = data[0]*data[0];
	
	for(--i;i;i--) //ֱ����i��Ϊѭ��������������Ҫ����ı���
		volume+=data[i]*data[i];
	
	return 10.0f*log10(volume);
#endif
}
#else   // BUFFER_RECYCLING_OPT = RECYCLING_YES
//���һ֡������һ���������
CyFLOAT GetFrmVolume(CyFLOAT *data, CyINT16 cursor, CyINT16 frmLength)
{
	CyFLOAT volume = 0.0f;
	CyINT16 i,j;
	for (i=0;i<frmLength;i++)
	{
		CyFLOAT sample;
		// �����������������ʵλ��
		j = (cursor+i)%MAX_SAMPLE_NUM;
		sample = *(data+j);
#if ((VOLUME_OPT == VOLUME_ENERGY) || (VOLUME_OPT == VOLUME_INTENSITY))
		volume += sample*sample;
#else (VOLUME_OPT == VOLUME_AMPLITUDE)
		volume += fabs(sample);
#endif
	}

#if (VOLUME_OPT == VOLUME_INTENSITY)
	return 10.0f*log10(volume);
#else
	return volume;
#endif
}
#endif

CyVOID StopSampling(VoiceBuffer *vbuff)
{
	vbuff->bSmplFinished = CyTRUE;
	AIC_Close();
}