#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <list>

#include "Sprite.hpp"
#include "MobileSprite.hpp"
#include "AnimatedMobileSprite.hpp"
#include "InteractionSprite.hpp"

namespace mcDirr {
	class Level {
		public:
			static Level* getInstance(Level* nextLvl);

			void tick(int timeDiff);
			void draw();

			void add(Sprite* sprite);
			void add(MobileSprite* sprite);
			void add(ImmobileSprite* sprite);
			void add(AnimatedMobileSprite* sprite);
			void add(InteractionSprite* sprite);

			void remove(Sprite* sprite);
			void remove(MobileSprite* sprite);
			void remove(ImmobileSprite* sprite);
			void remove(AnimatedMobileSprite* sprite);
			void remove(InteractionSprite* sprite);

			bool isComplete();
			Level* getNextLevel();

			virtual ~Level();

		protected:
			Level(Level* nextLvl);

		private:
			bool complete = false;
			Level* nextLevel;

			std::list<Sprite*> sprites;
			std::list<MobileSprite*> mobileSprites;
			std::list<ImmobileSprite*> immobileSprites;
			std::list<InteractionSprite*> interactionSprites;
	};
}

#endif // LEVEL_HPP
