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

#ifndef GNARLY_PINBALL_START_SPLASH
#define GNARLY_PINBALL_START_SPLASH

#include "../../geno/math/linear/GenoVector2.h"
#include "../../geno/math/linear/GenoVector4.h"
#include "../shaders/GlowShader.h"
#include "../Splash.h"
#include "../WallList.h"

Scene * loadSplash(GenoCamera2D * camera, GlowShader * glow) {
	uint32 numColors = 8;
	GenoVector4f * palette = new GenoVector4f[numColors] {
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 0.12156863, 0.14117648, 0.16078432, 1.0 },
		{ 0.43529412, 0.4745098, 0.5176471, 1.0 },
		{ 1.0, 0.28235295, 0.8392157, 1.0 },
		{ 0.93333334, 0.33333334, 0.2, 1.0 },
		{ 0.96862745, 0.5686275, 0.13333334, 1.0 },
		{ 0.0, 0.5882353, 0.0, 1.0 },
		{ 0.0, 0.5882353, 1.0, 1.0 }
	};

	uint32 numWalls = 11;
	WallList ** walls = new WallList*[numWalls] {
		new WallList(camera, palette, 
			new uint32[4] {
				0, 0, 0, 0
			},
			true, 4,
			new GenoVector2f[4] {
				{ 3.75, 3.75 },
				{ 1916.25, 3.75 },
				{ 1916.25, 1076.25 },
				{ 3.75, 1076.25 }
			}
		),
		new WallList(camera, palette, 
			new uint32[12] {
				3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
			},
			true, 12,
			new GenoVector2f[12] {
				{ 149.879, 350.969 },
				{ 237.625, 350.969 },
				{ 237.625, 263.224 },
				{ 325.37, 263.224 },
				{ 325.37, 350.969 },
				{ 413.116, 350.969 },
				{ 413.116, 438.715 },
				{ 325.37, 438.715 },
				{ 325.37, 526.461 },
				{ 237.625, 526.461 },
				{ 237.625, 438.715 },
				{ 149.879, 438.715 }
			}
		),
		new WallList(camera, palette, 
			new uint32[3] {
				4, 4, 4
			},
			false, 4,
			new GenoVector2f[4] {
				{ 588.109, 350.969 },
				{ 588.109, 155.604 },
				{ 711.103, 155.604 },
				{ 711.103, 350.969 }
			}
		),
		new WallList(camera, palette, 
			new uint32[5] {
				4, 4, 4, 4, 4
			},
			false, 6,
			new GenoVector2f[6] {
				{ 588.109, 438.715 },
				{ 588.109, 634.08 },
				{ 945.091, 634.08 },
				{ 945.091, 503.587 },
				{ 711.103, 503.587 },
				{ 711.103, 438.715 }
			}
		),
		new WallList(camera, palette, 
			new uint32[7] {
				5, 5, 5, 5, 5, 5, 5
			},
			false, 8,
			new GenoVector2f[8] {
				{ 1044.086, 350.969 },
				{ 1044.086, 155.604 },
				{ 1273.575, 155.604 },
				{ 1401.068, 286.098 },
				{ 1401.068, 503.587 },
				{ 1273.575, 634.08 },
				{ 1044.086, 634.08 },
				{ 1044.086, 438.715 }
			}
		),
		new WallList(camera, palette, 
			new uint32[7] {
				2, 2, 2, 2, 2, 2, 2
			},
			true, 7,
			new GenoVector2f[7] {
				{ 543.111, 350.969 },
				{ 1189.579, 350.969 },
				{ 1168.09, 286.098 },
				{ 1297.084, 394.842 },
				{ 1168.09, 503.587 },
				{ 1189.579, 438.715 },
				{ 543.111, 438.715 }
			}
		),
		new WallList(camera, palette, 
			new uint32[4] {
				6, 6, 6, 6
			},
			false, 4,
			new GenoVector2f[4] {
				{ 1590.361, 283.028 },
				{ 1590.361, 223.545 },
				{ 1649.844, 223.545 },
				{ 1649.844, 283.028 }
			}
		),
		new WallList(camera, palette, 
			new uint32[4] {
				6, 6, 6, 6
			},
			false, 4,
			new GenoVector2f[4] {
				{ 1590.361, 526.788 },
				{ 1590.361, 586.271 },
				{ 1649.844, 586.271 },
				{ 1649.844, 526.788 }
			}
		),
		new WallList(camera, palette, 
			new uint32[8] {
				6, 6, 6, 6, 6, 6, 6, 6
			},
			true, 8,
			new GenoVector2f[8] {
				{ 1620.103, 254.875 },
				{ 1727.103, 361.875 },
				{ 1620.103, 361.875 },
				{ 1727.103, 449.53 },
				{ 1620.103, 556.53 },
				{ 1513.103, 449.53 },
				{ 1620.103, 449.53 },
				{ 1513.103, 351.875 }
			}
		),
		new WallList(camera, palette, 
			new uint32[10] {
				4, 4, 4, 4, 4, 4, 4, 4, 4, 4
			},
			true, 10,
			new GenoVector2f[10] {
				{ 788.086, 712.846 },
				{ 847.522, 712.846 },
				{ 847.522, 802 },
				{ 906.957, 802 },
				{ 906.957, 712.846 },
				{ 966.393, 712.846 },
				{ 966.393, 950.589 },
				{ 906.957, 950.589 },
				{ 906.957, 861.436 },
				{ 788.086, 861.436 }
			}
		),
		new WallList(camera, palette, 
			new uint32[10] {
				5, 5, 5, 5, 5, 5, 5, 5, 5, 5
			},
			true, 10,
			new GenoVector2f[10] {
				{ 1017.772, 712.846 },
				{ 1077.208, 712.846 },
				{ 1077.208, 802 },
				{ 1136.643, 802 },
				{ 1136.643, 712.846 },
				{ 1196.079, 712.846 },
				{ 1196.079, 950.589 },
				{ 1136.643, 950.589 },
				{ 1136.643, 861.436 },
				{ 1017.772, 861.436 }
			}
		)
	};

	return new SplashScene(camera, glow, 1, "res/img/SplashBackground.png", numColors, palette, numWalls, walls);
}

#endif // GNARLY_PINBALL_START_SPLASH