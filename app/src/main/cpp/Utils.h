#include <raylib.h>
#include <math.h>

#pragma once

#ifdef PLATFORM_WEB

    #include <emscripten/emscripten.h>
    #include <emscripten/val.h>
    #include <emscripten/bind.h>

#endif

class Utils
{
public:
	static float magnitude(Vector2 v)
	{
		float magnitude = sqrt((v.x * v.x) + (v.y * v.y));

		return magnitude;
	}

	#ifdef PLATFORM_WEB
		static int GetLocal(const std::string& key)
		{
			emscripten::val localStorage = emscripten::val::global("localStorage");
			emscripten::val item = localStorage.call<emscripten::val>("getItem", key);

			return item.as<int>();
		}

		static void SetLocal(const std::string& key, int value)
		{
			emscripten::val localStorage = emscripten::val::global("localStorage");
			emscripten::val item = localStorage.call<emscripten::val>("setItem", key, std::to_string(value));
		}
	#endif
};