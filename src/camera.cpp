
#include "..\include\camera.h"
#include "..\include\screen.h"

Camera::Camera() {
	this->boundx0 = this->boundy0 = 0;
	this->boundx1 = Screen::Instance().GetWidth();
	this->boundy1 = Screen::Instance().GetHeight();
	this->x = this->y = 0;
	this->followingSprite = nullptr;
}

void Camera::SetPosition(double x, double y) {
	this->SetX(x);
	this->SetY(y);
}

void Camera::SetX(double x) {
	if (x >= this->boundx0 && x <= this->boundx1 - Screen::Instance().GetWidth())
		this->x = x;
	else if (x <= this->boundx0)
		this->x = this->boundx0;
	else if (x >= this->boundx1 - Screen::Instance().GetWidth())
		this->x = this->boundx1;
}

void Camera::SetY(double y) {
	if (y >= this->boundy0 && y <= this->boundy1 - Screen::Instance().GetHeight())
		this->y = y;
	else if (y <= this->boundy0)
		this->y = this->boundy0;
	else if (y >= this->boundy1 - Screen::Instance().GetHeight())
		this->y = this->boundy1;
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1) {
	this->boundx0 = bx0;
	this->boundy0 = by0;
	this->boundx1 = bx1;
	this->boundy1 = by1;
}

bool Camera::HasBounds() const {
	if (this->boundx0 == this->boundx1)
		return false;
	else
		return true;
}

void Camera::FollowSprite(Sprite * sprite) {
	this->followingSprite = sprite;
}

void Camera::Update() {
	if (this->followingSprite != nullptr) {
		//update camera position to get Sprite in the center of camera when possible
		this->SetPosition(this->followingSprite->GetX() - Screen::Instance().GetWidth() / 2, this->followingSprite->GetY() - Screen::Instance().GetHeight() / 2);
		printf("Camera::Update()\n");
	}
}
