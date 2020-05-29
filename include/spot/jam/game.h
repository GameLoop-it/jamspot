#pragma once

#include <spot/gfx/graphics.h>

#include "spot/jam/tileset.h"

namespace spot::jam
{

class Game
{
  public:
	Game();

	void run();

  private:
	/// Frame extent
	VkExtent2D extent;

	/// With this we make fireworks
	gfx::Graphics gfx;

	/// Model used to store everything related to a scene
	Handle<gfx::Model> model;
	
	Tileset tileset;
};

} // namespace spot::jam
