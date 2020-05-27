#pragma once

#include <spot/gfx/mesh.h>

namespace spot::gfx
{
class Material;
}

namespace spot::jam
{


class Tile
{
  public:
	static constexpr uint32_t tile_size = 16;

	/// @brief Constructs a mesh for a tile
	/// @param material Material with the texture atlas containing tiles
	/// @param x and y Coordinates of the tile in the atlas
	/// @return A mesh for that tile in the atlas
	static gfx::Mesh create_quad( const gfx::Material& material, uint32_t x, uint32_t y );
	
};


} // namespace spot::jam
