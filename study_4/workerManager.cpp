#include"workerManager.h"

WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化人数为0
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件为空的标志
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		//初始化属性
		//初始化人数为0
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件为空的标志
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，且有记录
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	//初始化属性
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//将文件的数据存到数组中
	this->init_Emp();

	//测试代码
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "职工编号：" << this->m_EmpArray[i]->m_Id
	//		<< "\t职工姓名：" << this->m_EmpArray[i]->m_Name
	//		<< "\t岗位：" << this->m_EmpArray[i]->getDeptName()
	//		<< "\t岗位职责：" << this->m_EmpArray[i]->getDeptName() << endl;
	//}
}

//获取职工人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id;
	string name;
	int dId;

	int num = 0;//记录人数
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数的标志
		num++;
	}
	ifs.close();
	
	return num;
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量" << endl;
	int addNum = 0;//保存用户的输入数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间大小=原来空间大小+用户输入的数量
		
		//开辟新空间
		Worker** newspace =  new Worker*[newSize];//开辟新空间
		
		//将原来空间中的数据，拷贝到新空间中
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			cout << "请输入第 " << i + 1 << "个新职工编号" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名" << endl;
			cin >> name;

			cout<<"请输入该职工的岗位"<<endl;
			cout<<"1.普通员工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
			cin>>dSelect;

			Worker * worker = NULL;//定义一个worker指针，指向新创建的对象
			switch (dSelect)
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
			//将创建职工的指针保存到数组里
			newspace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更新新空间
		this->m_EmpArray = newspace;

		//更新职工人数
		this->m_EmpNum = newSize;

		//更新文件不为空的标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名职工" << endl;

		//保存到文件中
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	//按任意键后，清屏返回上级目录
	system("pause");
	system("cls");
}


//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "************************************" << endl;
	cout << "***********  欢迎使用职工管理系统  ***********" << endl;
	cout << "***********  0.退出管理程序  ***********" << endl;
	cout << "***********  1.增加职工信息  ***********" << endl;
	cout << "***********  2.显示职工信息  ***********" << endl;
	cout << "***********  3.删除离职职工  ***********" << endl;
	cout << "***********  4.修改职工信息  ***********" << endl;
	cout << "***********  5.查找职工信息  ***********" << endl;
	cout << "***********  6.按照编号排序  ***********" << endl;
	cout << "***********  7.清空所有文档  ***********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	//打开文件
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件 -- 写文件

	//将每个人的数据写入文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}



//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工的成员函数
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或不存在" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键后，清屏返回上级目录
	system("pause");
	system("cls");
}


//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工编号" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//说明职工存在，并且要删除掉index处的职工
		{
			//从数组中删除元素
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录的人员个数
			//更新文件
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，查无此人" << endl;
		}
	}
	//按任意键后，清屏返回上级目录
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int id)
{
	int index = -1;

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

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"文件不存在或记录为空"<<endl;
	}
	else
	{
		cout << "请输入要修改职工的编号" << endl;
		int id = 0;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的员工
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout<<"查到： "<<id<<"号职工，请输入新职工号："<<endl;
			cin>>newId;

			cout<<"请输入新姓名："<<endl;
			cin>>newName;

			cout<<"请选择岗位："<<endl;
			cout<<"1、普通员工"<<endl;
			cout<<"2、经理"<<endl;
			cout<<"3、老板"<<endl;
			cin>>dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//更新数组到数组中
			this->m_EmpArray[ret] = worker;

			cout<<"修改成功"<<endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout<<"修改失败，查无此人"<<endl;
		}
	}
	//按任意键后，清屏返回上级目录
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"文件不存在或记录为空"<<endl;
	}
	else
	{
		cout<<"请输入查找方式："<<endl;
		cout<<"1、按职工编号查找"<<endl;
		cout<<"2、按职工姓名查找"<<endl;
		int select = 0;
		cin>>select;
		if (select == 1)
		{
			int id;
			cout<<"请输入职工编号："<<endl;
			cin>>id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout<<"查找成功，该职工信息如下："<<endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout<<"查找失败，查无此人"<<endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout<<"请输入职工姓名："<<endl;
			cin>>name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout<<"查找成功，该职工信息如下："<<endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout<<"查找失败，查无此人"<<endl;
			}
		}
		else
		{
			cout<<"输入有误，请重新输入"<<endl;
		}
	}
	//按任意键后，清屏返回上级目录
	system("pause");
	system("cls");
}

//按照编号排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "选择排序方式" << endl;
		cout << "1、按职工编号升序" << endl;
		cout << "2、按职工编号降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; i++)
		{
			//声明最小值或最大值
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else //降序
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			//判断一开始认定的最小值或最大值 是不是 计算的最小值或最大值，如果不是，交换数据
			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
	}

	cout << "排序成功！结果为： " << endl;
	this->save();
	this->Show_Emp();//展示所有职工	
}

//清空文件
void WorkerManager::Clean_File()
{
	cout<<"确认清空？"<<endl
		<<"1、确认"<<endl
		<<"2、返回"<<endl;
	int select = 0;
	cin>>select;
	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在，清空内容
		ofstream ofs(FILENAME, ios::trunc);

		ofs.close();
		//判断文件是否为空
		ifstream ifs(FILENAME, ios::in);
		if (ifs.peek() == EOF)
		{
			this->m_FileIsEmpty = true;
			cout<<"清空成功"<<endl;
			cout << "删除成功，速速跑路^-^" << endl;
			if (this->m_FileIsEmpty != NULL)
			{
				//释放堆区数据
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
			system("pause");
			system("cls");
		}
		else
		{
			this->m_FileIsEmpty = false;
			cout<<"清空失败"<<endl;
		}
		ifs.close();
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}