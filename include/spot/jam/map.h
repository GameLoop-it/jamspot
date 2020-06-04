#pragma once

#include <unordered_map>
#include <spot/handle.h>
#include <spot/math/math.h>

#include "spot/jam/entity.h"


namespace std
{
template<>
struct hash<spot::math::Vec2>
{
	size_t operator()(const spot::math::Vec2& v) const
	{
		return hash_combine( v.x, v.y );
	}
};
} // namespace std


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

	/// @brief Constructs a new map from raw data
	/// @param data Raw data containing json representation of map
	Map( const std::vector<uint8_t>& data, Tileset& tiles, gfx::Model& model );

	/// @brief Save map to file
	/// @param path File path where to save map data
	void save( const char* path ) const;

	/// @brief Adds an entity to the map at a specific cell position
	/// @param e Entity expected to have a valid node
	void emplace( const Entity& e );

	/// @brief Adds a dynamic entity to the map
	/// @param e Entity expected to have a valid node
	void emplace_dynamic( const Entity& e );

	/// The root node of the map is used to update and draw
	/// recursively all its child, which are nodes of the map
	Handle<gfx::Node> root;

	/// Map has a collection of entities, each entity should occupy one
	/// single cell, therefore key is hash of (x,y) coordinates
	std::unordered_map<math::Vec2, Entity> cells;

	/// Collection of dynamic entities. Unlike cells these entities are not
	/// confined to a cell, but they could go everywhere in the map.
	std::vector<Entity> entities;
};


} // namespace spot::jam
