#pragma once


class Game {
public:
	Game() {
	}
	~Game() {
	}
	bool Init();
	void HandleEvents();
	bool LoadMedia();
	static void Close();
};