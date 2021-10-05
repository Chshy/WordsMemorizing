#ifndef USERDEF_H
#define USERDEF_H

#include <string>
#include <time.h>
#include "./sha1/sha1.h"
#include "bfile.h"

class UserData
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

    //数据读取
    std::string get_signin_display_str();   //签到总天数
    std::string get_score_display_str();    //总得分
    std::string get_accuracy_display_str(); //正确率

    //数据更新
    void update_statistics(bool ans_is_correct);

    //签到统计/判断
    void update_login_date();
    bool today_first_login();

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

class User
{
private:
    std::string username;
    std::string password_sha1;

public:
    UserData data;

    User();
    ~User();

    std::string get_username();
    std::string get_password_sha1();

    void SetUsername(std::string setusername);
    void SetPassword(std::string setpassword);

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
