#include <iostream>
#include "header/menu.h"

Menu::Menu(AssetManager *asset_manager) {
    selected = 0;
    state = MAIN;
    options = {Options::FULL_HD, Options::WINDOWED, Options::HUNDRED_FORTY_FOUR_HERTZ};
    sf::Font *cour = asset_manager->getFonts()->at("cour");

    // BACKGROUND
    background.setTexture(*asset_manager->getTextures()->at("background-menu"));

    // MAIN MENU
    play_text = new sf::Text("PLAY", *cour, 50);
    play_text->setFillColor(sf::Color::White);
    play_text->setPosition(960 - play_text->getGlobalBounds().getSize().x / 2, 250);

    options_text = new sf::Text("OPTIONS", *cour, 50);
    options_text->setFillColor(sf::Color::White);
    options_text->setPosition(960 - options_text->getGlobalBounds().getSize().x / 2, 500);

    quit_text = new sf::Text("QUIT", *cour, 50);
    quit_text->setFillColor(sf::Color::White);
    quit_text->setPosition(960 - quit_text->getGlobalBounds().getSize().x / 2, 750);

    // OPTIONS MENU
    resolution_text = new sf::Text("resolution", *cour, 50);
    resolution_text->setFillColor(sf::Color::White);
    resolution_text->setPosition(768 - resolution_text->getGlobalBounds().getSize().x, 200);

    resolution_value_text = new sf::Text("", *cour, 50);
    resolution_value_text->setFillColor(sf::Color::White);
    resolution_value_text->setPosition(1152, 200);

    window_mode_text = new sf::Text("window mode", *cour, 50);
    window_mode_text->setFillColor(sf::Color::White);
    window_mode_text->setPosition(768 - window_mode_text->getGlobalBounds().getSize().x, 300);

    window_mode_value_text = new sf::Text("", *cour, 50);
    window_mode_value_text->setFillColor(sf::Color::White);
    window_mode_value_text->setPosition(1152, 300);

    refresh_rate_text = new sf::Text("max fps", *cour, 50);
    refresh_rate_text->setFillColor(sf::Color::White);
    refresh_rate_text->setPosition(768 - refresh_rate_text->getGlobalBounds().getSize().x, 400);

    refresh_rate_value_text = new sf::Text("", *cour, 50);
    refresh_rate_value_text->setFillColor(sf::Color::White);
    refresh_rate_value_text->setPosition(1152, 400);

    back_text = new sf::Text("back", *cour, 50);
    back_text->setFillColor(sf::Color::White);
    back_text->setPosition(768 - back_text->getGlobalBounds().getSize().x, 750);

    apply_text = new sf::Text("apply", *cour, 50);
    apply_text->setFillColor(sf::Color::White);
    apply_text->setPosition(1152, 750);

}

bool Menu::update(sf::Time delta_time, sf::RenderWindow *window) {
    if (state == MenuState::MAIN) {
        return updateMainMenu(delta_time);
    } else if (state == MenuState::OPTIONS) {
        updateOptionsMenu(delta_time, window);
    }
    return false;
}

void Menu::draw(sf::RenderWindow *window) {
    window->draw(background);
    if (state == MAIN) {
        drawMainMenu(window);
    } else if (state == OPTIONS) {
        drawOptionsMenu(window);
    }
}

bool Menu::updateMainMenu(sf::Time delta_time) {
    cooldown -= delta_time.asMilliseconds();
    if (cooldown > 0) {
        return false;
    }

    updateMainMenuSelection();
    return updateMainMenuExecution();
}

void Menu::updateOptionsMenu(sf::Time delta_time, sf::RenderWindow *window) {
    cooldown -= delta_time.asMilliseconds();
    if (cooldown > 0) {
        return;
    }

    updateOptionsMenuSelection();
    updateOptionsMenuExecution(window);
}

void Menu::drawMainMenu(sf::RenderWindow *window) {
    switch (selected) {
        case 0:
            play_text->setFillColor(sf::Color::Green);
            options_text->setFillColor(sf::Color::White);
            quit_text->setFillColor(sf::Color::White);
            break;
        case 1:
            play_text->setFillColor(sf::Color::White);
            options_text->setFillColor(sf::Color::Green);
            quit_text->setFillColor(sf::Color::White);
            break;
        case 2:
            play_text->setFillColor(sf::Color::White);
            options_text->setFillColor(sf::Color::White);
            quit_text->setFillColor(sf::Color::Green);
            break;
    }

    window->draw(*play_text);
    window->draw(*options_text);
    window->draw(*quit_text);
}

void Menu::drawOptionsMenu(sf::RenderWindow *window) {
    switch (selected) {
        case 0:
            resolution_value_text->setFillColor(sf::Color::Green);
            window_mode_value_text->setFillColor(sf::Color::White);
            refresh_rate_value_text->setFillColor(sf::Color::White);
            back_text->setFillColor(sf::Color::White);
            apply_text->setFillColor(sf::Color::White);
            break;
        case 1:
            resolution_value_text->setFillColor(sf::Color::White);
            window_mode_value_text->setFillColor(sf::Color::Green);
            refresh_rate_value_text->setFillColor(sf::Color::White);
            back_text->setFillColor(sf::Color::White);
            apply_text->setFillColor(sf::Color::White);
            break;
        case 2:
            resolution_value_text->setFillColor(sf::Color::White);
            window_mode_value_text->setFillColor(sf::Color::White);
            refresh_rate_value_text->setFillColor(sf::Color::Green);
            back_text->setFillColor(sf::Color::White);
            apply_text->setFillColor(sf::Color::White);
            break;
        case 3:
            resolution_value_text->setFillColor(sf::Color::White);
            window_mode_value_text->setFillColor(sf::Color::White);
            refresh_rate_value_text->setFillColor(sf::Color::White);
            back_text->setFillColor(sf::Color::Green);
            apply_text->setFillColor(sf::Color::White);
            break;
        case 4:
            resolution_value_text->setFillColor(sf::Color::White);
            window_mode_value_text->setFillColor(sf::Color::White);
            refresh_rate_value_text->setFillColor(sf::Color::White);
            back_text->setFillColor(sf::Color::White);
            apply_text->setFillColor(sf::Color::Green);
            break;
    }

    switch (selected_options.resolution) {
        case Options::QUARTER_HD:
            resolution_value_text->setString("  640 x 360 >");
            break;
        case Options::HD:
            resolution_value_text->setString("< 1280 x 720 >");
            break;
        case Options::FULL_HD:
            resolution_value_text->setString("< 1920 x 1080 >");
            break;
        case Options::WQHD:
            resolution_value_text->setString("< 2560 x 1440  ");
            break;
    }

    switch (selected_options.window_mode) {
        case Options::WINDOWED:
            window_mode_value_text->setString("< windowed >");
            break;
        case Options::BORDERLESS:
            window_mode_value_text->setString("< borderless >");
            break;
    }

    switch (selected_options.refresh_rate) {
        case Options::THIRTY_HERTZ:
            refresh_rate_value_text->setString("  30 Hz >");
            break;
        case Options::SIXTY_HERTZ:
            refresh_rate_value_text->setString("< 60 Hz >");
            break;
        case Options::HUNDRED_FORTY_FOUR_HERTZ:
            refresh_rate_value_text->setString("< 144 Hz  ");
            break;
    }

    window->draw(*resolution_text);
    window->draw(*resolution_value_text);
    window->draw(*window_mode_text);
    window->draw(*window_mode_value_text);
    window->draw(*refresh_rate_text);
    window->draw(*refresh_rate_value_text);
    window->draw(*back_text);
    window->draw(*apply_text);
}

void Menu::updateMainMenuSelection() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        selected = (selected + 1) % 3;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        selected = (selected - 1) > 3 ? 2 : (selected - 1) % 3;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
        selected = 0;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
        selected = 1;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        selected = 2;
        cooldown = 250;
    }
}

bool Menu::updateMainMenuExecution() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        switch (selected) {
            case 0:
                return true;
            case 1:
                state = OPTIONS;
                selected_options = options;
                selected = 0;
                cooldown = 250;
                break;
            case 2:
                std::exit(EXIT_SUCCESS);
        }
    }
    return false;
}

void Menu::updateOptionsMenuSelection() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        selected = (selected + 1) % 5;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        selected = (selected - 1) > 5 ? 4 : (selected - 1) % 5;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        switch (selected) {
            case 0:
                switch (selected_options.resolution) {
                    case Options::QUARTER_HD:
                        selected_options.resolution = Options::HD;
                        cooldown = 250;
                        break;
                    case Options::HD:
                        selected_options.resolution = Options::FULL_HD;
                        cooldown = 250;
                        break;
                    case Options::FULL_HD:
                        selected_options.resolution = Options::WQHD;
                        cooldown = 250;
                        break;
                    case Options::WQHD:
                        break;
                }
                break;
            case 1:
                switch (selected_options.window_mode) {
                    case Options::WINDOWED:
                        selected_options.window_mode = Options::BORDERLESS;
                        cooldown = 250;
                        break;
                    case Options::BORDERLESS:
                        selected_options.window_mode = Options::WINDOWED;
                        cooldown = 250;
                        break;
                }
                break;
            case 2:
                switch (selected_options.refresh_rate) {
                    case Options::THIRTY_HERTZ:
                        selected_options.refresh_rate = Options::SIXTY_HERTZ;
                        cooldown = 250;
                        break;
                    case Options::SIXTY_HERTZ:
                        selected_options.refresh_rate = Options::HUNDRED_FORTY_FOUR_HERTZ;
                        cooldown = 250;
                        break;
                    case Options::HUNDRED_FORTY_FOUR_HERTZ:
                        break;
                }
                break;
            case 3:
                selected = 4;
                cooldown = 250;
                break;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        switch (selected) {
            case 0:
                switch (selected_options.resolution) {
                    case Options::QUARTER_HD:
                        break;
                    case Options::HD:
                        selected_options.resolution = Options::QUARTER_HD;
                        cooldown = 250;
                        break;
                    case Options::FULL_HD:
                        selected_options.resolution = Options::HD;
                        cooldown = 250;
                        break;
                    case Options::WQHD:
                        selected_options.resolution = Options::FULL_HD;
                        cooldown = 250;
                        break;
                }
                break;
            case 1:
                switch (selected_options.window_mode) {
                    case Options::WINDOWED:
                        selected_options.window_mode = Options::BORDERLESS;
                        cooldown = 250;
                        break;
                    case Options::BORDERLESS:
                        selected_options.window_mode = Options::WINDOWED;
                        cooldown = 250;
                        break;
                }
                break;
            case 2:
                switch (selected_options.refresh_rate) {
                    case Options::THIRTY_HERTZ:
                        break;
                    case Options::SIXTY_HERTZ:
                        selected_options.refresh_rate = Options::THIRTY_HERTZ;
                        cooldown = 250;
                        break;
                    case Options::HUNDRED_FORTY_FOUR_HERTZ:
                        selected_options.refresh_rate = Options::SIXTY_HERTZ;
                        cooldown = 250;
                        break;
                }
                break;
            case 4:
                selected = 3;
                cooldown = 250;
                break;
        }
    }
}

void Menu::updateOptionsMenuExecution(sf::RenderWindow *window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        selected = 1;
        state = MAIN;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        switch (selected) {
            case 3:
                selected = 1;
                state = MAIN;
                cooldown = 250;
                break;
            case 4:
                options = selected_options;
                applyOptions(window);
                cooldown = 250;
                break;
        }
    }
}

void Menu::applyOptions(sf::RenderWindow *window) {
    switch (options.window_mode) {
        case Options::WINDOWED:
            window->create(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Default);
            break;
        case Options::BORDERLESS:
            window->create(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::None);
            break;
    }

    switch (options.resolution) {
        case Options::QUARTER_HD:
            window->setSize({640, 360});
            break;
        case Options::HD:
            window->setSize({1280, 720});
            break;
        case Options::FULL_HD:
            window->setSize({1920, 1080});
            break;
        case Options::WQHD:
            window->setSize({2560, 1440});
            break;
    }

    switch (selected_options.refresh_rate) {
        case Options::THIRTY_HERTZ:
            window->setFramerateLimit(30);
            break;
        case Options::SIXTY_HERTZ:
            window->setFramerateLimit(60);
            break;
        case Options::HUNDRED_FORTY_FOUR_HERTZ:
            window->setFramerateLimit(144);
            break;
    }
}
