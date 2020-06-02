#pragma once

#include <spot/gfx/graphics.h>
#include <spot/gfx/collisions.h>

#include "spot/jam/tileset.h"
#include "spot/jam/map.h"

namespace spot::jam
{

class Game
{
  public:
	Game();
	~Game();

	void run();

  private:
	/// Frame extent
	VkExtent2D extent;

	/// With this we make fireworks
	gfx::Graphics gfx;

	/// With this we trigger cool explosions
	gfx::Collisions collisions;

	/// The model stores everything related to a scene
	Handle<gfx::Model> model;
	
	Tileset tileset;

	Entity player;

	/// This is the game map
	Map map;
};

} // namespace spot::jam
