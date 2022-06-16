#include "modules/modules.h"
#include "mem/memory.h"
#include "game/Player.h"

using namespace std;

string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

void init()
{
	std::thread{ modules::console }.detach();
}

int main()
{


	procId = GetProcId(L"BBCF.exe");


	if (procId == 0) {
		return 1;
	}

	moduleBase = GetModuleBaseAddress(procId, L"BBCF.exe");
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	init();

	while (run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		p1.ObjectBase = FindDMAAddy(hProcess, (moduleBase + 0x8609A0), { 0x0 });
		ReadProcessMemory(hProcess, (LPVOID)(p1.ObjectBase + BBCF::pos_x), &p1.Position.X, sizeof(p1.Position.X), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p1.ObjectBase + BBCF::pos_y), &p1.Position.Y, sizeof(p1.Position.Y), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p1.ObjectBase + BBCF::facingLeft), &p1.FacingLeft, sizeof(p1.FacingLeft), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p1.ObjectBase + BBCF::currHP), &p1.Health, sizeof(p1.Health), nullptr);
		p1.SpritePtr = FindDMAAddy(hProcess, (p1.ObjectBase + 0xD8), { 0x0 });
		ReadProcessMemory(hProcess, (LPVOID)(p1.SpritePtr), &p1.cSprite, sizeof(p1.cSprite), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p1.ObjectBase + BBCF::currAction), &p1.cActionChar, sizeof(p1.cActionChar), nullptr);
		p1.cAction = convertToString(p1.cActionChar, (sizeof(p1.cActionChar) / sizeof(char)));

		p2.ObjectBase = FindDMAAddy(hProcess, (moduleBase + 0x8609A4), { 0x0 });
		ReadProcessMemory(hProcess, (LPVOID)(p2.ObjectBase + BBCF::pos_x), &p2.Position.X, sizeof(p2.Position.X), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p2.ObjectBase + BBCF::pos_y), &p2.Position.Y, sizeof(p2.Position.Y), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p2.ObjectBase + BBCF::facingLeft), &p2.FacingLeft, sizeof(p2.FacingLeft), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p2.ObjectBase + BBCF::currHP), &p2.Health, sizeof(p2.Health), nullptr);
		p2.SpritePtr = FindDMAAddy(hProcess, (p2.ObjectBase + 0xD8), { 0x0 });
		ReadProcessMemory(hProcess, (LPVOID)(p2.SpritePtr), &p2.cSprite, sizeof(p2.cSprite), nullptr);
		ReadProcessMemory(hProcess, (LPVOID)(p2.ObjectBase + BBCF::currAction), &p2.cActionChar, sizeof(p2.cActionChar), nullptr);
		p2.cAction = convertToString(p2.cActionChar, (sizeof(p2.cActionChar) / sizeof(char)));

		p1.Distance = floor(abs((p1.Position.X + 1865000) - (p2.Position.X + 1865000)));

		if (GetAsyncKeyState(VK_DIVIDE)) {
			int p1reset = -260000;
			int p2reset = 260000;
			for (int i = 0; i < 50; i++) {
				WriteProcessMemory(hProcess, (LPVOID)(p1.ObjectBase + BBCF::pos_x), &p1reset, sizeof(p1reset), nullptr);
				WriteProcessMemory(hProcess, (LPVOID)(p2.ObjectBase + BBCF::pos_x), &p2reset, sizeof(p2reset), nullptr);
				this_thread::sleep_for(chrono::milliseconds(1));
			}
		}

	}

	return 0;
}