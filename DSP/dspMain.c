#include "fft.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/asrconfig.h"
#include <math.h>
#include <stdio.h>


int main()   
{  
	int i;
	CyFLOAT data[FRAME_SIZE];
	
	InitFFT(FRAME_SIZE);
	for(i=0;i<FRAME_SIZE;i++)                           //���ṹ�帳ֵ
	{
		data[i]=(CyFLOAT)i/FRAME_SIZE;
	}
	
	RealFFT(data, FRAME_SIZE);                                        //���п��ٸ���Ҷ�任
	
	for(i=0;i<FRAME_SIZE/2;i++)                           //��任������ģֵ�����븴����ʵ������
	{
		printf("[%3d]  %3.14f\n", i+1, sqrt(data[i]));
	}

	return 0;
}
