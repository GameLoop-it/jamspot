#pragma once

#include <nlohmann/json.hpp>


namespace spot::gfx
{


class Node;

void to_json( nlohmann::json& j, const Node& n );

void from_json( const nlohmann::json& j, Node& n );


} // namespace spot::jam
