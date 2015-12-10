#include "../include/bone.h"
#include "../include/glinclude.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/renderer.h"

Bone::Bone() {
    this->id = "id";
    this->image = NULL;
    this->pivotX = 0;
    this->pivotY = 0;
    this->handleX = 0;
    this->handleY = 0;
    currentX = currentY = currentRotation = 0;
    currentScaleX = currentScaleY = 1;
}

Bone::Bone(const String& id, Image* image, double pivotX, double pivotY, double handleX, double handleY) {
    this->id = id;
	this->image = image;
	this->pivotX = pivotX;
	this->pivotY = pivotY;
	this->handleX = handleX;
	this->handleY = handleY;
	currentX = currentY = currentRotation = 0;
    currentScaleX = currentScaleY = 1;
}

const Bone* Bone::FindChild(const String &id) const {
    // Buscamos en los hijos del hueso
    for ( uint32 i = 0; i < children.Size(); i++ )
        if ( children[i].GetID() == id )
            return &children[i];

	// Si no, en toda su descendencia
    for ( uint32 i = 0; i < children.Size(); i++ ) {
        const Bone* bone = children[i].FindChild(id);
		if ( bone != NULL )
			return bone;
	}

	// No se ha encontrado
    return NULL;
}

Bone* Bone::FindChild(const String &id) {
    // Buscamos en los hijos del hueso
    for ( uint32 i = 0; i < children.Size(); i++ )
        if ( children[i].GetID() == id )
            return &children[i];

    // Si no, en toda su descendencia
    for ( uint32 i = 0; i < children.Size(); i++ ) {
        Bone* bone = children[i].FindChild(id);
        if ( bone != NULL )
            return bone;
    }

    // No se ha encontrado
    return NULL;
}

const Frame* Bone::FindFrame(uint32 id) const {
    for ( uint32 i = 0; i < frames.Size(); i++ )
        if ( frames[i].GetId() == id )
            return &frames[i];
	return NULL;
}

void Bone::TranslationForFrame(int32 f, double* x, double* y) const {
    const Frame* frame = NULL, * prevFrame = NULL, * nextFrame = NULL;
	GetFrame(f, &frame, &prevFrame, &nextFrame);

	if ( frame != NULL ) {
		*x = frame->GetTranslationX();
		*y = frame->GetTranslationY();
	} else if ( prevFrame != NULL  &&  nextFrame != NULL ) {
		*x = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetTranslationX(), nextFrame->GetTranslationX());
		*y = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetTranslationY(), nextFrame->GetTranslationY());
	} else {
		*x = *y = 0;
	}
}

double Bone::RotationForFrame(int32 f) const {
    const Frame* frame = NULL, * prevFrame = NULL, * nextFrame = NULL;
	GetFrame(f, &frame, &prevFrame, &nextFrame);

	if ( frame != NULL )
		return frame->GetRotation();
	else if ( prevFrame != NULL  &&  nextFrame != NULL )
		return WrapValue(Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetRotation(), nextFrame->GetRotation()), 360);
	else
		return 0;
}

void Bone::ScaleForFrame(int32 f, double* x, double* y) const {
    const Frame* frame = NULL, * prevFrame = NULL, * nextFrame = NULL;
	GetFrame(f, &frame, &prevFrame, &nextFrame);

	if ( frame != NULL ) {
		*x = frame->GetScaleX();
		*y = frame->GetScaleY();
	} else if ( prevFrame != NULL  &&  nextFrame != NULL ) {
		*x = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetScaleX(), nextFrame->GetScaleX());
		*y = Interpolate(f, prevFrame->GetId(), nextFrame->GetId(), prevFrame->GetScaleY(), nextFrame->GetScaleY());
	} else {
		*x = *y = 0;
	}
}

void Bone::Update(int32 currentFrame) {
	this->TranslationForFrame(currentFrame, &this->currentX, &this->currentY);
	this->currentRotation = this->RotationForFrame(currentFrame);
	this->ScaleForFrame(currentFrame, &this->currentScaleX, &this->currentScaleY);

	for (unsigned short int i = 0; i < this->children.Size(); i++) {
		this->children[i].Update(currentFrame);
	}
}

void Bone::Render() {
	Renderer::Instance().PushMatrix();
	Renderer::Instance().TranslateMatrix(this->currentX, this->currentY, 0);
	Renderer::Instance().RotateMatrix(this->currentRotation, 0, 0, -1);

	if (this->image) {
		this->image->SetHandle(this->handleX * this->image->GetWidth(), this->handleY * this->image->GetHeight());
		Renderer::Instance().DrawImage(this->image, 0, 0, 0U, this->image->GetWidth() * this->currentScaleX, this->image->GetHeight() * this->currentScaleY, 0);	//angle must be 0 because rotation is done before in matrix
		Renderer::Instance().TranslateMatrix(this->pivotX * this->image->GetWidth(), this->pivotY * this->image->GetHeight(), 0);
	}

	for (unsigned short int i = 0; i < this->children.Size(); i++) {
		this->children[i].Render();
	}

	Renderer::Instance().PopMatrix();
}

void Bone::GetFrame(int32 f, const Frame** frame, const Frame** prevFrame, const Frame** nextFrame) const {
	*frame = NULL;
	*prevFrame = NULL;
	*nextFrame = NULL;
    for ( uint32 i = 0; i < frames.Size(); i++ ) {
        if ( frames[i].GetId() == f )
            *frame = &frames[i];
        if ( frames[i].GetId() < f  &&  (*prevFrame == NULL  ||  (*prevFrame)->GetId() < frames[i].GetId()) )
            *prevFrame = &frames[i];
        if ( frames[i].GetId() > f  &&  (*nextFrame == NULL  ||  (*nextFrame)->GetId() > frames[i].GetId()) )
            *nextFrame = &frames[i];
	}
}

double Bone::Interpolate(int32 id, int32 prevId, int32 nextId, double prevVal, double nextVal) const {
	// TAREA: Implementar la especificacion del enunciado
	//valor = prevVal + (nextVal - prevVal) * (id - prevId) / (nextId - prevId
	return prevVal + (nextVal - prevVal) * static_cast<double>(id - prevId) / static_cast<double>(nextId - prevId);
}
