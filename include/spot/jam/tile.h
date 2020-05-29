#pragma once

#include <spot/handle.h>

namespace spot::gfx
{
class Mesh;
class Material;
class Model;
}

namespace spot::jam
{


class Tile
{
  public:
	static constexpr uint32_t tile_size = 16;

	Tile() = default;
	Tile( uint32_t xx, uint32_t yy ) : x { xx }, y { yy } {}

	bool operator==( const Tile& o ) const { return x == o.x && y == o.y; }

	/// @brief Constructs a mesh for a tile
	/// @param material Material with the texture atlas containing tiles
	/// @param model Model where to store resources
	/// @return A mesh for that tile in the atlas
	Handle<gfx::Mesh> create_quad( const gfx::Material& material, gfx::Model& model ) const;

	/// Coordinates of the tile in the atlas
	uint32_t x = 0;
	uint32_t y = 0;
};


} // namespace spot::jam


namespace std
{
template <>
class hash<spot::jam::Tile>
{
  public:
	size_t operator()( const spot::jam::Tile& t ) const
	{
		return hash_combine( t.x, t.y );
	}
};
}
