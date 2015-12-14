#ifndef UGINE_FONT_H
#define UGINE_FONT_H

#include "glyph.h"
#include "image.h"
#include "string.h"		//includes array.h
#include "types.h"

class Font : public Image {
public:
	Font(const String &filename);

	virtual uint16 GetSize() const;
	virtual uint32 GetTextWidth(const String &text) const;
	virtual uint32 GetTextHeight(const String &text) const;

	virtual float GetX() const { return this->x; }
	virtual float GetY() const { return this->y; }
	virtual double GetSpeedX() const { return this->speedX; }
	virtual double GetSpeedY() const { return this->speedY; }
	virtual void SetX(float x) { this->x = x; }
	virtual void SetY(float y) { this->y = y; }
	virtual void SetSpeedX(double speedX) { this->speedX = speedX; }
	virtual void SetSpeedY(double speedY) { this->speedY = speedY; }

	virtual void Render(const String &text, double x, double y) const;
private:
	float x, y;
	double speedX, speedY;

	Array<Glyph> glyphs;
};

#endif