#pragma once // 防止重复包含
#ifdef __cplusplus
extern "C" {
#endif
// 定义一个枚举类型表示车头朝向
typedef enum {
 EAST = 0,
 SOUTH = 1,
 WEST = 2,
 NORTH = 3,
} Heading;
Heading TurnLeft(Heading heading);
Heading TurnRight(Heading heading);
#ifdef __cplusplus
}
#endif