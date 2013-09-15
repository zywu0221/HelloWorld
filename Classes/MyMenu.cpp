#include "MyMenu.h"
#include <stdlib.h>

USING_NS_CC;

void MyMenu::registerWithTouchDispatcher()
{
	//这里优先级设为1，只要比CCScrollView低就可以
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

	/*CCLOG( " MyMenu::registerWithTouchDispatcher() --->");*/

	ADJUST_ANIM_VELOCITY = 2000.0f;
	MOVE_MIN_DISTANCE = 20.0f;

}

bool MyMenu::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){   

	//set the curPage index (important)  start from 1
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	curPage= (int)fabsf (showScrollView->getContentOffset().x/ visibleSize.width )+1;

	/*CCLOG(" curPage: %d " , curPage );*/

	if(visibleRect_.size.width && visibleRect_.size.height){
		if(!visibleRect_.containsPoint(pTouch->getLocation()))
			return false;
	}
	startPosition = pTouch->getLocation(); 

	/*CCLOG(" MyMenu::ccTouchBegan  ---> ");*/

	return CCMenu::ccTouchBegan(pTouch,pEvent);
}

void MyMenu::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	CCMenu::ccTouchMoved(pTouch,pEvent);
}

void MyMenu::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

	CCPoint position = pTouch->getLocation();

	//移动的距离在范围内,则触发点击事件
	if( abs(position.x - startPosition.x) <= 10 )
	{
		CCMenu::ccTouchEnded(pTouch,pEvent);
	}
	else
	{
		if(m_pSelectedItem){
			m_pSelectedItem->unselected();
		}
		m_eState = kCCMenuStateWaiting;
	}
	
	/*about->adjustScrollView();*/
	adjustScrollView();
}


void MyMenu::adjustScrollView()
{
	if(showScrollView==NULL)
	{
		CCLOG(" MyMenu::adjustScrollView() ---> showScrollView is NULL");
		return;
	}

	int srceen_width = CCDirector::sharedDirector()->getWinSize().width;

	/*CCLOG(" srceen_width: %d , visibleSize.width: %f , showScrollView->getContentSize().width: %f" , srceen_width , visibleSize.width , showScrollView->getContentSize().width);*/

	// 关闭CCScrollView中的自调整
	showScrollView->unscheduleAllSelectors();

	// 调整位置
	CCPoint adjustPos;
	// 调整动画时间
	float adjustAnimDelay;

	int x =  - showScrollView->getContentOffset().x; 

	int dis_tance = x - ( (curPage-1) * srceen_width);   //移动的距离，大于0向右移动，小于0向左移动 

	//注意，由于curPage是由一开始的，所以在计算的时候，要减去1来表示,下面也是这样

// 	CCLOG(" curPage: %d , page_size: %d" , curPage , page_size);
// 	CCLOG(" x : %d , dis_tance : %d " , x , dis_tance);

	if( abs(dis_tance)> srceen_width/4 ) //切换页 
	{
		if(dis_tance>0 && curPage!=page_size) //下一页,且非最后一页
		{
			adjustPos = ccp( -curPage*srceen_width, 0);

			adjustAnimDelay = (float) (srceen_width - abs(dis_tance)) / ADJUST_ANIM_VELOCITY;

		}else if(dis_tance <0 && curPage!=1 ){ //上一页,且非第一页

			adjustPos = ccp( -(curPage-2)*srceen_width, 0 );
			adjustAnimDelay = (float) (srceen_width - abs(dis_tance)) / ADJUST_ANIM_VELOCITY;

		}else{ //返回原页

			adjustPos = ccp( -(curPage-1)*srceen_width, 0);
			adjustAnimDelay = (float) abs(dis_tance) / ADJUST_ANIM_VELOCITY;
		}

		/*CCLOG(" adjustPos . x  ; %f" , adjustPos.x);*/

	}else{ //返回原页

		adjustPos = ccp( -(curPage-1)*srceen_width, 0 );
		adjustAnimDelay = (float) abs(dis_tance) / ADJUST_ANIM_VELOCITY;

	}

	// 调整位置
	showScrollView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);
}



MyMenu* MyMenu::createWithItems( CCMenuItem* item, va_list args )
{
	CCArray* pArray = NULL;
	if( item )
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while(i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}

	return MyMenu::createWithArray(pArray);
}


MyMenu* MyMenu::createWithArray( CCArray* pArrayOfItems )
{
	MyMenu *pRet = new MyMenu();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}


MyMenu* MyMenu::create( CCMenuItem* item, ... )
{
	va_list args;
	va_start(args,item);

	MyMenu *pRet = MyMenu::createWithItems(item, args);

	va_end(args);

	return pRet;
}

void MyMenu::setScrollView( cocos2d::extension::CCScrollView * val )
{
	showScrollView = val; 

	//set the page size as the same time
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	page_size = (showScrollView->getContentSize().width)/visibleSize.width;

}
