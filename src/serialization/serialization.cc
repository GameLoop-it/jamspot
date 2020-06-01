#include "spot/jam/serialization/serialization.h"

#include <fstream>
#include <spot/log.h>


namespace spot::jam
{


std::vector<uint8_t> read_file( const char* path )
{
	auto file = std::fstream( path, std::ios::binary | std::ios::in );
	if ( !file.is_open() )
	{
		loge( "Failed to open {}\n", path );
		return {};
	}

	file.seekg( 0, std::ios::end );
	size_t file_size = file.tellg();
	file.seekg( 0, std::ios::beg );

	std::vector<uint8_t> data;
	data.resize( file_size );
	file.read( reinterpret_cast<char *>( data.data() ), file_size );

	return data;
}


} // namespace spot::jam
