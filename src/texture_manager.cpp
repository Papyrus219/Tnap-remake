#include <Meme/texture_manager.hpp>
#include <iostream>

using namespace meme;

uint8_t meme::Texture_manager::Add_texture(const std::filesystem::path & path)
{
    if(next_texture_id >= MAX_TEXTURES_AMOUNT)
    {
        throw std::runtime_error{"TEXTURE_MANAGER::TEXTURE ARRAY OVERFLOW."};
    }

    if(!textures[ next_texture_id ].loadFromFile( path))
    {
        std::cerr << "Failed to load texture: " << path << "\n";
    }

    next_texture_id++;
    return next_texture_id - 1;
}

sf::Texture & meme::Texture_manager::Get_texture(uint8_t texture_id)
{
    if(texture_id <= next_texture_id)
    {
        std::clog << "Warning::Getting texture of id, not loaded yet.";
    }

    return textures[ texture_id ];
}
