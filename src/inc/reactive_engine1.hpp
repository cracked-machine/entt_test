#ifndef __REACTIVE_ENGINE1_HPP__
#define __REACTIVE_ENGINE1_HPP__

#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>
#include <components1.hpp>
#include <spdlog/spdlog.h>

namespace Test {

class ReactiveEngine1
{
public:
    ReactiveEngine1()
    {
        m_registry.on_construct<Position>().connect<&ReactiveEngine1::pos_cb>(this);

        m_pool.bind( m_registry );

        // not caught by reactive mixin: pool = 0
        add_entity_with_position();
        SPDLOG_INFO("Pool size - {}", m_pool.size());

        // setup reactive mixin for Position types
        m_pool
            .on_construct<Position>()
            .on_update<Position>();

        // caught by reactive mixin: pool = 1
        add_entity_with_position();
        // caught by reactive mixin: pool = 2
        auto p = add_entity_with_position();
        
        SPDLOG_INFO("Pool size - {}", m_pool.size());


    }
private:
    entt::registry m_registry{};

    
    
    using my_reactive_storage = entt::reactive_mixin<entt::storage<bool>>;
    my_reactive_storage m_pool{}; 

    Position& add_entity_with_position()
    {
        const entt::entity entity{m_registry.create()};
        return m_registry.emplace<Position>(entity, 1.f, 1.f);
        // return entity;
    }

    void pos_cb(entt::registry &m_registry, entt::entity entity)
    {   
        SPDLOG_INFO(" Entity {} - Added Position component {},{}", 
            entt::entt_traits<entt::entity>::to_entity(entity), // id
            m_registry.get<Position>(entity).x, 
            m_registry.get<Position>(entity).y
        );
    }

};

} // namespace Test


#endif // __REACTIVE_ENGINE1_HPP__