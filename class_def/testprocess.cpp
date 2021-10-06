#include "testprocess.h"

TestProcess::TestProcess()
{
    srand((unsigned)time(NULL));
}

// TestProcess::TestProcess(std::vector<Vocabulary> input_list)
// {
//     srand((unsigned)time(NULL));
//     init(input_list);
// }

TestProcess::~TestProcess()
{
}

void TestProcess::init(std::vector<Vocabulary> input_list, QuizRange range_input)
{
    range = range_input;        //记录出题范围
    list = input_list;          //复制单词表
    quiz_total = list.size();   //记录单词总数
    visited.clear();            //清空visited标记
    visited.resize(quiz_total); //调整visited的大小

    //统计数据归0
    ans_correct = 0;
    ans_total = 0;
    accuracy = 0;
}

QuizUnit TestProcess::DrawQuiz(QuizType quiz_type_t)
{
    QuizUnit quiz_ret; //函数的返回值
    QuizType quiz_type;

    //随机选取一个未访问过的
    int rand_ind;
    do
    {
        rand_ind = rand() % list.size(); //产生[0,list.size()-1]的随机数
    } while (visited[rand_ind]);

    if (range == QUIZRANGE_ONCE) //如果每个单词只出一道题
    {
        visited[rand_ind] = true; //访问标记
    }

    quiz_ret.voc = list[rand_ind]; //复制单词
    quiz_ret.voc_index = rand_ind;

    //那就在QUIZTYPE_CHOICE和QUIZTYPE_FILLIN里随机选择一个
    if (quiz_type_t == QUIZTYPE_ALL)
        quiz_type = QuizType(rand() % QUIZTYPE_ALL);
    else
        quiz_type = quiz_type_t;

    switch (quiz_type)
    {
    //生成选择题
    case QUIZTYPE_CHOICE:
        quiz_ret.type = QUIZTYPE_CHOICE;

        quiz_ret.ans_choice = QuizChoice(rand() % 4);                      //随机生成答案A~D
        quiz_ret.quiz_str = "选择题: " + quiz_ret.voc.word + "的解释：\n"; //生成题干

        //生成A~D四个选项
        for (int i = 0; i < 4; i++)
        {
            std::string tmp_str;
            //选项头
            switch (i)
            {
            case 0:
                tmp_str = "A: ";
                break;
            case 1:
                tmp_str = "B: ";
                break;
            case 2:
                tmp_str = "C: ";
                break;
            case 3:
                tmp_str = "D: ";
                break;
            }
            if (quiz_ret.ans_choice == QuizChoice(i)) //如果当前正在构造的是正确选项
            {
                tmp_str += quiz_ret.voc.paraphrases[rand() % quiz_ret.voc.paraphrases.size()].get_display_str(); //随机取一个解释
            }
            else
            {
                //随机取一个其他单词
                int rand_tmp;
                do
                {
                    rand_tmp = rand() % list.size();
                } while (rand_tmp == rand_ind);

                tmp_str += list[rand_tmp].paraphrases[rand() % list[rand_tmp].paraphrases.size()].get_display_str(); //随机取一个解释
            }
            tmp_str += "\n";
            quiz_ret.quiz_str += tmp_str;
        }
        break;

    //生成拼写题
    case QUIZTYPE_FILLIN:
        quiz_ret.type = QUIZTYPE_FILLIN;

        quiz_ret.quiz_str = "拼写题: \n";
        quiz_ret.quiz_str += quiz_ret.voc.paraphrases[rand() % quiz_ret.voc.paraphrases.size()].get_display_str(); //随机取一个解释
        // quiz_ret.quiz_str += "\n的拼写：\n";

        quiz_ret.ans_str = quiz_ret.voc.word;
        break;
    default:
        break;
    }

    return quiz_ret;
}

double TestProcess::DataUpdate(bool ans_is_correct)
{
    ans_total++;
    if (ans_is_correct)
        ans_correct++;
    accuracy = ans_correct * 1.0 / ans_total;
    return accuracy;
}

QuizRange TestProcess::get_quiz_range()
{
    return range;
}

bool TestProcess::mark_by_index(int ind_input)
{
    if (ind_input >= (int)visited.size())
        return false;
    if (visited[ind_input])
        return false;
    return visited[ind_input] = true;
}

std::string TestProcess::get_progress_display_str()
{
    char tmp[16];
    switch (range)
    {
    case QUIZRANGE_ONCE:
        sprintf(tmp, "%d/%d", ans_total, quiz_total);
        break;
    case QUIZRANGE_UNSOLVED:
        sprintf(tmp, "%d/%d", ans_correct, quiz_total);
        break;
    case QUIZRANGE_ALL:
        sprintf(tmp, "%d/∞", ans_total);
        break;
    default:
        break;
    }
    std::string ret(tmp);
    return ret;
}

std::string TestProcess::get_accuracy_display_str()
{
    char tmp[16];
    sprintf(tmp, "%0.2lf%%", accuracy * 100);
    std::string ret(tmp);
    return ret;
}
std::string TestProcess::get_score_display_str()
{
    char tmp[16];
    sprintf(tmp, "%d", 10 * (2 * ans_correct - ans_total));
    std::string ret(tmp);
    return ret;
}

int TestProcess::get_quiz_total()
{
    return quiz_total;
}
int TestProcess::get_ans_correct()
{
    return ans_correct;
}
int TestProcess::get_ans_total()
{
    return ans_total;
}
double TestProcess::get_accuracy()
{
    return accuracy;
}
