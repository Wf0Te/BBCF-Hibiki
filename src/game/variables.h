#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <initializer_list>

inline struct var
{
	bool run = true;
	bool isPlayer1 = true;
	int displayMode = 0;
	int frameCount;
	int enemyInput;
	float distance;
}v;

inline std::map<int, int> directions = { {8, 0x57 }, {4, 0x41}, {2, 0x53}, {6, 0x44} };
inline std::map<char, int> buttons = { {'a', VK_NUMPAD7 }, {'b', VK_NUMPAD8}, {'c', VK_NUMPAD9}, {'d', VK_NUMPAD4}, {'fr', 0x45}, {'br', 0x51} };