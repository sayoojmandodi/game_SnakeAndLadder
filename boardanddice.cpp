#include "boardanddice.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <thread>

void BoardAndDice::rollTheDice()
{
     this->randNum = rand();
     this->randNum %= 6;
     if (this->randNum == 0)
          this->randNum = 6;
}

void BoardAndDice ::runningNumbers()
{
     int i = 0;
     while (drawLuckyNum != true)
     {
          ++i;
          fflush(stdout);
          usleep(120000);
          std::cout << i << " ";
          if (i == 6)
          {
               i = 0;
               std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b";
          }
     }

     std::cout << "\b\b\b   ";
     drawLuckyNum = false;
}

void BoardAndDice ::isClimbLadder()
{
     auto it = LadderStartAndEnd.find(currPos);
     if (it != LadderStartAndEnd.end())
     {
          std::cout << "\nHurray $$$ You are climbing from Pos :" << currPos;
          currPos = it->second;
          playerDetails.at(currPlayerName) = currPos;
          std::cout << " to Pos :" << currPos << std::endl;
     }
}

void BoardAndDice::isSnakeCaught()
{

     auto it = SnakeHeadAndTailPos.find(currPos);
     if (it != SnakeHeadAndTailPos.end())
     {
          std::cout << "\noops :( --xxxx-- Snake Caught You from Pos :" << currPos;
          currPos = it->second;
          playerDetails.at(currPlayerName) = currPos;
          std::cout << " going down to Pos :" << currPos << std::endl;
     }
}

void BoardAndDice::isOpponentHitted()
{
     for (auto &i : playerDetails)
     {
          if (i.second == currPos && currPlayerName != i.first) // Hitting the Other Opposition
          {
               i.second = 0;
               std::cout << "\nYou Hitted " << i.first << ":)" << std::endl;
          }
     }
}

void BoardAndDice::checkUpsandDowns()
{
     isClimbLadder();
     isSnakeCaught();
     isOpponentHitted();
}

void BoardAndDice::initSnakeAndLadderPos()
{

     SnakeHeadAndTailPos.insert(std::make_pair<int, int>(37, 17));
     SnakeHeadAndTailPos.insert(std::make_pair<int, int>(31, 14));
     SnakeHeadAndTailPos.insert(std::make_pair<int, int>(78, 9));
     SnakeHeadAndTailPos.insert(std::make_pair<int, int>(73, 53));
     SnakeHeadAndTailPos.insert(std::make_pair<int, int>(99, 7));
     SnakeHeadAndTailPos.insert(std::make_pair<int, int>(92, 35));

     LadderStartAndEnd.insert(std::make_pair<int, int>(5, 25));
     LadderStartAndEnd.insert(std::make_pair<int, int>(10, 29));
     LadderStartAndEnd.insert(std::make_pair<int, int>(22, 41));
     LadderStartAndEnd.insert(std::make_pair<int, int>(28, 55));
     LadderStartAndEnd.insert(std::make_pair<int, int>(44, 95));
     LadderStartAndEnd.insert(std::make_pair<int, int>(70, 89));
     LadderStartAndEnd.insert(std::make_pair<int, int>(79, 81));
}

void BoardAndDice::checkUpdatedCurrPosStatus()
{

     if (currPos > 100)
     {
          std::cout << "Next Pos will be " << currPos << " Not Valid" << std::endl;
          std::cout << "You need " << 100 - prevPos << " to win or less Num to move to next Pos" << std::endl;
          currPos = prevPos;
     }
     else if (currPos == 100)
     {
          std::cout << std::endl
                    << currPlayerName << " Won the game " << std::endl;
          gameFinished = true;
     }
     else
     {
          std::cout << "\n              Updated pos is : " << currPos << std::endl;
          checkUpsandDowns();
     }

     playerDetails.at(currPlayerName) = currPos;
}

void BoardAndDice::startGame()
{
     while (!gameFinished)
     {
          for (auto &i : playerDetails)
          {
               std::cout << "----------------                  ------------------\n\n"
                         << i.first << " Playing ::  Press Enter to Start && Stop \n";

               std::cin.get();
               std::cout << "               ";
               std::thread th1(&BoardAndDice::runningNumbers, this);

               std::cin.get();
               drawLuckyNum = true; // This variable is responsible to will cause the system to come out of while loop in thread.

               th1.join();
               th1.~thread();

               rollTheDice();

               std::cout
                   << "\n          $$$ Dice Stays at " << randNum << " $$$ " << std::endl;
               std::cout << "              Prev Pos is :" << i.second;

               prevPos = currPos;
               currPos = i.second + randNum;
               currPlayerName = i.first;

               checkUpdatedCurrPosStatus();
               std::cout << "\n----------------                  ------------------\n";
          }
     }
}
