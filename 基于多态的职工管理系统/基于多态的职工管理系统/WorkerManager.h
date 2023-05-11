#pragma once
#include<iostream>
#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

using namespace std;

//管理类

//与用户的沟通菜单页面
//对职工增删改查的操作
//与文件的读写交互
class WorkManager
{
public:

	//构造函数
	WorkManager();

	//展示菜单
	void Show_Menu();


	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//员工数组的指针
	Worker** m_EmpArray;

	//增加职工
	void Add_Emp();

	//保存文件
	void save();

	//文件是否为空的标志
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化员工
	void Init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//判断员工是否存在，若存在，返回员工所在数组中的位置，不存在，返回-1
	int IsExist(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空文件
	void Clean_File();

	//析构函数
	~WorkManager();

};