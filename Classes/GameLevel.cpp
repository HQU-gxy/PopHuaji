#include "PopStarLayer.h"
#include "PopStarDataMgr.h"
#include "GameScene.h"

#include "GameLevel.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool GameLevel::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	char szData[32] = {0};
	int level = getPopStarDataMgr().getLevel();
	int score = getPopStarDataMgr().getTargetScoreByLevel(level);
	snprintf(szData, 32, "Level:%d", level);
	labelLevel = Label::createWithTTF(szData, "fonts/arial.ttf", 24);

	labelLevel->setPosition(origin.x + visibleSize.width/2 + 250,
		origin.y + visibleSize.height - labelLevel->getContentSize().height - 50);

	this->addChild(labelLevel, 1);

	snprintf(szData, 32, "Target Score:%d", score);
	labelTargetScore = Label::createWithTTF(szData, "fonts/arial.ttf", 24);

	labelTargetScore->setPosition(origin.x + visibleSize.width/2 + 500,
		origin.y + visibleSize.height - labelTargetScore->getContentSize().height - 150);

	this->addChild(labelTargetScore, 1);

	this->schedule(CC_SCHEDULE_SELECTOR(GameLevel::onTimeUp), 4);

	Point pos1 = labelLevel->getPosition();
	MoveTo* move1 = MoveTo::create( 1, Vec2(pos1.x-250, pos1.y ));
	labelLevel->runAction(move1);

	Point pos2 = labelTargetScore->getPosition();
	MoveTo* move2 = MoveTo::create( 2, Vec2(pos2.x-500, pos2.y) );
	labelTargetScore->runAction(move2);

	return true;
}

void GameLevel::onTimeUp(float delta)
{
	changeLayer( this, PopStarLayer::create() );
}
