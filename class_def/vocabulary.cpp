#include "vocabulary.h"

const std::string VOC_PATH = "\\config";
// const std::string USER_FILENAME = "user.dat";

//////////////////////////////////////////////////////////////////////////////////////////////

Paraphrase::Paraphrase()
{

}

Paraphrase::Paraphrase(WordCharacteristic input_char,std::string input_trans)
{
    characteristic = input_char;
    translation = input_trans;
}

Paraphrase::~Paraphrase()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////

std::string Paraphrase::get_display_str()
{
    std::string char_str;
    switch (characteristic)
    {
    case CHAR_noun:
        char_str = "n.   ";
        break;
    case CHAR_pronoun:
        char_str = "pron.";
        break;
    case CHAR_adjective:
        char_str = "adj. ";
        break;
    case CHAR_adverb:
        char_str = "adv. ";
        break;
    case CHAR_verb:
        char_str = "v.   ";
        break;
    case CHAR_numeral:
        char_str = "num. ";
        break;
    case CHAR_article:
        char_str = "art. ";
        break;
    case CHAR_preposition:
        char_str = "prep.";
        break;
    case CHAR_conjunction:
        char_str = "conj.";
        break;
    case CHAR_interjection:
        char_str = "int. ";
        break;
    default:
        break;
    }
    return char_str + " " + translation;
}

//////////////////////////////////////////////////////////////////////////////////////////////

Vocabulary::Vocabulary()
{
}

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
void Vocabulary::add_paraphrase(Paraphrase::WordCharacteristic input_char, std::string input_trans)
{
    Paraphrase input;
    input.characteristic = input_char;
    input.translation = input_trans;
    this->paraphrases.push_back(input);
}

bool Vocabulary::delet(std::vector<Paraphrase>::size_type index)
{
    if (index >= paraphrases.size())
    {
        return false;
    }
    else
    {
        paraphrases[index] = paraphrases.back();
        paraphrases.pop_back();
        return true;
    }
}

int Vocabulary::find(std::string input)
{
    for (std::vector<Vocabulary>::size_type it = 0; it < paraphrases.size(); ++it)
    {
        if ((paraphrases[it].translation.compare(input)) == 0) //两个字符串相等
        {
            return it;
        }
    }
    return -1;
}

bool Vocabulary::find_and_delet(std::string input)
{
    //删除前6个字符
    std::string cut_str = input.substr(6);

    int ind = find(cut_str);
    if(ind == -1)
    {
        return false;
    }
    else
    {
        delet(ind);
        return true;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

// VocabularyList::VocabularyList(/* args */)
// {
// }

// VocabularyList::~VocabularyList()
// {
// }

// //添加词汇
// void VocabularyList::add(Vocabulary input)
// {
//     this->list.push_back(input);
// }

// //下标删除
// bool VocabularyList::delet(std::vector<Vocabulary>::size_type index)
// {
//     if(index >= this->list.size())
//     {
//         return false;
//     }
//     else
//     {
//         this->list[index] = this->list.back();
//         this->list.pop_back();
//         return true;
//     }
// }