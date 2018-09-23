#ifndef _BO_MATH_H_
#define _BO_MATH_H_

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

struct Vec4 {
	float x, y, z, w;
};

union Mat4 {
	float e[16];
	Vec4 rows[4];
};

#endif
