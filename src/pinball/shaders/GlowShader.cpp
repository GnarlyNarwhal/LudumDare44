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

#include <iostream>

#include "../../geno/gl/GenoGL.h"

#include "GlowShader.h"

GlowShader::GlowShader() :
	GenoMvpShader("res/shaders/GlowShader/GlowShaderv.gls",
	              "res/shaders/GlowShader/GlowShaderf.gls",
	               GENO_SHADER_STRING_IS_PATH) {

	resolutionLoc = glGetUniformLocation(program, "resolution");
	horizontalLoc = glGetUniformLocation(program, "horizontal");
	brightnessLoc = glGetUniformLocation(program, "brightness");
	distanceLoc   = glGetUniformLocation(program, "distance");

	uint32 texLoc        = glGetUniformLocation(program, "tex");
	uint32 backgroundLoc = glGetUniformLocation(program, "background");
	
	enable();
	glUniform1i(texLoc,        0);
	glUniform1i(backgroundLoc, 1);
}

void GlowShader::setResolution(float width, float height) {
	glUniform2f(resolutionLoc, width, height);
}

void GlowShader::setHorizontal(bool horizontal) {
	glUniform1i(horizontalLoc, horizontal);
}

void GlowShader::setBrightness(float brightness) {
	glUniform1f(brightnessLoc, brightness);
}

void GlowShader::setDistance(float distance) {
	glUniform1f(distanceLoc, distance);
}

GlowShader::~GlowShader() {}