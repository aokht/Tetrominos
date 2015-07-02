//
//  Grid.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "Grid.h"
#include "Tetromino.h"

bool Grid::init()
{
    if (! Sprite::initWithFile("grid.png")) {
        return false;
    }

    return true;
}