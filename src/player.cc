#include "spot/jam/player.h"

#include <spot/gfx/input.h>
#include <spot/gfx/node.h>

namespace spot::jam
{


void Player::update( const float delta, const gfx::Input& input )
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
		node->translate( move );
	}
}


} // namespace spot::jam
