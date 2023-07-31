
#include "vaaac.hpp"
#include "memory.h"

#include <thread>

struct vec3f {
	float x, y, z;

	vec3f& operator+(vec3f arg) {
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}

	vec3f& operator-(vec3f arg) {
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return *this;