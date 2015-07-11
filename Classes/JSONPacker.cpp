//
//  JSONPacker.cpp
//  Tetrominos
//
//  Created by Akihito OKUHATA on 2015/07/01.
//
//

#include "JSONPacker.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "Coordinate.h"

using namespace cocos2d;

namespace JSONPacker
{

    TetrominoState unpackTetrominoJSON(std::string json, TetrominoType type)
    {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());

        const char* typeStr;
        switch (type)
        {
            case TetrominoType::I: typeStr = "I"; break;
            case TetrominoType::O: typeStr = "O"; break;
            case TetrominoType::T: typeStr = "T"; break;
            case TetrominoType::S: typeStr = "S"; break;
            case TetrominoType::Z: typeStr = "Z"; break;
            case TetrominoType::J: typeStr = "J"; break;
            case TetrominoType::L: typeStr = "L"; break;
        }

        rapidjson::Value& tetrominoDoc = document[typeStr];

        rapidjson::Value& colorDoc = tetrominoDoc["color"];
        int r = colorDoc["r"].GetInt();
        int g = colorDoc["g"].GetInt();
        int b = colorDoc["b"].GetInt();
        Color3B color(r, g, b);

        std::vector<std::vector<Coordinate>> rotations;
        rapidjson::Value& rotationDoc = tetrominoDoc["rotations"];

        for (rapidjson::SizeType rotationIndex = 0; rotationIndex < rotationDoc.Size(); ++rotationIndex) {
            rapidjson::Value& rDoc = rotationDoc[rotationIndex];

            std::vector<Coordinate> r;
            for (rapidjson::SizeType rIndex = 0; rIndex < rDoc.Size(); ++rIndex) {
                rapidjson::Value& coordinateDoc = rDoc[rIndex];
                int x = coordinateDoc["x"].GetInt();
                int y = coordinateDoc["y"].GetInt();
                r.push_back(Coordinate(x, y));
            }

            rotations.push_back(r);
        }

        TetrominoState tetrominoState;
        tetrominoState.color = color;
        tetrominoState.rotations = rotations;

        return tetrominoState;
    }

    std::string packGameState(const GameState gameState)
    {
        rapidjson::Document document;
        document.SetObject();

        document.AddMember("score", gameState.score, document.GetAllocator());
        document.AddMember("name", gameState.name.c_str(), document.GetAllocator());
        document.AddMember("gameOver", gameState.gameOver, document.GetAllocator());

        rapidjson::Value columns(rapidjson::kArrayType);
        for (int column = 0; column < gameState.board.size(); ++column) {
            rapidjson::Value blocks(rapidjson::kArrayType);
            for (int index = 0; index < gameState.board[column].size(); ++index) {
                Color3B color = gameState.board[column][index];

                rapidjson::Value colorJson(rapidjson::kObjectType);
                colorJson.AddMember("r", color.r, document.GetAllocator());
                colorJson.AddMember("g", color.g, document.GetAllocator());
                colorJson.AddMember("b", color.b, document.GetAllocator());

                blocks.PushBack(colorJson, document.GetAllocator());
            }

            columns.PushBack(blocks, document.GetAllocator());
        }
        document.AddMember("board", columns, document.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::string returnString(buffer.GetString());

        return returnString;
    }

    GameState unpackGameStateJSON(std::string json)
    {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());

        GameState gameState;

        gameState.score = document["score"].GetInt();
        gameState.name = document["name"].GetString();
        gameState.gameOver = document["gameOver"].GetBool();

        rapidjson::Value& columns = document["board"];
        for (rapidjson::SizeType column = 0; column < columns.Size(); ++column) {
            rapidjson::Value& blocksJson = columns[column];
            std::vector<Color3B> blocks;

            for (rapidjson::SizeType index = 0; index < blocksJson.Size(); ++index) {
                rapidjson::Value& block = blocksJson[index];
                int r = block["r"].GetInt();
                int g = block["g"].GetInt();
                int b = block["b"].GetInt();
                Color3B color = Color3B(r, g, b);
                blocks.push_back(color);
            }

            gameState.board.push_back(blocks);
        }

        return gameState;
    }

}