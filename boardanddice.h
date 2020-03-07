#ifndef SNAKEANDLADDER_BOARDANDDICE_H
#define SNAKEANDLADDER_BOARDANDDICE_H

#include <map>
#include "player.h"
#include <thread>

class BoardAndDice : public Player
{

public:
     std::string currPlayerName;
     int currPos;
     int prevPos;
     int randNum;
     bool drawLuckyNum;
     bool gameFinished;
     BoardAndDice()
         : drawLuckyNum(false), randNum(0), currPlayerName(" "), currPos(0), gameFinished(false)
     {
          initSnakeAndLadderPos();
     }

     void initSnakeAndLadderPos();
     void rollTheDice();
     void runningNumbers();
     void checkUpsandDowns();
     void startGame();
     void isClimbLadder();
     void isSnakeCaught();
     void isOpponentHitted();
     void checkUpdatedCurrPosStatus();

private:
     std::map<int, int> SnakeHeadAndTailPos;
     std::map<int, int> LadderStartAndEnd;
};

#endif