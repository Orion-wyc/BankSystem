//
// Created by wyc19 on 2018/5/16.
//
/* 资料查询：
 * 复利银行赚的钱多,单利银行付的利息少.实际上就是银行为了多赚钱.
 * 另外一个原因是贷款按照月计息,因此就是实际利率就会升高.
 * 存款是按年计息,甚至五年算一次息,实际利率就会偏低.
 */
/*这部分的功能是计算
 *
 *
 *
 */
#ifndef BANKMANAGEMENTSYSTEM_LOAN_H
#define BANKMANAGEMENTSYSTEM_LOAN_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

/*固定贷款利率，有时间模仿花呗借呗设计*/
const double rate[3] = {0.046,0.050,0.0515};
/*此处计算复利方式*/
double Power(double rates,int k){
    double ans = 1;
    for(int i=1;i<=k;i++){
        ans *= (1+rates);
    }
    return ans;
}
class Loan{
public:
    Loan(){};
    void setLoan(string Date,double loanMoney, int loanYear){
        this->Date = Date;
        this->loanMoney = loanMoney;
        this->loanYear = loanYear;
    }
    string getDate(){
        return Date;
    }
    double getMoney(){
        return loanMoney;
    }
    int getYear(){
        return loanYear;
    }
    double getPay(){
        double rates = 1;
        if(loanYear<=1 && loanYear>0)
            rates = rate[0];
        else if(loanYear <=5)
            rates = rate[1];
        else rates = rate[2];

       // return loanMoney*pow((1+rates),loanTime);
        return loanMoney*Power(rates,loanYear);
    }
    ~Loan(){};
private:
    string Date;
    double loanMoney;
    int loanYear;
};

void welcome(){
    cout<<"             欢迎使用ORION贷款系统                "<<endl;
    cout<<"##################--个人贷款--##################\n"
        <<"#     利率:                                    #\n"
        <<"#          >一年及一年以内 4.6%                 #\n"
        <<"#          >一到五年之间   5%                   #\n"
        <<"#          >五年以上      5.15%                 #\n"
        <<"#              <1>贷款业务                      #\n"
        <<"#              <2>贷款记录                      #\n"
        <<"#              <0>退出系统                      #\n"
        <<"###############################################\n"
        <<"\n";
}

void getInfo(){

    /*读取账户信息读写,注意追加TXT的时候不要覆盖原文件内容*/
    ifstream myfile("G:\\Code\\FinalHomework\\BankManagementSystem\\AccountData\\LoanBook\\loanAccount.txt");
    ofstream savefile("G:\\Code\\FinalHomework\\BankManagementSystem\\AccountData\\LoanBook\\loanRecord.txt",ios::ate|ios::app|ios::out);
    /*嘻嘻，文件打开预备姿势*/
    if(!myfile){
        cout << "Unable to open loanAccount.txt";
        exit(1); // terminate with error

    }
    if(!savefile){
        cout << "Unable to open loanRecord.txt";
        exit(1); // terminate with error
    }

    /*判断账号是否存在，密码是否正确*/
    string buffer;
    /*从文件读取账号记录，切分为账号密码，有时间实现密码的加密功能*/
    string account,password,rightAct,rightPwd;
    bool flag = false;//标记是否存在此账号
    cout<<"输入账号：";
    cin>>account;
    while (!myfile.eof() ) {
        getline(myfile,buffer);  //读入每行
        flag = false;
        /*分离账号密码*/
        rightAct = buffer.substr(0,8);
        rightPwd = buffer.substr(9,6);
        if(account == rightAct) {
            flag = true;
            break;
        }
    }
    if(!flag){
        cout<<"账号不存在!"<<endl;
        return;
    }

    cout<<"输入密码：";
    cin>>password;
    /*增加密码验证*/
    if(password == rightPwd){
        Loan loan;

        string date;
        double loanMoney;
        int loanYear;

        cout<<"输入贷款日期、金额、年限(单位：人民币/元)：";
        cin>>date>>loanMoney>>loanYear;
        //cout<<date<<loanMoney<<loanYear;

        /*设置存款类日期，存款金额，贷款年限等*/
        loan.setLoan(date,loanMoney,loanYear);

        //cout<<loan.getDate()<<" "<<loan.getMoney()<<" "<<loan.getPay()<<endl;
        //cout<<loan.getYear()<<endl;

        /*下面实现存储记录，用户可在个人账户内查看*/
        /*列：账号 日期 贷款日期 （还款日期） 贷款年限 贷款金额 本利合计 */
        savefile<< rightAct <<" "<<loan.getDate()<<" "<<loan.getYear()
                <<" "<<loan.getMoney()<<" "<<loan.getPay()<<"\r\n";//windows下换行是"\r\n"
        /*提示贷款成功*/
        cout<<"贷款成功"<<endl;
    }
    else{
        cout<<"密码不正确！"<<endl;
        return;
    }
    myfile.close();
    savefile.close();

}

void split(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


void showHistory(){
    /*读取账户信息读写*/
    ifstream myfile("G:\\Code\\FinalHomework\\BankManagementSystem\\AccountData\\LoanBook\\loanAccount.txt");
    //ifstream getfile("G:\\Code\\FinalHomework\\BankManagementSystem\\AccountData\\LoanBook\\loanRecord.txt",ios::binary);
    /*嘻嘻，文件打开预备姿势*/
    if(!myfile){
        cout << "Unable to open loanAccount.txt";
        exit(1); // 报错

    }
  /*  if(!getfile){
        cout << "Unable to open loanRecord.txt";
        exit(1); // 报错
    }*/

    /*判断账号是否存在，密码是否正确*/
    string buffer;
    /*从文件读取账号记录，切分为账号密码，有时间实现密码的加密功能*/
    string account,password,rightAct,rightPwd;
    bool flag = false;//标记是否存在此账号
    cout<<"输入账号：";
    cin>>account;
    while (!myfile.eof() ) {
        getline(myfile,buffer);  //读入每行
        flag = false;
        /*分离账号密码*/
        rightAct = buffer.substr(0,8);
        rightPwd = buffer.substr(9,6);
        if(account == rightAct) {
            flag = true;
            break;
        }
    }
    if(!flag){
        cout<<"账号不存在!"<<endl;
        return;
    }
    myfile.close();
    myfile.clear();
    myfile.open("G:\\Code\\FinalHomework\\BankManagementSystem\\AccountData\\LoanBook\\loanRecord.txt");
    /*判断是否有记录*/
    cout<<"输入密码：";
    cin>>password;

    cout<< "                 贷款记录如下" <<endl;

    /*增加密码验证*/
    if(password == rightPwd){
        int cntNum = 1;
        string checkAct,aDate,aYear,aMoney,aPay;
        while(!myfile.eof()) {
            getline(myfile,buffer);  //读入每行
            /*此处为后期发现的一个bug，windows系统下换行是"\r\n"，在读取每一行的数据时
             * buffer中读取的内容是空，经过输出buffer的length发现的确如此
             * 所以此处要添加一个判断buffer为空的代码，这样系统不会出现异常退出
             */
            if(buffer.length() == 0)break;
            //cout<<"buffer size = " << buffer.length()<<endl;
            /*分离账号密码,此处依照空格切分，子串不大好实现*/
            checkAct = buffer.substr(0,8);
            vector<string> vec;
            split(buffer,vec," ");
            //for(vector<string>::iterator it=vec.begin();it!=vec.end();it++)
            aDate = vec[1];
            aYear = vec[2];
            aMoney = vec[3];
            aPay = vec[4];
            if(checkAct == rightAct) {
                /*列：账号  贷款日期 （还款日期） 贷款年限 贷款金额 本利合计 */
                printf("序号          贷款日期     贷款年限     贷款金额     本利合计\n");
                cout<< cntNum++ <<"             "<<aDate<<"        "<<aYear<<"     "<<aMoney<<"          "<<aPay<<endl;
            }
        }
        if(cntNum == 1)cout<<"没有贷款记录" <<endl;
    }
    else{
        cout<<"密码不正确！"<<endl;
        return;
    }
    myfile.close();

}
void loanRecord(){
    while(true){
        welcome();
        int choice;
        cin>>choice;

        switch(choice){
            case 1:
                getInfo();
                break;
            case 2:
                showHistory();
                break;
            case 0:
                cout<< ">退出贷款系统<" <<endl;
                return;
            default:
                cout<<"输入选项错误！"<<endl;
                break;
        }
    }
}

#endif //BANKMANAGEMENTSYSTEM_LOAN_H
