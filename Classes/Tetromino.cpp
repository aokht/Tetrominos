//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "Tetromino.h"

using namespace cocos2d;

Tetromino* Tetromino::createWithType(TetrominoType type)
{
    Tetromino* tetromino = Tetromino::create();
    if (tetromino && tetromino->initWithType(type)) {
        return tetromino;
    }

    return nullptr;
}

bool Tetromino::initWithType(TetrominoType type)
{
    if (! Node::init()) {
        return false;
    }

    this->type = type;

    this->rotations = std::vector<std::vector<Coordinate>>();

    return true;
}