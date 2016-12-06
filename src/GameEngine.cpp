#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#endif


#include "GameEngine.hpp"
#include "System.hpp"

#define W_WIDTH 1000
#define W_HEIGHT 800

namespace mcDirr {
    
    // helloooo

	GameEngine::GameEngine(std::string windowName, int _fps): fps(_fps) {
		sys.initialize(windowName, W_WIDTH, W_HEIGHT);
	}

	void GameEngine::add(Sprite* sprite) {
		sprites.push_back(sprite);
	}

	void GameEngine::remove(Sprite* sprite) {
		sprites.remove(sprite);
		delete sprite;
	}

	void GameEngine::run() {
		const Uint32 MILLIS_PER_LOOP = 1000 / fps;
		Uint32 lastTick = SDL_GetTicks();
		Uint32 nextTick;

		running = true;
		while(running) {
			nextTick = SDL_GetTicks() + MILLIS_PER_LOOP;
			sys.collectInputs();

			for(Sprite* curr : sprites)
				curr->tick(nextTick - lastTick);

			SDL_RenderClear(sys.getRen());
			for(Sprite* curr : sprites)
				curr->draw();

			SDL_RenderPresent(sys.getRen());

			running = !sys.isQuitRequested();
			delay(nextTick);
			lastTick = nextTick;
		}
	}

	void const GameEngine::delay(Uint32 nextTick) {
		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}


	GameEngine::~GameEngine() {
		for(Sprite* sprite : sprites)
			delete sprite;

		sys.Quit();
	}
}
