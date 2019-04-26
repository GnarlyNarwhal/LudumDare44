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

#include "geno/thread/GenoTime.h"
#include "geno/engine/GenoEngine.h"
#include "geno/engine/GenoLoop.h"
#include "geno/engine/GenoInput.h"
#include "geno/engine/GenoWindow.h"
#include "geno/engine/GenoCamera2D.h"
#include "geno/gl/GenoFramebuffer.h"

bool init();
void begin();
void loop();
void update();
void render();
void cleanup();

GenoWindow * window;
GenoCamera2D * camera;

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
	//////// DO NOT REMOVE BELOW ////////

	#ifdef _DEBUG
	
	std::cout << "Press enter to continue . . ." << std::endl;
	std::cin.get();

	#endif // _DEBUG

	return 0;
}

bool init() {
	GenoEngine::init();

	GenoLoopCreateInfo loopInfo = {};
	loopInfo.targetFps   = GenoMonitors::getPrimaryMonitor()->getDefaultVideoMode()->getRefreshRate();
	loopInfo.deltaScale  = 1;
	loopInfo.callback    = loop;
	loopInfo.numSubLoops = 0;
	loopInfo.subLoops    = 0;

	GenoEngine::setLoop(loopInfo);

	int32 winHints[] = {
		GLFW_CONTEXT_VERSION_MAJOR, 3,
		GLFW_CONTEXT_VERSION_MINOR, 3,
		GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE,
		GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE
	};

	GenoWindowCreateInfo winInfo = {};
	winInfo.defaultPosition = true;
	winInfo.fullscreen      = true;
	winInfo.title           = "Genome";
	winInfo.numHints        = GENO_ARRAY_SIZE(winHints) / 2;
	winInfo.hints           = winHints;
	winInfo.depth           = true;
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

	camera = new GenoCamera2D(0, 1, 1, 0, 0, 1);

	GenoFramebuffer::bindDefault();

	return true;
}

void begin() {
	GenoEngine::startLoop();
}

void loop() {
	update();
	render();
}

void update() {
	if (window->shouldClose())
		GenoEngine::stopLoop();

	camera->update();
}

void render() {
	GenoFramebuffer::clear();
	window->swap();
}

void cleanup() {
	delete camera;
	delete window;

	GenoEngine::destroy();
}
