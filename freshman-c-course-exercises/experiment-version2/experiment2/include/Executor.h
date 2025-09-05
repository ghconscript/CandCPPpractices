#pragma once
#include "Pose.h"

#ifdef __cplusplus
extern "C" {
#endif

void ExecutorInitialize(const Pose pose);
void ExecutorExecCommands(const char *cmds);
Pose ExecutorQuery();

#ifdef __cplusplus
}
#endif
