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

	return node;
}


} // namespace spot::jam
