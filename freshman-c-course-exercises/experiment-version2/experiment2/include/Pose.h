#pragma once
#include <stdint.h>
#include "Direction.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
 int32_t x;
 int32_t y;
} Point;
typedef struct {
  Point pos;
  Heading heading;
} Pose;
#ifdef __cplusplus
}
#endif