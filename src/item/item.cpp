#include "item.h"

void Item::Spring::CollisionPlayer(Player::Player* player, sf::Vector2f delta) {
    auto tile = this->sprite;
    if(player->GetSprite().getGlobalBounds().intersects(tile.getGlobalBounds())) {
//            if (delta.x == -1) {
//                this->map.MoveX(-1 * (tile.getPosition().x + tileSize.first - player->GetCoordinates().x));
//            }
//
//            if (delta.x == 1) {
//                this->map.MoveX(player->GetCoordinates().x + playerSize.x - tile.getPosition().x);
//            }
//            object->Collision(player);
        player->jump();
    }
}

void Item::Box::CollisionPlayer(Player::Player *player, sf::Vector2f delta) {
    auto tile = this->sprite;
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
            //this->map.MoveX(-1 * (tile.getPosition().x + tileSize.first - player->GetCoordinates().x));
        }

        if (delta.x == 1) {
            auto player_xy = player->GetCoordinates();
            auto box_xy = this->sprite.getPosition();
            this->sprite.move(speed.x, 0);
        }
        //player->jump();
    }
}


