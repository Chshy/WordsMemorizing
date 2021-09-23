// #ifndef TEST_PROCESS_H
// #define TEST_PROCESS_H

// #include <string>
// #include <vector>

// #include "vocabulary.h"

// /* ==================================== */
// /* ===== 你需要的其他头文件放在这里 ===== */
// /* ==================================== */

// enum QuizChoice //选项
// {
//     QUIZCHOICE_A = 0,
//     QUIZCHOICE_B = 1,
//     QUIZCHOICE_C = 2,
//     QUIZCHOICE_D = 3
// };

// enum QuizType //出题的类型，选择还是填空
// {
//     QUIZTYPE_CHOICE = 0, //选择题
//     QUIZTYPE_FILLIN = 1, //填空题
//     QUIZTYPE_ALL = 2     //所有
//     /*
//     解释：
//     当表示一个已经出好的题目的类型时，只能出现前两个中的一个
//     当作为出题函数的参数传入时，都可以出现
//     */
// };

// enum QuizRange //出题的范围
// {
//     QUIZRANGE_ONCE = 0,     //只出没出过的单词
//     QUIZRANGE_UNSOLVED = 1, //出没出过的或者答错的单词
//     QUIZRANGE_ALL = 2       //所有
// };

// struct QuizUnit //测试中每一道题目的结构体
// {
//     QuizType type;         //记录这道题是选择题还是填空题
//     std::string quiz_str;  //出题时作为题目显示的字符串
//     QuizChoice ans_choice; //如果是选择题，答案存在这里
//     std::string ans_str;   //如果是填空题，答案存在这里
// };

// class TestProcess //测试进程的主结构体
// {
// private:
// public:
//     //你要加什么东西都先放在public里,最后我再来调整

//     VocabularyList list; //出题题库
//     int ans_correct;     //答对了几道题
//     int ans_total;       //总共答了几道题
//     float accuracy;      //正确率

//     //需要一个东西来记录哪些单词出过题目了

//     /* ================================== */
//     /* ===== 你需要的其他变量放在这里 ===== */
//     /* ================================== */

//     TestProcess(VocabularyList input_list); //构造函数
//     ~TestProcess();

//     QuizUnit DrawQuiz(QuizType quiz_type, QuizRange quiz_range); //出题函数

//     /* =================================== */
//     /* ===== 你需要的其他函数放在这里* ===== */
//     /* =================================== */
//     /*注意，这里是函数的声明，函数定义在testprocess.cpp里*/
// };

// #endif
