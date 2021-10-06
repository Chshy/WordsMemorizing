#ifndef USERDEF_H
#define USERDEF_H

#include <string>
#include <time.h>
#include "./sha1/sha1.h"
#include "bfile.h"

class UserData //用户数据 类
{
private:
    //数据变量
    int ans_total;   //总答题数
    int ans_correct; //总正确数
    int total_score; //总得分
    //签到变量
    int last_login_date; //上次签到日期
    int signin_total;    //签到总天数

public:
    UserData();
    ~UserData();

    //数据读取函数
    std::string get_signin_display_str();   //签到总天数
    std::string get_score_display_str();    //总得分
    std::string get_accuracy_display_str(); //正确率

    //数据更新函数
    void update_statistics(bool ans_is_correct);

    //签到统计/判断函数
    void update_login_date();
    bool today_first_login();

    //操作符重载
    friend BFile &operator<<(BFile &bfile, const UserData &dat)
    {
        bfile << dat.ans_total;
        bfile << dat.ans_correct;
        bfile << dat.total_score;
        bfile << dat.last_login_date;
        bfile << dat.signin_total;
        return bfile;
    }
    friend BFile &operator>>(BFile &bfile, UserData &dat)
    {
        bfile >> dat.ans_total;
        bfile >> dat.ans_correct;
        bfile >> dat.total_score;
        bfile >> dat.last_login_date;
        bfile >> dat.signin_total;
        return bfile;
    }
};

class User //用户 类
{
private:
    std::string username;      //用户名
    std::string password_sha1; //密码

public:
    UserData data; //用户数据

    User();
    ~User();

    //数据读取函数
    std::string get_username();
    std::string get_password_sha1();

    //数据设置函数
    void SetUsername(std::string setusername);
    void SetPassword(std::string setpassword);

    //操作符重载
    friend BFile &operator<<(BFile &bfile, const User &usr)
    {
        bfile << usr.username;
        bfile << usr.password_sha1;
        bfile << usr.data;
        return bfile;
    }
    friend BFile &operator>>(BFile &bfile, User &usr)
    {
        bfile >> usr.username;
        bfile >> usr.password_sha1;
        bfile >> usr.data;
        return bfile;
    }
};

#endif
