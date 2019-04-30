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

#ifndef GNARLY_PINBALL_INFO
#define GNARLY_PINBALL_INFO

#include "Rectangle.h"
#include "Scene.h"

class Info : public Scene {
	private:
		const static uint32 FADE_IN   = 0;
		const static uint32 WAITING   = 1;
		const static uint32 FADE_OUT  = 2;

		static Image * next;
		static Image * border;
		static Rectangle * overlay;

		Image * glowImage;
		
		float time;
		float alpha;
		float overlayTime;

		uint32 state;

	public:
		static void init(GenoCamera2D * camera);

		Info(GenoCamera2D * camera, GlowShader * glow, uint32 next, const char * info, const char * infoGlow);
		virtual void update();
		virtual void renderGlow();
		virtual void render();
		~Info();
};

#define GNARLY_PINBALL_INFO_FORWARD
#endif // GNARLY_PINBALL_INFO