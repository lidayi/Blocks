#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

class HelloWorld : public cocos2d::Layer
{
private:
	    cocos2d::Size visibleSize;
    int linesCount;
    bool showEnd;
    cocos2d::Label *timeLabel;
    Node *gameLayer;
    bool timerRunning;
    long startTime;
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void addStartLine();
    void addEndLine();
	void addNormallLine(int index);
	
    void startTimer();
    void stopTimer();
    
	void stareGame();
    void moveDown();
    
};

#endif // __HELLOWORLD_SCENE_H__
