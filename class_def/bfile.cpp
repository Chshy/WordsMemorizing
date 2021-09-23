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

void BFile::open(std::string filename, BFileMode mode = BFileMode_WRITE)
{
    if(file)
    {
        file.close();
    }

    switch (mode)
    {
    case BFileMode_WRITE:
        file.open(filename, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc); // discard the original file contents
        break;

    case BFileMode_READ:
        file.open(filename, std::ios_base::binary | std::ios_base::in);
        break;

    default:
        break;
    }
}

void BFile::close()
{
    file.close();
}