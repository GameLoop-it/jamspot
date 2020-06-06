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

	auto entities = nlohmann::json::array();
	for ( auto& entity : *p.entities )
	{
		if ( entity.handle )
		{
			entities.emplace_back( entity );
		}
	}
	j["entities"] = entities;
}


Map::Map( const char* path, const uint32_t i, Tileset& tiles, gfx::Model& model )
: Map( read_file( fmt::format( "{}/{}.json", path, i ) ), tiles, model )
{
	id = i;
}


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

	// Populate entities
	for ( auto& jentity : j["entities"] )
	{
		auto entity = Entity::from_cbor( nlohmann::json::to_cbor( jentity ), tiles, model );
		emplace_dynamic( std::move( entity ) );
	}
}


void Map::save( const char* dir ) const
{
	nlohmann::json j = *this;

	std::string path = fmt::format( "{}/{}.json", dir, id );
	auto file = std::fstream( path, std::ios::trunc | std::ios::out );
	file << j;
	logs( "Map saved to {}\n", path );
}


} // namespace spot::jam
