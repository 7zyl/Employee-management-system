#include"Manager.h"

Manager::Manager(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

//���麯��,����Ĵ��麯�����������д
//��ʾ������Ϣ
void Manager::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ�� " << this->getDeptName()
		<< "\t��λְ������ܲ��·������񣬲��ַ������Ա��" << endl;
}

//��ȡ��λ
string Manager::getDeptName()
{
	return string("����");
}
