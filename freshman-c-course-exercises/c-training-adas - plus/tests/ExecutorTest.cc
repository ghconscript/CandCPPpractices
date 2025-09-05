#include "gtest/gtest.h"
#include "Executor.h"
TEST(Executor, should_return_init_pose_when_without_command)
{
 // given
 ExecutorInitialize((Pose){.pos = {.x = 0, .y = 0}, .heading = NORTH});
 // when 
 Pose pose = ExecutorQuery(); 
 // then
 ASSERT_EQ(pose.pos.x, 0);
 ASSERT_EQ(pose.pos.y, 0);
 ASSERT_EQ(pose.heading, NORTH);
 ExecutorUnInitialize();
}
TEST(Executor, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
{
 // given
 ExecutorInitialize((Pose){.pos = {.x = 2 ,.y = 3}, .heading = NORTH});
 // when 
 ExecutorExecCommands("M");

 // then
 Pose pose = ExecutorQuery(); 
 ASSERT_EQ(pose.pos.x, 3);
 ASSERT_EQ(pose.pos.y, 3);
 ASSERT_EQ(pose.heading, NORTH);
 ExecutorUnInitialize();
}

