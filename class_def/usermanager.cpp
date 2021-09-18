#include "usermanager.h"

UserManager::UserManager(/* args */)
{
    this->login = false; //初始是没有用户登录的状态
}

UserManager::~UserManager()
{
}

bool UserManager::trylogin(User input_user)
{
    //加载存储的用户列表

    //尝试搜索用户名
    for (std::vector<User>::size_type it = 0; it < this->user_list.size(); ++it)
    {
        if ((this->user_list[it].username.compare(input_user.username)) == 0) //两个用户名相等
        {
            if ((this->user_list[it].password_sha1.compare(input_user.password_sha1)) == 0) //两个sha1相等
            {
                this->login = true;
                this->current_user = input_user;
                return true;
            }
            else
            {
                return false;
            }

        }
    }
    return false;
}

void UserManager::logout()
{
    this->login = false;
}

bool UserManager::tryregister(User input_user)
{
    //加载存储的用户列表

    //尝试搜索用户名
    for (std::vector<User>::size_type it = 0; it < this->user_list.size(); ++it)
    {
        if ((this->user_list[it].username.compare(input_user.username)) == 0) //两个用户名相等
        {
            return false;
        }
    }
    this->user_list.push_back(input_user);
    return true;
}