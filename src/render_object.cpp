#include <Meme/render_object.hpp>

sf::Texture meme::Render_object::tmp{};

void meme::Render_object::Init(Texture_manager & tex_manager, const std::filesystem::path & tex_path, sf::Vector2i variant_size)
{
    tex_id = tex_manager.Add_texture(tex_path);
    sprite.setTexture( tex_manager.Get_texture( tex_id ) );
    tex_changer.Init(tex_manager.Get_texture(tex_id), variant_size);
}
