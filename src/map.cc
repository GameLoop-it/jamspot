#include "spot/jam/map.h"

#include <spot/gfx/node.h>

namespace spot::jam
{


void Map::emplace( const Entity& e )
{
	// X and Y should be multiples of tile_size
	auto translation = e.node->get_translation();

	auto x = int32_t( translation.x );
	x -= x % Tile::tile_size;

	auto y = int32_t( translation.y );
	y -= y % Tile::tile_size;

	// Put static node below the player
	float z = -0.125;

	e.node->set_translation( math::Vec3( x, y, z ) );

	// Make sure there are no nodes in that cell
	auto key = math::Vec2( x, y );
	if ( auto it = cells.find( key ); it != std::end( cells ) )
	{
		// Otherwise remove old node
		auto& old = it->second.node;
		old->remove_from_parent();
		old->invalidate();
	}

	// Add new node
	root->add_child( e.node );
	cells[key] = std::move( e );
}


void Map::emplace_dynamic( const Entity& e )
{
	// Add new node
	e.node->set_translation_z( 0.0f );
	root->add_child( e.node );
	entities.emplace_back( std::move( e ) );
}


} // namespace spot::jam
