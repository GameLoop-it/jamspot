#include "spot/jam/player.h"

#include <spot/gfx/input.h>
#include <spot/gfx/node.h>

#include <spot/gfx/model.h>
#include "spot/jam/map.h"
#include "spot/jam/tileset.h"

#include "spot/jam/entity.h"

namespace spot::jam
{


float Player::Movement::speed = 32.0f;


void Player::Movement::update( const float delta, const gfx::Input& input, Entity& player )
{
	math::Vec2 move;

	move.y += input.key.w;
	move.x -= input.key.a;
	move.y -= input.key.s;
	move.x += input.key.d;

	if ( move != math::Vec2::Zero )
	{
		move.normalize();
		move *= delta * speed;
		player.node->translate( move );
	}
}


void Player::Action::update( const gfx::Input& input, const gfx::Node& player, Map& map, Tileset& tiles, gfx::Model& model )
{
}


} // namespace spot::jam
