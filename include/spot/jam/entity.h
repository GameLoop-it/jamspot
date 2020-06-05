#pragma once

#include <vector>
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

class Entity : public Handled<Entity>
{
  public:
	static Entity from_cbor( const std::vector<uint8_t>& data, Tileset& tiles, gfx::Model& model );

	Entity() = default;

	/// @brief Constructs a new entity from file
	/// @param path File path containing entity data
	/// @param tiles Tileset containing the mesh for the node
	/// @param model Model used to store meshes and nodes
	Entity( const char* path, Tileset& tiles, gfx::Model& model );

	/// @brief Constructs a new entity from raw data
	/// @param data Raw data containing entity json representation of entity
	Entity( const std::vector<uint8_t>& data, Tileset& tiles, gfx::Model& model );
	
	/// @brief Creates a node for the entity
	/// @param node Prototype node to use as reference
	void create_node( const gfx::Node& node, Tileset& tiles, gfx::Model& model );

	Entity( Tile t ) : tile { std::move( t ) } {}

	/// @brief Save entity to file
	/// @param path File path where to save entity data
	void save( const char* path ) const;

	Tile tile;

	Handle<gfx::Node> node;
};


} // namespace spot::jam
