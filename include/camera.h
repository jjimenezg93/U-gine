#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "sprite.h"

class Camera {
public:
	Camera();

	virtual void SetPosition(double x, double y);
	virtual void SetX(double x);
	virtual void SetY(double y);
	virtual double GetX() const { return this->x; };
	virtual double GetY() const { return this->y; };

	virtual void SetBounds(double bx0, double by0, double bx1, double by1);
	virtual bool HasBounds() const;
	virtual double GetMinX() const { return this->boundx0; };
	virtual double GetMinY() const { return this->boundy0; };
	virtual double GetMaxX() const { return this->boundx1; };
	virtual double GetMaxY() const { return this->boundy1; };
	
	virtual void FollowSprite(Sprite* sprite);

	virtual void Update();
private:
	double x, y;
	double boundx0, boundy0, boundx1, boundy1;
	Sprite * followingSprite;
};

#endif