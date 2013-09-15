#ifndef __MYMENU_H__
#define __MYMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class MyMenu : public cocos2d::CCMenu
{
public:
	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

	CCRect visibleRect_;

	void VisibleRect(cocos2d::CCRect val) { visibleRect_ = val; }

	static MyMenu* create(CCMenuItem* item, ...);
	static MyMenu* createWithItems(CCMenuItem* item, va_list args);
	static MyMenu* createWithArray(CCArray* pArrayOfItems);

	cocos2d::extension::CCScrollView * showScrollView ;
	void setScrollView(cocos2d::extension::CCScrollView * val);

private:

	int curPage;
	int page_size;

	float ADJUST_ANIM_VELOCITY;
	float MOVE_MIN_DISTANCE ;

	CCPoint startPosition;
	void adjustScrollView();
};
#endif