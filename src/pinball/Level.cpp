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

#include "../geno/engine/GenoEngine.h"
#include "../geno/engine/GenoInput.h"
#include "../geno/engine/GenoLoop.h"

#include "Level.h"

GenoVector4f fromHSV(float h, float s, float v);

Image * Level::startingGlow;
Image * Level::startingNonglow;
Rectangle * Level::overlay;
Rectangle * Level::left;
Rectangle * Level::right;
Rectangle * Level::bottom;
Rectangle * Level::bar;
Rectangle * Level::barInner;

void Level::init(GenoCamera2D * camera) {
	startingGlow = new Image(camera, { 0.0f, 0.0f }, { 1920, 1080 }, "res/img/StartingGlow.png");
	startingNonglow = new Image(camera, { 0.0f, 0.0f }, { 1920, 1080 }, "res/img/StartingNonglow.png");
	overlay = new Rectangle(camera, { 0.0f, 0.0f }, { 1920, 1080 }, { 0, 0, 0, 1 });
	left = new Rectangle(camera, { 0.0f, 942.5f }, { 7.5f, 130 }, { 1, 1, 1, 1 });
	right = new Rectangle(camera, { 1912.5f, 942.5f }, { 7.5f, 130 }, { 1, 1, 1, 1 });
	bottom = new Rectangle(camera, { 0.0f, 1072.5f }, { 1920, 7.5f }, { 1, 1, 1, 1 });
	bar = new Rectangle(camera, { 37.5f, 975 }, { 1845, 70 }, { 1, 1, 1, 1 });
	barInner = new Rectangle(camera, { 45, 982.5f }, { 1830, 55 }, { 0, 0, 0, 1 });
}

bool rangeCheck(float t) {
	return 0 <= t && t <= 1;
}

Level::Level(GenoCamera2D * camera, GlowShader * glow, uint32 next, uint32 reset, const char * path, uint32 numColors, GenoVector4f * palette, uint32 numWallLists, WallList ** walls, float timeLimit, uint32 wallDrawColor, uint32 ballColor, const GenoVector2f & ballStart, const GenoVector2f & ballVelocity) :
	Scene(camera, glow, next, path, numColors, palette, numWallLists, walls),
	reset(reset),
	timeLimit(timeLimit),
	wallDraw(new WallDraw(camera, palette, wallDrawColor)) {
	pinball = new Pinball(camera, palette, ballColor, ballStart, ballVelocity);
}

void Level::update() {
	if (state == FADE_IN) {
		bar->setColor(fromHSV(120, 0.8f, 1));
		bar->dimensions.x()      = 1845;
		barInner->dimensions.x() = bar->dimensions.x() - 15;
		const static auto SHADE = 0.5f;
		time += GenoEngine::getLoop()->getDelta();
		if (time < 1)
			overlay->setAlpha((1 - time) * (1 - SHADE) + SHADE);
		else {
			overlay->setAlpha(SHADE);
			time = 0;
			state = STARTING;
		}
	}
	else if (state == STARTING) {
		if (GenoInput::getKeyState(GLFW_KEY_R) == GENO_INPUT_PRESSED) {
			state = IN_MOTION;
			overlay->setAlpha(0);
		}
	}
	else if (state == IN_MOTION) {
		auto scale = float{ 1 };
		if (GenoInput::getKeyState(GLFW_KEY_SPACE) >= GENO_INPUT_PRESSED)
			scale = 0.25f;
		wallDraw->update();
		time += GenoEngine::getLoop()->getDelta() * (scale == 1 ? 1 : 1.15f);
		time += wallDraw->wallCompleted() * 0.15f;
		auto percent = (1 - time / timeLimit);
		if (percent < 0)
			percent = 0;
		bar->setColor(fromHSV(120 * percent, 0.8f, 1));
		bar->dimensions.x()      = 1845 * percent;
		barInner->dimensions.x() = bar->dimensions.x() - 15;
		if (barInner->dimensions.x() < 0)
			barInner->dimensions.x() = 0;
		if (GenoInput::getKeyState(GLFW_KEY_R) == GENO_INPUT_PRESSED || time > timeLimit) {
			state = FADE_OUT;
			next = reset;
		}
		auto delta = float( GenoEngine::getLoop()->getDelta() );
		auto collision = true;
		auto tempVelocity = pinball->velocity * delta * scale;
		auto remove = -1;
		while (collision && state == IN_MOTION) {
			collision = false;
			auto smallestT = float{ 1.0f };
			auto reflect = GenoVector2f{ 0.0f };
			auto angular = float { 0.0f };
			for (uint32 i = 0; i < numWallLists; ++i) {
				WallList * walls = wallLists[i];
				for (uint32 j = 0; j < walls->numVertices; ++j) {
					if (j < walls->numWalls) {
						auto normal = dot(walls->normals[j], tempVelocity) > 0 ? -walls->normals[j] : walls->normals[j];
						auto wallOrigin = walls->vertices[j];
						auto wallDirection = walls->vertices[j + 1] - wallOrigin;
						wallOrigin += normal * (Pinball::RADIUS + WallList::HALF_WALL_THICKNESS);
						auto t1 = (tempVelocity.y() * wallOrigin.x() - tempVelocity.x() * wallOrigin.y() + tempVelocity.x() * pinball->position.y() - tempVelocity.y() * pinball->position.x()) /
								  (tempVelocity.x() * wallDirection.y() - tempVelocity.y() * wallDirection.x());
						auto t2 = float{ 0 };
						if (tempVelocity.x() == 0)
							t2 = (wallOrigin.y() + wallDirection.y() * t1 - pinball->position.y()) / tempVelocity.y();
						else
							t2 = (wallOrigin.x() + wallDirection.x() * t1 - pinball->position.x()) / tempVelocity.x();
						if (rangeCheck(t1) && rangeCheck(t2) && t2 < smallestT) {
							if (i == numWallLists - 1)
								state = FADE_OUT;
							else {
								collision = true;
								smallestT = t2;
								auto m = tempVelocity * (1 - t2);
								reflect = 2.0f * project(m, wallDirection) - m;
								angular = project(setLength(m, pinball->velocity.getLength()), wallDirection).getLength() / Pinball::RADIUS;
								if (dot(tempVelocity, { normal.y(), -normal.x() }) > 0)
									angular = -angular;
							}
						}
					}
					{
						auto & vertex = walls->vertices[j];
						auto a = tempVelocity.x() * tempVelocity.x() +
								 tempVelocity.y() * tempVelocity.y();
						auto b = 2.0f * pinball->position.x() * tempVelocity.x() - 2.0f * vertex.x() * tempVelocity.x() +
								 2.0f * pinball->position.y() * tempVelocity.y() - 2.0f * vertex.y() * tempVelocity.y();
						auto c = pinball->position.x() * pinball->position.x() - 2.0f * pinball->position.x() * vertex.x() + vertex.x() * vertex.x() +
								 pinball->position.y() * pinball->position.y() - 2.0f * pinball->position.y() * vertex.y() + vertex.y() * vertex.y() -
								 (Pinball::RADIUS + WallList::HALF_WALL_THICKNESS) * (Pinball::RADIUS + WallList::HALF_WALL_THICKNESS);
						auto radical = b * b - 4.0f * a * c;
						if (radical > 0) {
							auto t = (-b - sqrt(radical)) / (2.0f * a);
							if (rangeCheck(t) && t < smallestT) {
								if (i == numWallLists - 1)
									state = FADE_OUT;
								else {
									collision = true;
									smallestT = t;
									auto reflectAxis = pinball->position + tempVelocity * t - vertex;
									auto m = tempVelocity * (1 - t);
									reflect = 2.0f * project(m, { -reflectAxis.y(), reflectAxis.x() }) - m;
									angular = project(setLength(m, pinball->velocity.getLength()), { -reflectAxis.y(), reflectAxis.x() }).getLength() / Pinball::RADIUS;
									if (dot(tempVelocity, { reflectAxis.y(), -reflectAxis.x() }) > 0)
										angular = -angular;
								}
							}
						}
					}
				}
			}
			if (state == IN_MOTION) {
				for (uint32 j = 0; j < wallDraw->walls.getLength() - wallDraw->skipLast(); ++j) {
					auto vertexIndex = j * 2;
					{
						auto normal = dot(wallDraw->normals[j], tempVelocity) > 0 ? -wallDraw->normals[j] : wallDraw->normals[j];
						auto wallOrigin = wallDraw->vertices[vertexIndex];
						auto wallDirection = wallDraw->vertices[vertexIndex + 1] - wallOrigin;
						wallOrigin += normal * (Pinball::RADIUS + WallList::HALF_WALL_THICKNESS);
						auto t1 = (tempVelocity.y() * wallOrigin.x() - tempVelocity.x() * wallOrigin.y() + tempVelocity.x() * pinball->position.y() - tempVelocity.y() * pinball->position.x()) /
								  (tempVelocity.x() * wallDirection.y() - tempVelocity.y() * wallDirection.x());
						auto t2 = float{ 0 };
						if (tempVelocity.x() == 0)
							t2 = (wallOrigin.y() + wallDirection.y() * t1 - pinball->position.y()) / tempVelocity.y();
						else
							t2 = (wallOrigin.x() + wallDirection.x() * t1 - pinball->position.x()) / tempVelocity.x();
						if (rangeCheck(t1) && rangeCheck(t2) && t2 < smallestT) {
							collision = true;
							smallestT = t2;
							auto m = tempVelocity * (1 - t2);
							reflect = 2.0f * project(m, wallDirection) - m;
							angular = project(setLength(m, pinball->velocity.getLength()), wallDirection).getLength() / Pinball::RADIUS;
							if (dot(tempVelocity, { normal.y(), -normal.x() }) > 0)
								angular = -angular;
						}
					}
					{
						for (uint32 k = 0; k < 2; ++k) {
							auto & vertex = wallDraw->vertices[vertexIndex + k];
							auto a = tempVelocity.x() * tempVelocity.x() +
									 tempVelocity.y() * tempVelocity.y();
							auto b = 2.0f * pinball->position.x() * tempVelocity.x() - 2.0f * vertex.x() * tempVelocity.x() +
									 2.0f * pinball->position.y() * tempVelocity.y() - 2.0f * vertex.y() * tempVelocity.y();
							auto c = pinball->position.x() * pinball->position.x() - 2.0f * pinball->position.x() * vertex.x() + vertex.x() * vertex.x() +
									 pinball->position.y() * pinball->position.y() - 2.0f * pinball->position.y() * vertex.y() + vertex.y() * vertex.y() -
									 Pinball::RADIUS * Pinball::RADIUS;
							auto radical = b * b - 4.0f * a * c;
							if (radical > 0) {
								auto t = (-b - sqrt(radical)) / (2.0f * a);
								if (rangeCheck(t) && t < smallestT) {
									collision = true;
									smallestT = t;
									auto reflectAxis = pinball->position + tempVelocity * t - vertex;
									auto m = tempVelocity * (1 - t);
									reflect = 2.0f * project(m, { -reflectAxis.y(), reflectAxis.x() }) - m;
									angular = project(setLength(m, pinball->velocity.getLength()), { -reflectAxis.y(), reflectAxis.x() }).getLength() / Pinball::RADIUS;
									if (dot(tempVelocity, { reflectAxis.y(), -reflectAxis.x() }) > 0)
										angular = -angular;
								}
							}
						}
					}
				}
				if (collision) {
					pinball->position += tempVelocity * smallestT;
					tempVelocity = reflect;
					setLength(tempVelocity, pinball->velocity.getLength(), pinball->velocity);
					pinball->angularVelocity = angular;
				}
			}
		};
		pinball->position += tempVelocity;
		pinball->rotation += pinball->angularVelocity * scale * delta;
		if (state == FADE_OUT)
			time = 0;
	}
	else if (state == FADE_OUT) {
		time += GenoEngine::getLoop()->getDelta();
		if (time < 1)
			overlay->setAlpha(time);
		else
			complete = true;
	}
}

void Level::renderGlow() {
	left->render();
	right->render();
	bottom->render();
	pinball->render();
	for (uint32 i = 0; i < numWallLists; ++i)
		wallLists[i]->render();
	wallDraw->render();
	//if (state == STARTING)
		//startingGlow->render();
}

void Level::render() {
	left->render();
	right->render();
	bottom->render();
	bar->render();
	barInner->render();
	pinball->render();
	for (uint32 i = 0; i < numWallLists; ++i)
		wallLists[i]->render();
	wallDraw->render();
	overlay->render();
	if (state == STARTING) {
		startingNonglow->render();
		//startingGlow->render();
	}
}

Level::~Level() {
	delete pinball;
}

GenoVector4f fromHSV(float h, float s, float v) {
	float hh, p, q, t, ff;
	float r, g, b;
	int64 i;
	if (s <= 0.0) {
		r = v;
		g = v;
		b = v;
	}
	else {
		hh = h;
		if (hh >= 360.0)
			hh = 0.0;
		hh /= 60.0;
		i = (int64) hh;
		ff = hh - i;
		p = v * (1.0 - s);
		q = v * (1.0 - (s * ff));
		t = v * (1.0 - (s * (1.0 - ff)));
		switch (i) {
			case 0:
				r = v;
				g = t;
				b = p;
				break;
			case 1:
				r = q;
				g = v;
				b = p;
				break;
			case 2:
				r = p;
				g = v;
				b = t;
				break;
			case 3:
				r = p;
				g = q;
				b = v;
				break;
			case 4:
				r = t;
				g = p;
				b = v;
				break;
			default:
				r = v;
				g = p;
				b = q;
				break;
		}
	}
	return { r, g, b, 1 };
}