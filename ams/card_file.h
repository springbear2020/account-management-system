#pragma once
#include"model.h"
//��������
int saveCard(const Card* pCard, const char* pPath); //������Ϣ���浽�ļ���
int readCard(Card* pCard, const char* pPath);//���ļ��ж�ȡ����Ϣ���ṹ������
Card praseCard(char* pBuf);//��һ������Ϣ�ַ������������һ�����ṹ��
int getCardCount(const char* pPath);//��ȡ����Ϣ�ļ��п���Ϣ����