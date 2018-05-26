#include <string>
#include <iostream>
#include <strstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "BankBook.h"
#include "Loan.h"
using namespace std;

void showAccountInterface()
{
cout<<"#   <欢迎使用JNU学生贷款系统>  \n"
<<"###   <1>进入个人账户    ###\n"//新增存款（无息）系统入口*
<<"###   <2>创建个人账户    ###\n" //新增开户系统入口*
<<"###   <3>进入贷款系统    ###\n" //新增贷款系统入口*
<<"###   <0>退出管理程序    ###\n"
<<"<Author: Wang Yuchen/Orion233>  \n"
<<"\n请选择功能:"<<endl;
}


int main() {
    cout<<"请输入个人账户数据文件存储的路径:( 如“D:\\stl\\”，注意文件路径必须存在！):"<<endl;
    cout<<"Default Path： G:\\Code\\FinalHomework\\BankManagementSystem\\AccountData\\" <<endl;
    /*此处最后修改，目录用户可以自定义*/
    string route;
    cin>>route;
    //存款类别申明
    BankBook theBankBook(route);
    //贷款类申明
    Loan loanbook;

    int choice;
    while(true)
    {
        showAccountInterface();
        cin>>choice;
        switch(choice)
        {
            case 1:
                theBankBook.enterPersonalAccount();
                break;
            case 2:
                theBankBook.createNewPersonalAccount();
                break;
            case 3:
                /*此处创建贷款入口*/
                loanRecord();
                break;
            case 0:
                cout<< ">欢迎下次使用<" <<endl;
                exit(0);
            default:
                cout<<"输入指令错误! 请重试!"<<endl;
                break;
        }
    }
    return 0;
}

