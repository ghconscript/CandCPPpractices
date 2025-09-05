#include "Executor.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Action.h"
#include "State.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    Pose pose;
    State state;
} Executor;

static Executor sys = {.pose = {.pos = {.x = 0, .y = 0}, .heading = NORTH}};

void ExecutorInitialize(const Pose pose)
{
    sys.pose = pose;
    sys.state.isFast = false;
    sys.state.isReverse = false;
}

void MoveCommand()
{
    if (sys.state.isFast) {
        if (sys.state.isReverse) {
            BackwardAction(&sys.pose);
            BackwardAction(&sys.pose);
        } else {
            ForwardAction(&sys.pose);
            ForwardAction(&sys.pose);
        }
    } else {
        if (sys.state.isReverse) {
            BackwardAction(&sys.pose);
        } else {
            ForwardAction(&sys.pose);
        }
    }
}

void TurnLeftCommand()
{
    if (sys.state.isFast) {  // 加速状态下转向前需要移动一格
        if (sys.state.isReverse) {
            BackwardAction(&sys.pose);
        } else {
            ForwardAction(&sys.pose);
        }
    }
    if (sys.state.isReverse) {
        ReverseTurnLeftAction(&sys.pose);
    } else {
        TurnLeftAction(&sys.pose);
    }
}

void TurnRightCommand()
{
     if (sys.state.isFast) {  // 加速状态下转向前需要移动一格
        if (sys.state.isReverse) {
            BackwardAction(&sys.pose);
        } else {
            ForwardAction(&sys.pose);
        }
    }
    if (sys.state.isReverse) {
        ReverseTurnRightAction(&sys.pose);
    } else {
        TurnRightAction(&sys.pose);
    }
    
}
void FastCommand()
{
    sys.state.isFast = !sys.state.isFast;
}

void ReverseCommand()
{
    sys.state.isReverse = !sys.state.isReverse;
}

void ExecutorExecCommands(const char *cmds)
{
    for (int i = 0; i < strlen(cmds); ++i) {
        if (cmds[i] == 'M') {
            MoveCommand();
        } else if (cmds[i] == 'L') {
            TurnLeftCommand();
        } else if (cmds[i] == 'R') {
            TurnRightCommand();
        } else if (cmds[i] == 'F') {
            FastCommand();
        } else if (cmds[i] == 'B') {
            ReverseCommand();
        }
    }
}

Pose ExecutorQuery()
{
    return sys.pose;
}

#ifdef __cplusplus
}
#endif
