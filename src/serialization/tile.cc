#include "spot/jam/serialization/tile.h"


namespace spot::jam
{


void to_json( nlohmann::json& j, const Tile& t )
{
	j["x"] = t.x;
	j["y"] = t.y;
}


void from_json( const nlohmann::json& j, Tile& t )
{
	t.x = j["x"].get<float>();
	t.y = j["y"].get<float>();
}


} // namespace spot::jam
