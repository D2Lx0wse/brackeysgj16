#include "Scenes.hpp"

void initNextScene(SceneTypes nextScene, Scenes scenes) {
	switch (nextScene) {
	case SceneTypes::MainMenu: scenes.mainMenu.init(); break;

	case SceneTypes::Credits:  break;

	case SceneTypes::Playing: scenes.playing.init(); break;

	default: break;
	}
}