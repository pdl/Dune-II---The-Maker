// a game object is the most super class of all game objects
// it has the bare bones that all other objects (structures, units, bullets, etc) use.

#ifndef CGAMEOBJECT_H_
#define CGAMEOBJECT_H_

class GameObject {

	public:
		GameObject();
		~GameObject();

		void setX(int value) {
			x = value;
		}
		void setY(int value) {
			y = value;
		}

		int getX() {
			return x;
		}
		int getY() {
			return y;
		}

	protected:

	private:
		int x;
		int y;

		int drawFrame;
};

#endif /* CGAMEOBJECT_H_ */
