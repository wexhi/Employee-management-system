//�����ļ�
#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>//���������������ͷ�ļ�
using namespace std;//ʹ�������ռ�std
#include"worker.h"//����worker.hͷ�ļ�

class Manager : public Worker
{
public:
	//���캯��
	Manager(int id, string name, int did);

	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDeptName();
};