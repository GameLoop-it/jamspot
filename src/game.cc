#include "spot/jam/game.h"

#include "spot/jam/tile.h"


namespace spot::jam
{

/// Default viewport is offset(-1,-1) extent(2, 2)
/// @return A screen-size viewport
VkViewport create_viewport( VkExtent2D extent )
{
	const float hsize = Tile::tile_size / 2.0f;

	return VkViewport {
		.x = -hsize,
		.y = -hsize,
		.width = float( extent.width ),
		.height = float( extent.height ),
		.minDepth = 0.125f,
		.maxDepth = 16.0f
	};
}


Game::Game()
: extent { 320, 240 }
, gfx { extent }
, model { gfx.models.push() }
, tileset { "res/img/assets.png", *model }
{
	player.node = tileset.create_node( Tile( 28, 1 ), *model );
	player.node->translate( extent.width / 2.0f, extent.height / 2.0f );
	gfx.camera.set_orthographic( create_viewport( extent ) );
}


void Game::run()
{
	while ( gfx.window.is_alive() )
	{
		gfx.glfw.poll();
		gfx.window.update();
		auto delta = gfx.glfw.get_delta();

		player.update( delta, gfx.window.input );
		player.node->update_transforms();

		if ( gfx.render_begin() )
		{
			gfx.draw( *player.node );

			gfx.render_end();
		}
	}

	gfx.device.wait_idle();
}


} // namespace spot::jam
