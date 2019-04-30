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

#include "../geno/engine/GenoEngine.h"
#include "../geno/engine/GenoLoop.h"

#include "Splash.h"

SplashScene::SplashScene(GenoCamera2D * camera, GlowShader * glow, uint32 next, const char * path, uint32 numColors, GenoVector4f * palette, uint32 numWallLists, WallList ** walls) :
	Scene(camera, glow, next, path, numColors, palette, numWallLists, walls),
	overlay(new Rectangle(camera, { 0.0f, 0.0f }, { 1920, 1080 }, { 0, 0, 0, 1 })) {}

void SplashScene::update() {
	time += GenoEngine::getLoop()->getDelta();
	if (time < 1)
		alpha = time;
	else if (time >= 4)
		complete = true;
	else if (time > 3)
		alpha = 4 - time;
	else
		alpha = 1;
	overlay->setAlpha(1 - alpha);
}

void SplashScene::renderGlow() {
	for (uint32 i = 0; i < numWallLists; ++i)
		wallLists[i]->render();
}

void SplashScene::render() {
	for (uint32 i = 0; i < numWallLists; ++i)
		wallLists[i]->render();
	overlay->render();
}

SplashScene::~SplashScene() {}