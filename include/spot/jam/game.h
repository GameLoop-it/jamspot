#pragma once

#include <spot/gfx/graphics.h>

namespace spot::jam
{

class Game
{
  public:
	void run();

  private:
	gfx::Graphics gfx = { VkExtent2D { 320, 240 } };
};

} // namespace spot::jam
