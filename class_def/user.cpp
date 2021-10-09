#include "user.h"

UserData::UserData()
{
    ans_total = 0;
    ans_correct = 0;
    total_score = 0;
    last_login_date = 0;
    signin_total = 0;
}

UserData::~UserData()
{
}

std::string UserData::get_signin_display_str()
{
    char tmp[16];
    sprintf(tmp, "%d", signin_total);
    std::string ret(tmp);
    return ret;
}

std::string UserData::get_score_display_str()
{
    char tmp[16];
    sprintf(tmp, "%d", total_score);
    std::string ret(tmp);
    return ret;
}

std::string UserData::get_accuracy_display_str()
{
    if (ans_total == 0)
    {
        std::string ret = "00.00%";
        return ret;
    }
    else
    {
        char tmp[16];
        sprintf(tmp, "%0.2lf%%", ans_correct * 100.0 / ans_total);
        std::string ret(tmp);
        return ret;
    }
}

void UserData::update_statistics(bool ans_is_correct)
{
    ans_total++;
    if (ans_is_correct)
    {
        ans_correct++;
        total_score += 10;
    }
    else
    {
        total_score -= 10;
    }
}

void UserData::update_login_date()
{
    time_t timestamp = time(NULL);
    if (last_login_date != timestamp)
    {
        signin_total++;                               //登录天数+1
        last_login_date = timestamp / (60 * 60 * 24); //获取天数
    }

    return;
}

bool UserData::today_first_login()
{
    time_t timestamp = time(NULL);
    int day = timestamp / (60 * 60 * 24); //获取天数
    return day != last_login_date;
}

User::User()
{
}

User::~User()
{
}

std::string User::get_username()
{
    return username;
}

std::string User::get_password_sha1()
{
    return password_sha1;
}

void User::SetUsername(std::string setusername)
{
    username = setusername;
}

void User::SetPassword(std::string setpassword)
{
    password_sha1 = sha1_encrypt(setpassword);
}
