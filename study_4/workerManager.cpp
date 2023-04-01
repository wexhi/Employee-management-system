#include"workerManager.h"

WorkerManager::WorkerManager()
{
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ������Ϊ0
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ�Ϊ�յı�־
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ���û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		//��ʼ������Ϊ0
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ�Ϊ�յı�־
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڣ����м�¼
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	//��ʼ������
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//���ļ������ݴ浽������
	this->init_Emp();

	//���Դ���
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
	//		<< "\tְ��������" << this->m_EmpArray[i]->m_Name
	//		<< "\t��λ��" << this->m_EmpArray[i]->getDeptName()
	//		<< "\t��λְ��" << this->m_EmpArray[i]->getDeptName() << endl;
	//}
}

//��ȡְ������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id;
	string name;
	int dId;

	int num = 0;//��¼����
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ�������ı�־
		num++;
	}
	ifs.close();
	
	return num;
}

//���ְ��
void WorkerManager::Add_Emp()
{
	cout << "���������ְ������" << endl;
	int addNum = 0;//�����û�����������
	cin >> addNum;
	if (addNum > 0)
	{
		//���
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ��С=ԭ���ռ��С+�û����������
		
		//�����¿ռ�
		Worker** newspace =  new Worker*[newSize];//�����¿ռ�
		
		//��ԭ���ռ��е����ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��

			cout << "������� " << i + 1 << "����ְ�����" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ������" << endl;
			cin >> name;

			cout<<"�������ְ���ĸ�λ"<<endl;
			cout<<"1.��ͨԱ��"<<endl;
			cout<<"2.����"<<endl;
			cout<<"3.�ϰ�"<<endl;
			cin>>dSelect;

			Worker * worker = NULL;//����һ��workerָ�룬ָ���´����Ķ���
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
			//������ְ����ָ�뱣�浽������
			newspace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ�
		this->m_EmpArray = newspace;

		//����ְ������
		this->m_EmpNum = newSize;

		//�����ļ���Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "��ְ��" << endl;

		//���浽�ļ���
		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}

	//������������������ϼ�Ŀ¼
	system("pause");
	system("cls");
}


//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "************************************" << endl;
	cout << "***********  ��ӭʹ��ְ������ϵͳ  ***********" << endl;
	cout << "***********  0.�˳��������  ***********" << endl;
	cout << "***********  1.����ְ����Ϣ  ***********" << endl;
	cout << "***********  2.��ʾְ����Ϣ  ***********" << endl;
	cout << "***********  3.ɾ����ְְ��  ***********" << endl;
	cout << "***********  4.�޸�ְ����Ϣ  ***********" << endl;
	cout << "***********  5.����ְ����Ϣ  ***********" << endl;
	cout << "***********  6.���ձ������  ***********" << endl;
	cout << "***********  7.��������ĵ�  ***********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	//���ļ�
	ofs.open(FILENAME, ios::out);//������ķ�ʽ���ļ� -- д�ļ�

	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}



//��ʼ��Ա��
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

//��ʾְ���ĳ�Ա����
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//������������������ϼ�Ŀ¼
	system("pause");
	system("cls");
}


//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//˵��ְ�����ڣ�����Ҫɾ����index����ְ��
		{
			//��������ɾ��Ԫ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼����Ա����
			//�����ļ�
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ����޴���" << endl;
		}
	}
	//������������������ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
	}
	else
	{
		cout << "������Ҫ�޸�ְ���ı��" << endl;
		int id = 0;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�Ա��
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout<<"�鵽�� "<<id<<"��ְ������������ְ���ţ�"<<endl;
			cin>>newId;

			cout<<"��������������"<<endl;
			cin>>newName;

			cout<<"��ѡ���λ��"<<endl;
			cout<<"1����ͨԱ��"<<endl;
			cout<<"2������"<<endl;
			cout<<"3���ϰ�"<<endl;
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
			//�������鵽������
			this->m_EmpArray[ret] = worker;

			cout<<"�޸ĳɹ�"<<endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout<<"�޸�ʧ�ܣ����޴���"<<endl;
		}
	}
	//������������������ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
	}
	else
	{
		cout<<"��������ҷ�ʽ��"<<endl;
		cout<<"1����ְ����Ų���"<<endl;
		cout<<"2����ְ����������"<<endl;
		int select = 0;
		cin>>select;
		if (select == 1)
		{
			int id;
			cout<<"������ְ����ţ�"<<endl;
			cin>>id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout<<"���ҳɹ�����ְ����Ϣ���£�"<<endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout<<"����ʧ�ܣ����޴���"<<endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout<<"������ְ��������"<<endl;
			cin>>name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout<<"���ҳɹ�����ְ����Ϣ���£�"<<endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout<<"����ʧ�ܣ����޴���"<<endl;
			}
		}
		else
		{
			cout<<"������������������"<<endl;
		}
	}
	//������������������ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//���ձ������
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "ѡ������ʽ" << endl;
		cout << "1����ְ���������" << endl;
		cout << "2����ְ����Ž���" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; i++)
		{
			//������Сֵ�����ֵ
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1) //����
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else //����
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			//�ж�һ��ʼ�϶�����Сֵ�����ֵ �ǲ��� �������Сֵ�����ֵ��������ǣ���������
			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
	}

	cout << "����ɹ������Ϊ�� " << endl;
	this->save();
	this->Show_Emp();//չʾ����ְ��	
}

//����ļ�
void WorkerManager::Clean_File()
{
	cout<<"ȷ����գ�"<<endl
		<<"1��ȷ��"<<endl
		<<"2������"<<endl;
	int select = 0;
	cin>>select;
	if (select == 1)
	{
		//��ģʽ ios::trunc ������ڣ��������
		ofstream ofs(FILENAME, ios::trunc);

		ofs.close();
		//�ж��ļ��Ƿ�Ϊ��
		ifstream ifs(FILENAME, ios::in);
		if (ifs.peek() == EOF)
		{
			this->m_FileIsEmpty = true;
			cout<<"��ճɹ�"<<endl;
			cout << "ɾ���ɹ���������·^-^" << endl;
			if (this->m_FileIsEmpty != NULL)
			{
				//�ͷŶ�������
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
			system("pause");
			system("cls");
		}
		else
		{
			this->m_FileIsEmpty = false;
			cout<<"���ʧ��"<<endl;
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