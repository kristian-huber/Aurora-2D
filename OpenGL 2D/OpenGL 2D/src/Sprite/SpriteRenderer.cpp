#include "SpriteRenderer.h"
#include "../Rendering/ModelManager.h"
#include "../Rendering/TextureManager.h"
#include "../Util/Constants.h"
#include "../Sprite/Sprite.h"
#include <iostream>
#include <typeinfo>

SpriteRenderer::SpriteRenderer(const glm::mat4& projection) {
	shader = new SpriteShader();
	shader->start();
	shader->loadProjectionMatrix(projection);
	shader->stop();
}

SpriteRenderer::~SpriteRenderer() {
	delete shader;
}

bool compareSprite(Sprite* s1, Sprite* s2) {
	return s1->y + s1->height < s2->y + s2->height ? true : false;
}

void SpriteRenderer::prepareInstance(const Sprite* s) {
	glm::mat4 model = glm::mat4(1.0);

	model = glm::translate(model, glm::vec3(s->x, s->y, 0.0f));

	model = glm::scale(model, glm::vec3(s->width, s->height, 1.0f));	

	shader->loadModelMatrix(model);
	shader->loadSpriteColor(1, 1, 1);
}

/* Returns true if it did not load the texture properly */
bool SpriteRenderer::prepareTexture(const std::string& texture, std::string& currentAtlas) {
	
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

void SpriteRenderer::renderSprites(const std::vector<Light>& lights, const glm::mat4& viewMatrix, VectorMap<int, Sprite*>& sprites) {

	shader->start();
	glBindVertexArray(ModelManager::quadVAO);
	shader->loadViewMatrix(viewMatrix);

	shader->loadAmbientLight(0.5);

	for (int i = 0; i < 16; i++) {
		if (i >= lights.size()) {
			shader->loadLight(i);
		} else {
			shader->loadLight(i, lights[i]);
		}
	}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	std::string currentAtlas = "NONE";

	// Loop over the layers
	for (auto weight = sprites.begin(); weight != sprites.end(); weight++) {
		std::vector<Sprite*> spr = sprites.get(weight->first);

		// Loop over all of the sprites in the current layer
		for (Sprite* sprite : spr) {

			// Load the texture
			if (prepareTexture(sprite->getTexture(), currentAtlas))
				continue;
			
			// Load transformations
			this->prepareInstance(sprite);

			glDrawArrays(GL_TRIANGLES, 0, ModelManager::quadSize);
		
			if (sprite->boundingBox != nullptr) {
				shader->loadRenderBounding(1);

				glm::mat4 model = glm::mat4(1.0);

				model = glm::translate(model, glm::vec3(sprite->boundingBox->x, sprite->boundingBox->y, 0.0f));

				model = glm::scale(model, glm::vec3(sprite->boundingBox->width, sprite->boundingBox->height, 1.0f));

				shader->loadModelMatrix(model);
				shader->loadSpriteColor(1, 0, 1);

				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawArrays(GL_TRIANGLES, 0, ModelManager::quadSize);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				shader->loadRenderBounding(0);
			}
		}
	}

	TextureManager::unbindTexture();
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
	shader->stop();
}