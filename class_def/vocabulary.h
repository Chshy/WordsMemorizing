#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <vector>
#include "bfile.h"

class Paraphrase //词汇解释 类
{
private:
public:
    enum WordCharacteristic //词性枚举
    {
        CHAR_noun = 0,        //名词n.
        CHAR_pronoun = 1,     //代词pron.
        CHAR_adjective = 2,   //形容词adj.
        CHAR_adverb = 3,      //副词adv.
        CHAR_verb = 4,        //动词v.
        CHAR_numeral = 5,     //数词num.
        CHAR_article = 6,     //冠词art.
        CHAR_preposition = 7, //介词prep.
        CHAR_conjunction = 8, //连词conj.
        CHAR_interjection = 9 //感叹词int.
    };

    WordCharacteristic characteristic; //词性
    std::string translation;           //中文翻译

    Paraphrase();                                                       //构造函数
    Paraphrase(WordCharacteristic input_char, std::string input_trans); //构造函数
    ~Paraphrase();                                                      //析构函数

    std::string get_display_str(); //获取显示字符串

    friend BFile &operator<<(BFile &bfile, const Paraphrase &par)
    {
        bfile << par.characteristic;
        bfile << par.translation;
        return bfile;
    }
    friend BFile &operator>>(BFile &bfile, Paraphrase &par)
    {
        bfile >> par.characteristic;
        bfile >> par.translation;
        return bfile;
    }
};

class Vocabulary
{
private:
public:
    std::string word;                    //词汇英文
    std::vector<Paraphrase> paraphrases; //词汇解释

    Vocabulary();                  //构造函数
    Vocabulary(std::string input); //构造函数
    ~Vocabulary();                 //析构函数

    void add_paraphrase(Paraphrase input);                //添加解释
    bool delet(std::vector<Paraphrase>::size_type index); //删除解释
    int find(std::string input);                          //查找解释
    bool find_and_delet(std::string input);               //查找并删除解释

    friend BFile &operator<<(BFile &bfile, const Vocabulary &voc)
    {
        bfile << voc.word;
        bfile << voc.paraphrases;
        return bfile;
    }
    friend BFile &operator>>(BFile &bfile, Vocabulary &voc)
    {
        bfile >> voc.word;
        bfile >> voc.paraphrases;
        return bfile;
    }
};

// class VocabularyList
// {
// private:
//     /* data */
// public:
//     BFile _file;//读写文件
//     std::vector<Vocabulary> list; //词汇表
//     std::vector<bool> visited;//访问标记

//     VocabularyList(/* args */);
//     ~VocabularyList();

//     void add(Vocabulary input);                           //添加词汇
//     bool delet(std::vector<Vocabulary>::size_type index); //下标删除
// };

#endif
