#include "D:\codes\cpp\hit practicse\experiment\include\Executor.h"
#include <stdio.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
 Pose pose;
} Executor;
static Executor sys;
void ExecutorInitialize(const Pose pose)
{
 sys.pose = pose;
}
void ExecutorExecCommands(const char *cmds)
{
    for(int i=0;i<strlen(cmds);i++) {
        if(cmds[i]=='M'){
            if(sys.pose.heading == EAST){
                sys.pose.pos.x++;
            }else if (sys.pose.heading == SOUTH)
            {
                sys.pose.pos.y--;
            }
            else if (sys.pose.heading == WEST)
            {
                sys.pose.pos.x--;
            }
            else
            {
                sys.pose.pos.y++;
            }
            
        }else if (cmds[i]=='L'){
            if(sys.pose.heading == EAST){
                sys.pose.heading=NORTH;
            }else if (sys.pose.heading == SOUTH)
            {
                sys.pose.heading=SOUTH;
            }
            else if (sys.pose.heading == WEST)
            {
                sys.pose.heading=WEST;
            }
            else
            {
                sys.pose.heading=EAST;
            }
        }else if (cmds[i]=='R')
        {
            if(sys.pose.heading == EAST){
                sys.pose.heading=SOUTH;
            }else if (sys.pose.heading == SOUTH)
            {
                sys.pose.heading=NORTH;
            }
            else if (sys.pose.heading == WEST)
            {
                sys.pose.heading=EAST;
            }
            else
            {
                sys.pose.heading=WEST;
            }
        }
    }
}
Pose ExecutorQuery()
{
 return sys.pose;
}
void ExecutorUnInitialize()
{
// 实验 4 才会真正用到此函数，这里暂时是空函数
}
#ifdef __cplusplus
}
#endif