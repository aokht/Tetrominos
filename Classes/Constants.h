//
//  Constants.h
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#ifndef Tetrominos_Constants_h
#define Tetrominos_Constants_h

static const int GRID_WIDTH = 10;
static const int GRID_HEIGHT = 20;

static const int BLOCKS_PER_TETROMINO = 4;

static const float INITIAL_STEP_INTERVAL = 1.0f;
static const int SCORE_TO_ACCELERATE = 5;
static const float ACCELERATION_FACTOR = 0.9f;
static const float SPPED_MAX = .05f;

static const float DROP_VELOCITY = 10000.0f;

enum class TetrominoType {
    I = 0,
    O = 1,
    T = 2,
    S = 3,
    Z = 4,
    J = 5,
    L = 6
};

#endif
