//vec.h
#include <stdio.h>
/*################################################################################
#                                  _          _           _                _                    #
#                                 /\ \    _ / /\         /\ \            /\ \                   #
#                                 \ \ \  /_/ / /        /  \ \          /  \ \                  #
#                                      \ \ \ \___\/        / /\ \ \        / /\ \ \                 #
#                                      / / /  \ \ \       / / /\ \_\      / / /\ \ \                #
#                                      \ \ \   \_\ \     / /_/_ \/_/     / / /  \ \_\               #
#                                       \ \ \  / / /    / /____/\       / / /    \/_/               #
#                                        \ \ \/ / /    / /\____\/      / / /                        #
#                                         \ \ \/ /    / / /______     / / /________                 #
#                                              \ \  /    / / /_______\   / / /_________\                #
#                                               \_\/     \/__________/   \/____________/                #
#                                                                               #
#                                                                               #
#                      @@@@@@@\  @@\   @@\                   @@\                                                        #
#                      @@  __@@\ \__|  @@ |                  \__|                           #
#                      @@ |  @@ |@@\ @@@@@@\   @@\  @@\  @@\ @@\  @@@@@@@\  @@@@@@\             #
#      @@@@@@\ @@@@@@@\ |@@ |\_@@  _|  @@ | @@ | @@ |@@ |@@  _____|@@  __@@\            #
#      \______|@@  __@@\ @@ |  @@ |    @@ | @@ | @@ |@@ |\@@@@@@\  @@@@@@@@ |           #
#                      @@ |  @@ |@@ |  @@ |@@\ @@ | @@ | @@ |@@ | \____@@\ @@   ____|           #
#                      @@@@@@@  |@@ |  \@@@@  |\@@@@@\@@@@  |@@ |@@@@@@@  |\@@@@@@@\            #
#                      \_______/ \__|   \____/  \_____\____/ \__|\_______/  \_______|           #
#                                                                               #
#################################################################################*/
typedef enum { X1, Y1, Z1 }vect0r3;

class Vector3
{
public:
	float x, y, z;
	~Vector3();
	void Add(vect0r3 xyz, float value, Vector3&a),
		Sub(vect0r3 xyz, float value, Vector3&a),
		Sub(Vector3&s),
		Copy(vect0r3 xyz, float out),
		Copy(Vector3&out),
		Combine(Vector3 &c),
		Combine(vect0r3 xyz, float value),
		OutputXYZ(const char*title, const char*colorHex),
		Insert(vect0r3 xyz, float value),
		Insert(Vector3&value),
		Insert(float xx, float yy, float zz),
		Null(),
		//Memory
		SetVector3(int address);
	Vector3 AnglesToForward(),
		VectorToAngles(),
		Scale(float scale),
		Inverse(),
		Snap(),
		Normalize(),
		Polar(float radius, float theta, float phi);
	float Distance(Vector3&vec),
		Length(),
		Dot(Vector3&vec),
		Dot(),
		Normalize(Vector3&n);
	bool Equal(Vector3&e),
		Equal(vect0r3 xyz, float value),
		Compare(Vector3&vec);
};
//vec.cpp
#include <math.h>
#include <stdio.h>

inline float Vector3::Normalize(Vector3&n)
{
	if (!sqrt(x*x + y*y + z*z)){ n.Null(); return 0.00; }
	n.x = (x*(1.0 / sqrt(x*x + y*y + z*z)));
	n.y = (y*(1.0 / sqrt(x*x + y*y + z*z)));
	n.z = (z*(1.0 / sqrt(x*x + y*y + z*z)));
	return sqrt(x*x + y*y + z*z);
}


inline Vector3 Vector3::Normalize()
{
	Vector3 vec;
	if (!sqrt(x*x + y*y + z*z)){ vec.Null(); return vec; }
	vec.x = (x*(1.0 / sqrt(x*x + y*y + z*z)));
	vec.y = (y*(1.0 / sqrt(x*x + y*y + z*z)));
	vec.z = (z*(1.0 / sqrt(x*x + y*y + z*z)));
	return vec;
}

inline Vector3 GetVector3(int address)
{
	Vector3 vec;
	vec.Insert(*(float*)(address), *(float*)(address + 4), *(float*)(address + 8));
	//return vec;
}

inline Vector3 Vector3::Snap()
{
	Vector3 vec;
	vec.Insert(floor(x + 0.5), floor(y + 0.5), floor(z + 0.5));
	return vec;
}

inline Vector3 Vector3::Polar(float radius, float theta, float phi)
{
	Vector3 vec;
	vec.Insert(radius*cos(theta)*cos(phi), radius*sin(theta)*cos(phi), radius*sin(phi));
	return vec;
}
inline void Vector3::SetVector3(int address)
{
	for (int i = 0; i < 3; i++) for (int f = 0; f <= 0xC; f += 0x4) *(float*)(address + f) = (&x)[i];
}

inline void Vector3::Null()
{
	x, y, z = 0;
}

inline Vector3 Vector3::Inverse()
{
	Vector3 vec; vec.Insert(-x, -y, -z); return vec;
}

inline void Vector3::Insert(float xx, float yy, float zz)
{
	x = xx, y = yy, z = zz;
}

inline Vector3 Vector3::Scale(float scale)
{
	Vector3 vec;
	for (int i = 0; i <= 2; i++) (&vec.x)[i] = ((&x)[i] * scale);
	return vec;
}

inline float Vector3::Dot(Vector3&vec)
{
	return (x*vec.x + y*vec.y + z*vec.z);
}

inline float Vector3::Dot()
{
	return (x*x + y*y + z*z);
}

inline float Vector3::Distance(Vector3&vec)
{
	Sub(vec);
	return Length();
}

inline void Vector3::Insert(vect0r3 xyz, float value)
{
	(&x)[xyz] = value;
}

inline void Vector3::Insert(Vector3&value)
{
	for (int i = 0; i <= 2; i++)
		(&x)[i] = (&value.x)[i];
}

inline float Vector3::Length()
{
	return (float)sqrt((x*x + y*y + z*z));
}

inline Vector3::~Vector3()
{
	x = 0, y = 0, z = 0;
}

inline void Vector3::Add(vect0r3 xyz, float value, Vector3&a = *(Vector3*)0)
{
	(&x)[xyz] += (!value ? (&a.x)[xyz] : value);
}

inline void Vector3::Sub(vect0r3 xyz, float value, Vector3&s = *(Vector3*)0)
{
	(&x)[xyz] -= (!value ? (&s.x)[xyz] : value);
}

inline void Vector3::Combine(Vector3 &c)
{
	for (int i = 0; i <= 2; i++)
		(&x)[i] += (&c.x)[i];
}

inline void Vector3::Combine(vect0r3 xyz, float value)
{
	(&x)[xyz] += value;
}

inline void Vector3::OutputXYZ(const char*title = "Vec3 Origins", const char*colorHex = "a")//Note this should only be used with CLI apps, unless you wanna comment out line 0-2
{
	//char buffer[0x20];
	//sprintf(buffer, "color %s", colorHex);
	//system(buffer);
	printf("======= %s ========\n\tX: %f\n\tY: %f\n\tZ: %f\n\n", title, x, y, z);
}


inline Vector3 Vector3::VectorToAngles()
{
	Vector3 vec3;
	float yaw, pitch;
	if (!x && !y)
	{
		yaw = 0;
		if (z > 0) pitch = 90; else pitch = 270;
	}
	else
	{
		yaw = atan2(y, z) * 180 / 3.14159265358979323846;
		if (yaw<0)yaw += 360;
		pitch = atan2(z, sqrt(x*x + y*y)) * 180 / 3.14159265358979323846;
		if (pitch<0)pitch += 360;
	}
	vec3.x = pitch;
	vec3.y = yaw;
	vec3.z = 0;
	return vec3;
}

inline bool Vector3::Equal(Vector3&e)
{
	return (x == e.x&&y == e.y&&z == e.z);
}

inline bool Vector3::Equal(vect0r3 xyz, float value)
{
	return ((&x)[xyz] == value);
}

inline bool Vector3::Compare(Vector3&vec)
{
	for (int i = 0; i < 3; i++)
		return (fabs((&x)[i] - (&vec.x)[i]) > 0.001);
}