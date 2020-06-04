#include "spot/jam/map.h"

#include <spot/gfx/node.h>

namespace spot::jam
{


void Map::emplace( const Entity& e )
{
	// Make sure there are no nodes in that cell
	auto& translation = e.node->get_translation();
	auto key = math::Vec2( translation.x, translation.y );
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
	root->add_child( e.node );
	entities.emplace_back( std::move( e ) );
}


} // namespace spot::jam
