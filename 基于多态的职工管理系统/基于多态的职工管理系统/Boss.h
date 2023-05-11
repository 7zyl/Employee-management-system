#pragma once
#include<iostream>
#include"Worker.h"
using namespace std;

//总裁类
class Boss :public Worker
{
public:

	//构造函数
	Boss(int id, string name, int did);

	//纯虚函数,父类的纯虚函数子类必须重写
	//显示个人信息
	virtual void ShowInfo();

	//获取岗位
	virtual string getDeptName();

};