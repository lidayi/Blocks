#include "HelloWorldScene.h"
#include "Block.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    ///////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
    //    // position the sprite on the center of the screen b = *it;
    
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    srand(time(NULL));
    
    gameLayer = Node::create();
    addChild(gameLayer);
    timeLabel = Label::create();
    timeLabel->setTextColor(Color4B::BLUE);
    timeLabel->setSystemFontSize(25);
    timeLabel->setPosition(visibleSize.width/2+150,visibleSize.height-10);
    timeLabel->setString("0.0000000");
    addChild(timeLabel);
    //addEndLine();
	stareGame();
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [this](Touch* touch,Event* event){
        log("on touch");
        Block *b;
        auto bs = Block::getBlocks();
        for (auto it=bs->begin();it!=bs->end(); it++) {
            b = *it;
            
            if (b->getLineIndex()==1&&
                b->getBoundingBox().containsPoint(touch->getLocation())){
                if (b->getColor()==Color3B::BLACK) {
                    if(!timerRunning){
                        this->startTimer();
                    }
                    b->setColor(Color3B::GRAY);
                    this->moveDown();
                }else if(b->getColor()==Color3B::GRAY){
                    this ->moveDown();
                    this ->stopTimer();
                }
                else{
                    MessageBox("GameOver", "失败");
                }
                break;
                
            }
            }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::addStartLine(){
    auto b = Block::createWithArgs(Color3B::YELLOW, Size(visibleSize.width+150,visibleSize.height/4), "", 10, Color4B::BLACK);
    gameLayer->addChild(b,0);
	b->setLineIndex(0);
    
}

void HelloWorld::addEndLine(){
    //Color4B color = ccc4(238, 118, 0, 255);
    auto b = Block::createWithArgs(Color3B::GRAY, Size(visibleSize.width+200,visibleSize.height), "over", 30, Color4B(238, 118, 0, 200));
    gameLayer->addChild(b,0);
	b->setLineIndex(4);
}

void HelloWorld::addNormallLine(int lineindex){
	
	Block *b;
	int blockIndex = rand()%4;
	
	for (int i = 0 ; i<4; i++) {
		b = Block::createWithArgs(blockIndex == i?Color3B::BLACK:Color3B::WHITE,Size (visibleSize.width/4-1,visibleSize.height/4-1) , "", 20, Color4B::BLACK);
		gameLayer->addChild(b,0);
		
		b->setPosition(i*(visibleSize.width/4)+150,lineindex*(visibleSize.height/4));
		b->setLineIndex(lineindex);
	}
    linesCount++;
}

void HelloWorld::moveDown(){
    
    if (linesCount<10) {
         addNormallLine(4);
    }else if(!showEnd){
        addEndLine();
        showEnd = true;
    }
    
    //addNormallLine(4);
    
    auto bs=Block::getBlocks();
    for (auto it = bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }

        
}

void HelloWorld::stareGame(){
    linesCount = 0;
    timerRunning = false;
    showEnd = false;
	addStartLine();
	addNormallLine(1);
	addNormallLine(2);
	addNormallLine(3);
}

void HelloWorld::update(float dt){
    long offset = clock()-startTime;
    timeLabel->setString( StringUtils::format("%g",((double)offset)/1000000));
    
}

void HelloWorld::startTimer(){
    if (!timerRunning) {
        scheduleUpdate();
        startTime = clock();
        timerRunning = true;
    }
    
}

void HelloWorld::stopTimer(){
    if (timerRunning) {
        unscheduleUpdate();
        timerRunning = false;
    }
}



























