#include <SDL.h>
#include "MobileSprite.hpp"
#include "System.hpp"
#include "Loader.hpp"

#include <iostream>
#include <math.h>

using namespace mcDirr;

MobileSprite* MobileSprite::getInstance(SDL_Surface* surface, int x, int y) {
	return new MobileSprite(surface, x, y);
}

MobileSprite::MobileSprite(SDL_Surface* surf, int x, int y) : Sprite(surf, x, y) {
	surface = surf;
	currentTime = 0;

	onGround = false;
	alive = true;

	debounceVel = 0.15;
	yVel = xVel = 0;
	yAccel = 9.82 / 5;
	xAccel = 0;
}

void MobileSprite::draw() const {
	SDL_RenderCopy(sys.getRen(), texture, NULL, &dest);
}

void MobileSprite::doPhysics(int millisPassed) {
	double secsPassed = millisPassed / 1000.0;

	if (!onGround) {
		xVel += xAccel * secsPassed;
		yVel += yAccel * secsPassed;
	} else {
		if (fabs(xVel) <= debounceVel)
			xVel = 0;
		if (fabs(yVel) <= debounceVel)
			yVel = 0;
	}

	dest.x += xVel * millisPassed;
	dest.y += yVel * millisPassed;
}

void MobileSprite::tick(int time) {

	// ~ temporary for controls: ~
	if (sys.isKeyDown(SDLK_w) && onGround)
		yVel -= 1;
	else if (sys.isKeyDown(SDLK_s))
		yVel = 1;
	if (sys.isKeyDown(SDLK_a))
		xVel = -0.5;
	else if (sys.isKeyDown(SDLK_d))
		xVel = 0.5;
	// ~ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ~

	doPhysics(time);

	if (sys.isKeyDown(SDLK_q)) {
		std::cout << "I've been killed by Q" << std::endl;
		alive = false;
	}
	checkBounds();
}

void MobileSprite::checkBounds() {
	int winWidth = 0;
	int winHeight = 0;

	SDL_Window* window = sys.getWin();
	SDL_GetWindowSize(window, &winWidth, &winHeight);
	// std::cout << dest.x << " - " << winWidth << std::endl;

	if (dest.y > winHeight) {
		dest.x = 50;
		dest.y = 50;
		return;
	}

	if (dest.x <= 0) {
		dest.x = 1;
		return;
	}

	if (dest.x > winWidth) {
		dest.x = 50;
	}
}

void MobileSprite::checkCollisions(std::list<ImmobileSprite*>& others) {
	onGround = false;
	for (std::list<ImmobileSprite*>::iterator immobile = others.begin(); immobile != others.end();) {
		handleCollision(*immobile, checkCollision(*immobile));

		if (!(*immobile)->isAlive())
			immobile = others.erase(immobile);
		else
			immobile++;
	}
}

int MobileSprite::checkCollision(Sprite* other) {
	SDL_Rect intersection;
	SDL_Rect& oDest = (* other->getDestRect());
	int side = 0;

	if (SDL_IntersectRect(&dest, &oDest, &intersection)) {

		int& oX = oDest.x;
		int& oY = oDest.y;
		int& myX = dest.x;
		int& myY = dest.y;

		if (intersection.h > intersection.w) {
			if (oX > myX) {
				side = 4;
			} else {
				side = 2;
			}
		} else {
			if (oY > myY) {
				side = 3;
			} else {
				side = 1;
			}
		}
		return side;
	}

}

void MobileSprite::handleCollision(ImmobileSprite* collidedWith, int side) {
	if (side) {
		SDL_Rect& oDest = (* collidedWith->getDestRect());
		int& oX = oDest.x;
		int& oY = oDest.y;
		int& myX = dest.x;
		int& myY = dest.y;

		if(side == 1) {
			myY = oY + oDest.h;
		} else if (side == 3) {
			myY = oY - dest.h;
			onGround = true;
		} else if (side == 2) {
			myX = oX + oDest.w;
		} else if (side == 4) {
			myX = oX - dest.w;
		}

		if (side == 1 || side == 3) {
			yVel *= -collidedWith->getBounciness();
			xVel = 0;
		}

		if (side == 4 || side == 2) {
			xVel *= -collidedWith->getBounciness();
		}
	}
}

bool MobileSprite::isAlive() const {
	return alive;
}

void MobileSprite::kill() {
	alive = false;
}

SDL_Surface* MobileSprite::getSurface() const {
	return surface;
}
