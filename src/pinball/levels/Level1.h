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

#ifndef GNARLY_PINBALL_LEVEL1
#define GNARLY_PINBALL_LEVEL1

#include "../../geno/math/linear/GenoVector2.h"
#include "../../geno/math/linear/GenoVector4.h"
#include "../shaders/GlowShader.h"
#include "../Intro.h"
#include "../WallList.h"

Scene * loadLevel1(GenoCamera2D * camera, GlowShader * glow) {
	uint32 numColors = 4;
	GenoVector4f * palette = new GenoVector4f[numColors] {
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 0.0, 0.0, 0.8, 1.0 },
		{ 0.0, 1.0, 0.5686275, 1.0 },
		{ 0.8, 0.0, 0.0, 1.0 }
	};

	uint32 numWalls = 4;
	WallList ** walls = new WallList*[numWalls] {
		new WallList(camera, palette, 
			new uint32[4] {
				1, 1, 1, 1
			},
			true, 4,
			new GenoVector2f[4] {
				{ 3.75, 3.75 },
				{ 1388.346, 3.75 },
				{ 963.75, 428.346 },
				{ 3.75, 428.346 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				1, 1, 1
			},
			true, 3,
			new GenoVector2f[3] {
				{ 1916.75, 670.431 },
				{ 1916.25, 942.5 },
				{ 1647.931, 942.5 }
			}
		),
		new WallList(camera, palette, 
			new uint32[4] {
				0, 0, 0, 0
			},
			true, 4,
			new GenoVector2f[4] {
				{ 3.75, 3.75 },
				{ 1916.25, 3.75 },
				{ 1916.25, 942.25 },
				{ 3.75, 942.25 }
			}
		),
		new WallList(camera, palette, 
			new uint32[4] {
				2, 2, 2, 2
			},
			true, 4,
			new GenoVector2f[4] {
				{ 1494.4, 36.087 },
				{ 1427.572, 102.915 },
				{ 1573.852, 249.196 },
				{ 1640.681, 182.367 }
			}
		)
	};

	return new Level(camera, glow, 5, 4, "res/img/Level1.png", numColors, palette, numWalls, walls, 6, 0, 3, { 184.5, 724.793 }, { 300, 0 });
}

#define GNARLY_PINBALL_LEVEL1_FORWARD
#endif // GNARLY_PINBALL_LEVEL1