//
// Created by wyc19 on 2018/5/10.
//

#include <iostream>
#include <strstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
#include "AccountData.h"
#include "PersonalAccount.h"

//using namespace std;


void PersonalAccount::changePassward()
{
    while(true)
    {
        cout<<"请输入新密码（数字）:"<<endl;
        long int p1,p2;
        cin>>p1;
        cout<<"请再次输入新密码（数字）:"<<endl;
        cin>>p2;
        if(p1!=p2)
            cout<<"两次输入的密码不一致!"<<endl;
        else
        {
            password=p1;
            cout<<"新密码设置成功!"<<endl;
            break;
        }
    }
}
void PersonalAccount::initializeData()
{
    getDataFromFile();
}
void PersonalAccount::initializeNewAccount()
{
    string numFileName = "Number";
    string fullName = route + numFileName + ".txt";
    const char *fullNumFileName = fullName.c_str();
    fstream numFile(fullNumFileName,ios::in);
    if(!numFile)
    {
        numFile.clear();
        numFile.open(fullNumFileName,ios::out);
        accountNumber="53070401";
        numFile<<accountNumber;
        numFile.close();
    }
    else
    {
        numFile>>accountNumber;
        const char *sNumber=accountNumber.c_str();
        long int nNumber=atol(sNumber);
        nNumber++;
        char s[21];
        ostrstream strout(s,20);
        strout<<nNumber<<ends;
        accountNumber=s;
        numFile.close();
        numFile.clear();
        numFile.open(fullNumFileName,ios::out);
        numFile<<accountNumber;
        numFile.close();
    }
    balance=0;
    string wholeFileName=route+accountNumber;
    const char* cFileName=wholeFileName.c_str();
    accountFile.clear();
    accountFile.open(cFileName,ios::out|ios::binary);
    accountFile.close();
}
double PersonalAccount::fetch()
{
    cout<<"请输入数额:"<<endl;
    double fetchMoney;
    cin>>fetchMoney;
    if(fetchMoney>balance)
    {
        cout<<"余额不足!"<<endl;
        return -1;
    }
    else
    {
        balance-=fetchMoney;
        setRecord(-fetchMoney);
        return fetchMoney;
    }
}
void PersonalAccount::deposit(double depositMoney)
{
    balance+=depositMoney;
    setRecord(depositMoney);
}
void PersonalAccount::deposit()
{
    cout<<"请输入要存入账户的数额:"<<endl;
    double depositMoney;
    cin>>depositMoney;
    balance+=depositMoney;
    setRecord(depositMoney);
}

void PersonalAccount::printHistoryRecord()
{
    if(!dataListHead->next)
        cout<<"没记录"<<endl;
    else
    {
        HistoryRecord *p=dataListHead->next;
        cout<<setw(6)<<"    日期"<<setw(30)<<"存/取款"<<setw(15)
            <<"余额"<<endl;
        while(p!=NULL){
            cout<<p->theTime<<setw(19)<<setiosflags(ios::showpos)
                <<p->perOperateMoney<<setw(15)<<p->perBalance
                <<endl;
            p=p->next;
        }
    }
}

void PersonalAccount::setRecord(double operateMoney)
{
    time_t perTime=time(NULL);
    string strTime=ctime(&perTime);
    strTime.resize(strTime.length()-1);
    dataListTail->next=new HistoryRecord;
    dataListTail=dataListTail->next;
    strcpy(dataListTail->theTime,strTime.c_str());
    dataListTail->perOperateMoney=operateMoney;
    dataListTail->perBalance=balance;
    dataListTail->next=NULL;
}
