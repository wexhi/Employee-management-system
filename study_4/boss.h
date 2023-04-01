//经理文件
#pragma once//防止头文件重复包含
#include<iostream>//包含输入输出流的头文件
using namespace std;//使用命名空间std
#include"worker.h"//包含worker.h头文件

class Boss : public Worker
{
public:
	//构造函数
	Boss(int id, string name, int did);

	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();
};