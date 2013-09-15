#include "AboutScene.h"
#include "VisibleRect.h"

#include "HelloWorldScene.h"
#include "MyMenu.h"

USING_NS_CC;

CCScene* About::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	About *layer = About::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool About::init()
{   
	if ( !CCLayer::init() )
	{
		return false;
	}

	curPage = 1;
	page_size =3;
	ADJUST_ANIM_VELOCITY = 2000.0f;

	//背景图片
	CCSprite* pSprite = CCSprite::create("bg2.jpg");
	pSprite->setPosition(VisibleRect::center());
	this->addChild(pSprite, 0);

	//左上角的返回按钮
	CCMenuItemSprite * pSprite_back_home = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("home_normal.png"),CCSprite::createWithSpriteFrameName("home_pressed.png"),CCSprite::createWithSpriteFrameName("home_pressed.png"), this, menu_selector(About::menuCallback));
	pSprite_back_home->setTag(1);

	CCMenu* pSpriteMenu_back_home = CCMenu::create(pSprite_back_home,NULL);
	pSpriteMenu_back_home->setPosition( ccpAdd(VisibleRect::leftTop(),ccp( pSprite_back_home->getContentSize().width/2   , -pSprite_back_home->getContentSize().height/2 )) );  
	this->addChild(pSpriteMenu_back_home ,1);


	//获取窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//创建一个层
	CCLayer *slayer=CCLayer::create();

	showScrollView = CCScrollView::create(CCSizeMake(visibleSize.width, visibleSize.height), slayer);
	showScrollView->setContentOffset(CCPointZero);
	//false自己写touch事件
	showScrollView->setTouchEnabled(true);
	showScrollView->setDelegate(this);

	//滚动方向
	showScrollView->setDirection(kCCScrollViewDirectionHorizontal);
	showScrollView->setBounceable(true);
	showScrollView->setContentSize(CCSizeMake(visibleSize.width*page_size, visibleSize.height));

	this->addChild(showScrollView,1);

	for (int i=1; i<=page_size; i++) {
		//背景
// 		CCSprite *bgsprite = CCSprite::create("deskBG@2x.png");
// 		bgsprite->setPosition(ccp(visibleSize.width * (i-0.5f), visibleSize.height / 2));
// 		slayer->addChild(bgsprite,1);

// 		CCString *nameString=CCString::createWithFormat("help/help_%02d.jpg",i);
// 
// 		CCLOG( " pic name ---> %s", nameString->getCString() );
// 
// 		CCSprite *sprite = CCSprite::create(nameString->getCString());
// 		sprite->setPosition(ccp(visibleSize.width * (i-0.5f), visibleSize.height / 2));
// 		slayer->addChild(sprite,1);


		/*CCLOG(" pic size --->  width:%f  ,  height:%f " , sprite->getContentSize().width , sprite->getContentSize().height);*/

// 		CCPoint point = ccp(visibleSize.width * (i-0.5f), visibleSize.height / 2);
// 		CCLOG(" position ---> width:%f  , height:%f" , point.x , point.y);


		CCString *nameString=CCString::createWithFormat("help/help_%02d.jpg",i);
		CCSprite *sprite = CCSprite::create(nameString->getCString());

		CCMenuItemSprite* pMenuItemSprite_small_left = CCMenuItemSprite::create(sprite,sprite , this, menu_selector(About::menuCallback));   
		MyMenu* pSpriteMenu_small_left = MyMenu::create(pMenuItemSprite_small_left,NULL);
		pSpriteMenu_small_left->setPosition(ccp(visibleSize.width * (i-0.5f), visibleSize.height / 2));
		slayer->addChild(pSpriteMenu_small_left,1);

		//传递CCScrollView对象(必须在CCScrollView create完后 调用)
		pSpriteMenu_small_left->setScrollView(showScrollView);
	}

	//Pagecontrol stuff
	//加载pagecontrol两张贴图到缓存中
	CCTextureCache::sharedTextureCache()->addImage("point_unchoose.png"); //未选中
	CCTextureCache::sharedTextureCache()->addImage("point_choose.png");//选中
	
	//居中显示
	for (int i=1; i<=page_size ;i++) {

		CCTexture2D *aTexture =CCTextureCache::sharedTextureCache()->textureForKey("point_unchoose.png");
		CCSprite *pageControlSprite=CCSprite::createWithTexture(aTexture);

		if(i==1)
		{
			pageControlSprite->setPosition(ccp( origin.x + (visibleSize.width - (page_size+((page_size-1)*0.5)) * pageControlSprite->getContentSize().width)/2 + pageControlSprite->getContentSize().width * (i-1), origin.y + 30));

		}else{

			pageControlSprite->setPosition(ccp( origin.x + (visibleSize.width - (page_size+((page_size-1)*0.5)) * pageControlSprite->getContentSize().width)/2 + pageControlSprite->getContentSize().width * (i-1) * 1.5, origin.y + 30));
		}

		pageControlSprite->setTag(100+i);
		this->addChild(pageControlSprite, 1);

	}

	//默认是第一页选中
	CCSprite *selectedSrite = (CCSprite *)this->getChildByTag(101);
	//换贴图
	CCTexture2D *aTexture =CCTextureCache::sharedTextureCache()->textureForKey("point_choose.png");
	selectedSrite->setTexture(aTexture);

	return true;
}

void About::onEnter()
{
	//触摸分发
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
	CCLayer::onEnter();
	CCLOG(" About scene onEnter --->");
}

void About::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


void About::menuCallback( CCObject* pSender )
{
	int id = ((CCNode *) pSender)->getTag();

	switch(id)
	{
		case 1:
		{
			CCDirector::sharedDirector()->purgeCachedData();

			CCScene* home = HelloWorld::scene();

			CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.5f,home));

			break;
		}

	default:
		break;
	}

	/*CCLOG(" click menu item --->");*/

}


void About::scrollViewDidScroll(CCScrollView *view)
{

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	int curPage= (int)fabsf(showScrollView->getContentOffset().x/visibleSize.width)+1;

	for (int i=1; i<=page_size; i++) {

		if (curPage==i) {

			CCSprite *selectedSrite = (CCSprite *)this->getChildByTag(100+curPage);

			CCTexture2D *aTexture =CCTextureCache::sharedTextureCache()->textureForKey("point_choose.png");

			selectedSrite->setTexture(aTexture);

		}
		else
		{

			CCSprite *selectedSrite = (CCSprite *)this->getChildByTag(100+i);

			CCTexture2D *aTexture =CCTextureCache::sharedTextureCache()->textureForKey("point_unchoose.png");

			selectedSrite->setTexture(aTexture);
		}
	}

	/*CCLOG("%d",curPage);*/

}


void About::scrollViewDidZoom( CCScrollView* view )
{

}

void About::adjustScrollView()
{
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

	CCLOG(" curPage: %d , page_size: %d" , curPage , page_size);
	CCLOG(" x : %d , dis_tance : %d " , x , dis_tance);

	if( abs(dis_tance)> srceen_width/4 ) //切换页 
	{
		if(dis_tance>0 && curPage != page_size) //下一页,且非最后一页
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


bool About::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	curPage= (int)fabsf(showScrollView->getContentOffset().x/visibleSize.width)+1;

	return true;
}

void About::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
// 	CCPoint startPoint = pTouch->getStartLocation();
// 	CCLOG(" startPoint ---> x :%f , y:%f" ,startPoint.x,startPoint.y);
// 
// 	CCPoint movePoint = pTouch->getLocation();
// 	CCLOG(" movePoint ---> x :%f , y:%f" ,movePoint.x,movePoint.y);
}

void About::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	adjustScrollView();
}

void About::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	adjustScrollView();
}

