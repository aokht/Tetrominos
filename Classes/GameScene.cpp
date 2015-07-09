//
//  GameScene.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include <time.h>
#include "GameScene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Tetromino.h"
#include "Coordinate.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

bool GameScene::init()
{
    if (! Node::init()) {
        return false;
    }

    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(background);

    this->tetrominoBag = std::unique_ptr<TetrominoBag>(new TetrominoBag());

    this->active = false;

    return true;
}

void GameScene::onEnter()
{
    Node::onEnter();

    Size visibleSize = Director::getInstance()->getVisibleSize();

    // setup grid
    this->grid = Grid::create();
    this->grid->setAnchorPoint(Vec2(0.5f, 0.0f));
    this->grid->setPosition(Vec2(visibleSize.width * 0.5f, 0.0f));
    this->addChild(this->grid);

    Tetromino* randomTest = this->createRandomTetromino();
    grid->spawnTetromino(randomTest);

    // setup menus
    ui::Button* backButton = ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    backButton->setPosition(Vec2(0.0f, visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(GameScene::backButtonPressed, this));
    this->addChild(backButton);

    this->setupTouchHandling();
    this->setGameActive(true);
}

void GameScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();

    static Vec2 firstTouchPos;
    static Vec2 lastTouchPos;
    static bool allowRotate;
    static std::clock_t touchStartedTime;

    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        firstTouchPos = this->convertTouchToNodeSpace(touch);
        lastTouchPos = firstTouchPos;
        allowRotate = true;
        touchStartedTime = clock();
        return true;
    };
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);

        Vec2 difference = touchPos - lastTouchPos;

        Tetromino* activeTetromino = grid->getActiveTetromino();
        if (activeTetromino) {
            Coordinate differenceCoordinate = this->convertPositionToCoordinate(difference);
            Coordinate activeTetrominoCoordinate = grid->getActiveTetrominoCoordinate();

            if (differenceCoordinate.y <= -1) {
                Coordinate newTetrominoCoordinate = Coordinate(activeTetrominoCoordinate.x, activeTetrominoCoordinate.y - 1);
                grid->setActiveTetrominoCoordinate(newTetrominoCoordinate);
                lastTouchPos = touchPos;

            }
            else if (abs(differenceCoordinate.x) >= 1) {
                Coordinate newTetrominoCoordinate;
                // we must mov tetromino

                bool movingRight = (differenceCoordinate.x > 0);
                newTetrominoCoordinate = Coordinate(activeTetrominoCoordinate.x + (movingRight ? 1 : -1), activeTetrominoCoordinate.y);

                grid->setActiveTetrominoCoordinate(newTetrominoCoordinate);
                allowRotate = false;
                lastTouchPos = touchPos;
            }

        }

    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
        Vec2 touchEndPos = this->convertTouchToNodeSpace(touch);
        float distance =  touchEndPos.distance(firstTouchPos);
        Size blockSize = this->grid->getBlockSize();

        // detect tap
        if (distance < blockSize.width && allowRotate) {
            grid->rotateActiveTetromino();
        }
        // detect swipe down
        else {
            Vec2 difference = touchEndPos - firstTouchPos;
            float touchDuration = (float)(clock() - touchStartedTime) / CLOCKS_PER_SEC;
            float velocity = fabsf(difference.y / touchDuration);

            CCLOG("%lf", velocity);
            if (velocity > DROP_VELOCITY) {
                CCLOG("DROP!");
                // TODO: Implement tetromino dropping
            }
            else {
            }
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}


#pragma mark -
#pragma mark Public Methods


#pragma mark -
#pragma mark Protected Methods

Tetromino* GameScene::createRandomTetromino()
{
    TetrominoType tetrominoType = tetrominoBag->getTetromino();
    Tetromino* newTetromino = Tetromino::createWithType(tetrominoType);
    return newTetromino;
}

#pragma mark -
#pragma mark UI Methods

void GameScene::backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        SceneManager::getInstance()->returnToLobby();
    }
}

void GameScene::setGameActive(bool active)
{
    this->active = active;

    if (active) {
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::step), INITIAL_STEP_INTERVAL);

    } else {
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::step));
        
    }
}

void GameScene::step(float dt)
{
    this->grid->step();
}

#pragma mark -
#pragma mark Utility Methods


Coordinate GameScene::convertPositionToCoordinate(cocos2d::Vec2 position)
{
    Size blockSize = this->grid->getBlockSize();

    return Coordinate(position.x / blockSize.width, position.y / blockSize.height);
    
}
