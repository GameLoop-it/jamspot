#pragma once

#include <spot/gfx/graphics.h>

namespace spot::jam
{

class Game
{
  public:
	Game();

	void run();

  private:
	/// With this we make fireworks
	gfx::Graphics gfx = { VkExtent2D { 320, 240 } };

	/// Model used to store everything related to a scene
	Handle<gfx::Model> model;

	/// Image used for the jam
	Handle<gfx::Image> assets;

	/// This is a texture made with the image
	/// It also has a sampler
	Handle<gfx::Texture> texture;

	/// Material containing the diffuse texture
	/// It will be the unique for every node
	Handle<gfx::Material> material;
};

} // namespace spot::jam
