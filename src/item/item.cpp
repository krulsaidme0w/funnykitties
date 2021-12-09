#include "item.h"

void Item::Spring::CollisionPlayer(Player::Player* player, sf::Vector2f delta) {
    auto tile = this->sprite;
    if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {
        player->big_jump();
    }
}

void Item::Box::CollisionPlayer(Player::Player *player, sf::Vector2f delta) {
    auto tile = this->sprite;
    auto tile_rect = this->sprite.getGlobalBounds();
    auto speed = player->GetSpeed();

    sf::Vector2u playerSize = player->GetSprite().getTexture()->getSize();
    if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {

//        if (speed.y < 0) {
//            player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tile.getPosition().y + 72));
//        }

        if (speed.y > 0 && player->GetCoordinates().y + playerSize.y < tile.getPosition().y + playerSize.y) {
            player->SetCoordinates(sf::Vector2f(player->GetCoordinates().x, tile.getPosition().y - playerSize.y));
            player->SetState(Player::ON_GROUND);
            player->SetSpeed(sf::Vector2f(speed.x, 0));
        }
    }

    if (player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())){
        if (delta.x == -1) {
            auto player_xy = player->GetCoordinates();
            auto box_xy = this->sprite.getPosition();
            this->sprite.move(-speed.x,0);
            player->SetCoordinates(sf::Vector2f (tile_rect.left + tile_rect.width, player_xy.y));
            //this->map.MoveX(-1 * (tile.getPosition().x + tileSize.first - player->GetCoordinates().x));
        }

        if (delta.x == 1) {
            auto player_xy = player->GetCoordinates();
            auto box_xy = this->sprite.getPosition();
            this->sprite.move(speed.x, 0);
            player->SetCoordinates(sf::Vector2f (tile_rect.left - player->GetSprite().getGlobalBounds().width, player_xy.y));
        }
        //player->jump();
    }
}


void Item::Key::CollisionPlayer(Player::Player *player, sf::Vector2f delta) {
    if (player->GetSprite().getGlobalBounds().intersects(this->sprite.getGlobalBounds())) {
        auto player_pos = player->GetSprite().getPosition();
        this->sprite.setPosition(player_pos.x, player_pos.y - 60);
    }
}

void Item::Exit::CollisionPlayer(Player::Player *player, sf::Vector2f delta) {
    auto tile = this->sprite;
    if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {
        exit(0);
    }
}


