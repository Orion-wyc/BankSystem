//
// Created by wyc19 on 2018/5/10.
//

#ifndef PersonalAccount_h
#define PersonalAccount_h
#include <iostream>
#include <iomanip>
using namespace std;

#include "AccountData.h"

class PersonalAccount:public AccountData
{
public:
	PersonalAccount(string aRoute)
	{
		dataListHead=dataListPreTail=dataListTail=new HistoryRecord;
		dataListTail->next=NULL;
		setRouteOfFile(aRoute);
	}
	void deposit();
	void deposit(double depositMoney);
	double fetch();
	void setPassword(long int newPassword)   //初始化密码
	{
		password=newPassword;
	}
	void changePassward();
	void readBalance(){						//查询余额
		cout<<"余额:  "<<setiosflags(ios::showpos)
		                    <<balance<<endl;
	}
	void initializeData();                                        //初始化个人数据
	void initializeNewAccount();                                  //建立新账号
	void printHistoryRecord();                                    //打印历史记录
	bool passwordEqualTo(long int inputPassword)                  //判断 密码是否相同
	{
		return ((password==inputPassword) ? true : false);
	}
private:
    void setRecord(double operateMoney);
};

#endif

