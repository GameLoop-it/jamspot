#include "spot/jam/editor/editor.h"

#include <spot/gfx/graphics.h>
#include <spot/gfx/model.h>
#include <spot/gfx/node.h>

#include "spot/jam/entity.h"
#include "spot/jam/tileset.h"
#include "spot/jam/map.h"

namespace spot::jam
{


Editor::Editor( gfx::Model& model )
: debug_rect {
	model.meshes.push( gfx::Mesh::create_rect(
		math::Rect::Unit * Tile::tile_size, gfx::Color::Red
	) ) }
{
	new_tile.name.resize( 16 );
}


void Editor::update( const gfx::Graphics& gfx, Map& map, Tileset& tileset, gfx::Model& model )
{
	if ( selected && gfx.window.input.click.left )
	{
		auto entity = Entity( *selected );
		entity.node = tileset.create_node( entity.tile, model );

		math::Vec2 coords = gfx.window.cursor_to( gfx.viewport.get_abstract() );
		entity.node->set_translation( coords );

		if ( entity.tile.movable )
		{
			map.emplace_dynamic( std::move( entity ) );
		}
		else
		{
			map.emplace( std::move( entity ) );
		}
	}
}


} // namespace spot::jam
