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

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);

protected:
    Grid* grid;

    bool init() override;
    void onEnter() override;

private:
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void setupTouchHandling();

    std::unique_ptr<TetrominoBag> tetrominoBag;
    Tetromino* createRandomTetromino();


};
#endif /* defined(__Tetrominos__GameScene__) */
