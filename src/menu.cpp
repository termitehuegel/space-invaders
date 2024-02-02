#include <iomanip>
#include <sstream>
#include "../include/menu.h"

Menu::Menu(AssetManager *asset_manager) {
    this->asset_manager = asset_manager;
    selected = 0;
    cooldown = 0;
    state = MAIN;
    options = {Options::FULL_HD, Options::WINDOWED, Options::HUNDRED_FORTY_FOUR_HERTZ, 10, 50};
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

    music_volume_text = new sf::Text("music volume", *cour, 50);
    music_volume_text->setFillColor(sf::Color::White);
    music_volume_text->setPosition(768 - music_volume_text->getGlobalBounds().getSize().x, 500);

    music_volume_value_text = new sf::Text("", *cour, 50);
    music_volume_value_text->setFillColor(sf::Color::White);
    music_volume_value_text->setPosition(1152, 500);

    sfx_volume_text = new sf::Text("sfx volume", *cour, 50);
    sfx_volume_text->setFillColor(sf::Color::White);
    sfx_volume_text->setPosition(768 - sfx_volume_text->getGlobalBounds().getSize().x, 600);

    sfx_volume_value_text = new sf::Text("", *cour, 50);
    sfx_volume_value_text->setFillColor(sf::Color::White);
    sfx_volume_value_text->setPosition(1152, 600);

    back_text = new sf::Text("back", *cour, 50);
    back_text->setFillColor(sf::Color::White);
    back_text->setPosition(768 - back_text->getGlobalBounds().getSize().x, 750);

    apply_text = new sf::Text("apply", *cour, 50);
    apply_text->setFillColor(sf::Color::White);
    apply_text->setPosition(1152, 750);

}

Menu::~Menu() {
    delete play_text;
    delete options_text;
    delete quit_text;
    delete resolution_text;
    delete resolution_value_text;
    delete window_mode_text;
    delete window_mode_value_text;
    delete refresh_rate_text;
    delete refresh_rate_value_text;
    delete back_text;
    delete apply_text;
}

bool Menu::update(sf::Time delta_time, sf::RenderWindow *window) {
    updateTimers(delta_time);
    if (state == MenuState::MAIN) {
        return updateMainMenu();
    } else if (state == MenuState::OPTIONS) {
        updateOptionsMenu(window);
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

bool Menu::updateMainMenu() {
    if (cooldown > 0) {
        return false;
    }

    updateMainMenuSelection();
    return updateMainMenuExecution();
}

void Menu::updateOptionsMenu(sf::RenderWindow *window) {
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
    resolution_value_text->setFillColor(sf::Color::White);
    window_mode_value_text->setFillColor(sf::Color::White);
    refresh_rate_value_text->setFillColor(sf::Color::White);
    music_volume_value_text->setFillColor(sf::Color::White);
    sfx_volume_value_text->setFillColor(sf::Color::White);
    back_text->setFillColor(sf::Color::White);
    apply_text->setFillColor(sf::Color::White);
    switch (selected) {
        case 0:
            resolution_value_text->setFillColor(sf::Color::Green);
            break;
        case 1:
            window_mode_value_text->setFillColor(sf::Color::Green);
            break;
        case 2:
            refresh_rate_value_text->setFillColor(sf::Color::Green);
            break;
        case 3:
            music_volume_value_text->setFillColor(sf::Color::Green);
            break;
        case 4:
            sfx_volume_value_text->setFillColor(sf::Color::Green);
            break;
        case 5:
            back_text->setFillColor(sf::Color::Green);
            break;
        case 6:
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

    std::stringstream music_volume_stream;
    music_volume_stream << (selected_options.music_volume > 0 ? "< " : "  ") << selected_options.music_volume
                        << std::setprecision(0) << (selected_options.music_volume < 100 ? " >" : "  ");
    music_volume_value_text->setString(music_volume_stream.str());
    std::stringstream sfx_volume_stream;
    sfx_volume_stream << (selected_options.sfx_volume > 0 ? "< " : "  ") << selected_options.sfx_volume
                      << std::setprecision(0) << (selected_options.sfx_volume < 100 ? " >" : "  ");
    sfx_volume_value_text->setString(sfx_volume_stream.str());

    window->draw(*resolution_text);
    window->draw(*resolution_value_text);
    window->draw(*window_mode_text);
    window->draw(*window_mode_value_text);
    window->draw(*refresh_rate_text);
    window->draw(*refresh_rate_value_text);
    window->draw(*music_volume_text);
    window->draw(*music_volume_value_text);
    window->draw(*sfx_volume_text);
    window->draw(*sfx_volume_value_text);
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
                cooldown = 1000;
                return true;
            case 1:
                state = OPTIONS;
                selected_options = options;
                selected = 0;
                cooldown = 250;
                break;
            case 2:
                delete asset_manager;
                std::exit(EXIT_SUCCESS);
        }
    }
    return false;
}

void Menu::updateOptionsMenuSelection() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        selected = (selected + 1) % 7;
        cooldown = 250;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        selected = (selected - 1) > 7 ? 6 : (selected - 1) % 7;
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
                selected_options.music_volume =
                        selected_options.music_volume + 5 >= 100 ? 100 : selected_options.music_volume + 5;
                cooldown = 250;
                break;
            case 4:
                selected_options.sfx_volume =
                        selected_options.sfx_volume + 5 >= 100 ? 100 : selected_options.sfx_volume + 5;
                cooldown = 250;
                break;
            case 5:
                selected = 6;
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
            case 3:
                selected_options.music_volume =
                        selected_options.music_volume - 5 <= 0 ? 0 : selected_options.music_volume - 5;
                cooldown = 250;
                break;
            case 4:
                selected_options.sfx_volume =
                        selected_options.sfx_volume - 5 <= 0 ? 0 : selected_options.sfx_volume - 5;
                cooldown = 250;
                break;
            case 6:
                selected = 5;
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
            case 5:
                selected = 1;
                state = MAIN;
                cooldown = 250;
                break;
            case 6:
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

    switch (options.refresh_rate) {
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

    asset_manager->getAudioManager()->setMusicVolume(options.music_volume);
    asset_manager->getAudioManager()->setMusicEnabled(options.music_volume > 0);
    asset_manager->getAudioManager()->setSFXVolume(options.sfx_volume);
}

void Menu::updateTimers(sf::Time delta_time) {
    cooldown = cooldown > delta_time.asMilliseconds() ? cooldown - delta_time.asMilliseconds() : 0;
}