#pragma once

#include <unordered_map>

#include "spot/jam/tile.h"

namespace spot::gfx
{
class Model;
class Image;
class Texture;
class Material;
class Node;
}

namespace spot::jam
{


class Tileset
{
  public:
	using Resources = std::unordered_map<TileId, std::pair<Tile, Handle<gfx::Mesh>>>;

	/// @brief Constructs a new editor from json file
	/// @param path File path containing tileset data
	/// @param model Model used to store meshes and nodes
	static Tileset from_json( const char* path, gfx::Model& model );

	/// @param path File path of the image to be loaded
	/// @param model Model where to store resources
	Tileset( const char* path, gfx::Model& model );

	/// @brief Save tileset to file
	/// @param path File path where to save tileset data
	void save( const char* path ) const;

	/// @brief Adds a tile to the tileset creating a mesh for it
	/// It does not do anything if the tile is already in the tileset
	/// @param tile Tile from which to create a mesh
	/// @param model Model where to store resources
	/// @return An iterator to tile resources
	Resources::iterator emplace( const Tile& tile, gfx::Model& model );

	/// @param tile Tile from which to create a node
	/// @param model Model where to store resources
	/// @return A new node from that tile
	Handle<gfx::Node> create_node( const Tile& tile, gfx::Model& model );

	/// Image with assets used for the jam
	Handle<gfx::Image> image;

	/// This is a texture made with the image
	/// It also has a sampler
	Handle<gfx::Texture> texture;

	/// Material containing the diffuse texture
	/// It will be the unique for every node
	Handle<gfx::Material> material;

	/// Map of tiles and their quad meshes
	Resources tiles;
};


} // namespace spot::jam
