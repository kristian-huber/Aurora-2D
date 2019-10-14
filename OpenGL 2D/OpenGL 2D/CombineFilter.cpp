#include "CombineFilter.h"
#include "CombineShader.h"

CombineFilter::CombineFilter() {
	shader = new CombineShader();
	renderer = new ImageRenderer();
}

CombineFilter::~CombineFilter() {
	delete shader;
	delete renderer;
}

void CombineFilter::render(int colorTexture, int highlightTexture) {
	shader->start();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	renderer->render();

	shader->stop();
}