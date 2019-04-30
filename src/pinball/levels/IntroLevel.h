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

#ifndef GNARLY_PINBALL_INTRO_LEVEL
#define GNARLY_PINBALL_INTRO_LEVEL

#include "../../geno/math/linear/GenoVector2.h"
#include "../../geno/math/linear/GenoVector4.h"
#include "../shaders/GlowShader.h"
#include "../Intro.h"
#include "../WallList.h"

Scene * loadIntroLevel(GenoCamera2D * camera, GlowShader * glow) {
	uint32 numColors = 4;
	GenoVector4f * palette = new GenoVector4f[numColors] {
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 1.0, 0.5176471, 0.85490197, 1.0 },
		{ 0.0, 1.0, 0.5686275, 1.0 },
		{ 0.17254902, 0.7019608, 0.83137256, 1.0 }

	};

	uint32 numWalls = 5;
	WallList ** walls = new WallList*[numWalls] {
		new WallList(camera, palette, 
			new uint32[3] {
				1, 1, 1
			},
			true, 3,
			new GenoVector2f[12] {
				{ 691.75, 3.5 },
				{ 1228.25, 3.5 },
				{ 1228.25, 540 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				1, 1, 1
			},
			true, 3,
			new GenoVector2f[12] {
				{ 691.75, 540 },
				{ 1228.25, 1076.5 },
				{ 691.75, 1076.5 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				1, 1, 1
			},
			true, 3,
			new GenoVector2f[12] {
				{ 1916.5, 540 },
				{ 1380, 1076.5 },
				{ 1916.5, 1076.5 }
			}
		),
		new WallList(camera, palette, 
			new uint32[4] {
				0, 0, 0, 0
			},
			true, 4,
			new GenoVector2f[4] {
				{ 3.5, 3.5 },
				{ 1916.5, 3.5 },
				{ 1916.5, 1076.5 },
				{ 3.5, 1076.5 }
			}
		),
		new WallList(camera, palette, 
			new uint32[4] {
				2, 2, 2, 2
			},
			true, 4,
			new GenoVector2f[12] {
				{ 1511.946, 164.803 },
				{ 1511.946, 237.412 },
				{ 1784.554, 237.412 },
				{ 1784.554, 164.803 }
			}
		)
	};

	return new Intro(camera, glow, 3, 2, "res/img/IntroLevel.png", numColors, palette, numWalls, walls, 0, 3, { 271.75, 808.25 }, { 0.0f, -300 });
}

#define GNARLY_PINBALL_INTRO_LEVEL_FORWARD
#endif // GNARLY_PINBALL_INTRO_LEVEL