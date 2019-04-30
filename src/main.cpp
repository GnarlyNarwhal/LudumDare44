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
#include <chrono>

#include "geno/GenoInts.h"
#include "geno/GenoMacros.h"

#include "geno/math/linear/GenoMatrix4.h"
#include "geno/thread/GenoTime.h"
#include "geno/engine/GenoEngine.h"
#include "geno/engine/GenoLoop.h"
#include "geno/engine/GenoInput.h"
#include "geno/engine/GenoWindow.h"
#include "geno/engine/GenoCamera2D.h"
#include "geno/gl/GenoGL.h"
#include "geno/gl/GenoFramebuffer.h"
#include "geno/gl/GenoVao.h"
#include "geno/shaders/GenoShader2c.h"
#include "geno/audio/GenoAudioDevice.h"
#include "geno/audio/GenoAudioSource.h"
#include "geno/audio/GenoAudioBuffer.h"

#include "pinball/shaders/GlowShader.h"
#include "pinball/Scene.h"
#include "pinball/Image.h"
#include "pinball/Intro.h"
#include "pinball/Level.h"

#include "pinball/levels/StartSplash.h"
#include "pinball/levels/Info1.h"
#include "pinball/levels/IntroLevel.h"
#include "pinball/levels/Info2.h"
#include "pinball/levels/Level1.h"
#include "pinball/levels/Level2.h"
#include "pinball/levels/Win.h"

bool init();
void begin();
void loop();
void load(uint32 level);
void update();
void render();
void cleanup();

bool toggle = true;

GenoWindow * window;
GenoCamera2D * camera;

GenoFramebuffer * framebuffer1;
GenoFramebuffer * framebuffer2;
GlowShader * glow;
GenoVao * vao;

GenoAudioSource * source;
GenoAudioBuffer * audio;

Image * image;

Scene * scene;

int32 main(int32 argc, char ** argv) {

	init();
	begin();
	cleanup();

	/////// TIME TRIALS - LEAVE FOR FUTURE USE ///////
/*
	const uint32 NUM_ITERATIONS = 1000000;
	
	auto begin1 = std::chrono::high_resolution_clock::now();
	auto end1 = std::chrono::high_resolution_clock::now();

	auto begin2 = std::chrono::high_resolution_clock::now();
	auto end2 = std::chrono::high_resolution_clock::now();
	
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << std::endl;
*/
	return 0;
}

bool init() {
	GenoEngine::init();
	
	GenoMonitor * monitor = GenoMonitors::getPrimaryMonitor();
	GenoVideoMode * videoMode = monitor->getDefaultVideoMode();

	GenoLoopCreateInfo loopInfo = {};
	loopInfo.targetFps   = videoMode->getRefreshRate();
	loopInfo.deltaScale  = 1;
	loopInfo.callback    = loop;
	loopInfo.numSubLoops = 0;
	loopInfo.subLoops    = 0;

	GenoEngine::setLoop(loopInfo);

	int32 winHints[] = {
		GLFW_CONTEXT_VERSION_MAJOR, 3,
		GLFW_CONTEXT_VERSION_MINOR, 3,
		GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE,
		GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE,
		GLFW_SAMPLES, 4
	};

	GenoWindowCreateInfo winInfo = {};
	winInfo.defaultPosition = true;
	winInfo.fullscreen      = true;

	winInfo.title           = "Genome";
	winInfo.numHints        = GENO_ARRAY_SIZE(winHints) / 2;
	winInfo.hints           = winHints;
	winInfo.depth           = false;
	winInfo.clearRed        = 0;
	winInfo.clearGreen      = 0;
	winInfo.clearBlue       = 0;

	window = GenoWindow::create(winInfo);
	if (window == 0) {
		std::cerr << "Window creation failed!" << std::endl;
		GenoEngine::stopLoop();
		return false;
	}
	window->activate();

	GenoEngine::setSwapInterval(1);
	GenoEngine::initGlew();

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera = new GenoCamera2D(0, 1920, 1080, 0, 0, 1);

	uint32 textureParams[] = {
		GL_TEXTURE_MIN_FILTER, GL_NEAREST,
		GL_TEXTURE_MAG_FILTER, GL_NEAREST,
		GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE,
		GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE
	};

	GenoFramebufferCreateInfo bufferInfo = {};
	bufferInfo.width               = videoMode->getWidth();
	bufferInfo.height              = videoMode->getHeight();
	bufferInfo.numColorAttachments = 1;
	bufferInfo.depthAttachmentType = GENO_FRAMEBUFFER_DEPTH_BUFFER;
	bufferInfo.numTextureParams    = GENO_ARRAY_SIZE(textureParams) / 2;
	bufferInfo.textureParams       = textureParams;

	framebuffer1 = new GenoFramebuffer(bufferInfo);
	framebuffer2 = new GenoFramebuffer(bufferInfo);

	glow = new GlowShader();

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

	GenoAudioDevices::getDefaultOutputDevice()->setActive();

	audio = new GenoAudioBuffer("res/audio/harp.wav");
	source = new GenoAudioSource(audio);
	source->loop(true);
	source->play();

	Scene::init();
	Intro::init(camera);
	Level::init(camera);
	Info::init(camera);

	load(0);

	image = new Image(camera, { 1, 1 }, { 5, 5 }, "res/img/Background.png");

	return true;
}

void begin() {
	GenoEngine::startLoop();
}

void loop() {
	update();
	render();
}

void load(uint32 level) {
	using SceneLoader = Scene * (*)(GenoCamera2D *, GlowShader *);
	const static SceneLoader loaders[] = {
		loadSplash,
		loadInfo1,
		loadIntroLevel,
		loadInfo2,
		loadLevel1,
		loadLevel2,
		loadWin
	};
	if (level == GENO_ARRAY_SIZE(loaders))
		GenoEngine::stopLoop();
	else {
		delete scene;
		scene = loaders[level](camera, glow);
	}
}

void update() {
	if (window->shouldClose())
		GenoEngine::stopLoop();
	scene->update();
	if (scene->isComplete())
		load(scene->nextScene());
	camera->update();
}

void render() {
	framebuffer1->bind();
	GenoFramebuffer::clear();
	scene->renderGlow();
	framebuffer2->bind();
	GenoFramebuffer::clear();
	framebuffer1->getColorTexture()->bind();
	image->getTexture()->bind(1);
	glow->enable();
	glow->setMvp(GenoMatrix4f::makeIdentity());
	glow->setResolution(window->getWidth(), window->getHeight());
	glow->setHorizontal(true);
	vao->render();
	GenoFramebuffer::bindDefault();
	GenoFramebuffer::clear();
	framebuffer2->getColorTexture()->bind();
	scene->bindBackground(1);
	glow->enable();
	glow->setMvp(GenoMatrix4f::makeIdentity());
	glow->setResolution(window->getWidth(), window->getHeight());
	glow->setHorizontal(false);
	vao->render();
	scene->render();
	window->swap();
}

void cleanup() {
	delete image;
	delete scene;

	delete vao;
	delete glow;
	delete framebuffer1;
	delete framebuffer2;

	delete camera;
	delete window;

	GenoEngine::destroy();
}
