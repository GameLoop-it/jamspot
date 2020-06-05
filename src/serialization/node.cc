#include "spot/jam/serialization/node.h"

#include <spot/gfx/node.h>


namespace spot::gfx
{


void to_json( nlohmann::json& j, const Node& n )
{
	j["x"] = n.get_translation().x;
	j["y"] = n.get_translation().y;
	j["z"] = n.get_translation().z;
	j["name"] = n.name;
}


void from_json( const nlohmann::json& j, Node& n )
{
	n.set_translation_x( j["x"].get<float>() );
	n.set_translation_y( j["y"].get<float>() );
	n.set_translation_z( j["z"].get<float>() );

	if ( j.count( "name" ) )
	{
		n.name = j["name"].get<std::string>();
	}
}


} // namespace spot::json
