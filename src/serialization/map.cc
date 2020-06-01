#include "spot/jam/serialization/map.h"
#include "spot/jam/map.h"

#include <spot/log.h>
#include <spot/file/ifstream.h>
#include <spot/gfx/model.h>
#include <spot/gfx/node.h>

#include "spot/jam/serialization/serialization.h"
#include "spot/jam/serialization/entity.h"
#include "spot/jam/tileset.h"


namespace spot::math
{


void to_json( nlohmann::json& j, const Vec2& v )
{
	j["x"] = v.x;
	j["y"] = v.y;
}


void from_json( const nlohmann::json& j, Vec2& v )
{
	v.x = j["x"].get<float>();
	v.y = j["y"].get<float>();
}


} // namespace spot::math


namespace spot::jam
{


void to_json( nlohmann::json& j, const Map& p )
{
	auto array = nlohmann::json::array();
	for ( auto& [_,entity] : p.cells )
	{
		array.emplace_back( entity );
	}
	j["cells"] = array;
}


Map::Map( const char* path, Tileset& tiles, gfx::Model& model )
: Map( read_file( path ), tiles, model )
{}


Map::Map( const std::vector<uint8_t>& data, Tileset& tiles, gfx::Model& model )
: root { model.nodes.push() }
{
	if ( data.empty() )
	{
		return;
	}

	auto j = nlohmann::json::parse( data );

	// Populate cells
	for ( auto& jentity : j["cells"] )
	{
		auto entity = Entity::from_cbor( nlohmann::json::to_cbor( jentity ), tiles, model );
		emplace( std::move( entity ) );
	}
}


void Map::save( const char* path ) const
{
	nlohmann::json j = *this;
	auto file = std::fstream( path, std::ios::trunc | std::ios::out );
	file << j;
}


} // namespace spot::jam