#include "AccountData.h"

//using namespace std;

void AccountData::setRouteOfFile(string routeOfFile){
    route=routeOfFile;
}

bool  AccountData::checkFileExist(string anAccountNumber){
    accountNumber=anAccountNumber;//账户编号
    string wholeFileName=route+accountNumber;//个人账户存储路径
    const char* cFileName=wholeFileName.c_str();//将string转换为 const* char的函数
    accountFile.clear();//调用clear()函数重置流的条件状态
    accountFile.open(cFileName,ios::in|ios::binary);
    if(!accountFile)
        return false;
    else
    {
        getPasswordFromFile();
        return true;
    }
}

void AccountData::getPasswordFromFile(){
    long int *pPassword=&password;
    accountFile.read((char*)pPassword,sizeof(long int));
    double *pBalance=&balance;
    accountFile.read((char*)pBalance,sizeof(double));
}

void AccountData::getDataFromFile(){
    dataListTail=new HistoryRecord;//历史记录
    while(accountFile.read((char*)dataListTail,sizeof(HistoryRecord))){
        dataListPreTail->next=dataListTail;
        dataListPreTail=dataListPreTail->next;
        dataListTail=new HistoryRecord;
    }
    //accountFile.close();
    delete dataListTail;
    dataListTail=dataListPreTail;
}

void AccountData::saveDataToFile(){
    long int *pPassword=&password;
    double *pBalance=&balance;

    string wholeFileName=route+accountNumber;
    const char* cFileName=wholeFileName.c_str();
    accountFile.close();
    accountFile.clear();

    accountFile.open(cFileName,ios::in|ios::out|ios::binary);
    accountFile.write((char*)pPassword,sizeof(long int));
    accountFile.write((char*)pBalance,sizeof(double));
    accountFile.seekp(0,ios::end);//把文件的写指针从结尾向后移0个字节
    //写入数据
    while(dataListPreTail->next){
        accountFile.write((char*)(dataListPreTail->next),sizeof(HistoryRecord));
        dataListPreTail=dataListPreTail->next;
    }
    //
    dataListTail=dataListHead->next;
    while(dataListTail){
        dataListPreTail=dataListTail;
        dataListTail=dataListTail->next;
        delete dataListPreTail;
    }
    dataListPreTail=dataListTail=dataListHead;
    dataListHead->next=NULL;
    accountFile.close();
}
