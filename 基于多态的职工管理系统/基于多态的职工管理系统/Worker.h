#pragma once

//��ͷ�ļ�������д��������.cpp�ļ���дʵ��
#include<iostream>
#include <string>
using namespace std;

//ְ���ķ���Ϊ��Ա���������ܲ�
//������ְ������Ϊһ���ࣨWorker)�����ö�̬����ְͬ������
//ְ�������ԣ�ְ����ţ�ְ��������ְ�����ڲ��ű��
//ְ������Ϊ����λ��Ϣ��������ȡ��λ����

//ְ���������
class Worker
{
public:
	
	//���麯��,����Ĵ��麯�����������д
	//ְ������Ϊ
	//��ʾ������Ϣ
	virtual void ShowInfo() = 0;

	//��ȡ��λ
	virtual string getDeptName() = 0;

	//ְ��������
	int m_Id;						//ְ�����
	string m_Name;			//ְ������
	int m_DeptId;				//ְ�����ڲ��ű��
};