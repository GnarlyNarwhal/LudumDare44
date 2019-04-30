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

#include "../geno/GenoMacros.h"

#include "Pinball.h"

const float Pinball::RADIUS = 25;
GenoTexture2D * Pinball::texture;
GenoVao * Pinball::vao;
MixShader * Pinball::shader;

void Pinball::init() {
	uint32 textureParams[] = {
		GL_TEXTURE_MIN_FILTER, GL_LINEAR,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR,
		GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE,
		GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE
	};

	GenoTexture2DCreateInfo textureInfo = {};
	textureInfo.type      = GENO_TEXTURE2D_TYPE_PNG;
	textureInfo.texture   = "res/img/Pinball.png";
	textureInfo.numParams = GENO_ARRAY_SIZE(textureParams) / 2;
	textureInfo.params    = textureParams;

	texture = GenoTexture2D::create(textureInfo);

	shader = new MixShader();

	float vertices[] = {
		 1, -1, 0, // Top left
		 1,  1, 0, // Bottom left
		-1,  1, 0, // Bottom right
		-1, -1, 0  // Top right
	};
	uint32 indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	float texCoords[] = {
		1, 0,
		1, 1,
		0, 1,
		0, 0
	};
	vao = new GenoVao(4, vertices, 6, indices);
	vao->addAttrib(4, 2, texCoords);
}

Pinball::Pinball(GenoCamera2D * camera, GenoVector4f * palette, uint32 color, const GenoVector2f & position, const GenoVector2f & velocity) :
	camera(camera),
	palette(palette),
	color(color),
	position(position),
	velocity(velocity) {}

void Pinball::render() {
	texture->bind();
	shader->enable();
	shader->setColor(palette[color]);
	shader->setMvp(translate2D(camera->getVPMatrix(), position).rotate2D(rotation).scale(RADIUS));
	vao->render();
}

Pinball::~Pinball() {}