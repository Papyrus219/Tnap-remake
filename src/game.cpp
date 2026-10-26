#include <Meme/game.hpp>
#include <Meme/constants.hpp>
#include <iostream>

using namespace meme;

void meme::Game::Init()
{
    main_window.create( sf::VideoMode{{ static_cast<uint>(win_width), static_cast<uint>(win_height)}}, "Tnap remake" );
    main_window.setVerticalSyncEnabled( true );
    main_window.setFramerateLimit( 120 );

    camera_panel_button.setSize( {800, 50} );
    camera_panel_button.setPosition( {200, 900} );
    camera_panel_button.setFillColor( sf::Color::Black );

    ui_view = main_window.getView();
    normal_view.setCenter( {0, 500} );
    normal_view.setSize( {view_width, win_height} );
    normal_view.setViewport( {{bar_width / win_width, 0.0f}, {viewport_width, 1.0f}} );

    left_hitbox.position = {0, 0};
    left_hitbox.size = {400, 1000};

    right_hitbox.position = {800, 0};
    right_hitbox.size = {400, 1000};

    office_render_object.Init(tex_manager, "../../img/office.png", {1200, 1000});
    left_door_render_object.Init(tex_manager, "../../img/left_door.png", {1200, 1000});
    left_button_render_object.Init(tex_manager, "../../img/buton_left.png", {85, 175});

    office_render_object.tex_changer.Set_variant_rect_on_sprite( office_render_object.sprite, constants::NORMAL_OFFICE_VARIANT_ID );
    office_render_object.sprite.setPosition( {-600,0} );

    left_door_render_object.tex_changer.Set_variant_rect_on_sprite(left_door_render_object.sprite, constants::DARK_LEFT_DOOR_VARIANT_ID );
    left_door_render_object.sprite.setPosition( {-600, 0} );

    left_button_render_object.tex_changer.Set_variant_rect_on_sprite(left_button_render_object.sprite, constants::LEFT_BUTTON_OFF_VARIANT_ID );
    left_button_render_object.sprite.setPosition( {-350, 300} );
}

void meme::Game::Run()
{
    while(main_window.isOpen())
    {
        Render();

        Update();
    }
}

void meme::Game::Render()
{
    main_window.clear();

    main_window.setView( normal_view );

    main_window.draw( office_render_object.sprite );
    main_window.draw( left_door_render_object.sprite );
    main_window.draw( left_button_render_object.sprite );

    main_window.setView( ui_view );

    if(!is_camera_open)
    {
        main_window.draw( camera_panel_button );
    }

    main_window.display();
}

void meme::Game::Update()
{
    sf::Vector2i mouse_pixel_pos = sf::Mouse::getPosition(main_window);
    sf::Vector2f ui_mouse_pos = main_window.mapPixelToCoords( mouse_pixel_pos, ui_view );
    sf::Vector2f world_mouse_pos = main_window.mapPixelToCoords( mouse_pixel_pos, normal_view );

    float delta_time = game_clock.restart().asSeconds();

    if(main_window.hasFocus())
    {
        if(right_hitbox.contains(ui_mouse_pos))
        {
            if(view_offset < 200)
            {
                view_offset += scroll_speed * delta_time;
                normal_view.move( {scroll_speed * delta_time, 0} );
            }
            else
            {
                view_offset = 200;
                normal_view.setCenter( {200, 500} );
            }
        }
        else if(left_hitbox.contains(ui_mouse_pos))
        {
            if(view_offset > -200)
            {
                view_offset -= scroll_speed * delta_time;
                normal_view.move( {-scroll_speed * delta_time, 0} );
            }
            else
            {
                view_offset = -200;
                normal_view.setCenter( {-200, 500} );
            }
        }

        if(!is_camera_open)
        {
            if(camera_panel_button.getGlobalBounds().contains( ui_mouse_pos ))
            {
                is_camera_open = true;
                camera_window.create(sf::VideoMode{ {1000,667} }, "Cameras");
            }
        }
    }

    while(const std::optional event = main_window.pollEvent())
    {
        if(auto button = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(button->button == sf::Mouse::Button::Left)
            {
                auto & left_door_button_sprite = left_button_render_object.sprite;
                auto & left_door_sprite = left_door_render_object.sprite;

                if(left_door_button_sprite.getGlobalBounds().contains( world_mouse_pos ))
                {
                    if(is_left_door_closed)
                    {
                        left_door_render_object.tex_changer.Set_variant_rect_on_sprite(left_door_sprite, constants::LIGHT_LEFT_DOOR_VARIANT_ID);
                        left_button_render_object.tex_changer.Set_variant_rect_on_sprite(left_door_button_sprite, constants::LEFT_BUTTON_ON_VARIANT_ID);
                    }
                    else
                    {
                        left_door_render_object.tex_changer.Set_variant_rect_on_sprite(left_door_sprite, constants::DARK_LEFT_DOOR_VARIANT_ID);
                        left_button_render_object.tex_changer.Set_variant_rect_on_sprite(left_door_button_sprite, constants::LEFT_BUTTON_OFF_VARIANT_ID);
                    }

                    is_left_door_closed = !is_left_door_closed;
                }
            }
        }
        else if(event->is<sf::Event::Closed>())
        {
            main_window.close();
        }
    }

    if(is_camera_open)
    {
        while(const std::optional event = camera_window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                camera_window.close();
                is_camera_open = false;
            }
        }
    }
}
