#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include "../include/screen.h"
#include <math.h>

Sprite::Sprite(Image* image) {
	this->image = image;
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->colx = 0;
	this->coly = 0;
	this->colwidth = 0;
	this->colheight = 0;
	this->angle = 0;
	this->scalex = 1;
	this->scaley = 1;
	this->radius = 1;
	this->animFPS = 0;
	this->firstFrame = 0;
	this->lastFrame = 1;
	this->currentFrame = this->firstFrame;
	this->blendMode = Renderer::BlendMode::ALPHA;
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->collision = nullptr;
	this->colPixelData = nullptr;
	this->colSprite = nullptr;
	this->collided = false;

	this->rotating = false;
	this->toAngle = 0;
	this->rotatingSpeed = 0;
	this->degreesToRotate = 0;

	this->moving = false;
	this->toX = this->x;
	this->toY = this->y;
	this->movingSpeedX = 0;
	this->movingSpeedY = 0;
	this->prevX = this->x;
	this->prevY = this->y;

	this->userData = nullptr;
}

Sprite::~Sprite() {
	// TAREA: Implementar
}

void Sprite::SetCollision(CollisionMode mode) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(Sprite* sprite) {
	// TAREA: Implementar
	return false;
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar
	return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
	double wrapAngle = WrapValue(angle, 360);

	if (WrapValue(angle, 360) == WrapValue(this->angle, 360) || speed == 0)
		this->rotating = false;
	else {
		this->rotating = true;
		double cw = WrapValue(this->angle - wrapAngle, 360);
		double ccw = WrapValue(wrapAngle - this->angle, 360);
		if (min(ccw, cw) == ccw) {
			this->degreesToRotate = ccw;
			this->toAngle = wrapAngle;
			this->rotatingSpeed = abs(speed);
		} else {
			this->degreesToRotate = cw;
			this->toAngle = wrapAngle;
			this->rotatingSpeed = -abs(speed);
		}
	}
}

void Sprite::MoveTo(double x, double y, double speed) {
	if (x == round(this->x) && y == round(this->y) || speed == 0) {
		this->moving = false;
	} else {
		this->toX = x;
		this->toY = y;
		this->moving = true;
		double time = sqrt(pow(this->toX - this->x, 2) + pow(this->toY - this->y, 2)) / speed;
		this->movingSpeedX = (this->toX - this->x) / time;
		this->movingSpeedY = (this->toY - this->y) / time;
	}
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	this->currentFrame += this->animFPS * elapsed;
	
	if (this->currentFrame >= this->lastFrame) {
		this->currentFrame = this->firstFrame;
	}

	if (this->currentFrame < this->firstFrame) {
		this->currentFrame = this->lastFrame;
	}

	//rotation update
	if (this->rotating == true) {
		double r = rotatingSpeed * elapsed;
		degreesToRotate -= abs(r);
		SetAngle(this->GetAngle() + r);

		if (this->degreesToRotate <= 0) {
			this->rotating = false;
			SetAngle(toAngle);
		}
	}

	//move update
	if (this->moving == true) {
		double moveX = this->x + (this->movingSpeedX * elapsed);
		double moveY = this->y + (this->movingSpeedY * elapsed);
		this->SetPosition(moveX, moveY);

		if (this->movingSpeedX <= 0 && this->x <= this->toX) {
			this->moving = false;
			this->x = this->toX;
			this->y = this->toY;
		} else if (this->movingSpeedX >= 0 && this->x >= this->toX) {
			this->moving = false;
			this->x = this->toX;
			this->y = this->toY;
		}

		if (this->movingSpeedY <= 0 && this->y <= this->toY) {
			this->moving = false;
			this->x = this->toX;
			this->y = this->toY;
		} else if (this->movingSpeedY >= 0 && this->y >= this->toY) {
			this->moving = false;
			this->x = this->toX;
			this->y = this->toY;
		}
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
	Renderer::Instance().SetBlendMode(this->blendMode);

	Renderer::Instance().SetColor(this->r, this->g, this->b, this->a);

	Renderer::Instance().DrawImage(this->image, this->x, this->y, this->currentFrame, this->image->GetWidth() * scalex, this->image->GetHeight() * scaley, this->angle);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
