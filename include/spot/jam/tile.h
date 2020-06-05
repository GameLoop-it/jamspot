#pragma once

#include <string>
#include <spot/handle.h>


namespace spot::gfx
{
class Mesh;
class Material;
class Model;
}

namespace spot::jam
{


/// @brief Coordinates of the tile in the atlas
struct TileId
{
	uint32_t x = 0;
	uint32_t y = 0;

	bool operator==( const TileId& o ) const { return x == o.x && y == o.y; }
};


class Tile
{
  public:
	static constexpr uint32_t tile_size = 16;

	Tile() = default;
	Tile( uint32_t xx, uint32_t yy ) : id { xx, yy } {}
	Tile( uint32_t xx, uint32_t yy, const std::string& n ) : id { xx, yy }, name { n } {}

	bool operator==( const Tile& o ) const { return id == o.id; }

	/// @brief Constructs a mesh for a tile
	/// @param material Material with the texture atlas containing tiles
	/// @param model Model where to store resources
	/// @return A mesh for that tile in the atlas
	Handle<gfx::Mesh> create_quad( const gfx::Material& material, gfx::Model& model ) const;

	TileId id = {};

	/// Name of the tile
	std::string name = "empty";

	/// Whether the player can pass on the tile or not
	/// @example This would be false for tiles like grass
	/// @example True for tiles like trees
	bool non_passable = false;

	/// Whether the player can push this tile or not
	/// @example False for tiles like trees
	/// @example True for tile like crates
	bool movable = false;
};


} // namespace spot::jam


namespace std
{
template <>
class hash<spot::jam::TileId>
{
  public:
	size_t operator()( const spot::jam::TileId& id ) const
	{
		return hash_combine( id.x, id.y );
	}
};
}
