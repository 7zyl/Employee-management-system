#pragma once

#include"Worker.h"
#include<iostream>
using namespace std;

//Ա����
class Employee:public Worker
{
public:

	//���캯��,��ʼ��
	Employee(int id, string name, int did);

	//��д���麯��
	//��ʾ������Ϣ
	virtual void ShowInfo();

	//��ȡ��λ
	virtual string getDeptName();

};