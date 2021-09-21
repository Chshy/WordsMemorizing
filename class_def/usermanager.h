#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>
#include <fstream>

#include <windows.h>

#include "user.h"

/* * * * * * * * * * * * * * * * * * * * * * * 
    用户管理器类定义
    2021/9/18
    B20011528姚昌硕
 * * * * * * * * * * * * * * * * * * * * * * */

class UserManager
{
private:
    bool login;                  //是否已经登录
    User current_user;           //当前登录用户
    // int user_list_size;          //用户列表大小
    std::vector<User> user_list; //用户列表

    std::string exe_path;

public:
    UserManager(/* args */);
    ~UserManager();


    //登录登出注册
    bool trylogin(User input_user);
    void logout();
    bool tryregister(User input_user);

    //状态判断
    bool islogin();
    User get_current_user();

    //文件
    void set_exe_path(std::string input);
    bool read_from();
    bool write_to();
};

#endif
