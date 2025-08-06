#ifndef __ENGINE1_HPP__
#define __ENGINE1_HPP__


#include <entt/entity/registry.hpp>
#include <components1.hpp>
#include <random>
#include <spdlog/spdlog.h>

namespace Test {

// Use emplace to create new components into the registry on the fly
// This does not create duplicate components
class Engine1
{
public:
    Engine1()
    {
    
        m_registry.on_construct<entt::entity>().connect<&Engine1::ent_cb>(this);
        m_registry.on_destroy<entt::entity>().connect<&Engine1::ent_death_cb>(this);

        m_registry.on_construct<Position>().connect<&Engine1::pos_cb>(this);
        m_registry.on_destroy<Position>().connect<&Engine1::pos_death_cb>(this);

        m_registry.on_construct<Velocity>().connect<&Engine1::vel_cb>(this);
        m_registry.on_destroy<Velocity>().connect<&Engine1::vel_death_cb>(this);

        this->emplace();
        this->emplace();
        this->emplace();

        m_registry.clear();
    }

    void emplace()
    {
        std::mt19937       rng(rd());  
        
        auto entity = m_registry.create();

        m_registry.emplace<Test::Position>(
            entity, 
            std::uniform_real_distribution(0.1f, 360.1f)(rng),
            std::uniform_real_distribution(0.1f, 360.1f)(rng)
        ); 

        m_registry.emplace<Test::Velocity>(
            entity, 
            std::uniform_real_distribution(360.1f, 720.1f)(rng),
            std::uniform_real_distribution(360.1f, 720.1f)(rng)
        ); 
        
    }

private:
    entt::basic_registry<entt::entity> m_registry;
    std::random_device rd;

    void ent_cb(entt::registry &m_registry, entt::entity entity)
    {
        SPDLOG_INFO(" Entity {} created", entt::entt_traits<entt::entity>::to_entity(entity));        
    }
    void ent_death_cb(entt::registry &m_registry, entt::entity entity)
    {
        SPDLOG_INFO(" Entity {} destroyed", entt::entt_traits<entt::entity>::to_entity(entity));        
    }
    void vel_cb(entt::registry &m_registry, entt::entity entity)
    {   
        SPDLOG_INFO(" Entity {} - Added Velocity component {},{}", 
            entt::entt_traits<entt::entity>::to_entity(entity), // id
            m_registry.get<Velocity>(entity).x, 
            m_registry.get<Velocity>(entity).y
        );
    }
    void vel_death_cb(entt::registry &m_registry, entt::entity entity)
    {
        SPDLOG_INFO(" Velocity for Entity {} destroyed", entt::entt_traits<entt::entity>::to_entity(entity));        
    }
    void pos_cb(entt::registry &m_registry, entt::entity entity)
    {   
        SPDLOG_INFO(" Entitiy {} - Added Position component {},{}", 
            entt::entt_traits<entt::entity>::to_entity(entity), //id
            m_registry.get<Position>(entity).x, 
            m_registry.get<Position>(entity).y
        );
    }
    void pos_death_cb(entt::registry &m_registry, entt::entity entity)
    {
        SPDLOG_INFO(" Position for Entity {} destroyed", entt::entt_traits<entt::entity>::to_entity(entity));        
    }
};

} // namespace Test

#endif // __ENGINE1_HPP__