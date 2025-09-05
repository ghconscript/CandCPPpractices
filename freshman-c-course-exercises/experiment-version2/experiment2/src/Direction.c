#include "Direction.h"
#ifdef __cplusplus
extern "C" {
#endif
Heading TurnLeft(Heading heading)
{
if(heading ==EAST){
    heading = NORTH;
}else if(heading == NORTH){
    heading = WEST;
}else if(heading == WEST){
    heading = SOUTH;
}else if(heading == SOUTH){
    heading = EAST;
}
return heading;
}
//更新方向向右转
Heading TurnRight(Heading heading)
{
if(heading ==EAST){
    heading = SOUTH;
}else if(heading == SOUTH){
    heading = WEST;
}else if(heading == WEST){
    heading = NORTH;
}else if(heading == NORTH){
    heading = EAST;
}
return heading;
}
#ifdef __cplusplus
}
#endif
