#pragma once

#include <spot/handle.h>

#include "spot/jam/tile.h"

namespace spot::gfx
{
class Input;
class Node;
class Model;
}

namespace spot::jam
{


class Tileset;

class Entity
{
  public:
	Entity() = default;

	/// @brief Constructs a new entity from file
	/// @param path File path containing entity data
	/// @param tiles Tileset containing the mesh for the node
	/// @param model Model used to store meshes and nodes
	Entity( const char* path, Tileset& tiles, gfx::Model& model );

	Entity( Tile t ) : tile { std::move( t ) } {}

	void save( const char* path ) const;

	Tile tile;

	Handle<gfx::Node> node;
};


} // namespace spot::jam
