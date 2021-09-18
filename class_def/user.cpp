#include "user.h"

User::User(/* args */)
{
}

User::~User()
{
}

void User::SetUsername(std::string setusername)
{
    username = setusername;
}

void User::SetPassword(std::string setpassword)
{
    password_sha1 = sha1_encrypt(setpassword);
}
