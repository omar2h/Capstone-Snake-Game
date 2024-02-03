#ifndef PLAYER_H
#define PLAYER_H

#include <string>
class Player
{
    public:
        Player(std::string const& name) : m_name{name} {}
        Player(const Player &source);
        Player &operator=(const Player &source); 
        Player(Player &&source); 
        Player &operator=(Player &&source); 

        std::string name() const;
    private:
        std::string m_name{};
};

#endif