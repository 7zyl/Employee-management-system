#include "WorkerManager.h"

//构造函数类内声明，类外定义
WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.文件不存在的情况
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->m_EmpNum = 0;			//初始化记录人数
		this->m_EmpArray = NULL;	//初始化数组指针
		this->m_FileIsEmpty = true;	//初始化文件是否为空
		ifs.close();
		return;
	}

	//2.文件存在 但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->m_EmpNum = 0;			//初始化记录人数
		this->m_EmpArray = NULL;	//初始化数组指针
		this->m_FileIsEmpty = true;	//初始化文件是否为空
		ifs.close();
		return;
	}

	//3.文件存在 且记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间,根据文件中职工的人数开辟
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数组，存到数组中
	this->Init_Emp();
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << " 职工编号："<<this->m_EmpArray[i]->m_Id
			<<"姓名："<< this->m_EmpArray[i]->m_Name
			<< "部门编号："<<this->m_EmpArray[i]->m_DeptId << endl;
	}*/

	////初始化人数
	//this->m_EmpNum = 0;
	////初始化数组指针
	//this->m_EmpArray = NULL;
}

WorkManager::~WorkManager()
{
	//在析构函数里释放堆区开放的空间
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

//展示菜单
void WorkManager::Show_Menu()
{
	cout << "***********************************" << endl;
	cout << "******欢迎使用职工管理系统！*******" << endl;
	cout << "**********0.退出管理程序***********" << endl;
	cout << "**********1.增加职工信息***********" << endl;
	cout << "**********2.显示职工信息***********" << endl;
	cout << "**********3.删除离职员工***********" << endl;
	cout << "**********4.修改职工信息***********" << endl;
	cout << "**********5.查找职工信息***********" << endl;
	cout << "**********6.按照编号排序***********" << endl;
	cout << "**********7.清空所有文档***********" << endl;
	cout << "***********************************" << endl;
	cout << endl;
}

//退出功能
void WorkManager:: ExitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);			//退出程序
}

//增加职工
void WorkManager::Add_Emp()
{
	cout << "请输入要增加的职工个数：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;		//新的人数=原来人数+要添加的人数

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];//创建了一个指针数组保存内容newSpace[]中保存的是worker*

		//将原空间下的内容存放到新空间下(如果原空间有内容)
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)	//把原来的数据拷贝到新空间下
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int id = 0;
			string name;
			int dselect;
			cout << "请输入第" << i + 1 << "个新职工的编号:" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的姓名:" << endl;
			cin >> name;
			cout << "请选择该职工的岗位:" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.总裁" << endl;
			cin >> dselect;

			//根据用户不同的选择，创建出不同的对象
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

			//把worker指针插到数组里面，为了下次使用
			newSpace[this->m_EmpNum + i] = worker;		//原本的数据+i，记录worker指针位置

		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入数据有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件
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

//记录文件中职工人数
int WorkManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);			//打开文件 读

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

//初始化员工
void WorkManager::Init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;		//数组中索引的位置
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = NULL;			//创建一个具体的职工
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

		//把员工存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	system("pause");
	system("cls");
}


//判断员工是否存在，若存在，返回员工所在数组中的位置，不存在，返回-1
int WorkManager::IsExist(int id)
{
	int index = -1;		//假设先不存在
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

//删除职工
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工号" << endl;
		int id = 0;
		cin >> id;
		//判断职工是否存在
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			//更新职工人数
			this->m_EmpNum--;

			//if (this->m_EmpNum == 0)
			//{
			//	this->m_FileIsEmpty = true;
			//}

			//更新到文件中
			this->save();

			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");
}

//修改职工
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到该职工
			//先删除指定空间
			delete this->m_EmpArray[ret];

			int newid = 0;
			string newname = "";
			int dselect = 0;
			
			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newid;
			cout << "请输入新姓名：" << endl;
			cin >> newname;
			cout << "请输入岗位：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.总裁" << endl;
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

			//更新数据到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功！"  << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，该职工不存在" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请选择查找方式：" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;
		int dselect = 0;
		cin >> dselect;
		if (dselect == 1)
		{
			//按职工编号查找
			cout << "请输入想要查找的职工编号：" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功，该职工信息如下：" << endl;
				this->m_EmpArray[ret]->ShowInfo();
			}
			else
			{
				cout << "查找失败，该职工不存在" << endl;
			}
		}
		else if (dselect == 2)
		{
			//按职工姓名查找
			cout << "请输入想要查找的职工姓名：" << endl;
			string name;
			cin >> name;

			//查找到的标志
			bool flag = false;

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_Id << "号的信息如下：" << endl;
					flag = true;
					this->m_EmpArray[i]->ShowInfo();
				}

			}
			if (flag == false)
			{
				cout << "查找失败，该职工不存在" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

//职工排序
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1.按职工编号升序排列" << endl;
		cout << "2.按职工编号降序排列" << endl;
		int dselect = 0;
		cin >> dselect;
		
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (dselect == 1)				//升序
				{
					//选择排序
					if (this->m_EmpArray[MinOrMax]->m_Id> this->m_EmpArray[j]->m_Id)
					{
						MinOrMax = j;
					}
				}
				else                                   //降序
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
		cout << "排序成功，排序后结果为：" << endl;
		this->save();
		this->Show_Emp();
	}
}

//清空文件
void WorkManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建，相当于清空
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;

	}
	system("pause");
	system("cls");
}
