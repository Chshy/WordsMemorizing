#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <vector>

enum WordCharacteristic
{
    CHAR_noun = 0,        //名词
    CHAR_pronoun = 1,     //代词
    CHAR_adjective = 2,   //形容词
    CHAR_adverb = 3,      //副词
    CHAR_verb = 4,        //动词
    CHAR_numeral = 5,     //数词
    CHAR_article = 6,     //冠词
    CHAR_preposition = 7, //介词
    CHAR_conjunction = 8, //连词
    CHAR_interjection = 9 //感叹词
};

struct Paraphrase
{
    WordCharacteristic characteristic;
    std::string translation;
};

class Vocabulary
{
private:
    /* data */
public:
    std::string word;
    std::vector<Paraphrase> paraphrases;

    Vocabulary(std::string input);
    ~Vocabulary();

    void add_paraphrase(Paraphrase input);
    void add_paraphrase(WordCharacteristic input_char, std::string input_trans);
};

class VocabularyList
{
private:
    
public:
    std::vector<Vocabulary> list; //词汇表
    VocabularyList(/* args */);
    ~VocabularyList();

    void add(Vocabulary input);                          //添加词汇
    bool delet(std::vector<Vocabulary>::size_type index); //下标删除
};



#endif
