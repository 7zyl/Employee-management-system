#pragma once
#include<iostream>
#include"Worker.h"
using namespace std;

//�ܲ���
class Boss :public Worker
{
public:

	//���캯��
	Boss(int id, string name, int did);

	//���麯��,����Ĵ��麯�����������д
	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ȡ��λ
	virtual string getDeptName();

};