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

#include "Rectangle.h"
#include "Pinball.h"

#include "Scene.h"

void Scene::init() {
	WallList::init();
	WallDraw::init();
	Pinball::init();
	Rectangle::init();
	Image::init();
}

Scene::Scene(GenoCamera2D * camera, GlowShader * glow, uint32 next, const char * path, uint32 numColors, GenoVector4f * palette, uint32 numWallLists, WallList ** walls) :
	numColors(numColors),
	glow(glow),
	palette(palette),
	numWallLists(numWallLists),
	wallLists(walls),
	next(next),
	background(new Image(camera, { 0.0f, 0.0f }, { 1920.0f, 1080.f }, path)) {}

bool Scene::isComplete() {
	return complete;
}

uint32 Scene::nextScene() {
	return next;
}

void Scene::bindBackground(uint8 unit) {
	background->getTexture()->bind(unit);
}

Scene::~Scene() {
	for (uint32 i = 0; i < numWallLists; ++i)
		delete wallLists[i];
	delete [] wallLists;
	delete [] palette;
	delete background;
}