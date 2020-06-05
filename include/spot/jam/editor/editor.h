#pragma once

#include <spot/handle.h>

#include "spot/jam/tile.h"


namespace spot::gfx
{
class Graphics;
class Model;
class Mesh;
}


namespace spot::jam
{


class Tile;
class Tileset;
class Map;
class Entity;


/// @brief This is the in-game editor. Its purpose is to enable
/// developers to create new tiles, to modify them, to put entities
/// on the map, and similar things.
class Editor
{
  public:
	/// @param model Used to store nodes and meshes
	Editor( gfx::Model& model );

	/// @brief Draw a window with information about a tile prototype
	void draw( Tile& tile );

	/// @brief Draw a window with the list of tiles in a tileset
	/// @param model Used to store nodes and meshes
	void draw( Tileset& tileset, gfx::Model& model );

	/// @brief Draw a window with the information about an entity in the map
	void draw( Entity& entity, Map& map );

	/// @brief Draw a window with the list of tiles in the map
	void draw( Map& map );

	/// @brief Performs editor actions
	/// @param graphics Graphics with information to process
	/// @param map Map to work on, it could be modified
	/// @param tileset Tiles used to create tiles
	/// @param model Used to store nodes and meshes
	void update( const gfx::Graphics& window, Map& map, Tileset& tileset, gfx::Model& model );

	Handle<gfx::Mesh> debug_rect;

	/// New tile prototype to use within tileset window
	Tile new_tile;

	/// Current selected tile prototype
	Tile* selected = nullptr;

	/// Current selected entity on the map
	Handle<Entity> selected_entity;
};


} // namespace spot::jam
