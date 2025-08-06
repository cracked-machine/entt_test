#ifndef __COMPONENTS1_HPP__
#define __COMPONENTS1_HPP__

#include <SFML/System/Vector2.hpp>
#include <spdlog/spdlog.h>

namespace Test {

class Position : public sf::Vector2f 
{
public:
    Position(float x, float y) : sf::Vector2f(x, y) {}
    virtual ~Position() { SPDLOG_INFO("~Position()"); }
};

class Velocity : public sf::Vector2f 
{
public:
    Velocity(float x, float y) : sf::Vector2f(x, y) {}
    virtual ~Velocity() { SPDLOG_INFO("~Velocity()"); }
};


} // namespace Test 


#endif // __COMPONENTS1_HPP__