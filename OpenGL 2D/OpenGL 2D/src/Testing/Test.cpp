#include "Test.h"
#include "../Text/TextLoader.h"
#include "../Rendering/TextureManager.h"
#include "../GUI/GUIScreen.h"
#include "Cursor.h"
#include "World.h"
#include "../Rendering/MasterRenderer.h"
#include "../Sprite/Light.h"
#include "../../AudioManager2.h"

void Test::initialize() {
	TextLoader::initialize("OwreKynge");

	inGame = new GUIScreen();

	Text t("Testing");
	t.position = glm::vec2(50, 50);
	inGame->texts.push_back(t);

	Cursor* cursor = new Cursor("Cursor");
	inGame->guis.addElement(1, cursor);

	w = new World();
	w->lights.push_back(Light(1090, 300, 0.75f, 0.5f, 0.05f, 500));

	w->lights.push_back(Light(1090, 1000, 0.75f, 0.25f, 0.05f, 500));
}

void Test::loadResources() {
	AudioManager2::loadWAV("CrystalCaves");

	TextureManager::loadAtlas("cherokee", 1, 1);

	TextureManager::loadAtlas("Cursor", 1, 1);
	TextureManager::registerTexture("Cursor", "Cursor", 10, 0, 0, 1, 1);

	TextureManager::loadAtlas("GoldenUI", 7, 7);
	TextureManager::registerTexture("Button_Left", "GoldenUI", 1, 3, 0, 1, 1);
	TextureManager::registerTexture("Button_Middle", "GoldenUI", 1, 4, 0, 1, 1);
	TextureManager::registerTexture("Button_Right", "GoldenUI", 1, 5, 0, 1, 1);

	TextureManager::loadAtlas("cave", 40, 25);
	TextureManager::registerTexture("entrance", "cave", 1, 0, 1, 1, 1);

	TextureManager::loadAtlas("character", 16, 17);
	TextureManager::registerTexture("Character_Front", "character", 2, 0, 0, 1, 2);
	TextureManager::registerTexture("Character_Back", "character", 2, 0, 4, 1, 2);
	TextureManager::registerTexture("Character_Left", "character", 2, 0, 6, 1, 2);
	TextureManager::registerTexture("Character_Right", "character", 2, 0, 2, 1, 2);

	TextureManager::loadAtlas("Overworld", 40, 40);
	TextureManager::registerTexture("Grass", "Overworld", 1, 0, 0, 1, 1);

	TextureManager::registerTexture("Water1", "Overworld", 1, 0, 1, 1, 1);
	TextureManager::registerTexture("Water2", "Overworld", 1, 1, 1, 1, 1);
	TextureManager::registerTexture("Water3", "Overworld", 1, 2, 1, 1, 1);
	TextureManager::registerTexture("Water4", "Overworld", 1, 3, 1, 1, 1);

	TextureManager::registerTexture("Cliff_TopC", "Overworld", 1, 5, 11, 1, 1);
	TextureManager::registerTexture("Cliff_UpMid", "Overworld", 1, 5, 12, 1, 1);
	TextureManager::registerTexture("Cliff_LowMid", "Overworld", 1, 5, 13, 1, 1);
	TextureManager::registerTexture("Cliff_BottomC", "Overworld", 1, 5, 14, 1, 1);

	TextureManager::registerTexture("Cave", "Overworld", 2, 7, 12, 1, 1);
	TextureManager::registerTexture("Rocks", "Overworld", 2, 8, 5, 1, 1);

	TextureManager::registerTexture("Bush_L", "Overworld", 2, 1, 15, 1, 1);
	TextureManager::registerTexture("Bush_C", "Overworld", 2, 2, 15, 1, 1);
	TextureManager::registerTexture("Bush_R", "Overworld", 2, 3, 15, 1, 1);

	TextureManager::registerTexture("House", "Overworld", 2, 6, 0, 5, 5);
	TextureManager::registerTexture("Fountain1", "Overworld", 2, 22, 9, 3, 3);
	TextureManager::registerTexture("Fountain2", "Overworld", 2, 25, 9, 3, 3);
	TextureManager::registerTexture("Fountain3", "Overworld", 2, 28, 9, 3, 3);

	TextureManager::registerTexture("Tree", "Overworld", 2, 5, 16, 2, 2);
}

bool test = false;
void Test::loop() {
	w->update(delta);
	inGame->update(delta);

	

	if (!test) {
		AudioManager2::playSound("CrystalCaves");
		test = true;
	}

	renderer->render(delta, *w, *inGame);
}