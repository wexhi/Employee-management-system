#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>//���������������ͷ�ļ�
#include"worker.h"//����worker.hͷ�ļ�
#include"employee.h"//����employee.hͷ�ļ�
#include"manager.h"//����manager.hͷ�ļ�
#include"boss.h"//����boss.hͷ�ļ�
#include<fstream>//�����ļ�����ͷ�ļ�
#define FILENAME "empFile.txt"//�����FILENAMEΪempFile.txt
using namespace std;//ʹ�������ռ�std

class WorkerManager//������WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker ** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ����
	int IsExist(int id);

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�յı�־
	bool m_FileIsEmpty;

	//��ȡְ������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ���ĳ�Ա����
	void Show_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//���ձ������
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//��������
	~WorkerManager();
};