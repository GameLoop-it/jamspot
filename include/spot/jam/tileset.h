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
	/// @param path File path of the image to be loaded
	/// @param model Model where to store resources
	Tileset( const char* path, gfx::Model& model );

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
	std::unordered_map<Tile, Handle<gfx::Mesh>> tiles;
};


} // namespace spot::jam
