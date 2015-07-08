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
    Coordinate convertPositionToCoordinate(cocos2d::Vec2 position);


protected:
    Grid* grid;

    bool init() override;
    void onEnter() override;
    void step(float dt);

private:
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void setupTouchHandling();
    void setGameActive(bool active);

    std::unique_ptr<TetrominoBag> tetrominoBag;
    Tetromino* createRandomTetromino();
    bool active;


};
#endif /* defined(__Tetrominos__GameScene__) */
