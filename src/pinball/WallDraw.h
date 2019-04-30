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

#ifndef GNARLY_PINBALL_WALL_DRAW
#define GNARLY_PINBALL_WALL_DRAW

#include "../geno/GenoInts.h"
#include "../geno/template/GenoArrayList.h"
#include "../geno/math/linear/GenoVector2.h"
#include "../geno/math/linear/GenoVector4.h"
#include "../geno/engine/GenoCamera2D.h"
#include "../geno/gl/GenoVao.h"

class WallDraw {
	private:		
		GenoVector4f * palette;
		uint32 color;

		GenoCamera2D * camera;
		bool loop;

		void generateWall();
		void updateWall();

		bool drawing;
		bool finishedWall;

	public:
		static void init();

		GenoArrayList<GenoVector2f> vertices;
		GenoArrayList<GenoVector2f> normals;
		GenoArrayList<GenoVao*> walls;

		WallDraw(GenoCamera2D * camera, GenoVector4f * palette, uint32 color);
		void update();
		void render();
		void remove(uint32 index);
		bool skipLast();
		bool wallCompleted();
		~WallDraw();
};

#define GNARLY_PINBALL_WALL_DRAW_FORWARD
#endif // GNARLY_PINBALL_WALL_DRAW