#ifndef TEST_PROCESS_H
#define TEST_PROCESS_H

#include <string>
#include <vector>
#include <time.h>

#include "vocabulary.h"

enum QuizChoice //选项
{
    QUIZCHOICE_A = 0,
    QUIZCHOICE_B = 1,
    QUIZCHOICE_C = 2,
    QUIZCHOICE_D = 3
};

enum QuizType //出题的类型，选择还是填空
{
    QUIZTYPE_CHOICE = 0, //选择题
    QUIZTYPE_FILLIN = 1, //填空题
    QUIZTYPE_ALL = 2     //所有
    /*
    解释：
    当表示一个已经出好的题目的类型时，只能出现前两个中的一个
    当作为出题函数的参数传入时，都可以出现
    */
};

enum QuizRange //出题的范围
{
    QUIZRANGE_ONCE = 0,     //每个单词出现一次
    QUIZRANGE_UNSOLVED = 1, //出没出过的或者答错的单词
    QUIZRANGE_ALL = 2       //所有
};

struct QuizUnit //测试中每一道题目的结构体
{
    QuizType type;         //记录这道题是选择题还是填空题
    std::string quiz_str;  //出题时作为题目显示的字符串
    QuizChoice ans_choice; //如果是选择题，答案存在这里
    std::string ans_str;   //如果是填空题，答案存在这里
    Vocabulary voc;        //存储单词本体
    int voc_index;         //存储这个单词在TestProcess的list里的位置
};

class TestProcess //测试进程的主结构体
{
private:
    QuizRange range;
    std::vector<Vocabulary> list; //出题题库
    std::vector<bool> visited;    //临时访问标记，根据出题模式不同分别记录：这个单词出过题/这个单词已经正确回答
    int quiz_total;               //总共几道题
    int ans_correct;              //答对了几道题
    int ans_total;                //总共答了几道题
    double accuracy;              //正确率
public:
    TestProcess();
    // TestProcess(std::vector<Vocabulary> input_list); //构造函数
    ~TestProcess();

    void init(std::vector<Vocabulary> input_list, QuizRange range_input); //初始化
    QuizUnit DrawQuiz(QuizType quiz_type_t);                              //出题函数
    double DataUpdate(bool ans_correct);                                  //统计数据更新

    QuizRange get_quiz_range();        //读取当前出题范围
    bool mark_by_index(int ind_input); //根据下标做标记

    //一些获取数据用的函数
    std::string get_progress_display_str();
    std::string get_accuracy_display_str();
    std::string get_score_display_str();

    int get_quiz_total();
    int get_ans_correct();
    int get_ans_total();
    double get_accuracy();
};

#endif
