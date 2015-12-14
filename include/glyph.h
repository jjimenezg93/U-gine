#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

class Glyph {
public:
	virtual float GetOrigX() const { return this->origX; }
	virtual float GetOrigY() const { return this->origY; }
	virtual void SetOrigX(float x) { this->origX = x; }
	virtual void SetOrigY(float y) { this->origY = y; }

	virtual float GetEndX() const { return this->endX; }
	virtual float GetEndY() const { return this->endY; }
	virtual void SetEndX(float x) { this->endX = x; }
	virtual void SetEndY(float y) { this->endY = y; }
private:
	double origX, origY, endX, endY;
};

#endif