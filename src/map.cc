#include "spot/jam/map.h"

#include <spot/gfx/node.h>

namespace spot::jam
{


/// @return A Vec2 which x and y are multiples of tile size
math::Vec2 gen_key( const math::Vec2& p )
{
	auto x = int32_t( p.x );
	x -= x % Tile::tile_size;

	auto y = int32_t( p.y );
	y -= y % Tile::tile_size;

	return { float( x ), float( y ) };
}


void Map::emplace( const Entity& e )
{
	auto translation = e.node->get_translation();
	auto key = gen_key( { translation.x, translation.y } );

	// Put static node below the player
	float z = -0.125;
	e.node->set_translation( math::Vec3( key.x, key.y, z ) );

	// Make sure there are no nodes in that cell
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


void Map::remove_static( const math::Vec2& p )
{
	// Remove node
	auto key = gen_key( p );
	if ( auto it = cells.find( key ); it != std::end( cells ) )
	{
		auto& old = it->second.node;
		old->remove_from_parent();
		old->invalidate();
	}

	// Remove entity
	cells.erase( key );
}


void Map::emplace_dynamic( const Entity& e )
{
	// Add new node
	e.node->set_translation_z( 0.0f );
	root->add_child( e.node );
	entities.push( std::move( e ) );
}


} // namespace spot::jam
