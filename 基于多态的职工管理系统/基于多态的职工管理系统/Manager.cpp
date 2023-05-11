#include"Manager.h"

Manager::Manager(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

//纯虚函数,父类的纯虚函数子类必须重写
//显示个人信息
void Manager::ShowInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位： " << this->getDeptName()
		<< "\t岗位职责：完成总裁下发的任务，并分发任务给员工" << endl;
}

//获取岗位
string Manager::getDeptName()
{
	return string("经理");
}
