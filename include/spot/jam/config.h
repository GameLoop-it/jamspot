#pragma once


namespace spot::jam
{


struct Config
{
	Config() = default;

	/// @brief Constructs a new config from file
	/// @param path File path containing config data
	Config( const char* path );

	bool pause = false;

	uint32_t scale = 2;
};


} // namespace spot::jam
