#include "MyMenu.h"
#include <stdlib.h>

USING_NS_CC;

void MyMenu::registerWithTouchDispatcher()
{
	//�������ȼ���Ϊ1��ֻҪ��CCScrollView�;Ϳ���
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

	//�ƶ��ľ����ڷ�Χ��,�򴥷�����¼�
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

	// �ر�CCScrollView�е��Ե���
	showScrollView->unscheduleAllSelectors();

	// ����λ��
	CCPoint adjustPos;
	// ��������ʱ��
	float adjustAnimDelay;

	int x =  - showScrollView->getContentOffset().x; 

	int dis_tance = x - ( (curPage-1) * srceen_width);   //�ƶ��ľ��룬����0�����ƶ���С��0�����ƶ� 

	//ע�⣬����curPage����һ��ʼ�ģ������ڼ����ʱ��Ҫ��ȥ1����ʾ,����Ҳ������

// 	CCLOG(" curPage: %d , page_size: %d" , curPage , page_size);
// 	CCLOG(" x : %d , dis_tance : %d " , x , dis_tance);

	if( abs(dis_tance)> srceen_width/4 ) //�л�ҳ 
	{
		if(dis_tance>0 && curPage!=page_size) //��һҳ,�ҷ����һҳ
		{
			adjustPos = ccp( -curPage*srceen_width, 0);

			adjustAnimDelay = (float) (srceen_width - abs(dis_tance)) / ADJUST_ANIM_VELOCITY;

		}else if(dis_tance <0 && curPage!=1 ){ //��һҳ,�ҷǵ�һҳ

			adjustPos = ccp( -(curPage-2)*srceen_width, 0 );
			adjustAnimDelay = (float) (srceen_width - abs(dis_tance)) / ADJUST_ANIM_VELOCITY;

		}else{ //����ԭҳ

			adjustPos = ccp( -(curPage-1)*srceen_width, 0);
			adjustAnimDelay = (float) abs(dis_tance) / ADJUST_ANIM_VELOCITY;
		}

		/*CCLOG(" adjustPos . x  ; %f" , adjustPos.x);*/

	}else{ //����ԭҳ

		adjustPos = ccp( -(curPage-1)*srceen_width, 0 );
		adjustAnimDelay = (float) abs(dis_tance) / ADJUST_ANIM_VELOCITY;

	}

	// ����λ��
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
