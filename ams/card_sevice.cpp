#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#include"card_sevice.h"
#include"model.h"
#include"global.h"

Card aCard[50];//���ṹ������
int nCount = 0;//���ṹ�������ʵ����Ϣ��

//��������addcard
//���ܣ���ӿ���Ϣ���ṹ������
//����������Ϣ�ṹ��
//����ֵ������1����ӳɹ�������0���������
int addCard(Card crd)
{
	if (nCount < 50)
	{//����δ�������һ������Ϣ
		strcpy(aCard[nCount].aName, crd. aName);
		strcpy(aCard[nCount].aPwd, crd.aPwd);
		aCard[nCount].nStatus = crd.nStatus;
		aCard[nCount].tStart = crd.tStart;
		aCard[nCount].tEnd = crd.tEnd;
		aCard[nCount].fTotalUse = crd.fTotalUse;
		aCard[nCount].tLastTime = crd.tLastTime;
		aCard[nCount].nUseCount = crd.nUseCount;
		aCard[nCount].fBalance = crd.fBalance;
		aCard[nCount].nDel = crd.nDel;

		nCount++;//��������1
		return TRUE;
	}
	else
	{
		printf("����������������ӣ�");
		return FALSE;
	}
}

//��������queryCard
//���ܣ��ڽṹ�������в���ָ�����ŵĿ���Ϣ
//�������û������Ҫ��ѯ�Ŀ��ŵ�ַ
//����ֵ���ṹ�������в�ѯ���Ŀ���Ϣ��ַ��û���ҵ�����NULL
Card* queryCard(const char* pName)
{
	Card* pCard = NULL;
	int i;
	for(i=0;i<nCount;i++)
		if (strcmp(aCard[i].aName, pName) == 0)
		{//�ڽṹ���������ҵ������ؿ���Ϣ��ַ
			pCard = &aCard[i];
			return pCard;
		}
	//û���ҵ�������NULL
	return pCard;
}
