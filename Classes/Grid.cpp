//
//  Grid.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "Grid.h"
#include "Tetromino.h"

#pragma mark -
#pragma mark Lifecycle

bool Grid::init()
{
    if (! Sprite::initWithFile("grid.png")) {
        return false;
    }

    this->activeTetromino = nullptr;

    return true;
}

void Grid::onEnter()
{
    Sprite::onEnter();

    this->activeTetromino = Tetromino::createWithType(TetrominoType::L);
    this->addChild(this->activeTetromino);
}

#pragma mark -
#pragma mark Public Methods

void Grid::rotateActiveTetromino()
{
    if (this->activeTetromino) {
        this->activeTetromino->rotate(true);
    }

    // TODO: Check if collision, undo rotation



    
}
