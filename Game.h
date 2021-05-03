#pragma once


class Game {
public:
	Game() {
	}
	~Game() {
	}
	static bool Init();
	static void HandleEvents();
	static bool LoadMedia();
	static void Close();
};