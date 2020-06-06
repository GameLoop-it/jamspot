#include "spot/jam/game.h"

#include "spot/jam/tile.h"
#include "spot/jam/player.h"
#include "spot/jam/editor/editor.h"
#include "spot/jam/flag.h"

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
: config { "res/data/config.json" }
, gfx { VkExtent2D { 320 * config.scale, 240 * config.scale }, true }
, model { gfx.models.push() }
, tileset { Tileset::from_json( "res/data/tileset.json", *model ) }
, player { "res/data/player.json", tileset, *model }
, map { "res/data/map.json", tileset, *model }
, editor { *model }
{
	player.node->name = "player";
	player.node->flags |= Flag::PLAYER;
	player.node->bounds->dynamic = true;
	gfx.camera.set_orthographic( create_viewport( VkExtent2D { 320, 240 } ) );
}


void Game::run()
{
	while ( gfx.window.is_alive() )
	{
		gfx.glfw.poll();
		gfx.window.update();
		auto delta = gfx.glfw.get_delta();

		// Do not propagate input when using gui
		if ( !ImGui::IsAnyWindowHovered() )
		{
			editor.update( gfx, map, tileset, *model );
		}

		if ( !config.pause )
		{
			Player::Movement::update( delta, gfx.window.input, player );

			map.root->update_transforms();
			player.node->update_transforms();

			collisions.add( *map.root );
			collisions.add( *player.node );
			collisions.update();

			player.node->update_transforms();
		}

		/// Victory conditions are that all blocks in the map are marked
		std::vector<gfx::Node*> blocks;

		for ( auto& entity : *map.entities )
		{
			if ( entity.node->flags & Flag::BLOCK )
			{
				blocks.emplace_back( &*entity.node );
			}
		};
		
		bool win = std::all_of( std::begin( blocks ), std::end( blocks ), []( gfx::Node* block ) {
			return block->flags & Flag::MARKED;
		} );


		// Draw gui between NewFrame and update
		ImGui::NewFrame();

		if ( win )
		{
			config.pause = true;

			ImGui::SetNextWindowBgAlpha( 0.75f );
			ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration |
				ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
				ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
			auto& io = ImGui::GetIO();
			float padding = Tile::tile_size;
			float height = io.DisplaySize.y / 3 - padding * 2.0f;
			float width = io.DisplaySize.x - padding * 2.0f;
			auto pos = ImVec2( padding, io.DisplaySize.y - height - padding );
			auto size = ImVec2( width, height );
			ImGui::SetNextWindowSize( size );
			ImGui::SetNextWindowPos( pos );
			ImGui::Begin( "Message", nullptr, flags );
			ImGui::Text( "You won!" );
			ImGui::End();
		}

		editor.draw( tileset, *model );
		editor.draw( map );
		gfx.gui.update( delta );

		if ( gfx.render_begin() )
		{
			gfx.draw( *map.root );
			gfx.draw( *player.node );

			if ( editor.selected_entity )
			{
				gfx.draw(
					*editor.selected_entity->node,
					*editor.debug_rect );
			}

			gfx.render_end();
		}
	}
}


Game::~Game()
{
	player.save( "res/data/player.json" );
	tileset.save( "res/data/tileset.json" );
	gfx.device.wait_idle();
}


} // namespace spot::jam
