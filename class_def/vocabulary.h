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
    std::string word;
    std::vector<Paraphrase> paraphrases;
public:
    Vocabulary(/* args */);
    ~Vocabulary();
};



#endif