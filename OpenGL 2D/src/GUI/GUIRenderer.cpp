#include "GUIRenderer.h"
#include "../Rendering/ModelManager.h"
#include "../Rendering/TextureManager.h"
#include "GUI.h"
#include <iostream>

GUIRenderer::GUIRenderer(const glm::mat4& projection) {
	shader = new GUIShader();
	shader->start();
	shader->loadProjectionMatrix(projection);
	shader->stop();
}

GUIRenderer::~GUIRenderer() {
	delete shader;
}

void GUIRenderer::prepareInstance(const GUI* s) {
	glm::mat4 model = glm::mat4(1.0);

	model = glm::translate(model, glm::vec3(s->x, s->y, 0.0f));

	/*model = glm::translate(model, glm::vec3(0.5f * s->width, 0.5f * s->height, 0.0f));
	model = glm::rotate(model, s->rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * s->width, -0.5f * s->height, 0.0f));*/

	model = glm::scale(model, glm::vec3(s->width, s->height, 1.0f));

	shader->loadModelMatrix(model);
}

/* Returns true if it did not load the texture properly */
bool GUIRenderer::prepareTexture(const std::string& texture, std::string& currentAtlas) {

	// Get the current texture so we don't have to keep indexing
	Texture* texturePtr = TextureManager::textures[texture];

	//Error handling
	if (texturePtr == nullptr) {
		std::cout << "[ERROR]: Could not find texture for '" << texture << "'" << std::endl;
		return true;
	}

	//Only load up the atlas if it is different
	if (currentAtlas != texturePtr->atlas) {
		glActiveTexture(GL_TEXTURE0);
		TextureManager::bindTexture(texturePtr->atlas);
		currentAtlas = texturePtr->atlas;
	}

	// Sprite sheet calculations
	GLfloat rows = TextureManager::atlases[texturePtr->atlas]->rows;
	GLfloat cols = TextureManager::atlases[texturePtr->atlas]->cols;

	shader->loadOffset((GLfloat)texturePtr->x / cols, (GLfloat)texturePtr->y / rows);
	shader->loadRows(rows / texturePtr->width);
	shader->loadCols(cols / texturePtr->height);

	return false;
}

void GUIRenderer::renderGUIs(VectorMap<int, GUI*>& guis) {

	shader->start();
	glBindVertexArray(ModelManager::quadVAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	std::string currentAtlas = "NONE";

	// Loop over the layers
	for (auto weight = guis.begin(); weight != guis.end(); weight++) {

		// Loop over all of the sprites in the current layer
		for (GUI* gui : guis.get(weight->first)) {

			// Load the texture
			if (prepareTexture(gui->getTexture(), currentAtlas))
				continue;

			// Load transformations
			this->prepareInstance(gui);

			glDrawArrays(GL_TRIANGLES, 0, ModelManager::quadSize);
		}
	}

	TextureManager::unbindTexture();
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->stop();
}