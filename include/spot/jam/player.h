#pragma once

namespace spot::gfx
{
class Input;

class Node;
class Model;
}

namespace spot::jam
{

class Entity;

class Map;
class Tileset;

struct Player
{
	struct Movement
	{
		static float speed;

		static void update( const float delta, const gfx::Input& input, Entity& player );
	};

	struct Action
	{
		static void update( const gfx::Input& input, const gfx::Node& player, Map& map, Tileset& tiles, gfx::Model& model );
	};
};

} // namespace spot::jam
