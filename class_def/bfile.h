#ifndef BFILE_H
#define BFILE_H

#include <fstream>
#include <vector>
#include <string>

class BFile
{
private:
    std::fstream file;

public:
    enum BFileMode
    {
        BFileMode_WRITE = 0,
        BFileMode_READ = 1
    };

    BFile();
    BFile(std::string filename, BFileMode mode);
    ~BFile();

    void open(std::string filename, BFileMode mode);
    void close();

    template <typename T>
    BFile &operator<<(const T &content)
    {
        file.write((char *)&content, sizeof(T));
        return *this;
    }
    template <typename T>
    BFile &operator<<(const std::vector<T> &v)
    {
        int size = v.size();
        file.write((char *)&size, sizeof(int));
        for (int i = 0; i < size; i++)
        {
            *this << v[i];
        }
        return *this;
    }
    BFile &operator<<(const std::string &s)
    {
        int size = s.size();
        file.write((char *)&size, sizeof(int));
        file.write((char *)s.data(), sizeof(char) * size);
        return *this;
    }

    template <typename T>
    BFile &operator>>(T &content)
    {
        file.read((char *)&content, sizeof(T));
        return *this;
    }
    template <typename T>
    BFile &operator>>(std::vector<T> &v)
    {
        int size;
        file.read((char *)&size, sizeof(int));
        v.resize(size);
        for (int i = 0; i < size; i++)
        {
            *this >> v[i];
        }
        return *this;
    }
    BFile &operator>>(std::string &s)
    {
        int size;
        file.read((char *)&size, sizeof(int));
        s.resize(size);
        file.read((char *)s.data(), sizeof(char) * size);
        return *this;
    }
};

#endif
