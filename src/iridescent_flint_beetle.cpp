#include <bn_keypad.h>
#include <bn_log.h>

#include "iridescent_flint_beetle.h"
#include "bn_sprite_items_iridescent_flint_beetle.h"

iridescent_flint_beetle::iridescent_flint_beetle(bn::fixed xcor, bn::fixed ycor) : 
    controllable(bn::sprite_items::iridescent_flint_beetle, xcor, ycor, 2) {    
}

void iridescent_flint_beetle::update(){
    controllable::update();
    if(bn::keypad::up_pressed()){
        bn::fixed start_angle = controllable::normalized_degrees_angle(_rotation_angle - bn::fixed(7.5));
        bn::fixed end_angle =  controllable::normalized_degrees_angle(_sprite.rotation_angle() + 15);

        if(end_angle < start_angle) end_angle = 360;

        _sprite.set_rotation_angle(start_angle);
        _rotation = bn::sprite_rotate_loop_action(_sprite, 5, end_angle);
    }
    if(bn::keypad::up_released()){
        _rotation.reset();
    }

    if(_rotation){
        _rotation->update();
    }
}