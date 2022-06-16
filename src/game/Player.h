#pragma once

struct Point {
public:
	int X, Y;
};

class Player{
public:
	std::uintptr_t ObjectBase;
	std::uintptr_t SpritePtr;

	Point Position;

	int Health;
	int MaxHealth;
	int PrevHealth;
	
	bool FacingLeft;
	char cActionChar[20];
	std::string cAction;
	char cSprite[12];
	int CharIndex;
	int Distance;
};

inline Player p1;
inline Player p2;
inline bool run = true;