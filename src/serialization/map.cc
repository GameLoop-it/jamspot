#include "spot/jam/map.h"

#include <spot/gfx/model.h>
#include <spot/gfx/node.h>

#include "spot/jam/serialization/tile.h"
#include "spot/jam/tileset.h"


namespace spot::jam
{


Map::Map( const char* path, Tileset& tiles, gfx::Model& model )
: root { model.nodes.push() }
{
}


} // namespace spot::jam
