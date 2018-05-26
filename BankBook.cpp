#include <string>
#include <iostream>
#include <strstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "BankBook.h"

using namespace std;

void BankBook::enterPersonalAccount() {
    cout<<"\n\n"<<"请输入您的账号:"<<endl;
    string anAccountNumber;
    cin>>anAccountNumber;
    while(!aPerson.checkFileExist(anAccountNumber))
    {
        cout<<"没有此账号!"<<"\n重新输入（Y），其他键退出"<<endl;
        char choice;
        cin>>choice;
        if(choice=='Y')
        {
            cout<<"请输入您的账号:"<<endl;
            cin>>anAccountNumber;
            continue;
        }
        else
            return;
    }
    long int password;
    cout<<"请输入您的密码:"<<endl;
    cin>>password;
    int i=1;
    while(!aPerson.passwordEqualTo(password))
    {
        if(i==3)
        {
            cout<<"密码输入三次错误! 对不起，您无权进入此账户!"<<endl;
            return;
        }
        cout<<"密码错误!   请重新输入密码:"<<endl;
        cin>>password;
        i++;
    }
    aPerson.initializeData();
    enterOperation();
}
void BankBook::createNewPersonalAccount()
{
    aPerson.initializeNewAccount();
    cout<<"您的账号为:"<<aPerson.getAccountNumber()
        <<"\n请记住您的账号!"<<endl;
    while(true)
    {
        cout<<"请输入您要设置的密码:"<<endl;
        long int p1,p2;
        cin>>p1;
        cout<<"请再次输入您要设置的密码:"<<endl;
        cin>>p2;
        if(p1!=p2)
            cout<<"两次输入的密码不一致,请重试!"<<endl;
        else
        {
            aPerson.setPassword(p1);
            break;
        }
    }
    cout<<"设置密码成功，请记住您的密码!"<<endl;
    cout<<"\n任意键进入个人账户操作!  输入'0'退出"<<endl;
    char choice;
    cin>>choice;
    if(choice=='0')
    {
        aPerson.saveDataToFile();
        return;
    }
    else
        enterOperation();
}
void BankBook::transferAccount()
{
    cout<<"请输入您要转入的账号:"<<endl;
    PersonalAccount anotherPerson(route);
    string anotherAccountNumber;
    cin>>anotherAccountNumber;
    if(!anotherPerson.checkFileExist(anotherAccountNumber)){
        cout<<"此账号不存在!"<<endl;
        return;
    }
    cout<<"您所要转入的账号是:"<<anotherAccountNumber<<'\n'
        <<"是否确认转账! （Y/N）"<<endl;
    char choice;
    cin>>choice;
    if(choice=='Y'){
        double transferMoney;
        while((transferMoney=aPerson.fetch())<0);
        anotherPerson.deposit(transferMoney);
        anotherPerson.saveDataToFile();
    }
    else
        anotherPerson.saveDataToFile();
}
void BankBook::enterOperation()
    {
    while(true)
                {
                    enterOperateInterface();
                    char choice;
                    cin>>choice;
                    switch(choice)
                    {
                        case '0':                      //退出
                            aPerson.saveDataToFile();
                            return;
                        case '1':
                            aPerson.readBalance();  //查询余额
                            break;
                        case '2':
                            aPerson.deposit();      //存款
                            break;
                        case '3':
                            aPerson.fetch();         //取款
                            break;
                        case '4':
                            aPerson.changePassward();// 改密码
                            break;
                        case '5':
                aPerson.printHistoryRecord();  //查记录
                break;
            case '6':
                transferAccount();            //转账
                break;
            default:
                cout<<"输入指令错误，请重试!"<<endl;
                break;
        }
    }
}
void BankBook::enterOperateInterface() {
    cout<<"\n\n";
    cout<<"##################--个人账户--##################\n"
        <<"#     <1>查询余额         <2>存款业务           #\n"
        <<"#     <3>取款业务         <4>修改密码           #\n"
        <<"#     <5>查询记录         <6>转账业务           #\n"
        <<"#                 <0>退出                      #\n"
        <<"###############################################\n"
        <<"\n请选择功能:";
}
