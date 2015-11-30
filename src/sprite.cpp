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
	// TAREA: Implementar
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
	this->currentFrame = 0;
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
		double ccw = WrapValue(this->angle - wrapAngle, 360);
		double cw = WrapValue(wrapAngle - this->angle, 360);
		if (min(ccw, cw) == ccw) {
			this->degreesToRotate = ccw;
			this->rotatingSpeed = abs(speed);
		} else {
			this->degreesToRotate = cw;
			this->rotatingSpeed = -abs(speed);
		}
	}
}

void Sprite::MoveTo(double x, double y, double speed) {
	this->toY = y;
	this->toX = x;
	if (this->toX == this->x || this->toY == this->y/*
													|| this->toX <= 0 || this->toY <= 0 || this->toX > Screen::Instance().GetWidth() || this->toY > Screen::Instance().GetHeight()*/) {
		this->moving = false;
	} else {
		this->moving = true;
		double time = sqrt(x * x + y * y) / speed;
		this->movingSpeedX = x / time;
		this->movingSpeedY = y / time;
	}
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

	//rotation update
	double r = rotatingSpeed * elapsed;
	degreesToRotate -= r;
	SetAngle(this->GetAngle() + r);

	//move update
	double moveX = this->x + (this->movingSpeedX * elapsed);
	double moveY = this->y + (this->movingSpeedY * elapsed);
	this->SetPosition(moveX, moveY);

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
	Renderer::Instance().SetBlendMode(this->blendMode);

	Renderer::Instance().SetColor(this->r, this->g, this->b, this->a);

	Renderer::Instance().DrawImage(this->image, this->x, this->y, 0U, this->colwidth, this->colheight, this->angle);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
