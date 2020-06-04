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


Handle<gfx::Node> Tileset::create_node( const Tile& tile, gfx::Model& model )
{
	Handle<gfx::Node> node = model.nodes.push();

	// Reuse meshes for node created from the same tile
	if ( auto it = tiles.find( tile ); it != std::end( tiles ) )
	{
		node->mesh = it->second;
	}
	else
	{
		Handle<gfx::Mesh> mesh = tile.create_quad( *material, model );
		node->mesh = mesh;
		auto [pair, ok] = tiles.emplace( tile, std::move( mesh ) );
		assert( ok && "Can not add tile to tileset" );
	}

	// Create collision bounds for the node
	auto bounds = model.bounds.push();
	node->bounds = bounds;
	bounds->shape = math::Rect::Unit * Tile::tile_size;

	if ( tile.non_passable )
	{
		// Add logic to push player away
		bounds->colliding_with = []( gfx::Node& self, gfx::Node& other ) {
			math::Vec2 distance = gfx::Bounds::distance( self, other );

			// Choose shortest distance to move the player away
			if ( std::fabs( distance.x ) < std::fabs( distance.y ) )
			{
				distance.y = 1.0f / distance.y;
			}
			else
			{
				distance.x = 1.0f / distance.x;
			}

			other.translate( -distance );
		};
	}

	if ( tile.movable )
	{
		bounds->dynamic = true;

		// Add logic to push the node away
		bounds->colliding_with = []( gfx::Node& self, gfx::Node& other ) {
			if ( other.name == "player" )
			{
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

				// Push this node
				self.translate( distance / 2.0f );
				// While slowing down the player as well
				other.translate( -distance / 2.0f );
			}
		};
	}

	return node;
}


} // namespace spot::jam
