#ifndef PLAYER_H
#define PLAYER_H

#include <string>
class Player
{
    public:
        Player(std::string const& name) : m_name{name} {}
        std::string name() const;
    private:
        const std::string m_name{};
};

#endif