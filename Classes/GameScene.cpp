#include "StartLayer.h"

#include "GameScene.h"

USING_NS_CC;

Scene* createScene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	StartLayer *layer = StartLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void changeLayer(Layer* curLayer, Layer* newLayer)
{
	if (!curLayer || !newLayer)
	{
		return;
	}

	Scene* scene = Director::getInstance()->getRunningScene();
	if (scene)
	{
		scene->removeChild(curLayer);
		scene->addChild(newLayer);
	}
}
