#include <iostream>

namespace BBCF
{
	constexpr ::std::ptrdiff_t charIndex = 0x0034; //int
	constexpr ::std::ptrdiff_t sprite_img = 0x0D8; //int
	constexpr ::std::ptrdiff_t facingLeft = 0x0264; //int
	constexpr ::std::ptrdiff_t pos_x = 0x0268; //int
	constexpr ::std::ptrdiff_t pos_y = 0x026C; //int
	constexpr ::std::ptrdiff_t rotationDegrees = 0x027C; //int
	constexpr ::std::ptrdiff_t scaleX = 0x0284; //int
	constexpr ::std::ptrdiff_t scaleY = 0x0288; //int
	constexpr ::std::ptrdiff_t prevHP = 0x09D0; //int
	constexpr ::std::ptrdiff_t currHP = 0x09D4; //int
	constexpr ::std::ptrdiff_t maxHP = 0x09D8; //int
	constexpr ::std::ptrdiff_t lastAction = 0x1FF4; //char[20]
	constexpr ::std::ptrdiff_t currAction = 0x2070; //char[20]
	constexpr ::std::ptrdiff_t barrier = 0x5B04; //int
}