#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class About : public CCLayer ,public CCScrollViewDelegate
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	void adjustScrollView();

private:
	void menuCallback(CCObject* pSender);

	void scrollViewDidScroll(CCScrollView* view) ;
	void scrollViewDidZoom(CCScrollView* view);

	CCScrollView * showScrollView ;

	int page_size ;
	int curPage ;

	float ADJUST_ANIM_VELOCITY ;
	// implement the "static node()" method manually
	CREATE_FUNC(About);
};

#endif // __HELLOWORLD_SCENE_H__
