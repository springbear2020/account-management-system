#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<time.h>

#include"tool.h"

//��������timeToString
//���ܣ���time_t����ת��Ϊ�ַ������ַ�����ʽΪ����-��-�� ʱ���֡�
//������time_t t����Ҫת����ʱ�䣬char* pBuf:ת��֮����ַ���
//����ֵ��void
void timeToString(time_t t, char* pBuf)
{
	struct tm* timeinfo;

	timeinfo = localtime(&t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);
}

//��������stringToTime
//���ܣ�����ʽΪ����-��-�� ʱ���֡����ַ���ת��Ϊtime_t����ʱ��
//������char *pTime:����-��-�� ʱ���֡���ʽ���ַ���
//����ֵ��time_t:ת�����ʱ�����ͣ���1970����ʱ�������
time_t stringToTime(char* pTime)
{
	struct tm tml;
	time_t time1;

	sscanf(pTime, "%d-%d-%d %d:%d", &tml.tm_year, &tml.tm_mon, &tml.tm_mday, &tml.tm_hour, &tml.tm_min);

	tml.tm_year -= 1900;//��ݴ�1900�꿪ʼ
	tml.tm_mon -= 1;//�·�Ϊ0~11
	tml.tm_sec = 0;
	tml.tm_isdst = -1;

	time1 = mktime(&tml);

	return time1;
}