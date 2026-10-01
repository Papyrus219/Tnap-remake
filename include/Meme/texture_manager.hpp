#ifndef MEME_TEXTURE_MANAGER_HPP
#define MEME_TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <array>

namespace meme
{

class Texture_manager
{
public:
    uint8_t Add_texture(const std::filesystem::path & path);
    sf::Texture & Get_texture(uint8_t texture_id);

private:
    static constexpr uint8_t MAX_TEXTURES_AMOUNT{32};
    uint8_t next_texture_id{};

    std::array<sf::Texture, MAX_TEXTURES_AMOUNT> textures{};
};

}

#endif // MEME_TEXTURE_MANAGER_HPP
