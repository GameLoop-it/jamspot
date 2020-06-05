#include "spot/jam/serialization/entity.h"
#include "spot/jam/entity.h"

#include <spot/log.h>
#include <spot/file/ifstream.h>
#include <spot/gfx/model.h>
#include <spot/gfx/node.h>

#include "spot/jam/serialization/serialization.h"
#include "spot/jam/serialization/node.h"
#include "spot/jam/serialization/tile.h"

#include "spot/jam/tileset.h"


namespace spot::jam
{


void to_json( nlohmann::json& j, const Entity& p )
{
	j["tile"] = p.tile;
	j["node"] = *p.node;
}


void from_json( const nlohmann::json& j, Entity& p )
{
	p.tile = j["tile"].get<Tile>();
}


Entity::Entity( const char* path, Tileset& tiles, gfx::Model& model )
: Entity( read_file( path ), tiles, model )
{}


Entity::Entity( const std::vector<uint8_t>& data, Tileset& tiles, gfx::Model& model )
{
	auto j = nlohmann::json::parse( data );
	from_json( j, *this );
	create_node( j["node"].get<gfx::Node>(), tiles, model );
}


Entity Entity::from_cbor( const std::vector<uint8_t>& data, Tileset& tiles, gfx::Model& model )
{
	Entity entity;
	auto j = nlohmann::json::from_cbor( data );
	from_json( j, entity );
	entity.create_node( j["node"].get<gfx::Node>(), tiles, model );
	return entity;
}


void Entity::create_node( const gfx::Node& tnode, Tileset& tiles, gfx::Model& model )
{
	node = tiles.create_node( tile, model );
	node->set_translation( tnode.get_translation() );
	node->name = tnode.name;
}


void Entity::save( const char* path ) const
{
	nlohmann::json j = *this;
	auto file = std::fstream( path, std::ios::trunc | std::ios::out );
	file << j;
}


} // namespace spot::jam
