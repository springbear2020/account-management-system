#include<iostream>
#include<fstream>

#include"model.h"
#include"global.h"

using namespace std;

//��������saveMoney
//���ܣ�����ֵ�˷���Ϣ���浽�ļ���
//������pMoney����ֵ�˷ѽṹ�壻  pPath����ֵ�˷���Ϣ����·��
//����ֵ��TRUE:����ɹ���FALSE:����ʧ��
/*int saveMoney(const Money* pMoney, const char* pPath)
{
	//��׷�ӷ�ʽ�������Ʒ�ʽд��
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		cout << "�ļ��޷���ȷ�򿪣�����д���ֵ�˷���Ϣ��" << endl;
		ofile.close();
		return FALSE;
	}

	//����ֵ�˷���Ϣ���浽�ļ���
	ofile.write((const char*)pMoney, sizeof(Money));
	//�ر��ļ�
	ofile.close();
	cout << endl;
	cout << "-----******-----��ֵ�˷���Ϣ�ɹ������ļ���-----******-----" << endl << endl;
	return TRUE;
}
*/
int saveMoney(const Money* pMoney, const char* pPath)
{
	//��׷�ӷ�ʽ�������Ʒ�ʽд��
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣�����д���ֵ�˷���Ϣ!\n");
		ofile.close();
		return FALSE;
	}
	//����ֵ�˷���Ϣ���浽�ļ���
	ofile.write((const char*)pMoney, sizeof(Money));

	//�ر��ļ�
	ofile.close();
	printf("----*****-----��ֵ�˷���Ϣ�ɹ������ļ�!-----*****----\n");
	return TRUE;
}