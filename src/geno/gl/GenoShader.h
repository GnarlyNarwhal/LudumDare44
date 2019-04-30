/*******************************************************************************
 *
 * Copyright (c) 2018 Gnarly Narwhal
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

#ifndef GNARLY_GENOME_SHADER
#define GNARLY_GENOME_SHADER

#include "../GenoInts.h"

#include "../math/linear/GenoMatrix4.h"

#define GENO_SHADER_STRING_IS_SOURCE 0x00
#define GENO_SHADER_STRING_IS_PATH   0x01

class GenoShader {
	private:
		static int32 active;

		uint32 loadShader(const char * path, int32 type, bool file);
	protected:
		GenoShader(const char * vert, const char * frag, bool file);
		GenoShader(const char * vert, const char * geom, const char * frag, bool file);
		int32 program;
	public:
		void enable();
		void disable();
		virtual ~GenoShader();
};

class GenoMvpShader : public GenoShader {
	private:
		uint32 mvpLoc;
	protected:
		GenoMvpShader(const char * vert, const char * frag, bool file);
		GenoMvpShader(const char * vert, const char * frag, const char * geom, bool file);
	public:
		void setMvp(const GenoMatrix4f & mvp);
		void setMvp(const float * mvp);

};

#define GNARLY_GENOME_SHADER_FORWARD
#endif // GNARLY_GENOME_SHADER