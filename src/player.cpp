#include "player.h"

Player::Player(const Player &source) : m_name{source.m_name}
{}
Player &Player::operator=(const Player &source)
{
    if (this != &source) {
        m_name = source.m_name;
    }
    return *this;
}
Player::Player(Player &&source) : m_name{std::move(source.m_name)}
{} 

Player &Player::operator=(Player &&source)
{
    if (this != &source) {
        m_name = std::move(source.m_name);
    }
    return *this;
}

std::string Player::name() const
{
    return m_name;
}