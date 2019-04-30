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
#include "../geno/engine/GenoInput.h"
#include "../geno/math/GenoConstants.h"

#include "Info.h"

Image * Info::next;
Image * Info::border;
Rectangle * Info::overlay;

void Info::init(GenoCamera2D * camera) {
	next = new Image(camera, { 1324.471, 980.964 }, { 536.973, 68.997 }, "res/img/Continue.png");
	border = new Image(camera, { 0.0f, 0.0f }, { 1920.0f, 1080.f }, "res/img/InfoBorder.png");
	overlay = new Rectangle(camera, { 0.0f, 0.0f }, { 1920, 1080 }, { 0, 0, 0, 1 });
}

Info::Info(GenoCamera2D * camera, GlowShader * glow, uint32 next, const char * info, const char * infoGlow) :
	Scene(camera, glow, next, info, 0, 0, 0, 0),
	glowImage(new Image(camera, { 0.0f, 0.0f }, { 1920.0f, 1080.f }, infoGlow)) {}

void Info::update() {
	if (state == FADE_IN) {
		overlayTime += GenoEngine::getLoop()->getDelta();
		if (overlayTime > 1) {
			state = WAITING;
			overlayTime = 0;
			overlay->setAlpha(0);
		}
		else
			overlay->setAlpha(1 - overlayTime);
	}
	else if (state == WAITING) {
		time += GenoEngine::getLoop()->getDelta() * 2.23;
		if (time > GENO_TAU<float>)
			time -= GENO_TAU<float>;
		next->position.x() = 1324.471 + sin(time) * 15;
		if (GenoInput::getKeyState(GLFW_KEY_R) == GENO_INPUT_PRESSED)
			state = FADE_OUT;
	}
	else if (state == FADE_OUT) {
		overlayTime += GenoEngine::getLoop()->getDelta();
		if (overlayTime > 1)
			complete = true;
		overlay->setAlpha(overlayTime);
	}
}

void Info::renderGlow() {
	glowImage->render();
	border->render();
}

void Info::render() {
	glowImage->render();
	next->render();
	border->render();
	overlay->render();
}

Info::~Info() {
	delete glowImage;
}