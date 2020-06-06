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
	/// @param dir Directory path containing map json file
	/// @param id Number of the map
	/// @param tiles Tileset containing the mesh for the nodes
	/// @param model Model used to store meshes and nodes
	Map( const char* dir, uint32_t id, Tileset& tiles, gfx::Model& model );

	/// @brief Constructs a new map from raw data
	/// @param data Raw data containing json representation of map
	Map( const std::vector<uint8_t>& data, Tileset& tiles, gfx::Model& model );

	/// @brief Save map to file
	/// @param path Directory path where to save map json file
	void save( const char* dir ) const;

	/// @brief Adds an entity to the map at a specific cell position
	/// @param e Entity expected to have a valid node
	void emplace( const Entity& e );
	
	/// @brief Removes the static entity within the cell at that position
	/// @param p Position where to remove the static entity
	void remove_static( const math::Vec2& p );

	/// @brief Adds a dynamic entity to the map
	/// @param e Entity expected to have a valid node
	void emplace_dynamic( const Entity& e );

	/// Number of the map
	uint32_t id = 0;

	/// The root node of the map is used to update and draw
	/// recursively all its child, which are nodes of the map
	Handle<gfx::Node> root;

	/// Map has a collection of entities, each entity should occupy one
	/// single cell, therefore key is hash of (x,y) coordinates
	std::unordered_map<math::Vec2, Entity> cells;

	/// Collection of dynamic entities. Unlike cells these entities are not
	/// confined to a cell, but they could go everywhere in the map.
	Uvec<Entity> entities;

	/// Position the player should be when loading the map
	math::Vec2 player_position;
};


} // namespace spot::jam
