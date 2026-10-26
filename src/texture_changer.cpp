#include <Meme/texture_changer.hpp>

using namespace meme;

void meme::Texture_changer::Init(const sf::Texture & texture, sf::Vector2i variant_size)
{
    this->variant_size = variant_size;
    this->texture_size = static_cast<sf::Vector2i>( texture.getSize() );
    this->colums_amount = texture_size.x / variant_size.x;
}

void meme::Texture_changer::Set_variant_rect_on_sprite(sf::Sprite & sprite, uint8_t variant_number)
{
    sprite.setTextureRect( Get_variant_rect( variant_number ) );
}

sf::IntRect meme::Texture_changer::Get_variant_rect(uint8_t variant_number)
{
    uint8_t column = variant_number % colums_amount;
    uint8_t row = variant_number / colums_amount;

    sf::IntRect variant_rect{};
    variant_rect.size = variant_size;
    variant_rect.position = { (column * variant_size.x), (row * variant_size.y) };

    return variant_rect;
}
