#ifdef __APPLE__
#include <SDL2/SDL.h>

#else
#include <SDL.h>
#endif

#include "PhysicalSprite.hpp"
#include "System.hpp"
#include <iostream>



using namespace mcDirr;

PhysicalSprite* PhysicalSprite::getInstance(SDL_Texture* t, int x, int y, int z) {
	return new PhysicalSprite(t, x, y, z);
}

void PhysicalSprite::draw() const {
	SDL_RenderCopy(sys.getRen(), texture, NULL, &dest);
}

void PhysicalSprite::tick(int time) {
	if (sys.isKeyDown(SDLK_q)) {
		std::cout << "yes?" << std::endl;
		alive = false;
	}
	if (sys.isKeyDown(SDLK_d)) {
		dest.x += ttSpeed * time;
	}
	if (sys.isKeyDown(SDLK_a)) {
		dest.x -= ttSpeed * time;
	}
	if (sys.isKeyDown(SDLK_w)) {
		dest.y -= ttSpeed * time;
	}
	if (sys.isKeyDown(SDLK_s)) {
		dest.y += ttSpeed * time;
	}
}

void PhysicalSprite::checkCollision(PhysicalSprite* other) {
	if ( SDL_HasIntersection(getRect(), other->getRect())) {
		std::cout << "box collision!" << std::endl;
	}
}

bool PhysicalSprite::isAlive() const {
	return alive;
}

//Sprite::~Sprite() {
//    SDL_DestroyTexture(texture);
//}
