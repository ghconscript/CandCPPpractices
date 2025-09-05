#include <Pose.h>
void ForwardAction(Pose *pose)
{
if(pose->heading == EAST){
pose->pos.x+=1;
 } else if(pose->heading == WEST){
pose->pos.x-=1;
 } else if(pose->heading == NORTH){
pose->pos.y+=1;
 } else if(pose->heading== SOUTH){
pose->pos.y-=1;
 }
}
void TurnLeftAction(Pose *pose){
    pose->heading=TurnLeft(pose->heading);
}
void TurnRightAction(Pose*pose){
    pose->heading=TurnRight(pose->heading);
}
void BackwardAction(Pose*pose){
     if (pose->heading == WEST) {
        pose->pos.x += 1;
    } else if (pose->heading == EAST) {
        pose->pos.x -= 1;
    } else if (pose->heading == SOUTH) {
        pose->pos.y += 1;
    } else if (pose->heading == NORTH) {
        pose->pos.y -= 1;
    }
}
void ReverseTurnLeftAction(Pose *pose)
{
    pose->heading = TurnRight(pose->heading);
}

void ReverseTurnRightAction(Pose *pose)
{
    pose->heading = TurnLeft(pose->heading);
}