#pragma once
#include <bn_sprite_ptr.h>
#include <bn_sprite_item.h>
#include <bn_fixed_point.h>
#include <bn_random.h>
#include <bn_sprite_animate_actions.h>

#define MAX_SPEED_MIN bn::fixed(0.8)
#define MAX_SPEED_MAX bn::fixed(1.2)
#define ACCEL bn::fixed(0.05)
#define TOLERANCE bn::fixed(1)

class pikmin {
    private:
        bn::sprite_ptr _flower;
        bn::sprite_animate_action<9> _blow;
        bn::fixed_point _target;
        bn::fixed _speed;
        bn::fixed _direction;

        bn::fixed _max_speed;

        bool _blowing;

        bool at_target();
        void point_at_target();
        void move();
    public:
        pikmin(bn::sprite_item item, bn::fixed xcor, bn::fixed ycor, bn::random &rand);
        bn::fixed x() {return _flower.x();}
        bn::fixed y() {return _flower.y();}
        bn::fixed_point position() {return _flower.position();}
        void set_x(bn::fixed x){_flower.set_x(x);}
        void set_y(bn::fixed y){_flower.set_y(y);}

        void set_target(bn::fixed_point target){_target = target;}

        void start_blowing() {_blowing=true; }
        void stop_blowing();
        
        void update();
};
