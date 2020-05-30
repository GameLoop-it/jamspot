#pragma once

namespace spot::gfx { class Input; }

namespace spot::jam
{

class Entity;

struct Player
{
	static float speed;

	static void update( const float delta, const gfx::Input& input, Entity& player );
};

} // namespace spot::jam
