#ifndef PLAYER_H
#define PLAYER_H

#include <string>
class Player
{
    public:
        Player(std::string name) : m_name{name} {}
        std::string name();
        void setName(std::string);
    private:
        std::string m_name{};
};

#endif