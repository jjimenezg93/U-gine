#include "..\include\font.h"
#include "..\include\renderer.h"

extern "C" {
	unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
	void stbi_image_free(void *retval_from_stbi_load);
}

Font::Font(const String &filename) : Image(filename, 16, 16) {
	this->x = 0;
	this->y = 0;
	this->speedX = 0;
	this->speedY = 0;

	for (unsigned short int f = 0; f < this->GetNumFrames(); f++) {
		this->glyphs.Add(Glyph());

		//debug
		if (f == this->GetNumFrames() - 1) {	//last exec
			f = this->glyphs.Size();			//size = 256 -> OK
		}
	}

	int width32 = 0;
	int height32 = 0;
	int *ptrComp = NULL;
	
	uint8 *buffer = stbi_load(filename.ToCString(), &width32, &height32, ptrComp, 4);
	
	uint8 *ptrBuffer = buffer;
	double diff = 0;

	//debug
	uint8 *endBuffer = buffer;
	endBuffer += this->GetHeight() * this->GetWidth() * this->GetNumFrames() * 4;

	//0x<alpha><blue><green><red>
	uint8 red = 0xff0000ff;
	uint8 yellow = 0xff00ffff;
	uint8 black = 0xff000000;
	uint8 transparent = 0x00000000;

	unsigned short int i, j;
	double row = 0;
	double col = 0;

	for (unsigned short int frame = 0; frame < this->GetNumFrames(); frame++) {
		row = frame / GetHFrames();
		col = frame % GetHFrames();
		for (j = row * this->GetHeight(); j < (row + 1) * this->GetHeight(); j++) {
			for (i = col * this->GetWidth(); i < (col + 1) * this->GetWidth(); i++) {
				//inside each frame
				if (*ptrBuffer == black)
					memset(ptrBuffer, transparent, 4);
				else if (*ptrBuffer == yellow) {
					glyphs[frame].SetOrigX(i);
					glyphs[frame].SetOrigY(j);
					memset(ptrBuffer, transparent, 4);
				} else if (*ptrBuffer == red) {
					glyphs[frame].SetEndX(i);
					glyphs[frame].SetEndY(j);
					memset(ptrBuffer, transparent, 4);
				}

				if (ptrBuffer >= endBuffer)
					break;

				ptrBuffer += 4;
				diff = (ptrBuffer - buffer);
			}

			ptrBuffer += this->GetWidth() * (this->GetHFrames() - frame) * 4;
		}

		//ptrBuffer += this->GetHeight() * (this->GetVFrames() - frame) * 4;
	}

	Renderer::Instance().GenImage(buffer, width32 / this->GetHFrames(), height32 / this->GetVFrames());
}

uint16 Font::GetSize() const {
	return this->GetHeight();
}

uint32 Font::GetTextWidth(const String & text) const {
	uint32 toRet;

	const char * str = text.ToCString();

	while (*str != '\0') {
		toRet += glyphs[*str].GetEndX() - glyphs[*str].GetOrigX();
	}

	return toRet;
}

uint32 Font::GetTextHeight(const String & text) const {
	uint32 toRet = 0;

	const char * str = text.ToCString();

	uint32 height;

	while (*str != '\0') {
		height = glyphs[*str].GetEndY() - glyphs[*str].GetOrigY();
		if (height > toRet)
			toRet = height;
	}

	return toRet;
}

void Font::Render(const String & text, double x, double y) const{
	/* ASCII
	* 32 = (space)
	* 48 = 0
	* 64 = @
	* 65 = A
	* 126 = ~		<- last
	*/

	const char * str = text.ToCString();
	unsigned short int offset = 0;

	while (*str != '\0') {
		Renderer::Instance().DrawImage(this, x + offset, y, *str, this->GetHeight(), this->GetWidth(), 0);

		offset += glyphs[*str].GetEndX() - glyphs[*str].GetOrigX();
		str++;
	}
}
