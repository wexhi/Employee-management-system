//��ͨԱ���ļ�
#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>//���������������ͷ�ļ�
using namespace std;//ʹ�������ռ�std
#include"worker.h"//����worker.hͷ�ļ�

class Employee :public Worker//������Employee�̳���Worker
{
public:
	//���캯��
	Employee(int id,string name,int did);

	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDeptName();
};