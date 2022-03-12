#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include"menu.h"
#include"model.h"
#include"card_service.h"
#include"global.h"
#include"tool.h"
#include"service.h"

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
	if (queryCardInfo(name) != NULL)
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

	//����Ϣ��ӵ��ļ���
//	if (FALSE == addCard(card))
	if(addCardInfo(card)==FALSE)
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
	char name[18];        //���Ҫ��ѯ���û���
	Card* pCard = NULL;
	char aLastTime[30];//���ָ����ʽ�ַ�����ʱ��
	int icha = 0;
	int nIndex = 0;
	int i;                  //��ѯ������Ϣ����


	printf("������Ҫ��ѯ�Ŀ���(����1~18):");
	scanf("%s", name);

	printf("1.��ȷ��ѯ||2.ģ����ѯ(����1��2):");
	scanf("%d", &icha);



	if (icha == 1)
		pCard = queryCardInfo(name);
	else if (icha == 2)
		pCard = queryCardsInfo(name, &nIndex);
	else
	{
		do {
			printf("�������\n���������룺");
			scanf("%d", &icha);
		} while (icha != 1 && icha != 2);

		if (icha == 1)
			pCard = queryCard(name);
		else if (icha == 2)
			pCard = queryCards(name, &nIndex);

	}

	if (pCard == NULL)
	{
		printf("----******------û�иÿ���Ϣ��------******----\n");
		printf("\n");
	}
	else
	{
		if (icha == 1)
		{
			printf("-------------******-------------��ѯ���Ŀ���Ϣ����-------------******-------------\n");
			//������ı�ͷ
			printf("\t����\t״̬\t���\t�ۼƽ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");

			//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ����-��-�� ʱ���֡�
			timeToString(pCard->tLastTime, aLastTime);
			//����鵽�Ŀ���Ϣ
			printf("\t%s\t%d\t%.2f\t%.2f\t%10d\t\t%s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse, pCard->nUseCount, aLastTime);
			printf("----------------------------------------------------------------------------------\n");
			printf("\n");

		}
		else if (icha == 2)   //ģ����ѯ������
		{
			for (i = 0; i < nIndex; i++)
			{
				printf("-------------******-------------��ѯ���Ŀ���Ϣ����-------------******-------------\n");
				//������ı�ͷ
				printf("\t����\t״̬\t���\t�ۼƽ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");

				//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ"��-��-�� ʱ����"
				timeToString(pCard[i].tLastTime, aLastTime);   //�ṹ��ָ�뵱��������

				//�����ѯ���Ŀ���Ϣ
				printf("\t%s\t%d\t%.2f\t%.2f\t%10d\t\t%s\n", pCard[i].aName, pCard[i].nStatus, pCard[i].fBalance, pCard[i].fTotalUse, pCard[i].nUseCount, aLastTime);
				printf("----------------------------------------------------------------------------------\n");

			}
			//�ͷŶ�̬������ڴ�
			free(pCard);

		}

		else
			;
		pCard = NULL;
	}
}


//��������exitApp
//���ܣ��˳�Ӧ�ó���
//������void
//����ֵ��void
void exitApp()
{
	releaseList();
}

//��������logon
//���ܣ������ϻ�����Ϣ����ѯ��������ϻ�����Ϣ
//������void
//����ֵ��void
void logon()
{
	char aName[30] = { 0 };//�ϻ�����
	char aPwd[20] = { 0 };//�ϻ�������
//  Card* pCard = NULL;
	LogonInfo* pInfo = NULL;
	int nResult = 0;
	char aLastTime[30];//���ָ����ʽ�ַ�����ʱ��

	//��ʾ�������ϻ�����
	printf("�������ϻ��Ŀ���(����Ϊ1~18)��");
	scanf("%s", &aName);
	//�ж�����Ŀ����Ƿ����Ҫ��
	if (getSize(aName) >= 18)
	{
		printf("����Ŀ��ų��ȳ������ֵ��\n");
		return;
	}
	//��ʾ�������ϻ�����
	printf("�������ϻ�����(����Ϊ1~8):");
	scanf("%s", &aPwd);
	//�ж�����������Ƿ����Ҫ��
	if (getSize(aPwd) >= 8)
	{
		printf("��������볤�ȳ������ֵ!\n");
		return;
	}

	//��ʼ�ϻ�����ȡ�ϻ����
	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	nResult = doLogon(aName, aPwd,pInfo);
	switch (nResult)
	{
	case 0:printf("---------�ϻ�ʧ�ܣ�---------\n"); break;
	case 1:
		//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ��-��-�� ʱ:��
		timeToString(pInfo->tLogon, aLastTime);//�ṹ��ָ�뵱������ʹ��

		printf("----***-----�ϻ��Ŀ���Ϣ����-----***---\n");
		//������ı�ͷ
		printf("\t����\t���\t�ϻ�ʱ��\n");

		//����鵽�Ŀ���Ϣ
		printf("\t%s\t%.2f\t%s\n", pInfo->aCardName, pInfo->fBalance, aLastTime);
		printf("---------�ϻ��ɹ���---------\n");
		printf("\n");
		break;
	case 2:printf("---------�ÿ�����ʹ�ã�---------\n"); break;
	case 3:printf("---------���㣡---------\n"); break;
	}
	//�ͷ��ϻ���Ϣ
	free(pInfo);

}

//��������settle
//���ܣ������»�����Ϣ����ѯ��������ϻ�����Ϣ
//������void
//����ֵ��void
void settle()
{
	char aName[18] = { 0 };//����
	char aPwd[8] = { 0 };//����
	int nResult = -1;//�»����
	SettleInfo* pInfo = NULL;//�»���Ϣ
	char aStartTime[30] = { 0 };//�ϻ�ʱ��
	char aEndTime[30] = { 0 };//�»�ʱ��

	//Ϊ�»���Ϣ��̬�����ڴ�
	pInfo = (SettleInfo*)malloc(sizeof(SettleInfo));

	printf("�������»�����(����Ϊ1~18):");//������ʾ
	scanf("%s", &aName);
	printf("�������»�����(����Ϊ1~8):");//������ʾ
	scanf("%s", &aPwd);

	//�����»�
	nResult = doSettle(aName, aPwd, pInfo);

	//�����»��������ʾ��ͬ��Ϣ
	printf("\n");
	printf("------------******------------�»���Ϣ����------------******------------\n");
	
	switch (nResult)
	{
	case 0://�»�ʧ��
		printf("�»�ʧ��!\n"); break;
	case 1://�»��ɹ�
		//������ı�ͷ
		printf("\t����\t����\t���\t�ϻ�ʱ��\t�»�ʱ��\n");

		//�ϻ�ʱ��Ĭ��Ϊ�������ʹ��ʱ�䣬������ӼƷѶ���Ϣ��ʹ�üƷ�ʱ��
		//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ"��-��-�� ʱ����"
		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);
		
		//����»�����Ϣ
		printf("\t%s\t%.2f\t%.2f\t%s\t%s\n\n", pInfo->aCardName, pInfo->fAmount, pInfo->fBalance, aStartTime, aEndTime);
		printf("------------******------------�»��ɹ���------------******------------\n");
		break;
	case 2://����ʹ�û���ע��
		printf("�ÿ�δ��ʹ�ã�\n"); break;
	case 3://����
		printf("������\n"); break;
	default:
		break;
	}
	free(pInfo);
}

//��������addMoney
//���ܣ���ֵ
//������void
//����ֵ��void
/*void addMoney()
{
	char aName[18] = { 0 };//����
	char aPwd[8] = { 0 };//����
	float fAmount = 0;//��ֵ���
	MoneyInfo sMoneyInfo;//��ֵ��Ϣ

	printf("������Ҫ��ֵ�Ŀ��ţ�����Ϊ1~18��:");//������ʾ
	scanf("%s", &aName);
	printf("�������ֵ�������루����Ϊ1~8��:");//������ʾ
	scanf("%s", &aPwd);
	printf("�������ֵ��RMB����");//������ʾ
	scanf("%lf", &fAmount);

	//�����ֵ���
	sMoneyInfo.fMoney = fAmount;

	//�жϳ�ֵ�Ƿ�ɹ�
	if (doAddMoney(aName, aPwd, &sMoneyInfo) == TRUE)
	{
		//��ʾ��ֵ��Ϣ
		printf("-----***-----��ֵ��Ϣ����-----***-----\n");
		//�������ͷ
		printf("\t����\t��ֵ���\t���\n");
		//�����ֵ����Ϣ
		printf("\t%s\t%2f\t%.2f\n\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
	}
	else
		printf("------��ֵʧ�ܣ�------\n");
}
*/
void addMoney()
{
	char aName[18] = { 0 };		//����
	char aPwd[8] = { 0 };			//����
	float fAmount = 0;			//��ֵ���
	MoneyInfo sMoneyInfo;		//��ֵ����Ϣ

	printf("�������ֵ�Ŀ��ţ�����1~18����");
	scanf_s("%s", aName, 18);
	//�ж�����Ŀ����Ƿ����Ҫ��
	if (getSize(aName) >= 18)
	{
		printf("����Ŀ��ų��ȳ������ֵ��\n");
		return;
	}

	printf("�������ֵ���루����1~8����");
	scanf_s("%s", aPwd, 8);
	//�ж�����������Ƿ����Ҫ��
	if (getSize(aPwd) >= 8)
	{
		printf("��������볤�ȳ������ֵ��\n");
		return;
	}

	printf( "�������ֵ��RMB)��");
	scanf(" %lf",fAmount);

	//�����ֵ���
	sMoneyInfo.fMoney = fAmount;
	//�ж��Ƿ񱣴�ɹ�
	if (TRUE == doAddMoney(aName, aPwd, &sMoneyInfo))
	{
		//��ʾ��ֵ��Ϣ
		printf("-----***---��ֵ��Ϣ����---***-----\n");
		//������ͷ
		printf("\t����\t��ֵ���\t���\n");
		//�����ֵ����Ϣ
		printf("\t%s\t%.2f    \t%.2f\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
	}
	else
	{
		printf("-------��ֵʧ�ܣ�-------\n");
	}
}
