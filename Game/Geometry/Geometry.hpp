/* Some geometry helper functions */

#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

namespace Geometry
{

/**
 * Calculates and returns vector's length
 * 
 * @param[in] v
 *  Vector whose length we want to calculate
 * 
 * @return calculated length of the vector
 */
float GetVectorLength(
    sf::Vector2f const& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

/**
 * Calculates the vector from one point to another
 * 
 * @param[in] pointA
 *  vector's begin point
 * @param[in] pointB
 *  vector's end point
 * 
 * @return vector from point A to point B
 */
sf::Vector2f GetVector(
    sf::Vector2f pointA,
    sf::Vector2f pointB)
{
    return pointB - pointA;
}

/**
 * Normalises the given vector,
 * meaning that it returns a vector
 * pointing in the same direction as the given vector,
 * but with length = 1.
 * 
 * @param[in] v
 *  Vector that we want to normalise
 * 
 * @return normalised vector with length = 1
 */
sf::Vector2f NormaliseVector(
    sf::Vector2f const& v)
{
    return v / GetVectorLength(v);
}

} // namespace Geometry