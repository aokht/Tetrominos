//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "Tetromino.h"
#include "JSONPacker.h"

#define GRID_SIZE 4

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

    std::string jsonString = FileUtils::getInstance()->getStringFromFile("tetrominos.json");
    JSONPacker::TetrominoState tetrominoState = JSONPacker::unpackTetrominoJSON(jsonString, type);

    this->type = type;
    this->color = tetrominoState.color;
    this->rotations = tetrominoState.rotations;

    this->blocks = std::vector<Sprite*>(4);

    Sprite* dummyBlock = Sprite::create("block.png");
    Size dummySize = dummyBlock->getContentSize();
    float gridSizeF = float(GRID_SIZE);
    this->setContentSize(Size(dummySize.width * gridSizeF, dummySize.height * gridSizeF));

    auto coordinates = rotations[0];
    for (Coordinate coordinate : coordinates) {
        Sprite* block = Sprite::create("block.png");
        block->setColor(this->color);
        block->setAnchorPoint(Vec2(0.0f, 0.0f));
        block->setPosition(Vec2(coordinate.x * dummySize.width, coordinate.y * dummySize.height));

        this->addChild(block);
        this->blocks.push_back(block);
    }

    return true;
}