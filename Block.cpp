//
//  Block.cpp
//  blocks
//
//  Created by MEME on 16/3/12.
//
//

#include "Block.hpp"
using namespace cocos2d;

Vector<Block*> * Block::blocks = new Vector<Block*>();
Vector<Block*> * Block::getBlocks(){
    return Block::blocks;
}


Block* Block::createWithArgs(Color3B color,Size size,std::string label,float frontSize,Color4B textColor){

    auto b = new Block();
    b->initWithArgs(color, size, label, frontSize, textColor);
    b->autorelease();
    
    blocks->pushBack(b);
    
    return b;
}


bool Block::initWithArgs(Color3B color,Size size,std::string label,float frontSize,Color4B textColor){
	
	lineIndex = 0;
    Sprite::init();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    setContentSize(size);
    setAnchorPoint(Point::ZERO);
    setTextureRect(Rect(0,0,size.width,size.height));
    setColor(color);
    
    //auto l=Label::createWithTTF(, , )()
    
    //auto l = Label::create();
    auto l = Label::createWithTTF(label, "fonts/Marker Felt.ttf", frontSize);
    
    //l->setString(label);
    //l->setSystemFontSize(frontSize);
    l->setTextColor(textColor);
    addChild(l);
    l->setPosition(size.width/2,size.height/2);
    
//    auto l = Label::create();
//    l->setString(label);
//    l->setSystemFontSize(frontSize);
//    l->setTextColor(textColor);
//    addChild(l);
//    l->setPosition(size.width/2,size.height/2);
    
    
    return true;
    
}

void Block::removeBlock(){
    
    auto c = getColor();
    
    log("remove block,color is (%d,%d,%d)",c.r,c.g,c.b);
    
    removeFromParent();
    blocks->eraseObject(this);
}

int Block::getLineIndex(){
	
	return this->lineIndex;
}
void Block::setLineIndex(int v){
	this->lineIndex = v;
}

void Block::moveDown(){
    this->lineIndex--;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
//    
//    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), lineIndex*visibleSize.height/4)),
//                               CallFunc::create([this](){
//        
//        if (lineIndex<0) {
//            this->removeBlock();
//        }
//        
//    }), NULL));
    
    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(),lineIndex*visibleSize.height/4)),CallFunc::create([this](){if(lineIndex<0){this->removeBlock();}}),NULL));
}





















