#ifndef MEME_GAME_HPP
#define MEME_GAME_HPP

#include <Meme/texture_manager.hpp>
#include <Meme/render_object.hpp>
#include <SFML/Graphics.hpp>

namespace meme
{

class Game
{
public:
    void Init();

    void Run();

private:
    void Update();
    void Render();

    Texture_manager tex_manager{};

    sf::RenderWindow main_window{};
    sf::RenderWindow camera_window{};

    sf::RectangleShape camera_panel_button{};

    Render_object office_render_object{};
    Render_object left_door_render_object{};
    Render_object left_button_render_object{};

    bool is_camera_open{};

    sf::View ui_view{};
    sf::View normal_view{};
    sf::Clock game_clock{};

    sf::FloatRect left_hitbox{};
    sf::FloatRect right_hitbox{};

    bool is_left_door_closed{true};

    float view_offset{};
    float scroll_speed{250};

    static constexpr float win_width{ 1000.0f };
    static constexpr float win_height{ 750.0f};
    static constexpr float bar_width{ 100.0f};
    static constexpr float view_width{ win_width - 2.0f * bar_width};
    static constexpr float viewport_width{ view_width / win_width };
};

}

#endif // MEME_GAME_HPP
