#include "usermanager.h"

#include <QDebug>

const std::string USER_FILEPATH = "\\config";
const std::string USER_FILENAME = "user.dat";

UserManager::UserManager()
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
        if ((this->user_list[it].get_username().compare(input_user.get_username())) == 0) //两个用户名相等
        {
            if ((this->user_list[it].get_password_sha1().compare(input_user.get_password_sha1())) == 0) //两个sha1相等
            {
                this->login = true;
//                this->current_user = user_list[it];
                this->current_user_index = it;
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
        if ((this->user_list[it].get_username().compare(input_user.get_username())) == 0) //两个用户名相等
        {
            return false;
        }
    }
    this->user_list.push_back(input_user);
    this->write_to(); //保存到文件
    return true;
}

bool UserManager::islogin()
{
    return login;
}

User UserManager::get_current_user()
{
    //return current_user;
    return user_list[current_user_index];
}

void UserManager::update_currentuser_status(bool ans_is_correct)
{
    if(!login)
        return;
    user_list[current_user_index].data.update_statistics(ans_is_correct);
    this->write_to();
}

void UserManager::update_currentuser_logindate()
{
     if(!login)
         return;
    user_list[current_user_index].data.update_login_date();
    this->write_to();
}

bool UserManager::currentuser_today_firstlogin()
{
    if(!login)
        return false;
    return user_list[current_user_index].data.today_first_login();
}





void UserManager::set_exe_path(std::string input)
{
    this->exe_path = input;
}

bool UserManager::read_from()
{
    std::fstream _file;
    _file.open(this->exe_path + USER_FILEPATH + "\\" + USER_FILENAME, std::ios::in | std::ios::binary); //以读模式打开

    std::string tmps = this->exe_path + USER_FILEPATH + "\\" + USER_FILENAME;
    qDebug() << tmps.c_str() << endl;

    if (!_file) //文件不存在
    {
        // qDebug() << "File Not Found" << endl;

        std::string mkdir_path = "mkdir " + this->exe_path + USER_FILEPATH;
        qDebug() << mkdir_path.c_str() << endl;
        system(mkdir_path.c_str());                                                                          //创建文件夹
        _file.open(this->exe_path + USER_FILEPATH + "\\" + USER_FILENAME, std::ios::out | std::ios::binary); //尝试创建文件

        if (!_file) //创建文件失败
        {
            qDebug() << "Create File Failed" << endl;
            return false;
        }
        else
        {
            // qDebug() << "Create File Sucess" << endl;
            _file.close();
            return true; //反正文件是空的，没必要再读了
        }
    }
    else
    {
        // qDebug() << "File Found" << endl;
        _file.close();
    }

    BFile _bfile(this->exe_path + USER_FILEPATH + "\\" + USER_FILENAME, BFile::BFileMode_READ);
    ;
    // qDebug() << "Start Reading File" << endl;
    _bfile >> this->user_list;
    _bfile.close();
    // qDebug() << "Return From read" << endl;
    return true;
}

bool UserManager::write_to()
{
    //启动程序的时候会读文件，那个时候已经检查过文件是否存在了，这里就不检查了
    //如果你在程序启动后又把文件删了，那我也不管 喜欢卡bug是吧😓
    BFile _file(this->exe_path + USER_FILEPATH + "\\" + USER_FILENAME, BFile::BFileMode_WRITE);

    // qDebug() << "vector_size = " << this->user_list.size();
    _file << this->user_list;
    _file.close();
    // qDebug() << "Return From write";
    return true;
}
