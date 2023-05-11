#include"Employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = id;
}

//实现具体功能 不要virtual 
//显示个人信息
 void Employee::ShowInfo()
{
	 cout << "职工编号：" << this->m_Id
		 << "\t职工姓名：" << this->m_Name
		 << "\t岗位： " << this->getDeptName()
		 << "\t岗位职责：完成经理交给你的任务" << endl;
}

//获取岗位
 string  Employee::getDeptName()
 {
	 return string("员工");
 }