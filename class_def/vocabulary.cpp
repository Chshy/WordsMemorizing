#include "vocabulary.h"

//词汇构造（初始化英文）
Vocabulary::Vocabulary(std::string input)
{
    this->word = input;
}

Vocabulary::~Vocabulary()
{
}

//词汇添加解释
void Vocabulary::add_paraphrase(Paraphrase input)
{
    this->paraphrases.push_back(input);
}

//词汇添加解释
void Vocabulary::add_paraphrase(WordCharacteristic input_char, std::string input_trans)
{
    Paraphrase input;
    input.characteristic = input_char;
    input.translation = input_trans;
    this->paraphrases.push_back(input);
}

///////////////////////////////////////////////////////////

VocabularyList::VocabularyList(/* args */)
{
}

VocabularyList::~VocabularyList()
{
}

//添加词汇
void VocabularyList::add(Vocabulary input)
{
    this->list.push_back(input);
}

//下标删除
bool VocabularyList::delet(std::vector<Vocabulary>::size_type index)
{
    if(index >= this->list.size())
    {
        return false;
    }
    else
    {
        this->list[index] = this->list.back();
        this->list.pop_back();
        return true;
    }
}