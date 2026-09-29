#include <vector>
#include "Entity.h"

#pragma once

inline int score;

class Game
{
public:
		
	enum State
	{
		MENU,
		GAME
	};

	static inline int WIDTH;
	static inline int HEIGHT;
	static inline RenderTexture2D GameTexture;
	inline static State state;

	static inline int high_score;

	static void Init();
	static void Setup();
	static void Update();
	static void Draw();
};