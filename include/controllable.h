#pragma once
#include <bn_sprite_ptr.h>
#include <bn_sprite_item.h>
#include <bn_fixed_point.h>

class controllable {
    protected:
        bn::sprite_ptr _sprite;
        bn::fixed _speed;
        bn::fixed _rotation_angle;
        bool _attractive;

        bn::fixed normalized_degrees_angle(bn::fixed angle);

    public:
        virtual ~controllable() = default;
        controllable(bn::sprite_item item, bn::fixed xcor, bn::fixed ycor, bn::fixed speed, bool attractive);

        virtual void update();
        bn::fixed_point position(){return _sprite.position();}
        bool attractive(){return _attractive;}
        bool repellent(){return !_attractive;}
};
