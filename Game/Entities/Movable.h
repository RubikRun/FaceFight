#pragma once

#include <SFML/Graphics.hpp>

/**
 * An abstract class for objects in the game that can be moved in space.
 * Such objects consist of a center point and the ability to move it around.
 * The center is not neccessarily the geometric center of the object,
 * but it acts as a handle to the object's movement.
 * It is the job of the inherited class to implement
 * how the object should move relative to the center.
 */
class Movable
{

  public:

    /**
     * Creates a movable object with the given initial position
     * 
     * @param[in] position (optional)
     *  Initial position of the object's center point
     */
    Movable(
      sf::Vector2f const& position = {0.f, 0.f}
    );

    /**
     * Sets the position of the center point of the movable object.
     * Also moves the whole object following the center.
     * 
     * @param[in] position
     *  Position of the center point to set
     */
    void SetPosition(
      sf::Vector2f const& position
    );

    /**
     * Returns the position of the center point of the movable object
     * 
     * @return position of the center point
     */
    sf::Vector2f GetPosition() const;

    /**
     * Moves the object by the given delta vector
     * 
     * @param[in] delta
     *  Delta vector by which to move the object
     */
    void Move(
      sf::Vector2f const& delta
    );

  protected:

    /**
     * Makes the object "follow" its center,
     * meaning that the whole object moves to where the center is.
     * This function is called every time the center moves,
     * and should be implemented by the inherited class
     * to describe how the object's position should relate to the center,
     * such that moving the center results in the expected movement of the object.
     */
    virtual void FollowCenter() = 0;

  private:

    /// Center point of the object
    sf::Vector2f _center;
};