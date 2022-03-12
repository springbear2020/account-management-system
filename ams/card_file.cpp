#include<iostream>
#include<fstream>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"card_file.h"
#include"model.h"
#include"global.h"
#include"tool.h"

using namespace std;

//��������saveCard
//���ܣ�������Ϣ���浽�ļ���
//������pCard:ָ��Ҫ����Ŀ���Ϣ�ṹ�壻 pPath:������ļ�·��
//����ֵ������ɹ�����TRUE,ʧ�ܷ���FALSE
/*int saveCard(const Card* pCard, const char* pPath)
{
	//��׷�ӷ�ʽ�������Ʒ�ʽд��
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		cout << "�ļ��޷���ȷ�򿪣�����д�뿨��Ϣ��" << endl;
		ofile.close();
		return FALSE;
	}

	//������Ϣ���浽�ļ�
	ofile.write((const char*)pCard, sizeof(Card));

	//�ر��ļ�
	ofile.close();

	cout << endl;
	cout << "----******-----����Ϣ�����ļ��ɹ���----******-----" << endl << endl;
	return TRUE;
}
*/
int saveCard(const Card* pCard, const char* pPath)
{
	//��׷�ӷ�ʽ�������Ʒ�ʽд��
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣�����д�뿨��Ϣ!\n");
		ofile.close();
		return FALSE;
	}
	//������Ϣ���浽�ļ���
	ofile.write((const char*)pCard, sizeof(Card));

	//�ر��ļ�
	ofile.close();
	printf("----*****-----����Ϣ�ɹ������ļ�!-----*****----\n");
	return TRUE;

}


//��������readCard
//���ܣ����ļ��ж�ȡ����Ϣ���ṹ������
//������pCard��ָ��ṹ�����飻pPath���ļ�·��
//����ֵ����ȷ��ȡ����TRUE,���򷵻�FALSE
/*int readCard(Card* pCard, const char* pPath)
{
	int nIndex = 0;//����Ϣ����

	//�Զ����Ʒ�ʽ��ȡ
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{
		cout << "�ļ��޷���ȷ�򿪣����ܶ�ȡ����Ϣ��" << endl;
		ifile.close();
		return FALSE;
	}
	else//�����ļ�����ȡ�ļ�����
	{
		while (!ifile.eof())
		{
			if (ifile.read((char*)(&pCard[nIndex]), sizeof(Card)))
				;
			else
				nIndex++;
		}
		//�ر��ļ�
		ifile.close();
		return TRUE;
	}
}
*/
int readCard(Card* pCard, const char* pPath)
{
	int nIndex = 0;

	//�Զ����Ʒ�ʽ��ȡ
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣����ܶ�ȡ����Ϣ!\n");
		ifile.close();
		return FALSE;
	}
	else
	{
		//�����ļ���ȡ�ļ�����
		while (!ifile.eof())
		{
			if (!ifile.read((char*)(&pCard[nIndex]), sizeof(Card)))
				;
			else
			{
				nIndex++;
			}

		}
		//�ر��ļ�
		ifile.close();
		return TRUE;
	}
}


//��������getCardCount
//���ܣ���ȡ����Ϣ�ļ��п���Ϣ����
//�������ļ�·��
//����ֵ������Ϣ����
/*int getCardCount(const char* pPath)
{
	int nCount = 0;//����Ϣ����
	Card* pCard = (Card*)malloc(sizeof(Card));
	//�Զ����Ʒ�ʽ��ȡ
	ifstream ifile(pPath, ios_base::in | ios_base::binary);

	if (!ifile.is_open())
	{
		cout << "�ļ��޷���ȷ�򿪣�����ͳ�ƿ���Ϣ������" << endl;
		ifile.close();
		return -1;//-1��ʾ�ļ�û����ȷ��
	}
	else//�����ļ�
	{
		while (!ifile.eof())
		{
			if (ifile.read((char*)pCard, sizeof(Card)))
				;
			else
				nCount++;
		}
		//�ر��ļ�
		ifile.close();
		free(pCard);
		return nCount;
	}
}
*/
int getCardCount(const char* pPath)
{
	int nCount = 0;        //����Ϣ����
	Card* pCard = (Card*)malloc(sizeof(Card));
	//�Զ����Ʒ�ʽ��ȡ
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣�����ͳ�ƿ���Ϣ����!\n");
		ifile.close();
		return -1;   //-1��ʾ�ļ�û����ȷ��
	}
	else
	{	//�����ļ�
		while (!ifile.eof())
		{
			if (!ifile.read((char*)pCard, sizeof(Card)))
				;
			else
			{
				nCount++;
			}
		}
		//�ر��ļ�
		ifile.close();
		free(pCard);
		return nCount;
	}
}

//��������updateCard
//���ܣ����¿���Ϣ�ļ��ж�Ӧ��һ������Ϣ
//������pCard�����º�Ŀ����� pPath������Ϣ�ļ���·��
//      nIndex:��Ҫ���µĿ���Ϣ���ļ��еĿ����
//����ֵ��TRUE:���³ɹ���FALSE:����ʧ��
/*int updateCard(const Card* pCard, const char* pPath, int nIndex)
{
	int nCount = 0;//�ļ��е�ǰ�����
	long lPosition = 0;//�ļ����λ��
	Card pcBuf;

	//�Զ�дģʽ��������ģʽ���ļ������ʧ�ܣ�����FALSE
	fstream iofile(pPath, ios_base::out | ios_base::in | ios_base::binary);
	if (!iofile.is_open());
	{
		cout << "�ļ��޷���ȷ�򿪣����ܸ��¿���Ϣ��" << endl;
		iofile.close();
		return FALSE;
	}

	//�����ļ�����ȡ����Ϣ���ļ��е�λ��
	while ((!iofile.eof()) && (nCount < nIndex))
	{
		if (iofile.read((char*)(&pcBuf), sizeof(Card)))
				;
		else
			//��ȡ�ļ���ʶλ�ã����һ�����ҵ�λ��
			lPosition = iofile.tellg();
		nCount++;
	}

	//�Ƶ��ļ���ʶλ��
	//ע��ָ��ʽ�ڸ���������Ϣ֮����֮ǰ������
	//����õ��Ķ�дָ������һ����Ϣ��ͷ��Ҫ�Ƶ�������Ϣ��ͷ��
	iofile.seekp(lPosition - sizeof(Card), ios::beg);
	//����������Ϣ���ļ�
	iofile.write((const char*)(pCard), sizeof(Card));
	cout << "----*******-----����Ϣ���µ��ļ��ɹ���" << endl << endl;
	//�ر��ļ�
	iofile.close();
	return TRUE;
}
*/
int updateCard(const Card* pCard, const char* pPath, int nIndex)
{
	int nCount = 0;
	long lPosition = 0;
	Card pbBuf;

	//�Զ�дģʽ��������ģʽ���ļ������ʧ�ܷ���FALSE
	fstream iofile(pPath, ios_base::out | ios_base::in | ios_base::binary);
	if (!iofile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣����ܸ��¿���Ϣ��\n");
		iofile.close();
		return FALSE;
	}
	//�����ļ�����ȡ������Ϣ���ļ��е�λ��
	while ((!iofile.eof()) && (nCount < nIndex))
	{
		if (!iofile.read((char*)(&pbBuf), sizeof(Card)))
			;
		else
		{
			//��ȡ�ļ���ʶλ�ã����һ���ҵ���λ��
			lPosition = (long)iofile.tellg();
		}
		nCount++;
	}
	//�ƶ����ļ���ʶλ��
	//ע��ָ�����ڸ�������֮����֮ǰ������
	//����õ��Ķ�дָ������һ����Ϣ��ͷ��Ҫ�ƶ���������Ϣ��ͷ��
	iofile.seekp((__int64)lPosition - sizeof(Card), ios_base::beg);
	//����������Ϣ���ļ�
	iofile.write((const char*)(pCard), sizeof(Card));
	printf("----*****----����Ϣ���µ��ļ��ɹ���----*****----\n");
	//�ر��ļ�
	iofile.close();
	return TRUE;
}
