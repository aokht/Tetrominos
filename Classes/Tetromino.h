//
//  Tetromino.h
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#ifndef __Tetrominos__Tetromino__
#define __Tetrominos__Tetromino__

#include "cocos2d.h"
#include "Constants.h"
#include "Coordinate.h"

class Tetromino : public cocos2d::Node
{
public:
    static Tetromino* createWithType(TetrominoType type);

    void rotate(bool right);

    TetrominoType getTetrominoType();
    int getHighestYCoordinate();
    int getWidthInBlocks();
    int getMinimumXCoordinate();
    std::vector<int> getSkirt();
    std::vector<cocos2d::Sprite*> getBlocks();
    std::vector<Coordinate> getCurrentRotaion();


private:
    bool initWithType(TetrominoType type);
    CREATE_FUNC(Tetromino);

    TetrominoType type;
    cocos2d::Color3B color;
    std::vector<std::vector<Coordinate>> rotations;
    std::vector<cocos2d::Sprite*> blocks;

    int rotationIndex;
};

#endif /* defined(__Tetrominos__Tetromino__) */
