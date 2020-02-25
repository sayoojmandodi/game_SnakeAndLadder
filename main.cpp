#include <iostream>
#include <map>
#include <random>
#include <thread>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>

#include "player.h"
#include "boardanddice.h"

using namespace std;

int main()
{

     string startPlaying;
     int luckyNum;
     std::map<string, int> playerDetails;

     BoardAndDice p;
     p.getPlayerCount();
     p.getPlayerName();
     p.showPlayerDetails();

     std::cout << "\n                       Can We Start The Game y/n : ";
     std::cin >> startPlaying;

     if (startPlaying == "n" || startPlaying == "no" || startPlaying == "N")
     {
          std::cout << "Game Finished" << std::endl;
          return 0;
     }
     else
     {
          p.startGame();
     }

     p.showPlayerDetails();

     return 0;
}
