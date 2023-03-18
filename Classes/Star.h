#ifndef __POPSTAR_STAR_H__
#define __POPSTAR_STAR_H__

#include "cocos2d.h"

class HelloWorld;
class Star : public cocos2d::Sprite
{
public:
    Star(int index);
    
    static Star* create(int index);
    
    bool isHighLight();
    void setHighLight(bool hl);
    int  getIndex();
    void setPos(const cocos2d::Point& pos);
    cocos2d::Point getDestPos();
    void setDestPos(const cocos2d::Point& pos);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);
    
    void onUpdate(float delta);
    
    virtual bool init();
    
private:
    std::string getPath();
    
private:
    int  index;
    bool highlight; // 是否高亮显示
    cocos2d::Point destPos;
};

#endif // __POPSTAR_STAR_H__