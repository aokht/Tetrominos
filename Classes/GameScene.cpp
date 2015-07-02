//
//  GameScene.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "GameScene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Tetromino.h"

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
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        return true;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
        grid->rotateActiveTetromino();
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