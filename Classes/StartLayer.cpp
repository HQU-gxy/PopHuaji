#include "GameScene.h"
#include "GameLevel.h"

#include "StartLayer.h"

USING_NS_CC;


Scene* StartLayer::scene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object
	StartLayer* layer = StartLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartLayer::init()
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

	Sprite* popStarBg = Sprite::create("popstar_start.png");
	popStarBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	popStarBg->setScale(2);
	this->addChild(popStarBg, 0);


	MenuItemImage* item = MenuItemImage::create("buttons/default/00010.png",
		"buttons/default/00010.png",
		CC_CALLBACK_1(StartLayer::onClickMenu,this));

	item->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	item->setScale(1.0, 1.0);

	Menu* menu = Menu::create(item, NULL);
	menu->setPosition(Vec2(-10,0));
	this->addChild(menu);
	
	return true;
}

void StartLayer::onClickMenu(Ref* obj)
{
	changeLayer(this, GameLevel::create());
}
