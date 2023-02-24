#include "controllable.h"
#include <bn_keypad.h>
#include <bn_math.h>

controllable::controllable(bn::sprite_item item, bn::fixed xcor, bn::fixed ycor, bn::fixed speed) : 
    _sprite(item.create_sprite(xcor, ycor)),
    _speed(speed),
    _rotation_angle(0) {    
}

void controllable::update(){

    if(bn::keypad::up_held()){
        _sprite.set_x(_sprite.x() + _speed * bn::degrees_sin(_rotation_angle));
        _sprite.set_y(_sprite.y() + _speed * bn::degrees_cos(_rotation_angle));        
    }

    if(bn::keypad::left_held() || bn::keypad::right_held()){
        bn::fixed new_angle;

        if(bn::keypad::left_held()){
            new_angle = _sprite.rotation_angle() + _speed;

        }else if(bn::keypad::right_held()){
            new_angle = _sprite.rotation_angle() - _speed;

        }

        //normalize

        _sprite.set_rotation_angle(normalized_degrees_angle(new_angle));
        _rotation_angle = _sprite.rotation_angle();

    }
}

bn::fixed controllable::normalized_degrees_angle(bn::fixed angle){
    while (angle < 0) angle += 360;
    while (angle > 360) angle -= 360;
    return angle;
}