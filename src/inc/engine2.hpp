#ifndef __ENGINE2_HPP__
#define __ENGINE2_HPP__


#include <entt/entity/registry.hpp>
#include <components1.hpp>
#include <random>
#include <spdlog/spdlog.h>

namespace Test {

// Uses insert to copy components into registry
// This duplicates the components
class Engine2
{
public:
    Engine2()
    {
    
        m_registry.on_construct<entt::entity>().connect<&Engine2::ent_cb>(this);
        m_registry.on_destroy<entt::entity>().connect<&Engine2::ent_death_cb>(this);

        m_registry.on_construct<Position>().connect<&Engine2::pos_cb>(this);
        m_registry.on_destroy<Position>().connect<&Engine2::pos_death_cb>(this);

        m_registry.on_construct<Velocity>().connect<&Engine2::vel_cb>(this);
        m_registry.on_destroy<Velocity>().connect<&Engine2::vel_death_cb>(this);

        this->insert();

        m_registry.clear();
    }

    void insert()
    {
        std::array<entt::entity, 3u> entities{};

        m_registry.create( entities.begin(), entities.end() );
        
        m_registry.insert<Position>
        (
            entities.begin(), entities.end(),
            m_positions.begin() 
        );

        m_registry.insert<Velocity>
        (
            entities.begin(), entities.end(),
            m_velocities.begin() 
        );        
    }

private:
    entt::basic_registry<entt::entity> m_registry;
    std::random_device rd;
        
    std::array<Position, 3u> m_positions{{
        {1.f, 1.f},
        {2.f, 2.f},
        {3.f, 3.f}
    }};
    std::array<Velocity, 3u> m_velocities{{
        {1.5f, 1.5f},
        {2.5f, 2.5f},
        {3.5f, 3.5f}
    }};

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

#endif // __ENGINE2_HPP__