#pragma once

#include <nlohmann/json.hpp>

#include "spot/jam/entity.h"


namespace spot::jam
{


void to_json( nlohmann::json& j, const Entity& p );

void from_json( const nlohmann::json& j, Entity& p );


} // namespace spot::jam
