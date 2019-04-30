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

#ifndef GNARLY_PINBALL_SCENE
#define GNARLY_PINBALL_SCENE

#include "../geno/math/linear/GenoVector4.h"
#include "../geno/engine/GenoCamera2D.h"
#include "../geno/audio/GenoAudioBuffer.h"
#include "../geno/audio/GenoAudioSource.h"

#include "shaders/GlowShader.h"

#include "Image.h"
#include "WallList.h"
#include "WallDraw.h"

class Scene {
	protected:
		Image * background;

		uint32 numColors;
		GenoVector4f * palette;

		GlowShader * glow;

		uint32 numWallLists;
		WallList ** wallLists;

		bool complete;
		uint32 next;

	public:
		static void init();

		Scene(GenoCamera2D * camera, GlowShader * glow, uint32 next, const char * path, uint32 numColors, GenoVector4f * palette, uint32 numWallLists, WallList ** walls);
		virtual void update() = 0;
		virtual void renderGlow() = 0;
		virtual void render() = 0;
		bool isComplete();
		uint32 nextScene();
		void bindBackground(uint8 unit);
		virtual ~Scene();
};

#define GNARLY_PINBALL_SCENE
#endif // GNARLY_PINBALL_SCENE