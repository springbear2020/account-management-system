#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"billing_service.h"
#include"model.h"//�����������Ͷ���ͷ�ļ�
#include"global.h"  //����ȫ�ֶ���ͷ�ļ�
#include"billing_file.h"

lpBillingNode billingList = NULL;//�Ʒ���Ϣ����

//��������addBilling
//���ܣ��ϻ�ʱ���������Ϣ���ļ�
//������pName:�ϻ����ţ�pBilling:ָ��������Ϣ�ṹ��
//����ֵ��TRUE:����ɹ���FALSE:����ʧ��
int addBilling(const char* pName, Billing* pBilling)
{
	//��������Ϣд��ṹ��
	strcpy_s(pBilling->aCardName, pName);//�ϻ�����
	pBilling->tStart = time(NULL);//�ϻ�ʱ��
	pBilling->tEnd = 0;//�»�ʱ��
	pBilling->fAmount = 0;//���ѽ��
	pBilling->nStatus = 0;//����״̬��0-δ���㣬1-�Ѿ�����
	pBilling->nDel = 0;//ɾ����ʶ��0-δɾ����1-��ɾ��

	//������Ϣ�ṹ��д���ļ�
	if (saveBilling(pBilling, BILLINGPATH) == FALSE)
		return FALSE;
	return TRUE;
}

//��������initBillingList
//���ܣ���ʼ���Ʒ���Ϣ����
//������void
//����ֵ��void
void initBillingList()
{
	lpBillingNode head = NULL;
	if (billingList == NULL)
	{
		head = (lpBillingNode)malloc(sizeof(BillingNode));
		head->next = NULL;
		billingList = head;
	}
}

//��������releaseBillingList
//���ܣ��ͷżƷ���Ϣ����
//������void
//����ֵ��void
void releaseBillingList()
{
	lpBillingNode cur = billingList;
	lpBillingNode next = NULL;
	//��������
	while (cur != NULL)
	{
		next = cur->next;//����ڴ��ͷ�ǰ��next��������
		free(cur);//�ͷŽ���ڴ�
		cur = next;
	}
	billingList = NULL;
}

//��������getBilling
//���ܣ��ӼƷ���Ϣ�ļ��У���ȡ�Ʒ���Ϣ���浽������
//������void
//����ֵ��TRUE:��ȡ��Ϣ�ɹ���FALSE:��ȡ��Ϣʧ��
int getBilling()
{
	int nCount = 0;//�Ʒ���Ϣ����
	Billing* pBilling = NULL;//�Ʒ���Ϣ
	lpBillingNode node = NULL;
	int i = 0;//ѭ������
	lpBillingNode cur = NULL;

	//�������Ϊ�գ��ͷ�����
	if (billingList != NULL)
		releaseBillingList();
	//��ʼ������
	initBillingList();

	//��ȡ�Ʒ���Ϣ����
	nCount = getBillingCount(BILLINGPATH);
	//��̬�����ڴ�
	pBilling = (Billing*)malloc(sizeof(Billing) * nCount);

	if (pBilling != NULL)
	{
		//��ȡ�Ʒ���Ϣ
		if (readBilling(pBilling, BILLINGPATH) == FALSE)
		{
			free(pBilling);
			return FALSE;
		}
		//���Ʒ���Ϣ���浽������
		for (i = 0, node = billingList; i < nCount; i++)
		{
			//Ϊ��ǰ�������ڴ�
			cur = (lpBillingNode)malloc(sizeof(BillingNode));
			//�������ʧ�ܣ����ڷ���FALSEǰ����Ҫ�ͷ�pBilling���ڴ�
			if (cur == NULL)
			{
				free(pBilling);
				return FALSE;
			}
			//��ʼ���µĿռ䣬ȫ����ֵΪ0
			memset(cur, 0, sizeof(BillingNode));
			//��������ӵ������
			cur->data = pBilling[i];
			cur->next = NULL;
			//�������ӵ�������
			node->next = cur;
			node = cur;
		}
		free(pBilling);
		return TRUE;
	}
	return FALSE;
}

//��������queryBilling
//����:�ڼƷ���Ϣ�����У���ѯ��Ӧ���ļƷ���Ϣ������ȡ���������е�������
//������pName��Ҫ��ѯ�ļƷ���Ϣ�Ŀ���
//      pIndex����ѯ���ļƷ���Ϣ�������е�������
//����ֵ����ѯ���ļƷ���Ϣָ��
Billing* queryBilling(const char* pName, int* pIndex)
{
	lpBillingNode node = NULL;
	int nIndex = 0;

	if (getBilling() == FALSE)
		return NULL;
	//��������
	node = billingList;
	while (node != NULL)
	{
		//��ѯ��������ͬ������û�н���ļƷ���Ϣ
		if (strcmp(node->data.aCardName, pName) == 0 && node->data.nStatus == 0)
			return &node->data;
		node = node->next;
		nIndex++;
		*pIndex = nIndex;
	}
	return NULL;
}