#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>//���������������ͷ�ļ�
#include<string>//����stringͷ�ļ�
using namespace std;//ʹ�������ռ�std

//ְ��������
class Worker
{
public:

	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	
	//��ȡ��λ����
	virtual string getDeptName() = 0;

	//ְ�����
	int m_Id;
	//ְ������
	string m_Name;
	//ְ�����ű��
	int m_DeptId;
};