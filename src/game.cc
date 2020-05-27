#include "spot/jam/game.h"

#include "spot/jam/tile.h"


namespace spot::jam
{


Game::Game()
: model { gfx.models.push() }
, assets { model->images.push( gfx::Image( "res/img/assets.png" ) ) }
, texture { model->textures.push( gfx::Texture( assets ) ) }
, material { model->materials.push( gfx::Material( texture ) ) }
{}


void Game::run()
{
	Handle<gfx::Node> node = model->nodes.push();
	node->mesh = model->meshes.push( Tile::create_quad( *material, 1, 1 ) );

	while ( gfx.window.is_alive() )
	{
		gfx.glfw.poll();
		gfx.window.update();

		if ( gfx.render_begin() )
		{
			gfx.draw( *node );

			gfx.render_end();
		}
	}

	gfx.device.wait_idle();
}


} // namespace spot::jam
