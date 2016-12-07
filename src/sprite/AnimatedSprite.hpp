#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#ifdef __APPLE__
#include <SDL2/SDL.h>

#else
#include <SDL.h>
#endif

#include "../FramedSprite.hpp"

namespace mcDirr {
	class AnimatedSprite : public FramedSprite {
		public:
			AnimatedSprite(SDL_Texture* t, int x, int y, int sheetDivisions, int millisPerFrame);

			void tick(int passedTime) override;
			void setStartFrame(int frame);
			void setEndFrame(int frame);

			virtual ~AnimatedSprite();

		protected:

		private:
			int startFrame, endFrame;
			int millisPerFrame, currentCount = 0;

			void checkCurrentCount();
	};
}
#endif // ANIMATEDSPRITE_H