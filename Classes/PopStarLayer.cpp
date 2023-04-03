#include "PopStar.h"
// #include "../extensions/CocoStudio/gui/UIWidgets/UILabel.h"

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

	stringsJsonObj = new rapidjson::Document;
	std::string resFile = FileUtils::getInstance()->getStringFromFile("strings.json");
	stringsJsonObj->Parse<rapidjson::kParseDefaultFlags>(resFile.c_str());

	Sprite *levelInfoHint = Sprite::create("bg.png");
	levelInfoHint->setAnchorPoint(Vec2(0, 0));
	levelInfoHint->setPosition(Vec2(0, 0));
	levelInfoHint->setScale(1);
	this->addChild(levelInfoHint, 0);

	historyTotalScore = Label::createWithTTF("0", "fonts/msyh.ttc", 24);
	if (historyTotalScore)
	{
		historyTotalScore->setPosition(Vec2(260 * scale, 181 * scale));
		this->addChild(historyTotalScore, 1);
	}

	historyLevelScore = Label::createWithTTF("0", "fonts/msyh.ttc", 24);
	if (historyLevelScore)
	{
		historyLevelScore->setPosition(Vec2(260 * scale, 172 * scale));
		this->addChild(historyLevelScore, 1);
	}

	gameLevel = Label::createWithTTF("0", "fonts/msyh.ttc", 24);
	if (gameLevel)
	{
		gameLevel->setPosition(Vec2(260 * scale, 162 * scale));
		this->addChild(gameLevel, 1);
	}

	targetScore = Label::createWithTTF("0", "fonts/msyc.ttc", 24);
	if (targetScore)
	{
		targetScore->setPosition(Vec2(260 * scale, 152 * scale));
		this->addChild(targetScore, 1);
	}

	curScore = Label::createWithTTF("0", "fonts/msyc.ttc", 24);
	if (curScore)
	{
		curScore->setPosition(Vec2(260 * scale, 142 * scale));
		this->addChild(curScore, 1);
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
	auto *listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *pTouches, Event *pEvent)
	{
		Point locInView = pTouches->getLocationInView();
		Point loc = Director::getInstance()->convertToGL(locInView);

		if (popStar)
		{
			popStar->onClick(loc);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// this->setTouchEnabled(true);
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
			char szBuf[32] = {0};
			// itoa(nValue, szBuf, 10);
			sprintf(szBuf, "%s%d", (*stringsJsonObj)["current_score"].GetString(), nValue);
			curScore->setString(szBuf);
		}
	}
	break;
	case EVENT_UPDATE_TARGET_SCORE:
	{
		if (targetScore)
		{
			char szBuf[32] = {0};
			// itoa(nValue, szBuf, 10);
			sprintf(szBuf, "Target Score: %d", nValue);
			targetScore->setString(szBuf);
		}
	}
	break;
	case EVENT_UPDATE_LEVEL:
	{
		if (gameLevel)
		{
			char szBuf[32] = {0};
			// itoa(nValue, szBuf, 10);
			sprintf(szBuf, "Level: %d", nValue);
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
				char szBuf[32] = {0};
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
			char szBuf[32] = {0};
			snprintf(szBuf, 32, "Highest Total Score: %d", nValue);
			historyTotalScore->setString(szBuf);
		}
	}
	break;
	case EVENT_UPDATE_LEVEL_HISTORY_SCORE:
	{
		if (historyLevelScore)
		{
			char szBuf[32] = {0};
			snprintf(szBuf, 32, "Highest Score of Current Level: %d", nValue);
			historyLevelScore->setString(szBuf);
		}
	}
	break;
	}
}
