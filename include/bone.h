#ifndef UGINE_BONE_H
#define UGINE_BONE_H

#include "array.h"
#include "frame.h"
#include "string.h"
#include "types.h"

class Image;

class Bone {
public:
    Bone();
    Bone(const String& id, Image* image, double pivotX, double pivotY, double handleX, double handleY);

    virtual const String& GetID() const { return id; }
    virtual const Image* GetImage() const { return image; }

    virtual void AddChild(const Bone& bone) { children.Add(bone); }
    virtual uint32 CountChildren() const { return children.Size(); }
    virtual const Bone* GetChild(uint32 index) const { return &children[index]; }
    virtual Bone* GetChild(uint32 index) { return &children[index]; }
    virtual const Bone* FindChild(const String& id) const;
    virtual Bone* FindChild(const String& id);

    virtual void AddFrame(const Frame& frame) { frames.Add(frame); }
    virtual uint32 CountFrames() const { return frames.Size(); }
    virtual const Frame* GetFrame(uint32 index) const { return &frames[index]; }
    virtual const Frame* FindFrame(uint32 id) const;

    virtual void TranslationForFrame(int32 f, double* x, double* y) const;
    virtual double RotationForFrame(int32 f) const;
    virtual void ScaleForFrame(int32 f, double* x, double* y) const;

    virtual void Update(int32 currentFrame);
    virtual void Render();
protected:
    virtual void GetFrame(int32 f, const Frame** frame, const Frame** prevFrame, const Frame** nextFrame) const;
    virtual double Interpolate(int32 id, int32 prevId, int32 nextId, double prevVal, double nextVal) const;
private:
    String id;
    Image* image;
    double pivotX, pivotY;
    double handleX, handleY;
    Array<Bone> children;
    Array<Frame> frames;

    double currentX, currentY;
    double currentRotation;
    double currentScaleX, currentScaleY;
};

#endif
