#include "PopStar.h"
//#include "../extensions/CocoStudio/gui/UIWidgets/UILabel.h"

#include "PopStarLayer.h"

USING_NS_CC;

PopStarLayer::~PopStarLayer()
{
	if (popStar)
	{
		delete popStar;
		popStar = NULL;
	}
}

// on "init" you need to initialize your instance
bool PopStarLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	srand((unsigned)time(NULL));

	float scale = visibleSize.width / 320.f;
	Sprite* levelInfoHint = Sprite::create("level_info_hint.png");
	levelInfoHint->setPosition(Vec2(280 * scale, 160 * scale));
	levelInfoHint->setScale(1);
	this->addChild(levelInfoHint, 0);

	historyTotalScore = Label::createWithTTF("0", "fonts/arial.ttf", 24);
	if (historyTotalScore)
	{
		historyTotalScore->setPosition(Vec2(275 * scale, 181 * scale));
		this->addChild(historyTotalScore);
	}

	historyLevelScore = Label::createWithTTF("0", "fonts/arial.ttf", 24);
	if (historyLevelScore)
	{
		historyLevelScore->setPosition(Vec2(275 * scale, 172 * scale));
		this->addChild(historyLevelScore);
	}

	gameLevel = Label::createWithTTF("0", "fonts/arial.ttf", 24);
	if (gameLevel)
	{
		gameLevel->setPosition(Vec2(260 * scale, 162 * scale));
		this->addChild(gameLevel);
	}

	targetScore = Label::createWithTTF("0", "fonts/arial.ttf", 24);
	if (targetScore)
	{
		targetScore->setPosition(Vec2(300 * scale, 162 * scale));
		this->addChild(targetScore);
	}

	curScore = Label::createWithTTF("0", "fonts/arial.ttf", 24);
	if (curScore)
	{
		curScore->setPosition(Vec2(260 * scale, 152 * scale));
		this->addChild(curScore);
	}

	reduceScore = nullptr;
	if (reduceScore)
	{
		reduceScore->setPosition(Vec2(260 * scale, 152 * scale));
		reduceScore->setHorizontalAlignment(TextHAlignment::LEFT);
		this->addChild(reduceScore);
	}

	popStar = new PopStar(this);

	this->schedule(CC_SCHEDULE_SELECTOR(PopStarLayer::update));


	return true;
}

void PopStarLayer::onEnter()
{
	Layer::onEnter();
	auto* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* pTouches, Event* pEvent) {
		Point locInView = pTouches->getLocationInView();
		Point loc = Director::getInstance()->convertToGL(locInView);

		if (popStar)
		{
			popStar->onClick(loc);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//this->setTouchEnabled(true);
}

void PopStarLayer::update(float delta)
{
	if (!popStar)
	{
		return;
	}

	popStar->onUpdate(delta);
}

void PopStarLayer::onGuiEvent(GUI_EVENT_TYPE event, int nValue, unsigned int uValue)
{
	switch (event)
	{
	case EVENT_UPDATE_SCORE:
	{
		if (curScore)
		{
			char szBuf[32] = { 0 };
			//itoa(nValue, szBuf, 10);
			sprintf(szBuf, "%d", nValue);
			curScore->setString(szBuf);
		}
	}
	break;
	case EVENT_UPDATE_TARGET_SCORE:
	{
		if (targetScore)
		{
			char szBuf[32] = { 0 };
			//itoa(nValue, szBuf, 10);
			sprintf(szBuf, "%d", nValue);
			targetScore->setString(szBuf);
		}
	}
	break;
	case EVENT_UPDATE_LEVEL:
	{
		if (gameLevel)
		{
			char szBuf[32] = { 0 };
			//itoa(nValue, szBuf, 10);
			sprintf(szBuf, "%d", nValue);
			gameLevel->setString(szBuf);
		}
	}
	break;
	case EVENT_UPDATE_REDUCE_SCORE:
	{
		if (reduceScore)
		{
			if (nValue == 0)
			{
				reduceScore->setString("");
			}
			else
			{
				char szBuf[32] = { 0 };
				snprintf(szBuf, 32, "Number: %d Score: %u", nValue, uValue);
				reduceScore->setString(szBuf);
			}
		}
	}
	break;
	case EVENT_UPDATE_TOTAL_HISTORY_SCORE:
	{
		if (historyTotalScore)
		{
			char szBuf[32] = { 0 };
			snprintf(szBuf, 32, "%d", nValue);
			historyTotalScore->setString(szBuf);
		}
	}
	break;
	case EVENT_UPDATE_LEVEL_HISTORY_SCORE:
	{
		if (historyLevelScore)
		{
			char szBuf[32] = { 0 };
			snprintf(szBuf, 32, "%d", nValue);
			historyLevelScore->setString(szBuf);
		}
	}
	break;
	}
}
