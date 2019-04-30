/*******************************************************************************
 *
 * Copyright (c) 2019 Gnarly Narwhal
 *
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef GNARLY_PINBALL_INTRO
#define GNARLY_PINBALL_INTRO

#include "../geno/math/linear/GenoVector4.h"
#include "../geno/engine/GenoCamera2D.h"
#include "../geno/audio/GenoAudioBuffer.h"
#include "../geno/audio/GenoAudioSource.h"

#include "shaders/GlowShader.h"

#include "Scene.h"
#include "Rectangle.h"
#include "Pinball.h"
#include "WallList.h"
#include "WallDraw.h"

class Intro : public Scene {
	private:
		const static uint32 FADE_IN   = 0;
		const static uint32 STARTING  = 1;
		const static uint32 IN_MOTION = 2;
		const static uint32 FADE_OUT  = 3;
		
		static Image * startingGlow;
		static Image * startingNonglow;
		static Rectangle * overlay;

		WallDraw * wallDraw;
		Pinball * pinball;

		uint32 reset;
		uint32 state;
		float time;
	public:
		static void init(GenoCamera2D * camera);

		Intro(GenoCamera2D * camera, GlowShader * glow, uint32 next, uint32 reset, const char * path, uint32 numColors, GenoVector4f * palette, uint32 numWallLists, WallList ** walls, uint32 wallDrawColor, uint32 ballColor, const GenoVector2f & ballStart, const GenoVector2f & ballVelocity);
		virtual void update();
		virtual void renderGlow();
		virtual void render();
		virtual ~Intro();
};

#define GNARLY_PINBALL_INTRO_SCENE
#endif // GNARLY_PINBALL_INTRO