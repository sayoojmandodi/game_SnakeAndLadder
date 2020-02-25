#ifndef SNAKEANDLADDER_PLAYER_H
#define SNAKEANDLADDER_PLAYER_H

#include <map>

class Player
{

public:
     void init();
     void getPlayerCount();
     void getPlayerName();
     void showPlayerDetails();
     int playerCount;
     friend class BoardAndDice;

private:
     std::map<std::string, int> playerDetails;
};

#endif
