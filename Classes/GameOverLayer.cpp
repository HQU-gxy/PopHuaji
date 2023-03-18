#include "GameScene.h"
#include "GameLevel.h"
#include "StartLayer.h"

#include "GameOverLayer.h"
#include "AudioEngine.h"

USING_NS_CC;


Scene* GameOverLayer::scene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object
	GameOverLayer* layer = GameOverLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	float scale = visibleSize.width / 320.f;

	Sprite* popStarBg = Sprite::create("popstar_over.png");
	popStarBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	popStarBg->setScale(2);
	this->addChild(popStarBg, 0);

	AudioEngine::play2d("sounds/over.mp3", false);
	MenuItemImage* item = MenuItemImage::create("buttons/home.png",
		"buttons/home.png",
		CC_CALLBACK_1(GameOverLayer::onClickMenu, this));

	item->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	item->setScale(1.0, 1.0);

	Menu* menu = Menu::create(item, NULL);
	menu->setPosition(Vec2(-10, 0));
	this->addChild(menu);

	return true;
}

void GameOverLayer::onClickMenu(Ref* obj)
{
	
	changeLayer(this, StartLayer::create());
}
