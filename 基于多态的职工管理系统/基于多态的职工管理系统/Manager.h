#pragma once
#include"Worker.h"
#include<iostream>

using namespace std;

//������
class Manager:public Worker
{
public:
	//���캯��
	Manager(int id, string name, int did);

	//���麯��,����Ĵ��麯�����������д
	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ȡ��λ
	virtual string getDeptName();
};