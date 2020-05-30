#pragma once

#include <nlohmann/json.hpp>

#include "spot/jam/tile.h"

namespace spot::jam
{


void to_json( nlohmann::json& j, const Tile& t );

void from_json( const nlohmann::json& j, Tile& t );


} // namespace spot::jam
