#pragma once
#include<time.h>
typedef struct Card
{
	char aName[18];//����
	char aPwd[8];//����
	int nStatus;//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	time_t tStart;//����ʱ��
	time_t tEnd;//���Ľ�ֹʱ��
	float fTotalUse;//�ۼƽ��
	time_t tLastTime;//���ʹ��ʱ��
	int nUseCount;//ʹ�ô���
	float fBalance;//���
	int nDel;//ɾ����ʶ��0-δɾ����1-ɾ����
}Card;