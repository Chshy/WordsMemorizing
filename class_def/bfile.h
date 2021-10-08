#ifndef BFILE_H
#define BFILE_H

#include <fstream>
#include <vector>
#include <string>
#include <map>

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

    bool open(std::string filename, BFileMode mode); //打开/创建文件
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
    template <typename T1, typename T2>
    BFile &operator<<(const std::map<T1, T2> &m)
    {
        int size = m.size();
        file.write((char *)&size, sizeof(int));
        std::map<T1, T2>::iterator it;
        for (it = m.begin(); it != m.end(); ++it)
        {
            *this << it->first;
            *this << it->second;
        }
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
    template <typename T1, typename T2>
    BFile &operator>>(const std::map<T1, T2> &m)
    {
        int size;
        file.read((char *)&size, sizeof(int));
        T1 tmp_1st;
        T2 tmp_2nd;
        for (int i = 0; i < size; i++)
        {
            *this >> tmp_1st;
            *this >> tmp_2nd;
            // m->insert(make_pair(tmp_1st, tmp_2nd));
            m.insert(make_pair(tmp_1st, tmp_2nd));
        }
        return *this;
    }
};

#endif
