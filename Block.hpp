//
//  Block.hpp
//  blocks
//
//  Created by MEME on 16/3/12.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include <cocos2d.h>
using namespace cocos2d;

class Block:public Sprite{
private:
    static Vector<Block*> * blocks;
    
	int lineIndex;

	
public:
    static Vector<Block*> * getBlocks();
    virtual bool initWithArgs(Color3B color,Size size,std::string label,float frontSize,Color4B textColor);
    static Block* createWithArgs(Color3B color,Size size,std::string label,float frontSize,Color4B textColor);
    void removeBlock();
	int getLineIndex();
	void setLineIndex(int lineIndex);
    
    void moveDown();

    
};



#endif /* Block_hpp */
