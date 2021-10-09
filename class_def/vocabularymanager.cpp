#include "vocabularymanager.h"

VocabularyManager::VocabularyManager(/* args */)
{
    file_opened = false;
}

VocabularyManager::~VocabularyManager()
{
}

bool VocabularyManager::readfile(std::string filename)
{
    if (!(_file.open(filename, BFile::BFileMode_READ)))
        return false;
    _file >> list;
    _file.close();

    visited.clear();
    visited.resize(list.size());

    file_opened = true;
    return true;
}

bool VocabularyManager::savefile(std::string filename)
{
    if (!(_file.open(filename, BFile::BFileMode_WRITE)))
        return false;
    _file << list;
    _file.close();

    visited.clear();
    return true;
}

void VocabularyManager::clear()
{
    _file.close();
    file_opened = false;
    list.clear();
    visited.clear();
}

//添加词汇
void VocabularyManager::add(Vocabulary input)
{
    list.push_back(input);
    visited.push_back(false);
}

//下标删除
bool VocabularyManager::delet(std::vector<Vocabulary>::size_type index)
{
    if (index >= list.size())
    {
        return false;
    }
    else
    {
        list[index] = list.back();
        visited[index] = visited.back();
        list.pop_back();
        visited.pop_back();
        return true;
    }
}

int VocabularyManager::find(std::string input)
{
    for (std::vector<Vocabulary>::size_type it = 0; it < list.size(); ++it)
    {
        if ((list[it].word.compare(input)) == 0) //两个字符串相等
        {
            return it;
        }
    }
    return -1;
}

bool VocabularyManager::find_and_delet(std::string input)
{
    int ind = find(input);
    if (ind == -1)
    {
        return false;
    }
    else
    {
        delet(ind);
        return true;
    }
}
