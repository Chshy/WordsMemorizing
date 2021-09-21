#include "usermanager.h"

#include <QDebug>

const std::string USER_FILEPATH = "\\config";
const std::string USER_FILENAME = "user.dat";

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

bool UserManager::islogin()
{
    return login;
}

User UserManager::get_current_user()
{
    return current_user;
}

void UserManager::set_exe_path(std::string input)
{
    this-> exe_path = input;
}

bool UserManager::read_from()
{
    std::fstream _file;
    _file.open(this->exe_path + USER_FILEPATH + "\\" + USER_FILENAME, std::ios::in | std::ios::binary); //以读模式打开

    if (!_file) //文件不存在
    {
        qDebug() << "File Not Found" << endl;

        std::string mkdir_path = "mkdir " + this->exe_path + USER_FILEPATH;
        qDebug() << mkdir_path.c_str() << endl;
        system(mkdir_path.c_str());                                  //创建文件夹
        _file.open(this->exe_path + USER_FILEPATH + "\\" + USER_FILENAME, std::ios::out | std::ios::binary); //尝试创建文件

        if (!_file) //创建文件失败
        {
            qDebug() << "Create File Failed" << endl;
            return false;
        }
        else
        {
            qDebug() << "Create File Sucess" << endl;
            _file.close();
            return true; //反正文件是空的，没必要再读了
            //_file.open(USER_FILEPATH, std::ios::in | std::ios::binary); //以读模式打开
        }
    }

    // User
    // binary_file.read(reinterpret_cast<char *>(&p_Data),sizeof(WebSites));
    //    while (_file.read((char *)&s, sizeof(User)))
    //    {                                      //一直读到文件结束
    //        int readedBytes = _file.gcount(); //看刚才读了多少字节
    //        _file << s.szName << " " << s.age << endl;
    //    }

    // User
    //     binary_file.read(reinterpret_cast<char *>(&p_Data), sizeof(WebSites));
    // while (_file.read((char *)&s, sizeof(User)))
    // {                                     //一直读到文件结束
    //     int readedBytes = _file.gcount(); //看刚才读了多少字节
    //     _file << s.szName << " " << s.age << endl;
    // }

    for (User tmp_user; _file.read(reinterpret_cast<char *>(&tmp_user), sizeof(User)); this->user_list.push_back(tmp_user))
        ;
    _file.close();

    return true;
}

bool UserManager::write_to()
{
    std::fstream _file;
    _file.open(USER_FILEPATH, std::ios::in | std::ios::binary | std::ios::trunc); //以写模式打开

    for (std::vector<User>::size_type it = 0; it < this->user_list.size(); ++it)
    {
        _file.write(reinterpret_cast<char *>(&(this->user_list[it])), sizeof(User));
    }

    _file.close();

    return true;
}
