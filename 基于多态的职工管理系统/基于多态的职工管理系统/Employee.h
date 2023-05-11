#pragma once

#include"Worker.h"
#include<iostream>
using namespace std;

//员工类
class Employee:public Worker
{
public:

	//构造函数,初始化
	Employee(int id, string name, int did);

	//重写纯虚函数
	//显示个人信息
	virtual void ShowInfo();

	//获取岗位
	virtual string getDeptName();

};