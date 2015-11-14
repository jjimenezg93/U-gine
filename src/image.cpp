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

	//PO2 -> Power of 2
	double widthPO2 = pow(2, ceil(Log2(width)));
	double heightPO2 = pow(2, ceil(Log2(height)));

	if (widthPO2 != width || heightPO2 != height) {
		lastU = static_cast<double>(width / widthPO2);
		lastV = static_cast<double>(height / heightPO2);
		
		widthPO2 = static_cast<uint16>(widthPO2);
		heightPO2 = static_cast<uint16>(heightPO2);

		//allocating memory for new buffer
		uint8 *bufferPO2 = (uint8 *)malloc(widthPO2 * heightPO2 * 4);		// * 4 because each pixel needs 32 bits
		
		uint8 * const origBufferPO2pos = bufferPO2;		//ptr to keep reference to the bufferPO2
		
		//setting pixels to white -> as texture has transparent pixels, check everything is working properly
		memset(bufferPO2, 255, widthPO2 * heightPO2 * 4);

		for (unsigned int h = 0; h < height; h++) {
			memcpy(bufferPO2, buffer, width * 4);
			bufferPO2 += static_cast<int>(widthPO2) * 4;
			buffer += (width * 4);
		}

		bufferPO2 = origBufferPO2pos;
		//bufferPO2 -= static_cast<int>(widthPO2) * height * 4;

		//call to genImage, creating texture in VRAM
		this->gltex = Renderer::Instance().GenImage(bufferPO2, widthPO2, heightPO2);

		//now, the texture is in VRAM so we no longer need it in RAM
		stbi_image_free(bufferPO2);
	} else {
		// Generamos la textura
		if ( buffer ) {
			this->gltex = Renderer::Instance().GenImage(buffer, width, height);
			stbi_image_free(buffer);
		}
	}
}

Image::~Image() {
	if (gltex != 0) Renderer::Instance().DeleteImage(this->gltex);
}

void Image::Bind() const {
	Renderer::Instance().BindImage(this->gltex);
}
