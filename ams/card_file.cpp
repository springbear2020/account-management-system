#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>

/*#include<stdio.h>
#include<string.h>
#include<stdlib.h>*/

#include"model.h"
#include"global.h"
#include"tool.h"
#include"card_file.h"

using namespace std;

//��������saveCard
//���ܣ�������Ϣ���浽�ļ���
//������pCard:ָ��Ҫ����Ŀ���Ϣ�ṹ�壻 pPath:������ļ�·��
//����ֵ������ɹ�����TRUE,ʧ�ܷ���FALSE
extern int saveCard(const Card* pCard, const char* pPath)
{
	char aStart[30];//���ת�����ʱ���ַ���
	char aEnd[30];//���ת�����ʱ���ַ���
	char aLast[30];//���ת�����ʱ���ַ���

	timeToString(pCard->tStart, aStart);
	timeToString(pCard->tEnd, aEnd);
	timeToString(pCard->tLastTime, aLast);

	ofstream ofile(pPath, ios_base::out | ios_base::app);//��׷�ӷ�ʽд��
	if (!ofile.is_open())
	{
		cerr << "�ļ��޷������򿪣�����д�뿨��Ϣ��" << endl;
		exit(EXIT_FAILURE);
	}
	//���ļ���д����Ϣ
	ofile << pCard->aName << "##" << pCard->aPwd << "##" << pCard->nStatus << "##";
	ofile << aStart << "##" << aEnd << "##" << pCard->fTotalUse << "##" << aLast << "##";
	ofile << pCard->nUseCount << "##" << pCard->fBalance << "##" << pCard->nDel << endl;
	ofile.close();

	cout << endl;
	cout << "----******-----����Ϣ�ɹ������ļ���------******----" << endl << endl;
	return TRUE;
}
