#pragma once
#include"model.h"
//��������
int addCard(Card crd);//��ӿ���Ϣ���ṹ������
Card* queryCard(const char* pName); //�ڽṹ�������в���ָ�����ŵĿ���Ϣ
int getCard();//�ӿ���Ϣ�ļ��У���ȡ����Ϣ�����浽�ṹ��������
int initCardList(); //��ʼ������Ϣ����
void releaseCardList();//�ͷſ���Ϣ����
Card* queryCards(const char* pName, int* pIndex);//�ڿ���Ϣ�����У�ģ����ѯ���������п���Ϣ

