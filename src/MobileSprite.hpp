#ifndef PhysicalSprite_hpp
#define PhysicalSprite_hpp

#include "Sprite.hpp"
#include "ImmobileSprite.hpp"

#include <list>


namespace mcDirr {

	class MobileSprite : virtual public Sprite {

		public:
			static MobileSprite* getInstance(SDL_Surface* surface, int, int);
			void draw() const override;
			void tick(int passedMillis) override;
			void checkCollisions(std::list<ImmobileSprite*>& others);
			bool isAlive() const;
			void kill();
			SDL_Surface* getSurface() const;
			virtual ~MobileSprite() {};

		protected:
			MobileSprite(SDL_Surface* s, int x, int y);
			int checkCollision(Sprite* other) const;
			void virtual handleCollision(ImmobileSprite* collidedWith, int side);
			void doPhysics(int millisPassed);

			virtual void checkBounds();
			float currentTime;
			double yVel, xVel;
			double yAccel, xAccel;
			bool alive;
			bool onGround;

		private:
			double debounceVel;
			SDL_Surface* surface;
	};
}

#endif
