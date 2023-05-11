#include "WorkerManager.h"

//���캯���������������ⶨ��
WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.�ļ������ڵ����
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;			//��ʼ����¼����
		this->m_EmpArray = NULL;	//��ʼ������ָ��
		this->m_FileIsEmpty = true;	//��ʼ���ļ��Ƿ�Ϊ��
		ifs.close();
		return;
	}

	//2.�ļ����� ������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;			//��ʼ����¼����
		this->m_EmpArray = NULL;	//��ʼ������ָ��
		this->m_FileIsEmpty = true;	//��ʼ���ļ��Ƿ�Ϊ��
		ifs.close();
		return;
	}

	//3.�ļ����� �Ҽ�¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�,�����ļ���ְ������������
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����飬�浽������
	this->Init_Emp();
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << " ְ����ţ�"<<this->m_EmpArray[i]->m_Id
			<<"������"<< this->m_EmpArray[i]->m_Name
			<< "���ű�ţ�"<<this->m_EmpArray[i]->m_DeptId << endl;
	}*/

	////��ʼ������
	//this->m_EmpNum = 0;
	////��ʼ������ָ��
	//this->m_EmpArray = NULL;
}

WorkManager::~WorkManager()
{
	//�������������ͷŶ������ŵĿռ�
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

//չʾ�˵�
void WorkManager::Show_Menu()
{
	cout << "***********************************" << endl;
	cout << "******��ӭʹ��ְ������ϵͳ��*******" << endl;
	cout << "**********0.�˳��������***********" << endl;
	cout << "**********1.����ְ����Ϣ***********" << endl;
	cout << "**********2.��ʾְ����Ϣ***********" << endl;
	cout << "**********3.ɾ����ְԱ��***********" << endl;
	cout << "**********4.�޸�ְ����Ϣ***********" << endl;
	cout << "**********5.����ְ����Ϣ***********" << endl;
	cout << "**********6.���ձ������***********" << endl;
	cout << "**********7.��������ĵ�***********" << endl;
	cout << "***********************************" << endl;
	cout << endl;
}

//�˳�����
void WorkManager:: ExitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);			//�˳�����
}

//����ְ��
void WorkManager::Add_Emp()
{
	cout << "������Ҫ���ӵ�ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;		//�µ�����=ԭ������+Ҫ��ӵ�����

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];//������һ��ָ�����鱣������newSpace[]�б������worker*

		//��ԭ�ռ��µ����ݴ�ŵ��¿ռ���(���ԭ�ռ�������)
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)	//��ԭ�������ݿ������¿ռ���
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++)
		{
			int id = 0;
			string name;
			int dselect;
			cout << "�������" << i + 1 << "����ְ���ı��:" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������:" << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ:" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ܲ�" << endl;
			cin >> dselect;

			//�����û���ͬ��ѡ�񣬴�������ͬ�Ķ���
			Worker* worker = NULL;

			switch (dselect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//��workerָ��嵽�������棬Ϊ���´�ʹ��
			newSpace[this->m_EmpNum + i] = worker;		//ԭ��������+i����¼workerָ��λ��

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "����������������������" << endl;
	}
	system("pause");
	system("cls");
}

//�����ļ�
void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//��¼�ļ���ְ������
int WorkManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);			//���ļ� ��

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	return num;
}

//��ʼ��Ա��
void WorkManager::Init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;		//������������λ��
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = NULL;			//����һ�������ְ��
		if (did == 1)
		{
			worker = new Employee(id, name, 1);
		}
		else if (did == 2)
		{
			worker = new Manager(id, name, 2);
		}
		else
		{
			worker = new Boss(id, name, 3);
		}

		//��Ա�������������
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//��ʾְ��
void WorkManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	system("pause");
	system("cls");
}


//�ж�Ա���Ƿ���ڣ������ڣ�����Ա�����������е�λ�ã������ڣ�����-1
int WorkManager::IsExist(int id)
{
	int index = -1;		//�����Ȳ�����
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//ɾ��ְ��
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ����" << endl;
		int id = 0;
		cin >> id;
		//�ж�ְ���Ƿ����
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			//����ְ������
			this->m_EmpNum--;

			//if (this->m_EmpNum == 0)
			//{
			//	this->m_FileIsEmpty = true;
			//}

			//���µ��ļ���
			this->save();

			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}

	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı��" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ְ��
			//��ɾ��ָ���ռ�
			delete this->m_EmpArray[ret];

			int newid = 0;
			string newname = "";
			int dselect = 0;
			
			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newid;
			cout << "��������������" << endl;
			cin >> newname;
			cout << "�������λ��" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ܲ�" << endl;
			cin >> dselect;
			
			Worker* worker = NULL;
			switch (dselect)
			{
			case 1: 
				worker = new Employee(newid, newname, dselect);
				break;
			case 2:
				worker = new Manager(newid, newname, dselect);
				break;
			case 3:
				worker = new Boss(newid, newname, dselect);
				break;
			default:
				break;
			}

			//�������ݵ�������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���"  << endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ���ְ��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;
		int dselect = 0;
		cin >> dselect;
		if (dselect == 1)
		{
			//��ְ����Ų���
			cout << "��������Ҫ���ҵ�ְ����ţ�" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->ShowInfo();
			}
			else
			{
				cout << "����ʧ�ܣ���ְ��������" << endl;
			}
		}
		else if (dselect == 2)
		{
			//��ְ����������
			cout << "��������Ҫ���ҵ�ְ��������" << endl;
			string name;
			cin >> name;

			//���ҵ��ı�־
			bool flag = false;

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" << this->m_EmpArray[i]->m_Id << "�ŵ���Ϣ���£�" << endl;
					flag = true;
					this->m_EmpArray[i]->ShowInfo();
				}

			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ���ְ��������" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//ְ������
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.��ְ�������������" << endl;
		cout << "2.��ְ����Ž�������" << endl;
		int dselect = 0;
		cin >> dselect;
		
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (dselect == 1)				//����
				{
					//ѡ������
					if (this->m_EmpArray[MinOrMax]->m_Id> this->m_EmpArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
				else                                   //����
				{
					if (this->m_EmpArray[MinOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
			}
			if (i != MinOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[MinOrMax];
				this->m_EmpArray[MinOrMax] = temp;
			}
		}
		cout << "����ɹ����������Ϊ��" << endl;
		this->save();
		this->Show_Emp();
	}
}

//����ļ�
void WorkManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´������൱�����
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;

	}
	system("pause");
	system("cls");
}
