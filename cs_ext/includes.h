#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <cstddef>
using namespace std;

#include "find.h"
#include "memory.h"


process* proc;
mem* m;
DWORD hProcID, cli, eng;

namespace offsets {
	constexpr ::std::ptrdiff_t dwClientState = 0x58CFDC;
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDC14CC;
	constexpr ::std::ptrdiff_t dwViewMatrix = 0x4DCF254;
	constexpr ::std::ptrdiff_t dwRadarBase = 0x52126B4;
	constexpr ::std::ptrdiff_t m_bSpotted = 0x93D;
	constexpr ::std::ptrdiff_t m_aimPunchAngle = 0x303C;
	constexpr ::std::ptrdiff_t dwClientState_State = 0x108;
	constexpr ::std::ptrdiff_t dwClientState_ViewAngles = 0x4D90;
	//thanks haze
}

class vec3
{
public:
	float x;
	float y;
	float z;

	vec3()
	{
		x = y = z = 0;
	}

	vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3& operator+(vec3 arg)
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}

	vec3& operator-(vec3 arg)
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return *this;
	}

	vec3& operator/(vec3 arg)
	{
		x /= arg.x;
		y /= arg.y;
		z /= arg.z;
		return *this;
	}

	vec3& operator*(vec3 arg)
	{
		x *= arg.x;
		y *= arg.y;
		z *= arg.z;
		return *this;
	}

};
inline vec3 ClampAngle(vec3 angle)
{
	if (angle.x > 89.0f) angle.x = 89.0f;
	if (angle.x < -89.0f) angle.x = -89.0f;
	while (angle.y > 180.0f) angle.y -= 360.0f;
	while (angle.y < -180.0f) angle.y += 360.0f;
	angle.z = 0;
	return angle;
}
static vec3 dwOldPunchAngle;


#include "cheat.h"
rcs* rec;


using namespace offsets;