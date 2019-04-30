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

#include <iostream>
#include <algorithm>
#include <cmath>

#include "../geno/engine/GenoInput.h"
#include "../geno/shaders/GenoShader2c.h"

#include "WallList.h"

#include "WallDraw.h"

GenoShader2c * sshader;

void WallDraw::init() {
	sshader = new GenoShader2c();
}

void WallDraw::generateWall() {
	auto index = normals.getLength();
	auto segment = vertices[vertices.getLength() - 1] - vertices[vertices.getLength() - 2];
	normals.add(GenoVector2f{ -segment.y(), segment.x() }.normalize());

	const static uint32 INDICES[] = {
		0, 2, 3,
		0, 3, 5,
		0, 1, 2,
		5, 3, 4
	};
	GenoVector2f localNormal = setLength(normals[index], WallList::HALF_WALL_THICKNESS);
	auto vertexIndex = vertices.getLength() - 2;
	auto endPointBeg = (vertices[vertexIndex] - vertices[vertexIndex + 1]).setLength(WallList::HALF_WALL_THICKNESS);
	auto endPointEnd = (vertices[vertexIndex + 1] - vertices[vertexIndex]).setLength(WallList::HALF_WALL_THICKNESS);
	float verts[] = {
		vertices[vertexIndex    ].x() - localNormal.x(), vertices[vertexIndex    ].y() - localNormal.y(), 0,
		vertices[vertexIndex    ].x() + endPointBeg.x(), vertices[vertexIndex    ].y() + endPointBeg.y(), 0,
		vertices[vertexIndex    ].x() + localNormal.x(), vertices[vertexIndex    ].y() + localNormal.y(), 0,
		vertices[vertexIndex + 1].x() + localNormal.x(), vertices[vertexIndex + 1].y() + localNormal.y(), 0,
		vertices[vertexIndex + 1].x() + endPointEnd.x(), vertices[vertexIndex + 1].y() + endPointEnd.y(), 0,
		vertices[vertexIndex + 1].x() - localNormal.x(), vertices[vertexIndex + 1].y() - localNormal.y(), 0
	};

	walls.add(new GenoVao(6, verts, 12, INDICES));
}

void WallDraw::updateWall() {
	auto index = normals.getLength() - 1;
	auto segment = vertices[vertices.getLength() - 1] - vertices[vertices.getLength() - 2];
	normals[index] = (GenoVector2f{ -segment.y(), segment.x() }.normalize());

	const static uint32 INDICES[] = {
		0, 2, 3,
		0, 3, 5,
		0, 1, 2,
		5, 3, 4
	};
	GenoVector2f localNormal = setLength(normals[index], WallList::HALF_WALL_THICKNESS);
	auto vertexIndex = vertices.getLength() - 2;
	auto endPointBeg = (vertices[vertexIndex] - vertices[vertexIndex + 1]).setLength(WallList::HALF_WALL_THICKNESS);
	auto endPointEnd = (vertices[vertexIndex + 1] - vertices[vertexIndex]).setLength(WallList::HALF_WALL_THICKNESS);
	float verts[] = {
		vertices[vertexIndex    ].x() - localNormal.x(), vertices[vertexIndex    ].y() - localNormal.y(), 0,
		vertices[vertexIndex    ].x() + endPointBeg.x(), vertices[vertexIndex    ].y() + endPointBeg.y(), 0,
		vertices[vertexIndex    ].x() + localNormal.x(), vertices[vertexIndex    ].y() + localNormal.y(), 0,
		vertices[vertexIndex + 1].x() + localNormal.x(), vertices[vertexIndex + 1].y() + localNormal.y(), 0,
		vertices[vertexIndex + 1].x() + endPointEnd.x(), vertices[vertexIndex + 1].y() + endPointEnd.y(), 0,
		vertices[vertexIndex + 1].x() - localNormal.x(), vertices[vertexIndex + 1].y() - localNormal.y(), 0
	};

	walls[index]->rebuffer(0, 6, 3, verts);
}

WallDraw::WallDraw(GenoCamera2D * camera, GenoVector4f * palette, uint32 color) :
	palette(palette),
	color(color),
	camera(camera) {}

void WallDraw::update() {
		finishedWall = false;
	if (GenoInput::getMouseButtonState(GLFW_MOUSE_BUTTON_1) == GENO_INPUT_PRESSED) {
		vertices.add(GenoInput::getMouseCoords(camera));
		vertices.add(GenoInput::getMouseCoords(camera) + GenoVector2f{ 1, 1 });
		generateWall();
		drawing = true;
	}
	else if (GenoInput::getMouseButtonState(GLFW_MOUSE_BUTTON_1) > GENO_INPUT_PRESSED) {
		vertices[vertices.getLength() - 1] = GenoInput::getMouseCoords(camera);
		updateWall();
	}
	else if (GenoInput::getMouseButtonState(GLFW_MOUSE_BUTTON_1) == GENO_INPUT_RELEASED) {
		drawing = false;
		finishedWall = true;
	}
}

void WallDraw::render() {
	sshader->enable();
	sshader->setMvp(camera->getVPMatrix());
	for (uint32 i = 0; i < walls.getLength(); ++i) {
		sshader->setColor(palette[color]);
		walls[i]->render();
	}
}

void WallDraw::remove(uint32 index) {
	vertices.remove(index * 2, index * 2 + 1);
	normals.remove(index);
	delete walls[index];
	walls.remove(index);
}

bool WallDraw::skipLast() {
	return drawing;
}

bool WallDraw::wallCompleted() {
	return finishedWall;
}

WallDraw::~WallDraw() {
	for (uint32 i = 0; i < walls.getLength(); ++i)
		delete walls[i];
}
