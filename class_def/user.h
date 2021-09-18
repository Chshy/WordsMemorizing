#ifndef USERDEF_H
#define USERDEF_H

#include <string>
#include "./sha1/sha1.h"

/* * * * * * * * * * * * * * * * * * * * * * * 
    用户类定义
    2021/9/18
    B20011528姚昌硕
 * * * * * * * * * * * * * * * * * * * * * * */
class User
{
private:
    
public:
    std::string username;
    std::string password_sha1;

    User(/* args */);
    ~User();
    void SetUsername(std::string setusername);
    void SetPassword(std::string setpassword);
};

#endif
