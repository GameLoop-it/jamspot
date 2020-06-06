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
}


Config::Config( const char* path )
{
	auto file = file::Ifstream( path );
	nlohmann::json j;
	file >> j;

	pause = j["pause"].get<bool>();
	auto s = j["scale"].get<uint32_t>();
	scale = std::clamp<uint32_t>( s, 1, 4 );
}


} // namespace spot::jam
