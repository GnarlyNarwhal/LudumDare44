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

#include "../geno/shaders/GenoShader2c.h"

#include "WallList.h"

GenoShader2c * shader;

const float WallList::HALF_WALL_THICKNESS = 7.5f / 2.0f;

void WallList::init() {
	shader = new GenoShader2c();
}

void WallList::generateNormals() {
	for (uint32 i = 0; i < numWalls; ++i) {
		auto segment = vertices[i + 1] - vertices[i];
		normals[i] = GenoVector2f{ -segment.y(), segment.x() }.normalize();
	}

	auto average = vertices[0];
	for (uint32 i = 1; i < numWalls; ++i)
		average += vertices[i];
	average /= numVertices;
	const auto EXTERNAL_NEEDED = numWalls / 2;

	auto numExternal = uint32{ 0 };
	for (uint32 i = 0; i < numWalls && numExternal < EXTERNAL_NEEDED; ++i)
		numExternal += dot(normals[i], lerp(vertices[i] - average, vertices[i + 1] - average, 0.5)) < 0;

	if (numExternal >= EXTERNAL_NEEDED)
		for (uint32 i = 0; i < numWalls; ++i)
			normals[i] = -normals[i];
}

void WallList::generateWalls() {
	const uint32 INDICES[] = {
		0, 2, 3,
		0, 3, 5,
		0, 1, 2,
		5, 3, 4
	};
	for (uint32 i = 0; i < numWalls; ++i) {
		auto bisect1 = bisect(normals[i], normals[i - 1]);
		auto bisectLength1 = HALF_WALL_THICKNESS / sin(angleBetween(-bisect1, vertices[i + 1] - vertices[i]));
		auto bisect2 = bisect(normals[i], normals[i + 1]);
		auto bisectLength2 = HALF_WALL_THICKNESS / sin(angleBetween(-bisect2, vertices[i] - vertices[i + 1]));
		GenoVector2f localNormals[] = {
			bisect1.setLength(HALF_WALL_THICKNESS),
			bisect1.setLength(bisectLength1),
			bisect2.setLength(HALF_WALL_THICKNESS),
			bisect2.setLength(bisectLength2),
			setLength(normals[i], HALF_WALL_THICKNESS)
		};
		float verts[] = {
			vertices[i    ].x() - localNormals[1].x(), vertices[i    ].y() - localNormals[1].y(), 0,
			vertices[i    ].x() + localNormals[0].x(), vertices[i    ].y() + localNormals[0].y(), 0,
			vertices[i    ].x() + localNormals[4].x(), vertices[i    ].y() + localNormals[4].y(), 0,
			vertices[i + 1].x() + localNormals[4].x(), vertices[i + 1].y() + localNormals[4].y(), 0,
			vertices[i + 1].x() + localNormals[2].x(), vertices[i + 1].y() + localNormals[2].y(), 0,
			vertices[i + 1].x() - localNormals[3].x(), vertices[i + 1].y() - localNormals[3].y(), 0
		};
		if (!loop) {
			if (i == 0) {
				auto endPoint = (vertices[0] - vertices[1]).setLength(HALF_WALL_THICKNESS);
				verts[0] = vertices[0].x() - localNormals[4].x();
				verts[1] = vertices[0].y() - localNormals[4].y();
				verts[3] = vertices[0].x() + endPoint.x();
				verts[4] = vertices[0].y() + endPoint.y();
			}
			if (i == numWalls - 1) {
				auto endPoint = (vertices[numVertices - 1] - vertices[numVertices - 2]).setLength(HALF_WALL_THICKNESS);
				verts[12] = vertices[numVertices - 1].x() + endPoint.x();
				verts[13] = vertices[numVertices - 1].y() + endPoint.y();
				verts[15] = vertices[numVertices - 1].x() - localNormals[4].x();
				verts[16] = vertices[numVertices - 1].y() - localNormals[4].y();
			}
		}
		walls[i] = new GenoVao(6, verts, 12, INDICES);
	}
}

WallList::WallList(GenoCamera2D * camera, GenoVector4f * palette, uint32 * colors, bool loop, uint32 numVertices, GenoVector2f * vertices) :
	palette(palette),
	colors(colors),
	camera(camera),
	loop(loop),
	numVertices(numVertices),
	numWalls(numVertices - !loop),
	vertices(numVertices, vertices),
	normals(numWalls),
	walls(numWalls) {
	generateNormals();
	generateWalls();
	checkBounds();
}

void WallList::checkBounds() {
	for (uint32 i = 0; i < numVertices; ++i) {
		if (vertices[i].x() < vertices[bounds.left].x())
			bounds.left = i;
		else if (vertices[i].x() > vertices[bounds.right].x())
			bounds.right = i;
		if (vertices[i].y() < vertices[bounds.top].y())
			bounds.top = i;
		else if (vertices[i].y() > vertices[bounds.bottom].y())
			bounds.bottom = i;
	}
}

GenoVector4f WallList::getBounds() {
	return {
		vertices[bounds.left  ].x(),
		vertices[bounds.top   ].y(),
		vertices[bounds.right ].x(),
		vertices[bounds.bottom].y()
	};
}

GenoVector4f WallList::getBounds(uint32 index) {
	return {
		std::min(vertices[index].x(), vertices[index + 1].x()),
		std::min(vertices[index].y(), vertices[index + 1].y()),
		std::max(vertices[index].x(), vertices[index + 1].x()),
		std::max(vertices[index].y(), vertices[index + 1].y())
	};
}

void WallList::render() {
	shader->enable();
	shader->setMvp(camera->getVPMatrix());
	for (uint32 i = 0; i < numWalls; ++i) {
		shader->setColor(palette[colors[i]]);
		walls[i]->render();
	}
}

WallList::~WallList() {
	for (uint32 i = 0; i < numWalls; ++i)
		delete walls[i];
}
