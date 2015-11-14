#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>
#include "../include/renderer.h"

// TAREA: Declarar funciones de stb_image.c

extern "C" {
	unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
	void stbi_image_free(void *retval_from_stbi_load);
}

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;

	int width32 = 0;
	int height32 = 0;
	int *ptrComp = NULL;

	uint8 *buffer = stbi_load(filename.ToCString(), &width32, &height32, ptrComp, 4);

	width = static_cast<uint16>(width32);
	height = static_cast<uint16>(height32);

	// Generamos la textura
	if ( buffer ) {
		this->gltex = Renderer::Instance().GenImage(buffer, width, height);
		stbi_image_free(buffer);
	}
}

Image::~Image() {
	if (gltex != 0) Renderer::Instance().DeleteImage(this->gltex);
}

void Image::Bind() const {
	Renderer::Instance().BindImage(this->gltex);
}
