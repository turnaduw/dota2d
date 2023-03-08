#ifndef DOTA2D_BASE_SPRITE_HEADER
#define DOTA2D_BASE_SPRITE_HEADER
#include <iostream>
#include <SFML/Graphics.hpp>
#include "assets-config.h"

namespace dota2d
{
  class BaseSprite
  {
    public:
      BaseSrite();
      BaseSprite(std::string, sf::Vector2f);

    protected:
      std::string m_texture_path;
      sf::Texture m_texture;
      sf::Sprite m_sprite;
      sf::Vector2f m_position;

      void setTexture(std::string);
      void setPosition(sf::Vector2f);

      sf::Vector2f getPosition();
      sf::Texture getTexture();
      sf::Sprite getSprite();
      std::string getTexture_path();

      void printSprite_stats();
  };
}

#endif