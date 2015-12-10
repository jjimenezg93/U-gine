#include "..\include\font.h"
#include "..\include\renderer.h"

uint16 Font::GetSize() const {
	return this->GetHeight();
}

uint32 Font::GetTextWidth(const String & text) const {
	return this->GetWidth() * this->GetHFrames() * this->GetVFrames();
}

uint32 Font::GetTextHeight(const String & text) const {
	return this->GetHeight();
}

void Font::Render(const String & text, double x, double y) {
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

		offset += this->GetWidth();
		str++;
	}
}
