#ifndef __OVER_LAYER_H__
#define __OVER_LAYER_H__

#include "cocos2d.h"

class GameOverLayer : public cocos2d::Layer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	static cocos2d::Scene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(GameOverLayer);

	void onClickMenu(cocos2d::Ref* obj);

private:
};

#endif // __OVER_LAYER_H__
