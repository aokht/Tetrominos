//
//  GameScene.h
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#ifndef __Tetrominos__GameScene__
#define __Tetrominos__GameScene__

#include "cocos2d.h"
#include "cocosGUI.h"
#include "TetrominoBag.h"

class Grid;
class Tetromino;
class Coordinate;

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);


protected:
    Grid* grid;

    // Lifecycle
    bool init() override;
    void onEnter() override;
    void step(float dt);
    cocos2d::ui::Text* scoreLabel;
    void updateStateFromScore();
    int totalScore;

    void setupTouchHandling();

    std::unique_ptr<TetrominoBag> tetrominoBag;
    Tetromino* createRandomTetromino();
    void setGameActive(bool active);
    bool active;

    // Utility
    Coordinate convertPositionToCoordinate(cocos2d::Vec2 position);

    // UI
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void updateScoreLabel(int score);


};
#endif /* defined(__Tetrominos__GameScene__) */
