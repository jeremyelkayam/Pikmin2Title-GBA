#pragma once
#include <bn_sprite_ptr.h>
#include <bn_fixed_point.h>
#include <bn_random.h>

#define MAX_SPEED_MIN bn::fixed(0.8)
#define MAX_SPEED_MAX bn::fixed(1.2)
#define ACCEL bn::fixed(0.05)
#define TOLERANCE bn::fixed(1)

class pikmin {
    private:
        bn::sprite_ptr _flower;
        bn::fixed_point _target;
        bn::fixed _speed;
        bn::fixed _direction;

        bn::fixed _max_speed;

        bool at_target();
        void point_at_target();
        void move();
    public:
        pikmin(bn::fixed xcor, bn::fixed ycor, bn::random &rand);
        bn::fixed x() {return _flower.x();}
        bn::fixed y() {return _flower.y();}
        void set_x(bn::fixed x){_flower.set_x(x);}
        void set_y(bn::fixed y){_flower.set_y(y);}

        void set_target(bn::fixed_point target){_target = target;}
        
        void update();
};
