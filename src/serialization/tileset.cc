#include "spot/jam/serialization/tileset.h"
#include "spot/jam/tileset.h"

#include <spot/log.h>
#include <spot/file/ifstream.h>
#include <spot/gfx/model.h>

#include "spot/jam/serialization/tile.h"

namespace spot::jam
{


void to_json( nlohmann::json& j, const Tileset& t )
{
	j["image"] = t.image->uri;

	auto tiles = nlohmann::json::array();
	for ( auto& [_,pair] : t.tiles )
	{
		const Tile& tile = pair.first;
		tiles.emplace_back( tile );
	}
	j["tiles"] = tiles;
}


Tileset Tileset::from_json( const char* path, gfx::Model& model )
{
	auto file = file::Ifstream( path );
	nlohmann::json j;
	file >> j;
	
	auto image_path = j["image"].get<std::string>();

	auto tileset = Tileset( image_path.c_str(), model );

	for ( auto& tile : j["tiles"] )
	{
		tileset.emplace( tile.get<Tile>(), model );
	}

	return tileset;
}


void Tileset::save( const char* path ) const
{
	nlohmann::json j = *this;
	auto file = std::fstream( path, std::ios::trunc | std::ios::out );
	file << j;
	logs( "Tileset saved to {}\n", path );
}


} // namespace spot::jam
