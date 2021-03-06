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

#include "../gl/GenoGL.h"

#include "GenoShader2c.h"

GenoShader2c::GenoShader2c() :
	GenoMvpShader("res/shaders/Shader2c/Shader2cv.gls",
	              "res/shaders/Shader2c/Shader2cf.gls",
	               GENO_SHADER_STRING_IS_PATH) {
	colorLoc = glGetUniformLocation(program, "inputColor");
}

void GenoShader2c::setColor(float r, float g, float b, float a) {
	glUniform4f(colorLoc, r, g, b, a);
}

void GenoShader2c::setColor(const GenoVector4f & color) {
	glUniform4f(colorLoc, color.x(), color.y(), color.z(), color.w());
}

GenoShader2c::~GenoShader2c() {}