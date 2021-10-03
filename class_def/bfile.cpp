#include "bfile.h"

BFile::BFile()
{
}

BFile::BFile(std::string filename, BFileMode mode = BFileMode_WRITE)
{
    this->open(filename, mode);
}

BFile::~BFile()
{
    file.close();
}

bool BFile::open(std::string filename, BFileMode mode = BFileMode_WRITE)
{
    if (file) //如果已经打开其他文件，先关闭
        file.close();

    switch (mode)
    {
    case BFileMode_WRITE:
        file.open(filename, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc); // 覆盖原文件
        if (file)
            return true;
        else
            return false;
        break;

    case BFileMode_READ:
        file.open(filename, std::ios_base::binary | std::ios_base::in);
        if (file)
            return true;
        else
            return false;
        break;

    default:
        return false;
        break;
    }
}

void BFile::close()
{
    file.close();
}