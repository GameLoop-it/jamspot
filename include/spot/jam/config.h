#pragma once


namespace spot::jam
{


class Game;


struct Config
{
	Config() = default;

	/// @brief Constructs a new config from file
	/// @param path File path containing config data
	Config( const char* path );

	/// @brief Load new config values in the game
	void load_map( uint32_t map, Game& game );
	uint32_t get_map() const { return map; }

	/// @brief Sets the scale of the window
	void set_scale( uint32_t s );
	uint32_t get_scale() const { return scale; }

	/// @brief Save config to json file
	void save( const char* path ) const;

	/// Game pause state
	bool pause = false;

	/// Whether the in game editor is enabled or not
	bool editor = false;

  private:
	/// Scale of the window
	uint32_t scale = 2;

	/// Number of the map to load
	uint32_t map = 0;
};


} // namespace spot::jam
