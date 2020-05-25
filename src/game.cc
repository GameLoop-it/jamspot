#include "spot/jam/game.h"


namespace spot::jam
{


void Game::run()
{
	while ( gfx.window.is_alive() )
	{
		gfx.glfw.poll();
		gfx.window.update();

		if ( gfx.render_begin() )
		{
			// @todo Render something

			gfx.render_end();
		}
	}

	gfx.device.wait_idle();
}


}