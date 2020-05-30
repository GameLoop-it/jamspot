#pragma once

#include <nlohmann/json.hpp>

#include <spot/gfx/node.h>

namespace spot::gfx
{


void to_json( nlohmann::json& j, const gfx::Node& n );

void from_json( const nlohmann::json& j, gfx::Node& n );


} // namespace spot::jam
