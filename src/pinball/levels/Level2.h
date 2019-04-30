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

#ifndef GNARLY_PINBALL_LEVEL2
#define GNARLY_PINBALL_LEVEL2

#include "../../geno/math/linear/GenoVector2.h"
#include "../../geno/math/linear/GenoVector4.h"
#include "../shaders/GlowShader.h"
#include "../Intro.h"
#include "../WallList.h"

Scene * loadLevel2(GenoCamera2D * camera, GlowShader * glow) {
	uint32 numColors = 9;
	GenoVector4f * palette = new GenoVector4f[numColors] {
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 0.07058824, 0.34901962, 0.23137255, 1.0 },
		{ 0.0, 0.78431374, 1.0, 1.0 },
		{ 0.0, 0.6, 1.0, 1.0 },
		{ 0.0, 0.46666667, 1.0, 1.0 },
		{ 0.0, 0.33333334, 1.0, 1.0 },
		{ 0.36078432, 0.36078432, 0.36078432, 1.0 },
		{ 0.7019608, 0.7019608, 0.7019608, 1.0 },
		{ 1.0, 0.1, 0.1, 1.0 }
	};

	uint32 numWalls = 15;
	WallList ** walls = new WallList*[numWalls] {
		new WallList(camera, palette, 
			new uint32[2] {
				6, 6
			},
			false, 2,
			new GenoVector2f[2] {
				{ 492.279, 521.25 },
				{ 492.279, 942.25 }
			}
		),
		new WallList(camera, palette, 
			new uint32[2] {
				0, 0
			},
			false, 2,
			new GenoVector2f[2] {
				{ 1262.104, 521.25 },
				{ 1262.104, 942.25 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				2, 2, 2
			},
			true, 3,
			new GenoVector2f[3] {
				{ 226.953, 194.972 },
				{ 313.556, 194.972 },
				{ 270.255, 269.972 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				3, 3, 3
			},
			true, 3,
			new GenoVector2f[3] {
				{ 671.015, 194.972 },
				{ 757.617, 194.972 },
				{ 714.316, 269.972 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				4, 4, 4
			},
			true, 3,
			new GenoVector2f[3] {
				{ 996.834, 194.972 },
				{ 1083.437, 194.972 },
				{ 1040.136, 269.972 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				5, 5, 5
			},
			true, 3,
			new GenoVector2f[3] {
				{ 1440.896, 194.972 },
				{ 1527.498, 194.972 },
				{ 1484.197, 269.972 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				6, 6, 6
			},
			true, 3,
			new GenoVector2f[3] {
				{ 448.978, 521.25 },
				{ 492.279, 446.25 },
				{ 535.581, 521.25 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				7, 7, 7
			},
			true, 3,
			new GenoVector2f[3] {
				{ 833.89, 422.583 },
				{ 920.492, 422.583 },
				{ 877.191, 497.583 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				0, 0, 0
			},
			true, 3,
			new GenoVector2f[3] {
				{ 1218.802, 521.25 },
				{ 1262.104, 446.25 },
				{ 1305.405, 521.25 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				2, 2, 2
			},
			true, 3,
			new GenoVector2f[3] {
				{ 226.953, 750.288 },
				{ 313.556, 750.288 },
				{ 270.255, 675.288 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				3, 3, 3
			},
			true, 3,
			new GenoVector2f[3] {
				{ 612.989, 750.288 },
				{ 699.592, 750.288 },
				{ 656.29, 675.288 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				4, 4, 4
			},
			true, 3,
			new GenoVector2f[3] {
				{ 1055.955, 750.288 },
				{ 1142.558, 750.288 },
				{ 1099.256, 675.288 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				5, 5, 5
			},
			true, 3,
			new GenoVector2f[3] {
				{ 1440.896, 750.288 },
				{ 1527.498, 750.288 },
				{ 1484.197, 675.288 }
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
			new uint32[3] {
				1, 1, 1
			},
			true, 3,
			new GenoVector2f[3] {
				{ 1647.014, 404.503 },
				{ 1647.014, 537.997 },
				{ 1762.622, 471.25 }
			}
		)
	};

	return new Level(camera, glow, 6, 5, "res/img/Level2.png", numColors, palette, numWalls, walls, 9.5f, 0, 8, { 107.366, 471.25 }, { 400, 0 });
}

#define GNARLY_PINBALL_LEVEL2_FORWARD
#endif // GNARLY_PINBALL_LEVEL2