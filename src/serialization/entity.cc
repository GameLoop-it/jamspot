#include "spot/jam/serialization/entity.h"

#include <spot/file/ifstream.h>
#include <spot/gfx/model.h>

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
{
	auto file = file::Ifstream( path );
	nlohmann::json j;
	file >> j;
	*this = j.get<Entity>();
	gfx::Node tnode = j["node"].get<gfx::Node>();
	node = tiles.create_node( tile, model );
	node->set_translation( tnode.get_translation() );
}


void Entity::save( const char* path ) const
{
	nlohmann::json j = *this;
	auto file = std::fstream( path, std::ios::trunc | std::ios::out );
	file << j;
}


} // namespace spot::jam
