#pragma once
#include"Worker.h"
#include<iostream>

using namespace std;

//经理类
class Manager:public Worker
{
public:
	//构造函数
	Manager(int id, string name, int did);

	//纯虚函数,父类的纯虚函数子类必须重写
	//显示个人信息
	virtual void ShowInfo();

	//获取岗位
	virtual string getDeptName();
};