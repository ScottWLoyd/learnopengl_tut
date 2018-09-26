#ifndef _BO_MATH_H_
#define _BO_MATH_H_

#include <glm.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat4 Mat4;

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
#define CLAMP(v, min, max) (MAX(min, MIN(max, v)))

#endif
