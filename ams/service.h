#pragma once
#include"model.h"
//��������
int addCardInfo(Card card);//��ӿ���Ϣ
Card* queryCardInfo(const char* pName);//��ȷ��ѯ����Ϣ
Card* queryCardsInfo(const char* pName, int* pIndex);//ģ����ѯ����Ϣ
int doLogon(const char* pName, const char* pPwd, LogonInfo* pInfo);//�����ϻ�����
void releaseList();//�˳�Ӧ�ó���ʱ���ͷ������ڴ�
int doSettle(const char* pName, const char* pPwd, SettleInfo* pInfo);//�����»�����
double getAmount(time_t tStart);//�����ϻ�ʱ�䣬�������ѽ��