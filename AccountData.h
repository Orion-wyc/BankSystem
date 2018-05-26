//
// Created by wyc19 on 2018/5/10.
//
#ifndef AccountData_h
#define AccountData_h

#include <fstream>
#include <string>
using namespace std;

class AccountData
{
public:
   void setRouteOfFile(string routeOfFile);     //设置路径
   bool checkFileExist(string anAccountNumber);    //检查文件是否存在
   void getPasswordFromFile();    //从文件中读取密码
   void getDataFromFile();    //从文件中读取余额和历史记录
   void saveDataToFile();     //将密码、余额和历史记录存入文件
   string getAccountNumber()   //获取账号
   {
	   return accountNumber;
   }
protected:
    struct HistoryRecord
    {
       char theTime[30];
       double perOperateMoney;
       double perBalance;
       struct HistoryRecord *next;
    }*dataListHead,*dataListPreTail,*dataListTail; //历史记录链表
    string accountNumber;  //账号
    long int password;   //密码(数字)
    double balance;         //余额
	fstream accountFile;     //账号对应的文件流
    string route;           //路径
};


#endif
