#include "spot/jam/serialization/tile.h"


namespace spot::jam
{


void to_json( nlohmann::json& j, const TileId& id )
{
	j["x"] = id.x;
	j["y"] = id.y;
}


void from_json( const nlohmann::json& j, TileId& id )
{
	id.x = j["x"].get<float>();
	id.y = j["y"].get<float>();
}


void to_json( nlohmann::json& j, const Tile& t )
{
	j["id"] = t.id;
	j["name"] = t.name;
	j["non_passable"] = t.non_passable;
	j["movable"] = t.movable;
}


void from_json( const nlohmann::json& j, Tile& t )
{
	t.id = j["id"].get<TileId>();
	
	// Optionals

	if ( j.count( "name" ) )
	{
		t.name = j["name"].get<std::string>();
	}

	if ( j.count( "non_passable" ) )
	{
		t.non_passable = j["non_passable"].get<bool>();
	}

	if ( j.count( "movable" ) )
	{
		t.movable = j["movable"].get<bool>();
	}
}


} // namespace spot::jam
