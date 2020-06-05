#include "spot/jam/tileset.h"

#include <spot/gfx/model.h>
#include <spot/gfx/node.h>


namespace spot::jam
{


Tileset::Tileset( const char* path, gfx::Model& model )
: image { model.images.push( gfx::Image( path ) ) }
, texture { model.textures.push( gfx::Texture( image ) ) }
, material { model.materials.push( gfx::Material( texture ) ) }
{}


Tileset::Resources::iterator Tileset::emplace( const Tile& tile, gfx::Model& model )
{
	// Reuse meshes for node created from the same tile
	if ( auto it = tiles.find( tile.id ); it != std::end( tiles ) )
	{
		return it;
	}

	Handle<gfx::Mesh> mesh = tile.create_quad( *material, model );
	auto pair = std::make_pair( std::move( tile ), std::move( mesh ) );
	auto [it, ok] = tiles.emplace( tile.id, std::move( pair ) );
	assert( ok && "Can not add tile to tileset" );
	return it;
}


Handle<gfx::Node> Tileset::create_node( const Tile& tile, gfx::Model& model )
{
	Handle<gfx::Node> node = model.nodes.push();
	node->mesh = emplace( tile, model )->second.second;

	// Create collision bounds for the node
	auto bounds = model.bounds.push();
	node->bounds = bounds;
	bounds->shape = math::Rect::Unit * ( Tile::tile_size - 2 );

	if ( tile.non_passable )
	{
		// Add logic to push player away
		bounds->colliding_with = []( gfx::Node& self, gfx::Node& other ) {
			math::Vec2 distance = gfx::Bounds::distance( self, other );

			// Choose shortest distance to move the player away
			if ( std::fabs( distance.x ) < std::fabs( distance.y ) )
			{
				distance.y = 0.0f;
			}
			else
			{
				distance.x = 0.0f;
			}

			other.translate( -distance );
		};
	}

	if ( tile.movable )
	{
		bounds->dynamic = true;

		// Add logic to push the node away
		bounds->colliding_with = []( gfx::Node& self, gfx::Node& other ) {
			math::Vec2 distance = gfx::Bounds::distance( self, other );

			// Choose shortest distance
			if ( std::fabs( distance.x ) < std::fabs( distance.y ) )
			{
				distance.y = 0;
			}
			else
			{
				distance.x = 0;
			}

			if ( other.name == "player" )
			{
				// Push this node
				self.translate( distance / 2.0f );
				// While slowing down the player as well
				other.translate( -distance / 2.0f );
			}
			else if ( other.bounds->dynamic )
			{
				other.translate( -distance );
			}
			
		};
	}

	return node;
}


} // namespace spot::jam
