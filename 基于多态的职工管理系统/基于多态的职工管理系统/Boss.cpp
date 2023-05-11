#include"Boss.h"

Boss::Boss(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

//纯虚函数,父类的纯虚函数子类必须重写
//显示个人信息
void Boss::ShowInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位： " << this->getDeptName()
		<< "\t岗位职责：管理公司的所有事务" << endl;
}

//获取岗位
string Boss::getDeptName()
{
	return string("总裁");
}