#ifndef VOCABULARY_STATISTICS_H
#define VOCABULARY_STATISTICS_H

#include <string>
#include <map>
#include "bfile.h"

class VocabularyStatistic //词汇统计数据
{
private:
public:
    int count_total;   //词汇出现次数
    int count_correct; //词汇回答正确率

    VocabularyStatistic();
    ~VocabularyStatistic();
};

class VocabularyCounter //词汇统计器
{
private:
    std::string set_filename;                            //文件路径
    BFile _file;                                         //读写文件
    std::map<std::string, VocabularyStatistic> data_map; //存储单词与对应的数据

public:
    VocabularyCounter();
    ~VocabularyCounter();

    bool readfile(std::string filename); //读取文件
    bool savefile(std::string filename); //保存至文件
    void clear();                        //清空已加载内容
};

#endif
