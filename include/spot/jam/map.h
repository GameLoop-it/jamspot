#pragma once

#include <spot/handle.h>

#include "spot/jam/entity.h"

namespace spot::jam
{


class Map
{
  public:
	Map() = default;

	/// @brief Constructs a new map from file
	/// @param path File path containing map data
	/// @param tiles Tileset containing the mesh for the nodes
	/// @param model Model used to store meshes and nodes
	Map( const char* path, Tileset& tiles, gfx::Model& model );

	/// The root node of the map is used to update and draw
	/// recursively all its child, which are nodes of the map
	Handle<gfx::Node> root;
};


} // namespace spot::jam
