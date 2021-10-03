#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <vector>
#include "bfile.h"

class Paraphrase //词汇的一个解释
{
private:
    /* data */
public:
    enum WordCharacteristic
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

    Paraphrase();
    Paraphrase(WordCharacteristic input_char,std::string input_trans);
    ~Paraphrase();

    std::string get_display_str();

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
    /* data */
public:
    std::string word;                    //英文
    std::vector<Paraphrase> paraphrases; //解释们

    Vocabulary();
    Vocabulary(std::string input);
    ~Vocabulary();

    void add_paraphrase(Paraphrase input);
    void add_paraphrase(Paraphrase::WordCharacteristic input_char, std::string input_trans);
    bool delet(std::vector<Paraphrase>::size_type index);
    int find(std::string input);
    bool find_and_delet(std::string input);

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
