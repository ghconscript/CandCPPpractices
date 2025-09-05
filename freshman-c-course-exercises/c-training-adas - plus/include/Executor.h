#include "Pose.h"
void ExecutorInitialize(const Pose pose);
void ExecutorExecCommands(const char *cmds);
Pose ExecutorQuery();
void ExecutorUnInitialize(); //去初始化，和初始化接口配套
#ifdef __cplusplus
}
#endif