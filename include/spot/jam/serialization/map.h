#pragma once

#include <nlohmann/json.hpp>


namespace spot::math
{


class Vec2;

void to_json( nlohmann::json& j, const Vec2& v );

void from_json( const nlohmann::json& j, Vec2& v );


} // namespace spot::math


namespace spot::jam
{


class Map;

void to_json( nlohmann::json& j, const Map& p );


} // namespace spot::jam
