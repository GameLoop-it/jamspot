#include "spot/jam/serialization/config.h"
#include "spot/jam/config.h"

#include <spot/log.h>
#include <spot/file/ifstream.h>
#include <algorithm>

#include "spot/jam/serialization/serialization.h"


namespace spot::jam
{


void to_json( nlohmann::json& j, const Config& c )
{
	j["pause"] = c.pause;
	j["scale"] = c.get_scale();
	j["map"] = c.get_map();
	j["editor"] = c.editor;
}


Config::Config( const char* path )
{
	auto file = file::Ifstream( path );
	nlohmann::json j;
	file >> j;

	pause = j["pause"].get<bool>();

	set_scale( j["scale"].get<uint32_t>() );

	constexpr uint32_t map_count = 7;
	auto m = j["map"].get<uint32_t>();
	map = std::clamp<uint32_t>( m, 0, map_count );

	editor = j["editor"].get<bool>();
}


void Config::save( const char* path ) const
{
	nlohmann::json j = *this;
	auto file = std::fstream( path, std::ios::trunc | std::ios::out );
	file << j;
	logs( "Config saved to {}\n", path );
}


} // namespace spot::jam
