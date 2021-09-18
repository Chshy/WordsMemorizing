#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>

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

public:
    UserManager(/* args */);
    ~UserManager();
    bool trylogin(User input_user);
    void logout();
    bool tryregister(User input_user);
    bool islogin();
    User get_current_user();
};

#endif
