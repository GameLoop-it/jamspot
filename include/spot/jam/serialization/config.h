#pragma once

#include <nlohmann/json.hpp>


namespace spot::jam
{


struct Config;

void to_json( nlohmann::json& j, const Config& c );


} // namespace spot::jam
