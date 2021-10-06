#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>
#include <fstream>

#include <windows.h>

#include "user.h"
#include "bfile.h"

class UserManager //用户管理器 类
{
private:
    bool login;                  //是否已经登录
    int current_user_index;      //当前用户下标
    std::vector<User> user_list; //用户列表
    std::string exe_path;        //exe文件目录

public:
    UserManager();
    ~UserManager();

    //登录登出注册
    bool trylogin(User input_user);
    void logout();
    bool tryregister(User input_user);
    //没有删除用户的功能！

    //状态判断
    bool islogin();                      //当前有没有登录用户
    User get_current_user();             //获取当前登录用户信息(只读)
    bool currentuser_today_firstlogin(); //获取当前用户是否为当天第一次登录

    //数据更新
    void update_currentuser_status(bool ans_is_correct); //更新答题数据
    void update_currentuser_logindate();                 //更新登录日期

    //文件
    void set_exe_path(std::string input);
    bool read_from();
    bool write_to();

    // friend BFile &operator<<(BFile &bfile, const UserManager &usr_mnger)
    // {
    //     bfile << usr_mnger.user_list;
    //     return bfile;
    // }
    // friend BFile &operator>>(BFile &bfile, UserManager &usr_mnger)
    // {
    //     bfile >> usr_mnger.user_list;
    //     return bfile;
    // }
};

#endif
