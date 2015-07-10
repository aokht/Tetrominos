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

#pragma mark -
#pragma mark LifeCycles

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
    this->blocks.reserve(BLOCKS_PER_TETROMINO);

    this->rotationIndex = 0;


    Sprite* dummyBlock = Sprite::create("block.png");
    Size dummySize = dummyBlock->getContentSize();
    float gridSizeF = float(GRID_SIZE);
    this->setContentSize(Size(dummySize.width * gridSizeF, dummySize.height * gridSizeF));

    auto coordinates = rotations[this->rotationIndex];
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

#pragma mark -
#pragma mark Public Methods

void Tetromino::rotate(bool right)
{
    if (right) {
        this->rotationIndex++;
    } else {
        this->rotationIndex--;
    }

    int rotationSize = (int)rotations.size();
    if (rotationIndex >= rotationSize) {
        rotationIndex = 0;
    } else if (rotationIndex < 0) {
        rotationIndex = rotationSize - 1;
    }

    std::vector<Coordinate> coordinates = this->rotations[rotationIndex];
    for (int i = 0; i != GRID_SIZE; ++i) {
        Coordinate coordinate = coordinates[i];
        Sprite* block = this->blocks[i];

        Size size = block->getContentSize();
        block->setPosition(Vec2(coordinate.x * size.width, coordinate.y * size.height));
    }
}

int Tetromino::getHighestYCoordinate()
{
    int max_y = 0;
    for (Coordinate coordinate : this->rotations[this->rotationIndex]) {
        max_y = std::max(max_y, coordinate.y);
    }

    return max_y;
}

int Tetromino::getWidthInBlocks()
{
    int min_x = GRID_SIZE;
    int max_x = 0;

    for (Coordinate coordinate : this->rotations[this->rotationIndex]) {
        max_x = std::max(max_x, coordinate.x);
        min_x = std::min(min_x, coordinate.x);
    }

    return max_x - min_x + 1;
}

int Tetromino::getMinimumXCoordinate()
{
    int min_x = GRID_SIZE;
    for (Coordinate coordinate : this->rotations[this->rotationIndex]) {
        min_x = std::min(min_x, coordinate.x);
    }

    return min_x;
}

std::vector<int> Tetromino::getSkirt()
{
    int width = this->getWidthInBlocks();
    int skirtStart = this->getMinimumXCoordinate();

    std::vector<int> skirt = std::vector<int>(width, GRID_SIZE);

    for (Coordinate coordinate : this->rotations[this->rotationIndex]) {
        int x = coordinate.x - skirtStart;
        int skirtY = skirt[x];

        skirt[x] = std::min(coordinate.y, skirtY);
    }

    return skirt;
}

std::vector<Sprite*> Tetromino::getBlocks()
{
    return this->blocks;
}


std::vector<Coordinate> Tetromino::getCurrentRotaion()
{
    return rotations[rotationIndex];
}

TetrominoType Tetromino::getTetrominoType()
{
    return this->type;
}