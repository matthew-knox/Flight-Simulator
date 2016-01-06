//
//  ship.h
//  TestFlightSim
//
//  Created by Matthew Knox on 3/8/15.
//  Copyright (c) 2015 mpknox2. All rights reserved.
//

//
// Ship class, represent the position of the ship in the over world

#ifndef SHIP_H_
#define SHIP_H_

#include "geometry.h"

class Ship
{
    Point position;
    Vector forward, up, right;
    double speed;
public:
    Ship(Point initialPosition = Point(0, 0, 0));
    Point getPosition()
    {
        return position;
    }
    void fly()
    {
        position += speed * forward;
    }
    void teleport(Point newPosition)
    {
        position = newPosition;
    }
    Vector getDirection()
    {
        return forward;
    }
    Vector getVertical()
    {
        return up;
    }
    void pitch(double angle);
    void roll(double angle);
    void yaw(double angle);
    double getSpeed()
    {
        return speed;
    }
    void setSpeed(double newSpeed)
    {
        speed = newSpeed;
    }
};

/**
 *  Default Ship constructor
 *
 *  forward: along negative-z
 *  up: along positive-y
 *  right: along positive-x
 *  speed: initialized to 2.0
 */
inline Ship::Ship(Point initialPosition):
    position(initialPosition), forward(0, 0, -1), up(0, 1, 0), right(1, 0, 0), speed(2){}

/**
 *  Movement functions for the Ship class:
 *
 *  pitch:  rotate forward and up theta radians around right.
 *  roll:   rotate up and right theta radians around forward.
 *  yaw:    rotate forward and right theta radians around up.
 */
inline void Ship::pitch(double angle)
{
    forward = unit(forward * cos(angle) + up * sin(angle));
    up = right.cross(forward);
}

inline void Ship::roll(double angle)
{
    right = unit(right * cos(angle) + up * sin(angle));
    up = right.cross(forward);
}

/** unused but implimented */
inline void Ship::yaw(double angle)
{
    right = unit(right * cos(angle) + forward * sin(angle));
    forward = up.cross(right);
}

#endif
