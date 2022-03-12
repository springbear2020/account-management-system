#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include"menu.h"
#include"model.h"
#include"card_service.h"
#include"global.h"
#include"tool.h"

//��������outputMenu
//���ܣ����ϵͳ�˵�
//������void
//����ֵ��void
void outputMenu()
{   //���ϵͳ�˵�
	printf("------�Ʒ�ϵͳ�˵�------\n");
	printf("*                      *\n");
	printf("*       1.��ӿ�       *\n");
	printf("*       2.��ѯ��       *\n");
	printf("*       3.�ϻ�         *\n");
	printf("*       4.�»�         *\n");
	printf("*       5.��ֵ         *\n");
	printf("*       6.�˷�         *\n");
	printf("*       7.��ѯͳ��     *\n");
	printf("*       8.ע����       *\n");
	printf("*       0.�˳�         *\n");
	printf("------------------------\n\n");
}

//��������add
//���ܣ�����û���Ϣ�����ṹ�����������Ļ��ʾ
//������void
//����ֵ��void
void add()
{
	Card card;
	char name[30];//��ʱ���������û���
	char pwd[20];//��ʱ������������
	struct tm* endTime;//��ʱ��Ž�ֹʱ��
	struct tm* startTime;//��ʱ��ſ���ʱ��

	printf("�����뿨��(����Ϊ1-18):");
	scanf("%s", &name);
	if (getSize(name) >= 18) //�ж�����Ŀ��ų����Ƿ����Ҫ��
		printf("����Ŀ��ų��ȳ������ֵ");
	//�ж�����Ŀ����Ƿ����
	if (queryCard(name) != NULL)
	{
		printf("����Ŀ����Ѵ��ڣ����������룡\n\n");
		return;
	}
	strcpy(card.aName, name);//������Ŀ��ű��浽���ṹ�������

	printf("����������(����Ϊ1-8):");
	scanf("%s", &pwd);
	if (getSize(pwd) >= 8)//�ж���������볤���Ƿ����Ҫ��
		printf("��������볤�ȳ������ֵ��");
	strcpy(card.aPwd, pwd);//����������뱣�浽���ṹ����

	printf("�����뿪����RMB):");
	scanf("%f", &card.fBalance);

	card.fTotalUse = card.fBalance;//��ӿ�ʱ���ۼƽ����ڿ������
	card.nDel = 0;//ɾ����ʶ
	card.nStatus = 0;//��״̬
	card.nUseCount = 0;//ʹ�ô���
	//����ʱ�䣬��ֹʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ��
	//time��NULL����ȡ��ǰ����ʱ�䣨����ʱ�䣩��1970-01-01 00;00��00 �����ڵ�����
	card.tStart = card.tEnd = card.tLastTime = time(NULL);

	//���ݿ���ʱ�䣬�����ֹʱ�䣬ÿ�ſ�����Ч��Ϊһ��
	startTime = localtime(&card.tStart);//������ʱ��ת��Ϊ�ֽ�ʱ��
	endTime = localtime(&card.tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	card.tEnd = mktime(endTime);//���ֽ�ʱ��ת��Ϊ����ʱ��

	//�����ӿ�����Ϣ
	printf("\n");
	printf("----------------��ӵĿ���Ϣ����----------------\n");
	printf("\t����\t����\t״̬\t�������\n");
	printf("\t%s\t%s\t%s\t%.2f\n", card.aName, card.aPwd, card.nStatus, card.fBalance);

	//����Ϣ��ӵ��ṹ��������
	if (FALSE == addCard(card))
		printf("----******------��ӿ���Ϣʧ�ܣ�----******------\n\n");
	else
		printf("----******------��ӿ���Ϣ�ɹ���----******------\n\n");
}

//��������getSize
//���ܣ������ַ��������ַ�����
//�������ַ�������
//����ֵ���ַ�����
int getSize(const char* pString)
{
	int nSize = 0;

	//�����ַ������ַ�����
	while (*(pString + nSize) != '\0')
		nSize++;

	//�����ַ�����
	return nSize;
}

//��������query
//���ܣ���������Ŀ��ţ����ã���ѯ�Ƿ��иÿ����еĻ�������ÿ���Ϣ
//������void
//����ֵ��void
void query()
{
	Card* pCard = NULL;
	char name[18];//���Ҫ��ѯ���û���
	char aLastTime[30];//���ָ����ʽ�ַ�����ʱ��
	int icha = 0;
	int nIndex = 0;//����ѯ������Ϣ����
	int i;

//	struct tm* timeinfo;//��ʱ��Ŵ�time_tת��������tm�ṹʱ��

	printf("������Ҫ��ѯ�Ŀ���(����Ϊ1~18):");
	scanf("%s", &name);
	printf("\n");

	printf("||1.��ȷ��ѯ||2.ģ����ѯ||(����1��2)��");
	scanf("%d", &icha);
	printf("\n");

	if (icha == 1)//ѡ��ȷ��ѯ
		pCard = queryCard(name);
	else//Ĭ������ѡ��ģ����ѯ
		pCard = queryCards(name, &nIndex);

	//�ӽṹ�������в��ҿ���Ϣ
	//pCard = queryCard(name);

	//���pCardΪNULL����ʾû�иÿ���Ϣ
	if (pCard == NULL)
	{
		printf("----******------û�иÿ���Ϣ��------******----\n");
		printf("\n");
	}
	else
	{
		//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ��-��-�� ʱ����
		//timeinfo = localtime(&(pCard->tLastTime));//time_t����ʱ��ת����tm�ṹʱ��
		//strftime(aLastTime, 20,"%Y-%m-%d %H:%M" , timeinfo);//tm�ṹʱ�����Ϊָ����ʽ�ַ���		

		if (icha == 1)//��ȷ��ѯ������
		{
			//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ��-��-�� ʱ:��
			timeToString(pCard->tLastTime, aLastTime);
			
			printf("-------------******-------------��ѯ���Ŀ���Ϣ����-------------******-------------\n");
			//������ı�ͷ
			printf("\t����\t״̬\t���\t�ۼƽ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");

			//����鵽�Ŀ���Ϣ
			printf("\t%s\t%s\t%.2f\t%.2f\t\t%d\t\t%s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse, pCard->nUseCount, aLastTime);
			printf("----------------------------------------------------------------------------------\n");
			printf("\n");
		}
		else
		{
			for (i = 0; i < nIndex; i++)
			{
				//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ��-��-�� ʱ:��
				timeToString(pCard[i].tLastTime,aLastTime);//�ṹ��ָ�뵱������ʹ��

				printf("-------------******-------------��ѯ���Ŀ���Ϣ����-------------******-------------\n");
				//������ı�ͷ
				printf("\t����\t״̬\t���\t�ۼƽ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");

				//����鵽�Ŀ���Ϣ
				printf("\t%s\t%s\t%.2f\t%.2f\t\t%d\t\t%s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse, pCard->nUseCount, aLastTime);
				printf("----------------------------------------------------------------------------------\n");
				printf("\n");
			}
			//�ͷŶ�̬������ڴ�
			free(pCard);
		}
		pCard = NULL;
	}
}

//��������exitApp
//���ܣ��˳�Ӧ�ó���
//������void
//����ֵ��void
void exitApp()
{
	releaseCardList();
}