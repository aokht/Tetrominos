//
//  Grid.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "Grid.h"
#include "Tetromino.h"
#include "Coordinate.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

bool Grid::init()
{
    if (! Sprite::initWithFile("grid.png")) {
        return false;
    }

    this->activeTetromino = nullptr;
    this->activeTetrominoCoordinate = Coordinate();
    
    return true;
}

void Grid::onEnter()
{
    Sprite::onEnter();
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

void Grid::spawnTetromino(Tetromino *tetromino)
{
    this->activeTetromino = tetromino;

    // TODO: Place tetromino in correct position in grid

    this->activeTetromino->setAnchorPoint(Vec2(0.0f, 0.0f));

    int highestY = activeTetromino->getHighestYCoordinate();
    int width = activeTetromino->getWidthInBlocks();

    Coordinate spawnCoordinate = Coordinate(GRID_WIDTH / 2 - width / 2 - 1, GRID_HEIGHT - highestY - 1);
    this->setActiveTetrominoCoordinate(spawnCoordinate);

    this->addChild(this->activeTetromino);
}

void Grid::step()
{
    Coordinate activeCoordinate = this->getActiveTetrominoCoordinate();
    Coordinate nextCoordinate = Coordinate(activeCoordinate.x, activeCoordinate.y - 1);

    this->setActiveTetrominoCoordinate(nextCoordinate);

}

#pragma mark -
#pragma mark Setters / Getters

void Grid::setActiveTetrominoCoordinate(Coordinate coordinate)
{
    if (activeTetromino) {
        activeTetrominoCoordinate = coordinate;
        activeTetromino->setPosition(convertCoordinateToPosition(activeTetrominoCoordinate));
    }
}

Coordinate Grid::getActiveTetrominoCoordinate()
{
    return this->activeTetrominoCoordinate;
}


#pragma mark -
#pragma mark Private Methods

Vec2 Grid::convertCoordinateToPosition(Coordinate coordinate)
{
    Size contentSize = this->getContentSize();
    float blockWidth = contentSize.width / float(GRID_WIDTH);
    float blockHeight = contentSize.height / float(GRID_HEIGHT);

    return Vec2(coordinate.x * blockWidth, coordinate.y * blockHeight);
}
