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
#include "NetworkingWrapper.h"

class Grid;
class Tetromino;
class Coordinate;
class PreviewGrid;

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);

    void setNetworkedSession(bool networkedSession);
    void receivedData(const void* data, unsigned long length);

protected:
    Grid* grid;
    cocos2d::ui::Text* scoreLabel;
    cocos2d::ui::Text* timeLeftLabel;
    int totalScore;
    float stepInterval;
    std::unique_ptr<TetrominoBag> tetrominoBag;
    bool active;
    float timeLeft;
    bool networkedSession;
    bool gameIsOver;
    PreviewGrid* previewGrid;

    // Lifecycle
    bool init() override;
    void onEnter() override;
    void setupTouchHandling();

    // Game Logic
    Tetromino* createRandomTetromino();
    void setGameActive(bool active);
    void step(float dt);
    void update(float dt) override;
    void updateStateFromScore();
    void updateGameSpeed(int score);
    void gameOver();
    void setTimeLeft(float time);

    // Networking
    void sendGameStateOverNetwork();

    // Utility
    Coordinate convertPositionToCoordinate(cocos2d::Vec2 position);

    // UI
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void updateScoreLabel(int score);


};
#endif /* defined(__Tetrominos__GameScene__) */
