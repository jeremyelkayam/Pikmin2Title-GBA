#include <bn_math.h>
#include <bn_log.h>

#include "pikmin.h"
#include "bn_sprite_items_flower.h"

pikmin::pikmin(bn::fixed xcor, bn::fixed ycor, bn::random &rand) : 
    _flower(bn::sprite_items::flower.create_sprite(xcor, ycor)),
    _target(xcor, ycor),
    _speed(0),
    _direction(0),
    _max_speed(rand.get_fixed(MAX_SPEED_MIN, MAX_SPEED_MAX)) {
    
}

void pikmin::update(){
    if(at_target()){
        _speed = 0;
    }else{
        point_at_target();
    }
    move();
}

bool pikmin::at_target(){
    return (x() < _target.x() + TOLERANCE) && 
           (x() > _target.x() - TOLERANCE) && 
           (y() < _target.y() + TOLERANCE) && 
           (y() > _target.y() - TOLERANCE);
}

void pikmin::point_at_target(){
    bn::fixed xdist = _target.x() - x();
    bn::fixed ydist = _target.y() - y();

    _direction = bn::atan2(xdist.ceil_integer(), ydist.ceil_integer());
    
    _speed += ACCEL;
    if(_speed > _max_speed) _speed = _max_speed;
}

void pikmin::move(){
    set_x(x() + _speed * bn::sin(_direction));
    set_y(y() + _speed * bn::cos(_direction));
}
