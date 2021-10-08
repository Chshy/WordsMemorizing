#include "vocabularystatistics.h"

VocabularyStatistic::VocabularyStatistic()
{
    count_total = 0;
    count_correct = 0;
}

VocabularyStatistic::~VocabularyStatistic()
{
}


/////////////////////////////////////////////////

VocabularyCounter::VocabularyCounter()
{
}

VocabularyCounter::~VocabularyCounter()
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
