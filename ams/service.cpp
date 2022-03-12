#include<stdio.h>
#include<time.h>
#include<string.h>

#include"service.h"
#include"model.h"
#include"global.h"
#include"card_file.h"
#include"card_service.h"
#include"billing_file.h"
#include"billing_service.h"
#include"money_file.h"

//��������addCardInfo
//���ܣ���ӿ���Ϣ
//������card������Ϣ�ṹ��
//����ֵ��TRUE:����ɹ���FALSE:����ʧ��
int addCardInfo(Card card)
{
	//������Ϣ���浽�ļ���
	if (saveCard(&card, CARDPATH) == TRUE)
		return TRUE;
	return FALSE;
}

//��������queryCardInfo
//���ܣ���ȷ��ѯ����Ϣ
//������pName:ָ���û��������Ҫ��ѯ�Ŀ���
//����ֵ��ָ����Ϣ�ṹ���ָ��
Card* queryCardInfo(const char* pName)
{
	Card* pCard =NULL;
	pCard = queryCard(pName);
	return pCard;
}

//��������queryCardsInfo
//���ܣ�ģ����ѯ����Ϣ
//������pName��ָ���û������Ҫ��ѯ�Ŀ���
//      pIndex��ָ��鵽�Ŀ���Ϣ������
//����ֵ��ָ����Ϣ�ṹ���ָ��
Card* queryCardsInfo(const char* pName, int* pIndex)
{
	Card* pCard = NULL;
	pCard = queryCards(pName, pIndex);
	return pCard;
}

//��������doLogon
//���ܣ������ϻ�����
//������pName���ϻ����ţ�pPwd���ϻ����룻pInfo��ָ���ϻ���Ϣ�ṹ��
//����ֵ��TRUE:�ϻ��ɹ���FALSE:�ϻ�ʧ��
int doLogon(const char* pName, const char* pPwd, LogonInfo* pInfo)
{
	Card* pCard = NULL;
	int nIndex = 0;//����Ϣ�������е����������ڸ��¿���Ϣ
	Billing billing;//�Ʒ���Ϣ

	//���ݿ��ź����룬�������л�ȡ����Ϣ�Ϳ���Ϣ�������е�����
	pCard = checkCard(pName, pPwd, &nIndex);

	//�������ϢΪ�գ���ʾû�иÿ���Ϣ���ϻ�ʧ��
	if (pCard == NULL)
		return FALSE;
	//�����״̬��Ϊ0����ʾ�ÿ������ϻ�
	if (pCard->nStatus != 0)
		return UNUSE;
	//����������Ϊ0�������ϻ�
	if (pCard->fBalance <= 0)
		return ENOUGHMONEY;

	//��������ϻ������¿���Ϣ
	pCard->nStatus = 1;//״̬Ϊ����ʹ��
	pCard->nUseCount++;//ʹ�ô�����1
	pCard->tLastTime = time(NULL);//�������ʹ��ʱ��Ϊ��ǰʱ��

	//�����ļ��еĿ���Ϣ
	if (updateCard(pCard, CARDPATH, nIndex) == FALSE)
		//���ļ�����ʧ�ܷ��أ����³ɹ��ż���������Ѽ�¼
		return FALSE;

	//������Ѽ�¼
	strcpy_s(billing.aCardName, pName);//�ϻ�����
	billing.tStart = time(NULL);//�ϻ�ʱ��
	billing.tEnd = 0;//�»�ʱ��
	billing.nStatus = 0;//����״̬
	billing.fAmount = 0;//���ѽ��
	billing.nDel = 0;//ɾ����ʶ

	//�Ƚ��Ʒ���Ϣ���浽�ļ���
	if (saveBilling(&billing, BILLINGPATH) == TRUE)
	{
		//��װ�ϻ���Ϣ
		strcpy_s(pInfo->aCardName, pName);
		pInfo->fBalance = pCard->fBalance;
		pInfo->tLogon = billing.tStart;
		return TRUE;
	}
	return FALSE;
}

//��������releaseList
//���ܣ��˳�Ӧ�ó���ʱ���ͷ������ڴ�
//������void
//����ֵ��void
void releaseList()
{
	releaseCardList();//�ͷſ���Ϣ�����ڴ�
	releaseBillingList();//�ͷżƷ���Ϣ�����ڴ�
}

//��������doSettle
//���ܣ������»�����
//������pName���»����ţ�pPwd:�»����룻pInfo��ָ���»���Ϣ�ṹ��
//����ֵ���»���Ϣֵ����ͬ��������ͬ��Ϣ
int doSettle(const char* pName, const char* pPwd, SettleInfo* pInfo)
{
	Card* pCard = NULL;
	Billing* pBilling = NULL;
	int nIndex = 0;//����Ϣ�������е�������
	int nPosition = 0;//�Ʒ���Ϣ�������е�������
	double dbAmount = 0.0;//���ѽ��
	float fBalance = 0.0;//���

	//��ѯ�ϻ���
	pCard = checkCard(pName, pPwd, &nIndex);

	//���Ϊ�գ���ʾû�иÿ���Ϣ������FALSE
	if (pCard == NULL)
	{
		printf("�޸ÿ���Ϣ�����������룡\n");
		return FALSE;
	}
	//�жϸÿ��Ƿ������ϻ���ֻ�������ϻ��Ŀ����ܽ����»�����
	if (pCard->nStatus != 1)
	{
		printf("�ÿ�δ�ϻ���\n");
		return UNUSE;
	}
	//���ݿ��ţ���ѯ�Ʒ���Ϣ
	pBilling = queryBilling(pName, &nPosition);

	//�����ѯ�Ʒ���ϢΪ�գ���ʾ�»�ʧ��
	if (pBilling == NULL)
	{
		printf("�޸ÿ���Ϣ�����������룡\n");
			return FALSE;
	}

	//�������ѽ��
	dbAmount = getAmount(pBilling->tStart);
	
	//������С�����ѽ������»�
	fBalance = pCard->fBalance - (float)dbAmount;
	if (fBalance < 0)
		return ENOUGHMONEY;

	//���¿���Ϣ
	pCard->fBalance = fBalance;//���
	pCard->nStatus = 0;//״̬
	pCard->tLastTime = time(NULL);//�ϴ�ʹ��ʱ��

	//�����ļ��еĿ���Ϣ
	if (updateCard(pCard, CARDPATH, nIndex) == 0)
		return FALSE;

	//���¼Ʒ���Ϣ
	pBilling->fAmount = (float)dbAmount;//������Ϣ
	pBilling->nStatus = 1;//״̬��������
	pBilling->tEnd = time(NULL);//�»�ʱ��

	//�����ļ��еļƷ���Ϣ
	if (updateBilling(pBilling, BILLINGPATH, nPosition) == FALSE)
		return FALSE;

	//��װ�»���Ϣ
	strcpy(pInfo->aCardName, pName);//����
	pInfo->fAmount = (float)dbAmount;//���ѽ��
	pInfo->fBalance = fBalance;//���
	pInfo->tStart = pBilling->tStart;//�ϻ�ʱ��
	pInfo->tEnd = time(NULL);//�»�ʱ��

	return TRUE;
}

//��������getAmount
//���ܣ������ϻ�ʱ�䣬�������ѽ��
//�������ϻ�ʱ��
//����ֵ:���ѽ��
double getAmount(time_t tStart)
{
	double dbAmount = 0;//���ѽ��
	int nCount = 0;//�ϻ�ʱ�䵥λ����ÿ����Ԫ15����
	int nSec = 0;//����ʱ�䣨��λ���룩
	int nMinutes = 0;//����ʱ�䣨��λ�����ӣ�
	time_t tEnd = time(NULL);//����ʱ��Ϊ��ǰʱ��

	//��������ʱ��
	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	//��������ʱ��ĵ�Ԫ��
	if (nMinutes % UNIT == 0)
		nCount = nMinutes / UNIT;//����
	else
		nCount = nMinutes / UNIT + 1;///������
	//�������ѽ��
	dbAmount = nCount * CHARGE;
	return dbAmount;
}

//��������doAddmoney
//���ܣ����г�ֵ����
//������pName����ֵ���Ŀ��ţ�pPwd����ֵ�������룻pMoney����ֵ��Ϣ
//����ֵ��int����ֵ�Ľ����TRUE:��ֵ�ɹ���FALSE:��ֵʧ��
/*int doAddMoney(const char* pName, const char* pPwd, MoneyInfo* pMoneyInfo)
{
	Card* pCard = NULL;
	int nIndex = 0;//����Ϣ�������е�������
	Money sMoney;

	//��ѯ��ֵ��
	pCard = checkCard(pName, pPwd, &nIndex);

	//�������ϢΪ�գ���ʾû�иÿ���Ϣ����ֵʧ��
	if (pCard == NULL)
	{
		printf("�޸ÿ���Ϣ�����ܳ�ֵ��\n");
		return FALSE;
	}

	//�жϸÿ��Ƿ�δʹ�û������ϻ���ֻ��δʹ�ú������ϻ��Ŀ����ܽ��г�ֵ����
	if (pCard->nStatus != 0 && pCard->nStatus != 1)
		return FALSE;
	//������Գ�ֵ�����¿���Ϣ
	pCard->fBalance += pMoneyInfo->fMoney;
	pCard->fTotalUse += pMoneyInfo->fMoney;

	//�����ļ��еĿ���Ϣ
	if (updateCard(pCard, CARDPATH, nIndex) == FALSE)
		return FALSE;

	//��װ��ֵ��Ϣ
	strcpy(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(NULL);
	sMoney.nStatus = 0;
	sMoney.fMoney = pMoneyInfo->fMoney;
	sMoney.nDel = 0;

	//����ֵ��¼���浽�ļ���
	if (saveMoney(&sMoney, MONEYPATH) == TRUE)
	{
		//��װ������ʾ�ĳ�ֵ��Ϣ
		strcpy(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fBalance = pCard->fBalance;

		return TRUE;
	}
	return FALSE;
}
*/
int doAddMoney(const char* pName, const char* pPwd, MoneyInfo* pMoneyInfo)
{
	Card* pCard = NULL;
	int nIndex = 0;			//����Ϣ�������е�������
	Money sMoney;
	//��ѯ����ֵ
	pCard = checkCard(pName, pPwd, &nIndex);

	//�������ϢΪ�գ���ʾû�иÿ���Ϣ����ֵʧ��
	if (pCard == NULL)
	{
		printf("�޸ÿ���Ϣ�����ܳ�ֵ��\n");
		return FALSE;
	}
	//�жϸÿ��Ƿ�δʹ�û������ϻ���ֻ��δʹ�ú������ϻ��Ŀ����ܽ��г�ֵ����
	if (pCard->nStatus != 0 && pCard->nStatus != 1)
	{
		return FALSE;
	}
	//������Գ�ֵ�����¿���Ϣ
	pCard->fBalance += pMoneyInfo->fMoney;
	pCard->fTotalUse += pMoneyInfo->fMoney;

	//�����ļ��еĿ���Ϣ�ļ�
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		return FALSE;
	}
	//��װ��ֵ��Ϣ
	strcpy(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(NULL);
	sMoney.nStatus = 0;
	sMoney.fMoney = pMoneyInfo->fMoney;
	sMoney.nDel = 0;

	//����ֵ��¼���浽�ļ���
	if (TRUE == saveMoney(&sMoney, MONEYPATH))
	{
		//��װ������ʾ�ĳ�ֵ��Ϣ
		strcpy(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fBalance = pCard->fBalance;

		return TRUE;
	}
	return FALSE;
}
