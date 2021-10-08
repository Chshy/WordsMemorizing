#ifndef GLOBAL_VARIATE_H
#define GLOBAL_VARIATE_H

#include <string>
#include <QString>

#include "class_def/usermanager.h"
#include "class_def/vocabularymanager.h"
#include "class_def/vocabularystatistics.h"

extern UserManager User_Manager;
extern VocabularyManager Lib_Manager;
extern VocabularyManager Note_Manager;
extern VocabularyCounter Vocabulary_Counter;

extern QString EXE_QPATH;
extern std::string EXE_PATH;

#endif
