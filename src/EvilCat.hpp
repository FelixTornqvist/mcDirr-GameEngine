#ifndef EVILCAT_HPP
#define EVILCAT_HPP

#include "MobileSprite.hpp"

namespace mcDirr {
	static class EvilCat : public MobileSprite {


	public:
		EvilCat* getInstance(SDL_Surface* surface, int x, int y);

	protected:
		void customTick(int timeDiff);
		EvilCat(SDL_Surface* s, int x, int y);

	};
}

#endif