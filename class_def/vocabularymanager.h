#ifndef VOCABULARY_MANAGER_H
#define VOCABULARY_MANAGER_H

#include <string>
#include <vector>

#include "bfile.h"
#include "vocabulary.h"

class VocabularyManager
{
private:
public:
    std::string set_filename;     //文件路径
    bool file_opened;             //是否已经读取文件
    BFile _file;                  //读写文件
    std::vector<Vocabulary> list; //词汇表
    std::vector<bool> visited;    //临时访问标记
    int current_edit_ind;         //当前编辑标记

    VocabularyManager();
    ~VocabularyManager();

    bool readfile(std::string filename); //读取文件
    bool savefile(std::string filename); //保存至文件
    void clear();                        //清空已加载内容

    void add(Vocabulary input);                           //添加词汇
    bool delet(std::vector<Vocabulary>::size_type index); //删除词汇
    int find(std::string input);                          //查找词汇
    bool find_and_delet(std::string input);               //查找并删除词汇
};

#endif
