#pragma once


namespace spot::jam
{


struct Config
{
	Config() = default;

	/// @brief Constructs a new config from file
	/// @param path File path containing config data
	Config( const char* path );

	/// Game pause state
	bool pause = false;

	/// Scale of the window
	uint32_t scale = 2;

	/// Number of the map to load
	uint32_t map = 0;
};


} // namespace spot::jam
