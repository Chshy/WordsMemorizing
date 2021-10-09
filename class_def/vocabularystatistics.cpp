#include "vocabularystatistics.h"

VocabularyStatistic::VocabularyStatistic()
{
    count_total = 0;
    count_correct = 0;
}

VocabularyStatistic::~VocabularyStatistic()
{
}

VocabularyCounter::VocabularyCounter()
{
}

VocabularyCounter::~VocabularyCounter()
{
}

void VocabularyCounter::update_statistics(std::string word, bool answer_is_correct)
{
    if (data_map.find(word) == data_map.end()) //没有这个key
    {
        VocabularyStatistic tmp;
        tmp.count_total++;
        if (answer_is_correct)
            tmp.count_correct++;
        data_map.insert(std::make_pair(word, tmp));
    }
    else //有这个key
    {
        data_map[word].count_total++;
        if (answer_is_correct)
            data_map[word].count_correct++;
    }
    return;
}

bool VocabularyCounter::readfile(std::string filename)
{
    if (!(_file.open(filename, BFile::BFileMode_READ)))
        return false;
    _file >> data_map;
    _file.close();
    return true;
}

bool VocabularyCounter::savefile(std::string filename)
{
    if (!(_file.open(filename, BFile::BFileMode_WRITE)))
        return false;
    _file << data_map;
    _file.close();
    return true;
}

void VocabularyCounter::clear()
{
    _file.close();
    data_map.clear();
}

bool VocabularyCounter::generate(std::string filename)
{
    std::fstream file;
    file.open(filename, std::ios_base::out | std::ios_base::trunc);
    if (!file)
        return false;
    file << "单词\t\t出现次数\t正确率" << std::endl;
    char tmp[16];
    for (auto it = data_map.begin(); it != data_map.end(); ++it)
    {
        sprintf(tmp, "%2.2lf%%", (it->second.count_correct) * 100.0 / (it->second.count_total));
        std::string tmp_s(tmp);
        file << it->first << "\t\t" << it->second.count_total << "\t" << tmp_s << std::endl;
    }
    file.close();
    return true;
}
