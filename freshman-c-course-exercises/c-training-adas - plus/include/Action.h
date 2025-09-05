#pragma once
#include "Pose.h"
#ifdef __cplusplus
extern "C" {
#endif
void ForwardAction(Pose *pose);
void TurnLeftAction(Pose *pose);
void TurnRightAction(Pose *pose);
void BackwardAction(Pose *pose);
#ifdef __cplusplus
}
#endif