#include <bn_math.h>
#include <bn_log.h>

#include "pikmin.h"

pikmin::pikmin(bn::sprite_item item, bn::fixed xcor, bn::fixed ycor, bn::random &rand) : 
    _flower(item.create_sprite(xcor, ycor)),
    _blow(bn::create_sprite_animate_action_forever(
                    _flower, 4, item.tiles_item(), true, 0, 1, 2, 1, 0, 3, 4, 3)),
    _target(xcor, ycor),
    _speed(0),
    _direction(0),
    _max_speed(rand.get_fixed(MAX_SPEED_MIN, MAX_SPEED_MAX)),
    _blowing(false) {
    
}

void pikmin::update(){
    if(at_target()){
        _speed = 0;
    }else{
        point_at_target();
    }
    move();
    if(_blowing){
        _blow.update();
    }else if(_blow.current_index() !=0){
        _blow.update();
    }
}

bool pikmin::at_target(){
    return (x() < _target.x() + TOLERANCE) && 
           (x() > _target.x() - TOLERANCE) && 
           (y() < _target.y() + TOLERANCE) && 
           (y() > _target.y() - TOLERANCE);
}

void pikmin::point_at_target(){

    _direction = angle_between_points(position(), _target);
    
    _speed += ACCEL;
    if(_speed > _max_speed) _speed = _max_speed;
}

void pikmin::move(){
    set_x(x() + _speed * bn::sin(_direction));
    set_y(y() + _speed * bn::cos(_direction));
}

void pikmin::stop_blowing(){
    _blow.reset();
    _blowing=false;
}

void pikmin::attract_or_repel(bn::unique_ptr<controllable> &enemy){
    if(dist(position(), enemy->position()) < NOTICING_DISTANCE){
        if(enemy->attractive()){
            set_target(
                pos_at_distance_from_target(
                position(), enemy->position(), 
                25));
        }else{
            set_target(
                pos_at_distance_from_target(
                position(), enemy->position(), 
                100));
        }
    }
}

bn::fixed_point pikmin::pos_at_distance_from_target(bn::fixed_point pos, bn::fixed_point target, bn::fixed desired_dist){
    bn::fixed full_dist = dist(pos, target);
    bn::fixed_point x_y_dist = pos - target;

    return target + (x_y_dist * (desired_dist / full_dist));

}

bn::fixed pikmin::angle_between_points(bn::fixed_point pos, bn::fixed_point target){
    bn::fixed xdist = target.x() - pos.x();
    bn::fixed ydist = target.y() - pos.y();

    return bn::atan2(xdist.ceil_integer(), ydist.ceil_integer());
}

//simple euclidean distance
bn::fixed pikmin::dist(bn::fixed_point a, bn::fixed_point b){
    bn::fixed xdist = a.x() - b.x();
    bn::fixed ydist = a.y() - b.y();

    return bn::sqrt(xdist*xdist + ydist*ydist);
}