#pragma once
#include<iostream>
#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

using namespace std;

//������

//���û��Ĺ�ͨ�˵�ҳ��
//��ְ����ɾ�Ĳ�Ĳ���
//���ļ��Ķ�д����
class WorkManager
{
public:

	//���캯��
	WorkManager();

	//չʾ�˵�
	void Show_Menu();


	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//Ա�������ָ��
	Worker** m_EmpArray;

	//����ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ļ��Ƿ�Ϊ�յı�־
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void Init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�Ա���Ƿ���ڣ������ڣ�����Ա�����������е�λ�ã������ڣ�����-1
	int IsExist(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//��������
	~WorkManager();

};