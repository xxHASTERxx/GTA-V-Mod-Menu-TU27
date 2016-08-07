
// data type defs for easy cross-processor support
// 

#ifndef _COMMON_TYPES_
#define _COMMON_TYPES_
/*

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned __int64	u64;

typedef signed char			s8;
typedef signed short		s16;
typedef signed int			s32;
typedef signed __int64		s64;
*/

typedef void* Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
/*
typedef struct
{
	float x;
	float y;
	float z;
} 
//Vector3;
*/
#ifndef NULL
#define NULL	0
#endif // NULL

typedef unsigned __int64 QWORD;

#endif // _COMMON_TYPES_