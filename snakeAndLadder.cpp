#include <iostream>
#include <map>
#include <random>
#include <thread>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>
using namespace std;

map<int, int> SnakeHeadAndTailPos;
map<int, int> LadderStartAndEnd;

class Player
{
public:
     void init();
     void getPlayerCount();
     void getPlayerName();
     void showPlayerDetails();

private:
     int playerCount;
     string playerName;
     map<string, int> PlayerDetails;
};

void getPlayerCount(int &playercount)
{
     cout << "Enter The No of Player: ";
     cin >> playercount;
}

void getPlayerName(map<string, int> &playerDetails, const int &playerCount)
{
     string playerName;
     for (int i = 0; i < playerCount; ++i)
     {
          printf("Enter %d Player Name :", i + 1);
          cin >> playerName;
          playerDetails.insert({playerName, 0});
     }
}

void showPlayerDetails(const map<string, int> &playerDetails, const int playerCount)
{
     int iterator = 0;
     cout << endl;
     for (auto i : playerDetails)
     {
          printf("Player %d: %s  pos: %d || ", ++iterator, i.first.c_str(), i.second);
     }
     cout << endl;
}

void rollTheDice(int &randNum)
{
     randNum = rand();
     randNum %= 6;
     if (randNum == 0)
          randNum = 6;
}

void RunningNumbers(int &drawLuckyNum)
{
     int i = 0;
     string s_append;
     stringstream ss;
     while (drawLuckyNum != true)
     {
          ++i;
          fflush(stdout);
          usleep(120000);
          cout << i << " ";
          if (i == 6)
          {
               i = 0;
               cout << "\b\b\b\b\b\b\b\b\b\b\b\b";
          }
     }

     cout << "\b\b\b   ";
     drawLuckyNum = false;
}

void checkUpsandDowns(map<string, int> &playerDetails, string playerName, int currPos)
{

     auto it = LadderStartAndEnd.find(currPos);
     if (it != LadderStartAndEnd.end())
     {
          cout << "Hurray --- You are climbing from Pos :" << currPos;
          currPos = it->second;
          // playerDetails.insert(make_pair(playerName, currPos));
          playerDetails.at(playerName) = currPos;
          cout << " to Pos :" << currPos << endl;
     }

     it = SnakeHeadAndTailPos.find(currPos);
     if (it != SnakeHeadAndTailPos.end())
     {
          cout << "oops :( --xxxx-- Snake Caught You from Pos :" << currPos;
          currPos = it->second;
          // playerDetails.insert(make_pair(playerName, currPos));
          playerDetails.at(playerName) = currPos;
          cout << " going down to Pos :" << currPos << endl;
     }

     for (auto &i : playerDetails)
     {
          if (i.second == currPos && playerName != i.first) // Hitting the Other Opposition
          {
               i.second = 0;
               cout << "\nYou Hitted " << i.first << ":)" << endl;
          }
     }
}

void startGame(map<string, int> &playerDetails)
{
     int luckyNum;
     int drawLuckyNum = false;
     bool gameFinished = false;
     while (!gameFinished)
     {
          for (auto &i : playerDetails)
          {
               cout << "----------------                  ------------------\n\n"
                    << i.first << " Playing ::  Press Enter to Start && Stop \n";

               cin.get();
               cout << "           ";
               thread th1(RunningNumbers, ref(drawLuckyNum));

               cin.get();
               drawLuckyNum = true; // This variable is responsible to will cause the system to come out of while loop in thread.

               th1.join();
               th1.~thread();

               rollTheDice(luckyNum);

               cout << "\n          Dice Stays at " << luckyNum << endl;

               cout << i.first << " Prev Pos is :" << i.second;

               if (i.second + luckyNum > 100)
               {
                    cout << "Next Pos will be " << i.second + luckyNum << " Not Valid" << endl;
                    cout << "You need " << 100 - i.second << " to win or less Num to move to next Pos" << endl;
               }
               else if (i.second + luckyNum == 100)
               {
                    cout << endl
                         << i.first << " Won the game " << endl;
                    gameFinished = true;
               }
               else
               {
                    i.second += luckyNum;
                    cout << " Updated pos is : " << i.second << endl;
                    checkUpsandDowns(playerDetails, i.first, i.second);
               }
               cout << "\n----------------                  ------------------\n";
          }
     }
}

void initSnakeAndLadderPos()
{

     SnakeHeadAndTailPos.insert(make_pair<int, int>(37, 17));
     SnakeHeadAndTailPos.insert(make_pair<int, int>(31, 14));
     SnakeHeadAndTailPos.insert(make_pair<int, int>(78, 9));
     SnakeHeadAndTailPos.insert(make_pair<int, int>(73, 53));
     SnakeHeadAndTailPos.insert(make_pair<int, int>(99, 7));
     SnakeHeadAndTailPos.insert(make_pair<int, int>(92, 35));

     LadderStartAndEnd.insert(make_pair<int, int>(5, 25));
     LadderStartAndEnd.insert(make_pair<int, int>(10, 29));
     LadderStartAndEnd.insert(make_pair<int, int>(22, 41));
     LadderStartAndEnd.insert(make_pair<int, int>(28, 55));
     LadderStartAndEnd.insert(make_pair<int, int>(44, 95));
     LadderStartAndEnd.insert(make_pair<int, int>(70, 89));
     LadderStartAndEnd.insert(make_pair<int, int>(79, 81));
}

int main()
{

     int playerCount;
     string playerName;
     string startPlaying;
     int luckyNum;
     std::map<string, int> playerDetails;

     initSnakeAndLadderPos();
     getPlayerCount(playerCount);
     getPlayerName(playerDetails, playerCount);
     showPlayerDetails(playerDetails, playerCount);

     cout << "\n                       Can We Start The Game y/n : ";
     cin >> startPlaying;

     if (startPlaying == "n" || startPlaying == "no" || startPlaying == "N")
     {
          cout << "Game Finished" << endl;
          return 0;
     }
     else
     {
          startGame(playerDetails);
     }

     showPlayerDetails(playerDetails, playerCount);

     return 0;
}
