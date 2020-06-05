#include "spot/jam/tile.h"

#include <spot/gfx/material.h>
#include <spot/gfx/texture.h>
#include <spot/gfx/image.h>
#include <spot/gfx/model.h>

namespace spot::jam
{


Handle<gfx::Mesh> Tile::create_quad( const gfx::Material& material, gfx::Model& model ) const
{
	// Empty tile at (0,0)
	if ( id.x == 0 && id.y == 0 )
	{
		return {};
	}

	const float hsize = tile_size / 2.0f;

	// Create a default quad, then adjust texture coordinates
	auto quad = gfx::Mesh::create_quad(
		material,
		math::Vec3( -hsize, -hsize ),
		math::Vec3( hsize, hsize ) );

	uint32_t image_width = material.texture->source->width;
	uint32_t image_height = material.texture->source->height;

	float x_tiles = image_width / float( tile_size );
	float y_tiles = image_height / float( tile_size );

	float x_size = 1 / x_tiles;
	float y_size = 1 / y_tiles;

	float x_coord = id.x * x_size;
	float y_coord = id.y * y_size;

	gfx::Primitive& prim = quad.primitives[0];

	gfx::Vertex& a = prim.vertices[0];
	a.t.x = x_coord;
	a.t.y = y_coord + y_size;

	gfx::Vertex& b = prim.vertices[1];
	b.t.x = x_coord + x_size;
	b.t.y = y_coord + y_size;

	gfx::Vertex& c = prim.vertices[2];
	c.t.x = x_coord + x_size;
	c.t.y = y_coord;

	gfx::Vertex& d = prim.vertices[3];
	d.t.x = x_coord;
	d.t.y = y_coord;

	return model.meshes.push( std::move( quad ) );
}


} // namespace spot::jam
