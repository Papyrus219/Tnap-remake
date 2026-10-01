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

    office_tex_id = tex_manager.Add_texture("../../img/office.png");
    right_door_tex_id = tex_manager.Add_texture("../../img/left_door.png");
    right_button_tex_id = tex_manager.Add_texture("../../img/buton_left.png");

    office_tex_changer.Init( tex_manager.Get_texture( office_tex_id ), {1200, 1000} );
    right_door_tex_changer.Init( tex_manager.Get_texture( right_door_tex_id ), {1200, 1000} );
    right_button_tex_changer.Init( tex_manager.Get_texture( right_button_tex_id ), {1200, 1000} );

    office_sprite.setTexture( tex_manager.Get_texture( office_tex_id ), true);
    office_sprite.setTextureRect( office_tex_changer.Get_variant_rect( constants::NORMAL_OFFICE_VARIANT_ID ) );
    office_sprite.setPosition( {-600,0} );

    right_door_sprite.setTexture( tex_manager.Get_texture( right_door_tex_id ) );
    right_door_sprite.setTextureRect( right_door_tex_changer.Get_variant_rect( constants::DARK_LEFT_DOOR_VARIANT_ID ) );
    right_door_sprite.setPosition( {-600, 0} );

    right_button_sprite.setTexture( tex_manager.Get_texture( right_button_tex_id ) );
    right_button_sprite.setTextureRect( right_door_tex_changer.Get_variant_rect( constants::LEFT_BUTTON_ON_VARIANT_ID ) );
    right_button_sprite.setPosition( {-600, 0} );
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

    main_window.draw( office_sprite );
    main_window.draw( right_door_sprite );
    main_window.draw( right_button_sprite );

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
    sf::Vector2f mouse_pos = main_window.mapPixelToCoords( mouse_pixel_pos );

    float delta_time = game_clock.restart().asSeconds();

    if(main_window.hasFocus())
    {
        if(right_hitbox.contains(mouse_pos))
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
        else if(left_hitbox.contains(mouse_pos))
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
            if(camera_panel_button.getGlobalBounds().contains( mouse_pos ))
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
                if(right_button_sprite.getGlobalBounds().contains( mouse_pos ))
                {
                    if(is_left_door_closed)
                    {
                        right_door_sprite.setTextureRect( right_door_tex_changer.Get_variant_rect( constants::LIGHT_LEFT_DOOR_VARIANT_ID ) );
                        right_button_sprite.setTextureRect( right_button_tex_changer.Get_variant_rect( constants::LEFT_BUTTON_OFF_VARIANT_ID ) );
                    }
                    else
                    {
                        right_door_sprite.setTextureRect( right_door_tex_changer.Get_variant_rect( constants::DARK_LEFT_DOOR_VARIANT_ID ) );
                        right_button_sprite.setTextureRect( right_button_tex_changer.Get_variant_rect( constants::LEFT_BUTTON_ON_VARIANT_ID ) );
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
