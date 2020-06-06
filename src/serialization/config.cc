#include "spot/jam/serialization/config.h"
#include "spot/jam/config.h"

#include <spot/file/ifstream.h>
#include <algorithm>

#include "spot/jam/serialization/serialization.h"


namespace spot::jam
{


void to_json( nlohmann::json& j, const Config& c )
{
	j["pause"] = c.pause;
	j["scale"] = c.scale;
	j["map"] = c.map;
}


Config::Config( const char* path )
{
	auto file = file::Ifstream( path );
	nlohmann::json j;
	file >> j;

	pause = j["pause"].get<bool>();
	auto s = j["scale"].get<uint32_t>();
	scale = std::clamp<uint32_t>( s, 1, 4 );

	constexpr uint32_t map_count = 7;
	auto m = j["map"].get<uint32_t>();
	map = std::clamp<uint32_t>( m, 0, map_count );
}


} // namespace spot::jam
