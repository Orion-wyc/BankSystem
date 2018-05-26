#ifndef BankBook_h
#define BankBook_h

using namespace std;

#include "PersonalAccount.h"


class BankBook
{
private:
    string route;//数据存放目录
    PersonalAccount aPerson;
    void transferAccount();
    void enterOperation();
    void enterOperateInterface();
public:
    BankBook(string routeOfFile):aPerson(routeOfFile)
    {
        route=routeOfFile;
    }
    void enterPersonalAccount();
    void createNewPersonalAccount();
};


#endif
