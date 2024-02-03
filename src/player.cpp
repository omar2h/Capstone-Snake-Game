#include "player.h"

std::string Player::name()
{
    return m_name;
}

void Player::setName(std::string name)
{
    if(m_name == name)
        return;
    m_name = name;
}