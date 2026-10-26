#ifndef MEME_RENDER_OBJECT_HPP
#define MEME_RENDER_OBJECT_HPP

#include <Meme/texture_manager.hpp>
#include <Meme/texture_changer.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>

namespace meme
{

class Render_object
{
private:
    static sf::Texture tmp;

public:
    void Init(Texture_manager & tex_manager, const std::filesystem::path & tex_path, sf::Vector2i variant_size);

    sf::Sprite sprite{tmp};
    Texture_changer tex_changer{};
    uint8_t tex_id{};
};

}

#endif //MEME_RENDER_OBJECT_HPP
