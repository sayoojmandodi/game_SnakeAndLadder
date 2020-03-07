#include "player.h"
#include <iostream>

void Player::getPlayerCount()
{
     std::cout << "Enter The No of Player: ";
     std::cin >> this->playerCount;
}

void Player::getPlayerName()
{
     std::string playerName;

     for (int i = 0; i < this->playerCount; ++i)
     {
          printf("Enter %d Player Name :", i + 1);
          std::cin >> playerName;
          this->playerDetails.insert({playerName, 0});
     }
}

void Player::showPlayerDetails()
{
     int iterator = 0;
     std::cout << std::endl;
     for (auto i : playerDetails)
     {
          printf("Player %d: %s  pos: %d --- \n", ++iterator, i.first.c_str(), i.second);
     }

     std::cout << std::endl;
}