
#include <SFML/System/Vector2.hpp>
#include <basic_log_controller.hpp>
#include <entt/entity/registry.hpp>
#include <spdlog/spdlog.h>

struct Position : public sf::Vector2f 
{
    public:
        Position(float x, float y) : sf::Vector2f(x, y) {}
};

struct Velocity : public sf::Vector2f 
{
    public:
        Velocity(float x, float y) : sf::Vector2f(x, y) {}
};

int main()
{
    std::unique_ptr<Test::Logging::BasicLogController> logger{
        std::make_unique<Test::Logging::BasicLogController>("logger", "log.txt")
    };
    
    SPDLOG_INFO("Initialised");
    
    entt::basic_registry<entt::entity> registry;

    std::array<entt::entity, 3u> entities{};

    std::array<Position, 3u> positions{{
        {1.f, 1.f},
        {2.f, 2.f},
        {3.f, 3.f}
    }};
    std::array<Velocity, 3u> velocities{{
        {1.5f, 1.5f},
        {2.5f, 2.5f},
        {3.5f, 3.5f}
    }};
    
    registry.create( entities.begin(), entities.end() );

    registry.insert<Position>
    (
        entities.begin(), entities.end(),
        positions.begin() 
    );

    registry.insert<Velocity>
    (
        entities.begin(), entities.end(),
        velocities.begin() 
    );

    bool any = registry.all_of<Position, Velocity>(entities[0]);
    for( auto e: entities)
    {
        const auto [cpos, cvel] = registry.get<Position, Velocity>(e);
        SPDLOG_INFO("{},{}: {},{}", cpos.x, cpos.y, cvel.x, cvel.y);
    }
    return 0;
}