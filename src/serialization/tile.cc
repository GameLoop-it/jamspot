#include "spot/jam/serialization/tile.h"


namespace spot::jam
{


void to_json( nlohmann::json& j, const Tile& t )
{
	j["x"] = t.x;
	j["y"] = t.y;
	j["non_passable"] = t.non_passable;
	j["movable"] = t.movable;
}


void from_json( const nlohmann::json& j, Tile& t )
{
	t.x = j["x"].get<float>();
	t.y = j["y"].get<float>();
	
	// Optionals

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
