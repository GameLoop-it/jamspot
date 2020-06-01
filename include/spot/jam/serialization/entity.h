#pragma once

#include <nlohmann/json.hpp>


namespace spot::jam
{


class Entity;

void to_json( nlohmann::json& j, const Entity& e );

void from_json( const nlohmann::json& j, Entity& e );


} // namespace spot::jam
