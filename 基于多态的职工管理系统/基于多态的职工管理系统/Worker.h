#pragma once

//在头文件的类中写声明，在.cpp文件中写实现
#include<iostream>
#include <string>
using namespace std;

//职工的分类为：员工，经理，总裁
//将三种职工抽象为一个类（Worker)，利用多态管理不同职工种类
//职工的属性：职工编号，职工姓名，职工所在部门编号
//职工的行为：岗位信息描述，获取岗位名称

//职工抽象基类
class Worker
{
public:
	
	//纯虚函数,父类的纯虚函数子类必须重写
	//职工的行为
	//显示个人信息
	virtual void ShowInfo() = 0;

	//获取岗位
	virtual string getDeptName() = 0;

	//职工的属性
	int m_Id;						//职工编号
	string m_Name;			//职工姓名
	int m_DeptId;				//职工所在部门编号
};