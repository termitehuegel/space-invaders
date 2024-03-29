#include "../include/commons.h"
#include "../include/enemyController.h"

EnemyController::EnemyController(unsigned int reload_time, float acceleration, float speed, float step,
                                 GameState* game_state,
                                 AssetManager* asset_manager)
{
    this->asset_manager = asset_manager;
    change_direction = false;
    this->acceleration = acceleration;
    this->speed = speed;
    this->step = step;
    this->reload_time = reload_time;
    this->game_state = game_state;
    reload_cooldown = 0;
    animation_cooldown = 0;
    animation_time = 500;
    reset();
}

EnemyController::EnemyController(const EnemyController& enemy_controller)
{
    asset_manager = enemy_controller.asset_manager;
    speed = enemy_controller.speed;
    acceleration = enemy_controller.acceleration;
    for (int x = 0; x < 11; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            enemies[x][y] = enemy_controller.enemies[x][y] != nullptr ? new Enemy(*enemy_controller.enemies[x][y]) : nullptr;
        }
    }
    change_direction = enemy_controller.change_direction;
    step = enemy_controller.step;
    reload_cooldown = enemy_controller.reload_cooldown;
    reload_time = enemy_controller.reload_time;
    animation_cooldown = enemy_controller.animation_cooldown;
    animation_time = enemy_controller.animation_time;
    game_state = enemy_controller.game_state;
}

EnemyController::~EnemyController()
{
    for (int x = 0; x < 11; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            saveDelete(enemies[x][y]);
        }
    }
}

void EnemyController::update(sf::Time delta_time, std::vector<Projectile*>* player_projectiles,
                             std::vector<Projectile*>* enemy_projectiles)
{
    updateTimers(delta_time);
    updateMovement(delta_time);
    updateCollision(player_projectiles);
    shoot(enemy_projectiles);
    updateAnimation();

    if (playerReached())
    {
        asset_manager->getAudioManager()->playGameOverSFX();
        game_state->game_over = true;
    }
}

void EnemyController::draw(sf::RenderWindow* window)
{
    for (int x = 0; x < 11; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (enemies[x][y] == nullptr)
            {
                continue;
            }
            enemies[x][y]->draw(window);
        }
    }
}

void EnemyController::updateMovement(sf::Time delta_time)
{
    if (change_direction)
    {
        speed *= -1;
    }

    bool border_reached = false;
    for (int x = 0; x < 11; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (enemies[x][y] == nullptr)
            {
                continue;
            }
            sf::Vector2<float> position = enemies[x][y]->getPosition();
            float new_x = position.x + speed * static_cast<float>(delta_time.asMilliseconds());
            float new_y = position.y;
            if (change_direction)
            {
                new_y = position.y + step;
            }

            enemies[x][y]->setPosition(new_x, new_y);
            if ((new_x <= 0 && speed < 0) ||
                (new_x + 64.0f >= 1920 && speed > 0))
            {
                border_reached = true;
            }
        }
    }
    if (change_direction)
    {
        change_direction = false;
    } else if (border_reached)
    {
        change_direction = true;
    }
}

void EnemyController::updateCollision(std::vector<Projectile*>* player_projectiles)
{
    for (int x = 0; x < 11; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (enemies[x][y] == nullptr)
            {
                continue;
            }
            if (enemies[x][y]->detectCollision(player_projectiles))
            {
                saveDelete(enemies[x][y]);
                game_state->score += 100;
                if (speed >= 0)
                {
                    speed += acceleration;
                } else
                {
                    speed -= acceleration;
                }
            }
        }
    }
    if (isEmpty())
    {
        reset();
        if (speed > 0)
        {
            speed = speed - 11 * 5 * acceleration;
        } else
        {
            speed = speed + 11 * 5 * acceleration;
        }
    }
}

void EnemyController::shoot(std::vector<Projectile*>* enemy_projectiles)
{
    if (reload_cooldown > 0)
    {
        return;
    }
    for (int x = 0; x < 11; x++)
    {
        bool no_shoot = std::rand() % 5;
        if (no_shoot)
        {
            continue;
        }
        for (int y = 4; y >= 0; y--)
        {
            if (enemies[x][y] != nullptr)
            {
                enemy_projectiles->push_back(enemies[x][y]->shoot(asset_manager));
                reload_cooldown = reload_time;
                break;
            }
        }
    }
}

bool EnemyController::playerReached()
{
    for (int y = 4; y >= 0; y--)
    {
        for (int x = 0; x < 11; x++)
        {
            if (enemies[x][y] == nullptr)
            {
                continue;
            }
            return enemies[x][y]->getPosition().y >= 980;
        }
    }
    return false;
}

bool EnemyController::isEmpty()
{
    for (int x = 0; x < 11; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (enemies[x][y] != nullptr)
            {
                return false;
            }
        }
    }
    return true;
}

void EnemyController::reset()
{
    for (int y = 0; y < 5; y++)
    {
        sf::Texture* texture;
        switch (y)
        {
            case 0:
                texture = asset_manager->getTextures()->at("enemy-1");
                break;
            case 1:
            case 2:
                texture = asset_manager->getTextures()->at("enemy-2");
                break;
            case 3:
            case 4:
                texture = asset_manager->getTextures()->at("enemy-3");
                break;
            default:
                texture = asset_manager->getTextures()->at("enemy-1");
                break;
        }
        for (int x = 0; x < 11; x++)
        {
            enemies[x][y] = new Enemy(texture, static_cast<float>(150 + x * 150), + static_cast<float>(200 + y * 75));
        }
    }
}

void EnemyController::updateAnimation()
{
    if (animation_cooldown > 0)
    {
        return;
    }
    animation_cooldown = animation_time;
    for (int x = 0; x < 11; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (enemies[x][y] != nullptr)
            {
                enemies[x][y]->animationStep();
            }
        }
    }
}

void EnemyController::updateTimers(sf::Time delta_time)
{
    animation_cooldown =animation_cooldown > delta_time.asMilliseconds() ? animation_cooldown - delta_time.asMilliseconds() : 0;
    reload_cooldown = reload_cooldown > delta_time.asMilliseconds() ? reload_cooldown - delta_time.asMilliseconds() : 0;
}