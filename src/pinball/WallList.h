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

#ifndef GNARLY_PINBALL_WALL_LIST
#define GNARLY_PINBALL_WALL_LIST

#include "../geno/GenoInts.h"
#include "../geno/template/GenoArrayLoop.h"
#include "../geno/math/linear/GenoVector2.h"
#include "../geno/math/linear/GenoVector4.h"
#include "../geno/engine/GenoCamera2D.h"
#include "../geno/gl/GenoVao.h"

class WallList {
	private:
		struct Bounds {
			uint32 left;
			uint32 right;
			uint32 top;
			uint32 bottom;
		};
		
		GenoVector4f * palette;
		uint32 * colors;

		GenoCamera2D * camera;
		Bounds bounds;
		bool loop;

		void generateNormals();
		void generateWalls();
	public:
		const static float HALF_WALL_THICKNESS;

		static void init();
		
		uint32 numVertices;
		uint32 numWalls;
		GenoArrayLoop<GenoVector2f> vertices;
		GenoArrayLoop<GenoVector2f> normals;
		GenoArrayLoop<GenoVao*> walls;

		WallList(GenoCamera2D * camera, GenoVector4f * palette, uint32 * colors, bool loop, uint32 numVertices, GenoVector2f * vertices);
		void checkBounds();
		GenoVector4f getBounds();
		GenoVector4f getBounds(uint32 index);
		void render();
		~WallList();
};

#define GNARLY_PINBALL_WALL_LIST_FORWARD
#endif // GNARLY_PINBALL_WALL_LIST