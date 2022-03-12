#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"card_service.h"
#include"model.h"
#include"global.h"
#include"card_file.h"


//Card aCard[50];//���ṹ������
//int nCount = 0;//���ṹ�������ʵ����Ϣ��
lpCardNode cardList = NULL;//����Ϣ�������ͱ���


//��������addcard
//���ܣ���ӿ���Ϣ���ṹ������
//����������Ϣ�ṹ��
//����ֵ������1����ӳɹ�������0���������
int addCard(Card crd)
{
	/*if (nCount < 50)//ע�͵�����ɾ��
	{//����δ�������һ������Ϣ
		strcpy(aCard[nCount].aName, crd.aName);
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
	}              */
	if (TRUE == saveCard(&crd, CARDPATH))
		return TRUE;
	else
		return FALSE;
}

/*
//��������queryCard
//���ܣ��ڽṹ�������в���ָ�����ŵĿ���Ϣ
//�������û������Ҫ��ѯ�Ŀ��ŵ�ַ
//����ֵ���ṹ�������в�ѯ���Ŀ���Ϣ��ַ��û���ҵ�����NULL
Card* queryCard(const char* pName)
{
	Card* pCard = NULL;
	int i;

	//����ӿ���Ϣ�ļ��ж�ȡ����Ϣʧ�ܣ��򷵻�NULL
	if (getCard() == FALSE)
		return NULL;

	//�ڽṹ�������в���ָ������
	for (i = 0; i < nCount; i++)
		if (strcmp(aCard[i].aName, pName) == 0)
		{//�ڽṹ���������ҵ������ؿ���Ϣ��ַ
			pCard = &aCard[i];
			return pCard;
		}
	//û���ҵ�������NULL
	return pCard;
}
*/

//��������querycard
//���ܣ��������в���ָ�����ŵĿ���Ϣ
//�������û������Ҫ��ѯ�Ŀ��ŵ�ַ
//����ֵ�������в�ѯ���Ŀ���Ϣ��ַ��û���ҵ�����NULL
Card* queryCard(const char* pName)
{
	Card* pCard = NULL;
	lpCardNode p;//���ڲ����е�����һ��ָ�������е�ÿ�����

	//�ӿ���Ϣ�ļ��ж�ȡ����Ϣ������ʧ�ܷ���NULL
	if (getCard() == FALSE)
		return NULL;
	//ָ������ͷ��ͷ�����ڵ���
	p = cardList;
	//�������в���ָ������
	while (p != NULL)
	{
		if (strcmp(p->data.aName, pName) == 0)
		{
			pCard = &(p->data);
				return pCard;
		}
		else
			p=p->next;
	}
	//û���ҵ�������NULL
	return pCard;
}

//��������getcard
//���ܣ��ӿ���Ϣ�ļ��У���ȡ����Ϣ�����浽�ṹ��������
//������void
//����ֵ����ȡ�ɹ�����TRUE,���򷵻�FALSE
int getCard()
{
	int i = 0;
	Card* pCard = NULL;//��ȡ����һ������Ϣ
	int nCount = 0;//ʵ�ʿ���Ϣ��
	lpCardNode node = NULL;//��ǰβ���
	lpCardNode cur = NULL;//��ӵ������еĽ��
	
	//����������Ѿ����ڵ�����
	if (cardList != NULL)
		releaseCardList();
	
	//��ʼ������
	initCardList();

	//��ȡ�ļ��п���Ϣ����
	nCount = getCardCount(CARDPATH);
	if (nCount == 0)
		return FALSE;
	else if (nCount == -1)
	{
		printf("�ļ��޷��򿪣�\n\n");
		return FALSE;
	}

	//��̬�����ڴ������������п���Ϣ���൱�ڽṹ�����飬pCard�൱��������
	pCard = (Card*)malloc(sizeof(Card) * nCount);
	if (pCard != NULL)
	{	//�������FALSE,��ʾ��ȡ����Ϣʧ��
		if (readCard(pCard, CARDPATH) == 0)
		{
			free(pCard);
			return FALSE;
		}
		//����ȡ���Ŀ���Ϣ���浽������
		for (i = 0, node = cardList; i < nCount; i++)
		{
			//Ϊ�������ڴ�
			cur = (lpCardNode)malloc(sizeof(CardNode));
			//��������ڴ�ʧ�ܣ��򷵻�
			if (cur == NULL)
			{
				free(pCard);
				return FALSE;
			}
			//��ʼ���µĿռ䣬ȫ����ֵΪ0
			memset(cur, 0, sizeof(CardNode));

			//������Ϣ���浽�����
			cur->data = pCard[i];//�ṹ��ָ�뵱������ʹ��
			cur->next = NULL;

			//�������ӵ�����β��
			node->next = cur;
			node = cur;
		}

		//�ͷ��ڴ�
		free(pCard);
		return TRUE;
	}
	return FALSE;
}
	/*
	//����ṹ���������Ѿ����ڵ�����
	memset(aCard, 0, 50 * sizeof(Card));//�������

	//��ȡ�ļ��е���Ϣ����
	nCount = getCardCount(CARDPATH);
	if (nCount == 0)
		return FALSE;
	else if (nCount == -1)
	{
		printf("�ļ��޷��򿪣�");
		return FALSE;
	}
	//�������NULL����ʾ��ȡ����Ϣʧ��
	if (readCard(aCard, CARDPATH) == 0)
		return FALSE;
	return TRUE;
	
	*/



//��������initCardList
//���ܣ���ʼ������Ϣ����
//������void
//����ֵ��int�ͣ�TRUE��ʾ�ɹ���FALSE��ʾʧ��
int initCardList()
{
	lpCardNode head = NULL;
	if (cardList == NULL)
	{
		//Ϊ����������ڴ�
		head = (lpCardNode)malloc(sizeof(CardNode));

		//�������ɹ���������ָ��
		if (head != NULL)
		{
			head->next = NULL;
			cardList = head;
			return TRUE;
		}		
	}
	return FALSE;
}

//��������releaseCardList
//���ܣ��ͷſ���Ϣ����
//������void
//����ֵ��void
void releaseCardList()
{
	lpCardNode cur = cardList;
	lpCardNode next = NULL;

	while (cur != NULL)
	{
		next = cur->next;//�ͷ�cur���ǰ����next�������ĺ�̽��
		free(cur);//�ͷ�cur���
		cur = next;
	}
	cardList = NULL;
}

//��������queryCards
//���ܣ��ڿ���Ϣ�����У�ģ����ѯ���������п���Ϣ
//������pName��ָ���û������Ҫ��ѯ�Ŀ��ţ�pIndex��ָ��鵽�Ŀ���Ϣ������
//����ֵ��ָ����Ϣ�ṹ��ָ��
Card* queryCards(const char* pName, int* pIndex)
{
	lpCardNode node = NULL;
	Card* pCard = NULL;//�����ѯ���ķ��������Ŀ���Ϣ

	//�ӿ���Ϣ�ļ��ж�ȡ����Ϣ������ʧ���򷵻�NULL
	if (getCard() == FALSE)
		return NULL;

	//���ȷ���һ��Card��С�ڴ�ռ�
	pCard = (Card*)malloc(sizeof(Card));
	if (pCard == NULL)
		return NULL;

	//�������ͷ���ָ�����һ����㿪ʼ����
	node = cardList->next;

	//�����������Ϊ�ձ�ʾ��������β��
	while (node != NULL)
	{
		//�ж��ڱ������Ľ�㿨���У������Ƿ����pName�ַ���
		if (strstr(node->data.aName, pName) != NULL)
		{
			//����У��򱣴����е�����
			pCard[*pIndex] = node->data;
			(*pIndex)++;

			//����Ϊָ������ڴ棬�������е�����
			pCard = (Card*)realloc(pCard, ((*pIndex) + 1) * sizeof(Card));
		}

		//�Ƶ��������һ�����
		node = node->next;
	}
	return pCard;
}