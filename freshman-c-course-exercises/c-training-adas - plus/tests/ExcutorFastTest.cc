#include "gtest/gtest.h"
#include "Executor.h"
//测试加速
TEST(Executor, should_return_x_minus2_y_3_given_command_is_FMLM_and_facing_is_N)
{
    // given
    ExecutorInitialize((Pose){.pos = {.x = 0, .y = 0}, .heading = NORTH});
    // when
    ExecutorExecCommands("FMLM");
    // then
    Pose pose = ExecutorQuery();
    ASSERT_EQ(pose.pos.x, -2);
    ASSERT_EQ(pose.pos.y, 3);
    ASSERT_EQ(pose.heading, WEST);
}
//测试倒车
TEST(Executor, should_return_x_minus3_y_minus1_given_command_is_BMLM_and_facing_is_N)
{
    // given
    ExecutorInitialize((Pose){.pos = {.x = 0, .y = 0}, .heading = NORTH});
    // when
    ExecutorExecCommands("BMLM");  //(0,0),N->(0,-1),N->(0,-1),E->(-1,-1),E
    // then
    Pose pose = ExecutorQuery();
    ASSERT_EQ(pose.pos.x, -1);
    ASSERT_EQ(pose.pos.y, -1);
    ASSERT_EQ(pose.heading, EAST);
}
//测试倒车和加速的叠加
TEST(Executor, should_return_x_3_y_1_given_command_is_FMLBMLM_and_facing_is_N)
{
    // given
    ExecutorInitialize((Pose){.pos = {.x = 0, .y = 0}, .heading = NORTH});
    // when
    ExecutorExecCommands("FMLBMLM"); //(0,0),N->(0,2),N->(0,3),W->(2,3),W->(3,3),N->(3,1),N
    // then
    Pose pose = ExecutorQuery();
    ASSERT_EQ(pose.pos.x, 3);
    ASSERT_EQ(pose.pos.y, 1);
    ASSERT_EQ(pose.heading, NORTH);
}
TEST(Executor, should_return_x_minus2_y_3_given_command_is_FMLMFM_and_facing_is_N)
{
    // given
    ExecutorInitialize((Pose){.pos = {.x = 0, .y = 0}, .heading = NORTH});
    // when
    ExecutorExecCommands("FMLMFM");
    // then
    Pose pose = ExecutorQuery();
    ASSERT_EQ(pose.pos.x, -3);
    ASSERT_EQ(pose.pos.y, 3);
    ASSERT_EQ(pose.heading, WEST);
}