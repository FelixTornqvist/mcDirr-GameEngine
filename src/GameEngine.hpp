#ifndef FRAME_H
#define FRAME_H

#ifdef __APPLE__
#include <SDL2/SDL.h>

#else
#include <SDL.h>
#endif

#include <list>

#include "sprite/Sprite.hpp"
#include "PhysicalSprite.hpp"

namespace mcDirr {
	class GameEngine {
	public:
		GameEngine(std::string windowName, int _fps);
		void add(Sprite* sprite);
		void add(PhysicalSprite* pSprite);
		void remove(Sprite* sprite);
		void remove(PhysicalSprite* sprite);
		void run();
		virtual ~GameEngine();

	protected:

	private:
		int fps;
		bool running = false;

		std::list<Sprite*> sprites;
		std::list<PhysicalSprite*> physicalSprites;

		void const delay(Uint32 nextTick);
	};
}
#endif // FRAME_H
