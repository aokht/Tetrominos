//
//  SceneManager.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "SceneManager.h"
#include "GameScene.h"

using namespace cocos2d;

#pragma mark -
#pragma mark LifeCycles

static SceneManager* sharedInstance = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (! sharedInstance) {
        sharedInstance = new (std::nothrow)SceneManager();
    }

    return sharedInstance;
}


SceneManager::SceneManager()
{
    this->networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->networkingWrapper->setDelegate(this);

    this->gameScene = nullptr;
}
SceneManager::~SceneManager()
{

}

#pragma mark -
#pragma mark Public Methods

void SceneManager::enterGameScene(bool networked)
{
    Scene* scene = Scene::create();
    this->gameScene = GameScene::create();
    this->gameScene->setNetworkedSession(networked);
    scene->addChild(this->gameScene);

    Director::getInstance()->pushScene(scene);
}

void SceneManager::returnToLobby()
{
    if (gameScene) {
        Director::getInstance()->popScene();
        gameScene = nullptr;
        networkingWrapper->disconnect();
    }
}

void SceneManager::showPeerList()
{
    networkingWrapper->showPeerList();
}

void SceneManager::receiveMutiplayerInvitations()
{
    networkingWrapper->startAdvertisingAvailability();
}

void SceneManager::sendData(const void *data, unsigned long length)
{
    networkingWrapper->sendData(data, length);
}

#pragma mark -
#pragma mark NetworkingWrapper

void SceneManager::receivedData(const void *data, unsigned long length)
{
    if (gameScene) {
        gameScene->receivedData(data, length);
    }
}


void SceneManager::stateChanged(ConnectionState state)
{
    switch (state) {
        case ConnectionState::CONNECTING:
            CCLOG("Connecting...");
            break;
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected...");
            break;

        case ConnectionState::CONNECTED:
            CCLOG("Connected...");
            if (! gameScene) {
                this->networkingWrapper->stopAdvertisingAvailability();
                this->enterGameScene(true);
            }
            break;


    }
}