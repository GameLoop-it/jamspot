#pragma once


namespace spot::gfx { class Graphics; class Model; }

namespace spot::jam
{


class Tile;
class Tileset;
class Map;


/// @brief This is the in-game editor. Its purpose is to enable
/// developers to create new tiles, to modify them, to put entities
/// on the map, and similar things.
class Editor
{
  public:
	/// @brief Draw a window with information about a tile prototype
	void draw( Tile& tile );

	/// @brief Draw a window with the list of tiles in a tileset
	void draw( Tileset& tileset );

	/// @brief Performs editor actions
	/// @param graphics Graphics with information to process
	/// @param map Map to work on, it could be modified
	/// @param tileset Tiles used to create tiles
	/// @param model Used to store nodes and meshes
	void update( const gfx::Graphics& window, Map& map, Tileset& tileset, gfx::Model& model );

	/// Current selected tile prototype
	Tile* selected = nullptr;
};


} // namespace spot::jam
