#pragma once


namespace spot::jam
{


class Tileset;
class Tile;


/// @brief This is the in-game editor. Its purpose is to enable
/// developers to create new tiles, to modify them, to put entities
/// on the map, and similar things.
class Editor
{
  public:
	/// @brief Draw a window with the list of tiles in a tileset
	void draw( Tileset& tileset );

	/// Current selected tile prototype
	const Tile* selected = nullptr;
};


} // namespace spot::jam
