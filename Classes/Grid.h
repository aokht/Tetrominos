//
//  Grid.h
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#ifndef __Tetrominos__Grid__
#define __Tetrominos__Grid__

#include "cocos2d.h"
#include "Coordinate.h"

class Tetromino;

class Grid : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Grid);

    void rotateActiveTetromino();
    void spawnTetromino(Tetromino* tetromino);

    void step();

    void setActiveTetrominoCoordinate(Coordinate coordinate);
    Coordinate getActiveTetrominoCoordinate();

    cocos2d::Size getBlockSize();
    Tetromino* getActiveTetromino();
    void dropActiveTetromino();


protected:
    bool init() override;
    void onEnter() override;

private:
    Tetromino* activeTetromino;
    Tetromino* ghostTetromino;
    Coordinate activeTetrominoCoordinate;
    cocos2d::Vec2 convertCoordinateToPosition(Coordinate coordinate);
    std::vector<std::vector<cocos2d::Sprite*>> blocksLanded;


    bool checkIfTetrominoCollides(Tetromino* tetromino, Coordinate tetrominoCoordinate);

    void deactivateTetromino(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    void placeTetrominoOnBoard(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    Coordinate getTetrominoLandingCoordinate();
    void clearLines();
    void updateGhostTetrominoPosition();
    
};

#endif /* defined(__Tetrominos__Grid__) */
