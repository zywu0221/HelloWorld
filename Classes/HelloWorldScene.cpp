#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "AppMacros.h"
#include "AboutScene.h"

USING_NS_CC;

float top_distance;

CCSize* visibleSize;

const int MENU_ID_ABOUT = 3;
const int MENU_ID_START = 2;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{   
	if ( !CCLayer::init() )
    {
        return false;
    }

	CCLog(" HelloWorld  init --->");

	/*CCLog(" SCALE_FACTOR --->%f " , SCALE_FACTOR);*/

	top_distance = SCALE_FACTOR * 16;


    /*CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
 
    pCloseItem->setPosition(ccpAdd(VisibleRect::rightBottom(), 
                                ccp(-pCloseItem->getContentSize().width/2, pCloseItem->getContentSize().height/2)));
 
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);*/
 
    CCLabelTTF* pLabel = CCLabelTTF::create("hello cocos2d-x", "Arial", SCALE_FACTOR * 36 );
    pLabel->setPosition(ccpAdd(VisibleRect::top(),ccp(0, -pLabel->getContentSize().height)));
    this->addChild(pLabel, 1);
 
	//载入主菜单的pic list
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("main_menu.plist", "main_menu.png");


	//背景图片
    CCSprite* pSprite = CCSprite::create("bg.jpg");
    pSprite->setPosition(VisibleRect::center());
    this->addChild(pSprite, 0);
	
	//两片树叶
	//树叶1
	CCSprite* pSprite_leaf1 = CCSprite::createWithSpriteFrameName("leaf1.png");
	pSprite_leaf1->setPosition( ccpAdd(VisibleRect::center(), ccp(0,pSprite_leaf1->getContentSize().height/2*3)) );
	this->addChild(pSprite_leaf1);

	pSprite_leaf1->setAnchorPoint(ccp(0.5f,0.0f)); //设置锚点为中下点

	//不停摆动的动画
	CCActionInterval* rotateAction1 = CCRotateBy::create(0.1f,25.0f);
    CCActionInterval* rotateAction2 = CCRotateTo::create(0.1f, -25.0f);
	CCDelayTime* sleep_rotate = CCDelayTime::create(4.0f);

	pSprite_leaf1->runAction(CCRepeatForever::create((CCActionInterval*)(CCSequence::create(rotateAction1, rotateAction2,rotateAction1, rotateAction2,sleep_rotate, NULL))));

	//树叶2
	CCSprite* pSprite_leaf2 = CCSprite::createWithSpriteFrameName("leaf2.png");
	pSprite_leaf2->setPosition( ccpAdd(VisibleRect::center(), ccp(pSprite_leaf1->getContentSize().width,pSprite_leaf1->getContentSize().height/2*3)) );
	this->addChild(pSprite_leaf2);
	pSprite_leaf2->setAnchorPoint(ccp(0.5f,0.0f)); //设置锚点为中下点


	CCDelayTime* sleep_rotate_2 = CCDelayTime::create(2.0f);
	
	pSprite_leaf2->runAction(CCRepeatForever::create((CCActionInterval*)(CCSequence::create(sleep_rotate_2,rotateAction1, rotateAction2,rotateAction1, rotateAction2,sleep_rotate_2, NULL))));


	//小岛
	CCSprite* pSprite_Island = CCSprite::create("island.png");
    pSprite_Island->setPosition(VisibleRect::center());
    this->addChild(pSprite_Island, 0);



	//设置选项(左)
	CCMenuItemSprite* pMenuItemSprite_small_left = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("small_item_normal.png"), CCSprite::createWithSpriteFrameName("small_item_pressed.png") , this, menu_selector(HelloWorld::menuCallback));   
	
	CCMenu* pSpriteMenu_small_left = CCMenu::create(pMenuItemSprite_small_left,NULL);
	pSpriteMenu_small_left->setPosition( ccpAdd(VisibleRect::center(),ccp( - pSprite_Island->getContentSize().width / 2   ,- pSprite_Island->getContentSize().height/3)) );  
	this->addChild(pSpriteMenu_small_left ,1);

	
	//帮助选项(右)
	CCMenuItemSprite* pMenuItemSprite_small_right = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("small_item_normal.png"), CCSprite::createWithSpriteFrameName("small_item_pressed.png") , this,menu_selector(HelloWorld::menuCallback));   
	
	CCMenu* pSpriteMenu_small_right = CCMenu::create(pMenuItemSprite_small_right,NULL);
	pSpriteMenu_small_right->setPosition( ccpAdd(VisibleRect::center(),ccp(  pSprite_Island->getContentSize().width / 2   ,- pSprite_Island->getContentSize().height/3)) );  
	this->addChild(pSpriteMenu_small_right ,1);


	//开始游戏选项

	CCMenuItemSprite* pMenuItemSprite = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("start_normal.png"),  CCSprite::createWithSpriteFrameName("start_pressed.png"), this,menu_selector(HelloWorld::menuCallback));   
	pMenuItemSprite->setTag(MENU_ID_START);
	
	CCMenu* pSpriteMenu = CCMenu::create(pMenuItemSprite,NULL);    
	pSpriteMenu->setPosition( ccpAdd(VisibleRect::bottom(),ccp(0,pMenuItemSprite->getContentSize().height/2*3)) );   
	this->addChild(pSpriteMenu ,1); 


	//关于我们选项
	CCMenuItemSprite* pMenuItemSprite_about = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("about_us_normal.png"), CCSprite::createWithSpriteFrameName("about_us_pressed.png"), this,menu_selector(HelloWorld::menuCallback));   
	pMenuItemSprite_about->setTag(MENU_ID_ABOUT);

	CCMenu* pSpriteMenu_about = CCMenu::create(pMenuItemSprite_about,NULL);    
	pSpriteMenu_about->setPosition( ccpAdd(pSpriteMenu->getPosition(),ccp(- (pMenuItemSprite_about->getContentSize().width+(36*SCALE_FACTOR)),0 )) );   
	this->addChild(pSpriteMenu_about ,1); 


	//左上角心跳选项
	CCMenuItemSprite* pMenuItemSprite_heart = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("heart_normal.png"), CCSprite::createWithSpriteFrameName("heart_pressed.png") , this,menu_selector(HelloWorld::menuCallback));   
	
	CCMenu* pSpriteMenu_heart = CCMenu::create(pMenuItemSprite_heart,NULL);
	pSpriteMenu_heart->setPosition( ccpAdd(VisibleRect::leftTop(),ccp(pMenuItemSprite_heart->getContentSize().width / 2 + top_distance  , -pMenuItemSprite_heart->getContentSize().height / 2 - top_distance)) );  
	this->addChild(pSpriteMenu_heart ,1);

	//添加跳动的动画效果
	CCActionInterval* scaleAction1 = CCScaleTo::create(0.1f, 1.2f, 1.2f);
    CCActionInterval* scaleAction2 = CCScaleTo::create(0.1f, 1.0f, 1.0f);
	CCDelayTime* sleep = CCDelayTime::create(1.0f);

	CCActionInterval* seq = (CCActionInterval*)(CCSequence::create(scaleAction1, scaleAction2,scaleAction1, scaleAction2,sleep, NULL));
	CCActionInterval* rep = CCRepeatForever::create(seq);

	pMenuItemSprite_heart->runAction(rep);


	//小飞块 
	CCSprite* pS_fly = CCSprite::createWithSpriteFrameName("fly.png");
	pS_fly->setPosition( ccpAdd( pSpriteMenu_heart->getPosition() , ccp(pS_fly->getContentSize().width, -pS_fly->getContentSize().height*2) ) );

	this->addChild(pS_fly);

	//添加上下来回移动的动画效果
	CCMoveBy *move = CCMoveBy::create(3.5f,ccp(0,pS_fly->getContentSize().height));  
    pS_fly->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(move,move->reverse(),NULL))));  


    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


 void HelloWorld::menuCallback(CCObject* pSender)
{
	int menu_tag = ((CCNode*)pSender)->getTag();

	CCLog(" You press a button");
	CCLog(" tag is --->%i",((CCNode*)pSender)->getTag());

	switch(menu_tag){

	case MENU_ID_ABOUT:
		{
			//清空缓存
			CCDirector::sharedDirector()->purgeCachedData();

			CCScene *about = About::scene();

			CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.5f,about));

			break;
		}
	case MENU_ID_START:

		break;

	default:
		break;

	}
}

 void HelloWorld::onEnter()
 {
	 CCLayer::onEnter();
	 CCLOG(" HelloWorld  on Enter --->");
 }

 void HelloWorld::onExit()
 {
	 CCLayer::onExit();
	 CCLOG(" HelloWorld  on Exit --->");

	 //释放缓存
	/* CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("main_menu.plist");*/

 }

 void HelloWorld::onEnterTransitionDidFinish()
 {
	 CCLayer::onEnterTransitionDidFinish();
	 CCLOG(" HelloWorld  onEnterTransitionDidFinish --->");
 }

