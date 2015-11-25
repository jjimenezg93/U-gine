#ifndef UGINE_SPRITE_H
#define UGINE_SPRITE_H

#include "renderer.h"
#include "types.h"

class Collision;
class CollisionPixelData;
class Image;
class Map;

class Sprite {
public:
	enum CollisionMode {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_PIXEL,
		COLLISION_RECT
	};

	Sprite(Image* image);
	virtual ~Sprite();

	virtual void SetImage(Image* image) { this->image = image; }
	virtual const Image* GetImage() const { return this->image; }

	virtual void SetPosition(double x, double y, double z = 0) { this->x = x; this->y = y; this->z = z; }
	virtual void SetX(double x) { this->x = x; }
    virtual void SetY(double y) { this->y = y; }
    virtual void SetZ(double z) { this->z = z; }
	virtual double GetX() const { return this->x; }
    virtual double GetY() const { return this->y; }
    virtual double GetZ() const { return this->z; }
	virtual double GetScreenX() const { return this->GetX(); }		//isometrica, transformadas en coordenadas de pantalla. por ahora getX y getY
    virtual double GetScreenY() const { return this->GetY(); }

	virtual void SetAngle(double angle) { this->angle = angle; }
	virtual double GetAngle() const { return this->angle; }

	virtual void SetScale(double sx, double sy) { this->scalex = sx; this->scaley = sy; }
	virtual void SetScaleX(double sx) { this->scalex = sx; }
	virtual void SetScaleY(double sy) { this->scaley = sy; }
	virtual double GetScaleX() const { return this->scalex; }
    virtual double GetScaleY() const { return this->scaley; }

	virtual void SetFPS(int16 fps) { this->animFPS = fps; }
	virtual int16 GetFPS() const { return this->animFPS; }
	virtual void SetFrameRange(uint16 firstFrame, uint16 lastFrame) { this->firstFrame = firstFrame; this->lastFrame = lastFrame; }
	virtual uint16 GetFirstFrame() const { return this->firstFrame; }
	virtual uint16 GetLastFrame() { return this->lastFrame; }
	virtual void SetCurrentFrame(uint16 frame) { this->currentFrame = frame; }
	virtual uint16 GetCurrentFrame() const { return this->currentFrame; }

	virtual void SetBlendMode(Renderer::BlendMode blend) { this->blendMode = blend; }
	virtual Renderer::BlendMode GetBlendMode() const { return this->blendMode; }
	virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha = 255) { this->r = r; this->g = g; this->b = b; this->a = alpha; }
	virtual uint8 GetRed() const { return this->r; }
	virtual uint8 GetGreen() const { return this->g; }
	virtual uint8 GetBlue() const { return this->b; }
	virtual uint8 GetAlpha() const { return this->a; }

	virtual void SetRadius(double radius) { this->radius = radius; }
	virtual double GetRadius() const { return this->radius; }

	virtual void SetCollision(CollisionMode mode);
	virtual void SetCollisionPixelData(const CollisionPixelData* colPixelData) { this->colPixelData = colPixelData; }
	virtual const Collision* GetCollision() const { return this->collision; }
    virtual bool CheckCollision(Sprite* sprite);
    virtual bool CheckCollision(const Map* map);
	virtual const Sprite* CollisionSprite() const { return this->colSprite; }
	virtual bool DidCollide() const { return this->collided; }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speed);
	virtual bool IsRotating() const { return this->rotating; }
	virtual bool IsMoving() const { return this->moving; }

    virtual void Update(double elapsed, const Map* map = NULL);
    virtual void Render() const;
	
	virtual void SetUserData(void* data) { userData = data; }
	virtual void* GetUserData() { return userData; }
	virtual const void* GetUserData() const { return userData; }
protected:
    virtual void UpdateCollisionBox();
    virtual void UpdateCollisionBox(double x, double y, double w, double h);
private:
    Image* image;
    double x, y, z;
    double colx, coly, colwidth, colheight;
    double angle;
    double scalex, scaley;
    double radius;
    int16 animFPS;
    uint16 firstFrame, lastFrame;
    double currentFrame;
    Renderer::BlendMode blendMode;
    uint8 r, g, b, a;
    Collision* collision;
    const CollisionPixelData* colPixelData;
    Sprite* colSprite;
    bool collided;

    bool rotating;
    uint16 toAngle;
    double rotatingSpeed;
    double degreesToRotate;

    bool moving;
    double toX, toY;
    double movingSpeedX, movingSpeedY;
    double prevX, prevY;
	
	void* userData;
};

#endif
