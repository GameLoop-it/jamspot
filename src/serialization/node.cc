#include "spot/jam/serialization/node.h"


namespace spot::gfx
{


void to_json( nlohmann::json& j, const gfx::Node& n )
{
	j["x"] = n.get_translation().x;
	j["y"] = n.get_translation().y;
	j["z"] = n.get_translation().z;
}


void from_json( const nlohmann::json& j, gfx::Node& n )
{
	n.set_translation_x( j["x"].get<float>() );
	n.set_translation_y( j["y"].get<float>() );
	n.set_translation_z( j["z"].get<float>() );
}


} // namespace spot::json
