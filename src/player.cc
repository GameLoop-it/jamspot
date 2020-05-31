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
	if ( input.click.left || input.click.right )
	{
		auto road = Tile( 2, 0 );
		auto grass = Tile( 6, 0 );
		auto entity = input.click.left ? Entity( road ) : Entity( grass );
		entity.node = tiles.create_node( entity.tile, model );

		float px = player.get_translation().x + Tile::tile_size / 2;
		float py = player.get_translation().y + Tile::tile_size / 2;

		float x = int( px / Tile::tile_size );
		float y = int( py / Tile::tile_size );

		entity.node->set_translation_x( x * Tile::tile_size );
		entity.node->set_translation_y( y * Tile::tile_size );

		entity.node->set_translation_z( -0.125f );
		map.emplace( std::move( entity ) );
	}
}


} // namespace spot::jam
