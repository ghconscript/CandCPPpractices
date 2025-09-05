#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct { // 定义一个结构体表示一个坐标点
 int32_t x;
 int32_t y;
} Point;
// 定义一个枚举类型表示车头朝向
typedef enum {
 EAST = 0,
 SOUTH = 1,
 WEST = 2,
 NORTH = 3,
} Heading;
typedef struct {
 Point pos;
 Heading heading;
} Pose;
#ifdef __cplusplus
}
#endif