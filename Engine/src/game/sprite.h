#pragma once

#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"

#include "Box2D/Box2D.h"

namespace prev {

	typedef unsigned int SpriteTextureID;

	struct SpriteColor {
		SpriteColor() : r(0), g(0), b(0), a(255) {}
		SpriteColor(Vec4 color) :
			r((unsigned char)(color.r * 255)),
			g((unsigned char)(color.g * 255)),
			b((unsigned char)(color.b * 255)),
			a((unsigned char)(color.a * 255)) {
		}
		void operator=(const Vec4 & color) {
			r = (unsigned char)(color.r * 255);
			g = (unsigned char)(color.g * 255);
			b = (unsigned char)(color.b * 255);
			a = (unsigned char)(color.a * 255);
		}
		Vec4 ToVec4() {
			Vec4 res;
			res.r = (float)r / 255.0f;
			res.g = (float)g / 255.0f;
			res.b = (float)b / 255.0f;
			res.a = (float)a / 255.0f;
			return res;
		}
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};

	struct Sprite {
		Vec2			Position		= Vec2(0.0f);					// Center
		float			Depth			= 0.0f;							// Used for Z buffering
		Vec2			Dimension		= Vec2(1.0f);					// Width-Height
		float			Rotation		= 0.0f;							// Degrees
		SpriteColor		Color			= SpriteColor(Vec4(1.0f));		// RGBA

		Vec2			Uvx				= Vec2(0.0f, 1.0f);				// Texture Coordinated in x direction x => left, y => right
		Vec2			Uvy				= Vec2(0.0f, 1.0f);				// Texture Coordinated in y direction x => bottom, y => top
	};

}
