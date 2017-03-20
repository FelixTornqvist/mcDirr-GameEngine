#ifndef SCREEN_HPP
#define SCREEN_HPP

namespace mcDirr {
	class Screen {
		public:
			Screen();

			virtual void tick(int millisPassed) = 0;
			virtual void draw() = 0;

			bool isFinished();
			Screen* getNextScreen();

			virtual ~Screen();

		protected:
			bool finished = false;
			Screen* nextScreen;

		private:
	};
}
#endif // SCREEN_HPP