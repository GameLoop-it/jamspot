#pragma once

#include <nlohmann/json.hpp>


namespace spot::jam
{


class Tileset;

void to_json( nlohmann::json& j, const Tileset& t );


} // namespace spot::jam
