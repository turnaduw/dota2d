#include "../include/game.h"

void dota2d::Game::setMap_min_pos(sf::Vector2i _min)
{
  m_map_minimum_position = _min;
}

void dota2d::Game::setMap_max_pos(sf::Vector2i _max)
{
  m_map_maximum_position = _max;
}

sf::Vector2i dota2d::Game::getMap_max_pos()
{
  return m_map_maximum_position;
}

sf::Vector2i dota2d::Game::getMap_min_pos()
{
  return m_map_minimum_position;
}

void dota2d::Game::printGame_stats()
{

  std::cout << "game::print stats=\n"
   << " map_minimum_position : " << getMap_min_pos().x << " y= " << getMap_min_pos().y
   << " map_maximum_position : " << getMap_max_pos().x << " y= " << getMap_max_pos().y
   << std::endl;
}


void dota2d::Game::updateCamera()
{
  if(ptr_camera != nullptr)
  {
    ptr_camera->doReset(sf::FloatRect(ptr_camera->getCamera_position().x, ptr_camera->getCamera_position().y, m_window_width/2, m_window_height/2));
    ptr_camera->doViewport(ptr_camera->getCamera_viewport());
    ptr_camera->doZoom(ptr_camera->getCamera_zoom());
    ptr_camera->doRotate(ptr_camera->getCamera_rotate());


      //is heron on center?
          // ptr_camera->doCenter(...);



      //Camera position and movement is doing by baseEvent.cpp when mouse moved they move position.. here we show and init
      m_window.setView(ptr_camera->getView());
  }
}


void dota2d::Game::draw()
{

  /*
      in this funtion all renders/draws priority is important.
      1.render map.
      2.render heros/units/..
      3.render buildings
      4.render hud

      because of Z we muss draw background things first then forward things later.
  */


  // m_gameFunctionsTimer.init("game draw timer"); //count time since now untill call obj.finish()

  //map things
  m_window.draw(m_background_sprite.getSprite()); //background-sprite

  //render heroes
  for(int x=0; x<=1; x++)
    if(m_heros[x] != nullptr)
      m_heros[x]->render(&m_window);


  //draw buildings
  m_radiant_buildings.renderBuidlings(&m_window);
  m_dire_buildings.renderBuidlings(&m_window);


  //render hud
  if(m_current_hero != nullptr && m_current_unit == nullptr)
    m_game_huds.render<Hero> (m_window, (*ptr_camera), (*m_current_hero)); //pass window to draw. pass camera to just get valeus as const
  else if(m_current_unit != nullptr && m_current_hero == nullptr)
    m_game_huds.render<Unit> (m_window, (*ptr_camera), (*m_current_unit));
  else



    std::cout << "current selected is a buidling. or can not recognize.. \n";

  // m_gameFunctionsTimer.finish();
}


void dota2d::Game::init()
{
  m_gameFunctionsTimer.init("game initiliazation timer"); //count time since now untill call obj.finish()
  m_log.debug("game::init() called.");
  printGame_stats();

  // Window init
  m_window.create
  (
    sf::VideoMode(getWindow_width(),getWindow_height())
    , getWindow_title(), sf::Style::Default
  );
  // m_window.setPosition(getWindow_position());
  m_window.setFramerateLimit(60);
  m_window.setKeyRepeatEnabled(false);





  // Camera initiliazation is on constractor and Camera update has a function


  // HUD init
  m_game_huds.init();

  // Buildings init
  m_radiant_buildings.init_radiant();
  m_dire_buildings.init_dire();


  //heros init
  m_heros[0] = new Axe;
  m_heros[1] = new Dazzle;

  m_current_hero = m_heros[1];



  //untis
  m_dire_units[0] = new MeleeCreep;
  // m_current_unit = m_dire_units[0];


  m_gameFunctionsTimer.finish();
}


void dota2d::Game::run()
{
  m_log.debug("game::run() called.");
  init();
  while(m_window.isOpen())
  {

    //event
    m_game_events.inputs(&m_window, ptr_camera, getMap_min_pos(), getMap_max_pos(),
                         m_current_unit, m_target_unit, m_target_building);

    //render things.
    updateCamera();
    m_window.clear(sf::Color::Black);
    draw();
    m_window.display();

  }
}
