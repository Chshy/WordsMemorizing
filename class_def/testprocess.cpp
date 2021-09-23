// #include "testprocess.h"

// TestProcess::TestProcess(VocabularyList input_list)
// {
//     list = input_list;
//     int ans_correct;
//     int ans_total;
//     accuracy = 0;
// }

// TestProcess::~TestProcess()
// {
// }


// QuizUnit TestProcess::DrawQuiz(QuizType quiz_type_t, QuizRange quiz_range)
// {
//     QuizUnit quiz_ret;//函数的返回值
//     QuizType quiz_type;
//     if(quiz_type == QUIZTYPE_ALL)
//     {
//         //那就在QUIZTYPE_CHOICE和QUIZTYPE_FILLIN里随机选择一个
//     }
//     else
//     {
//         quiz_type = quiz_type_t;
//     }

    
    
//     //
//     switch(quiz_type)
//     {
//         case QUIZRANGE_ONCE:
//         break;
//         case QUIZRANGE_UNSOLVED:
//         break;
//         case QUIZRANGE_ALL:
//         break;
//     }





//     //这个是遍历单词表的循环
//     for(int i=0;i<list.list.size();i++)
//     {
//         int j;//0<=j<=list.list[i].paraphrases.size()
//         //以下可以读出第i个单词
//         list.list[i].word;//这是英文
//         list.list[i].paraphrases[j];//这是第j个中文解释
//         list.list[i].paraphrases[j].characteristic;//这是第j个中文解释的词性
//         list.list[i].paraphrases[j].translation;//这是第j个中文解释的中文字符

//         //code
//     }

//     //这里根据选定的题型出题
//     switch(quiz_range)
//     {
//         case QUIZTYPE_CHOICE:
//         //出题
//         break;
//         case QUIZTYPE_FILLIN:
//         //出题
//         break;
//     }
//     return quiz_ret;
// }

// /* =================================== */
// /* ===== 你需要的其他函数放在这里* ===== */
// /* =================================== */
// /* 注意，这里是函数的定义，还需要在testprocess.h的结构体里声明函数 */
// /* 另外，需要在函数返回值的后面，函数名的前面加上类名"TestProcess::"  (参考我对DrawQuiz函数的定义)*/