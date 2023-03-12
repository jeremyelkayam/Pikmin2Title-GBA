#include <bn_core.h>
#include <bn_log.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_fixed.h>
#include <bn_fixed_rect.h>
#include <bn_random.h>
#include <bn_math.h>
#include <bn_display.h>
#include "pikmin.h"
#include "iridescent_flint_beetle.h"
#include "bn_sprite_items_redpikmin.h"
#include "bn_sprite_items_bluepikmin.h"
#include "bn_sprite_items_yellowpikmin.h"
//debug settings for emulator
#define BN_LOG_BACKEND_MGBA true
#define NUM_PIKMIN 100
#define WINDSPEED bn::fixed(0.5)
#define WINDWIDTH 60

void disperse(bn::vector<pikmin, NUM_PIKMIN> &pikmin_vec){
    bn::fixed dist(200);
    bn::fixed pi(3.14159);
    for(int z = 0; z < pikmin_vec.size(); ++z){
        bn::fixed xtarget = bn::sin(pi * z * bn::fixed(0.1)) * dist;
        bn::fixed ytarget = bn::cos(pi * z * bn::fixed(0.1)) * dist;
        
        pikmin_vec.at(z).set_target(bn::fixed_point(xtarget, ytarget));
    }
}

bool point_inside_rect(bn::fixed_point pt, bn::fixed_rect rect){

    return (pt.x() < rect.right() &&
            pt.x() > rect.left() &&
            pt.y() < rect.bottom() &&
            pt.y() > rect.top() );
}

void update_wind(bn::fixed_rect &windbox, bn::vector<pikmin, NUM_PIKMIN> &pikmin_vec){
    for(pikmin &p : pikmin_vec){
        if(point_inside_rect(p.position(), windbox)){
            p.start_blowing();
        }else{
            p.stop_blowing();
        }
    }

    windbox.set_x(windbox.x() + WINDSPEED);
}


int main()
{
    bn::core::init();
    bn::vector<pikmin, NUM_PIKMIN> pikmin_vec;
    bn::random rand;
    bn::unique_ptr<controllable> enemy(new iridescent_flint_beetle(0, 0));


    for(int z = 0; z < pikmin_vec.max_size(); ++z){
        pikmin_vec.emplace_back(bn::sprite_items::redpikmin, 0, -90, rand);
        pikmin_vec.at(z).set_target(bn::fixed_point(-40 + (z % 10) * 10, -40 + (z / 10) * 10));
    }

    short time_dispersed=0;
    unsigned int next_gust = rand.get_int(20*60,60*60);
    unsigned int timer=0;

    bn::optional<bn::fixed_rect> windbox;
    
    while(true)
    {   
        ++timer;
        if(timer == next_gust){
            BN_LOG("windy time");
            windbox = bn::fixed_rect(-200,0,WINDWIDTH,160);
            next_gust = timer + rand.get_int(20*60,60*60);
        }

        if(bn::keypad::r_pressed() || bn::keypad::l_pressed()) {
            disperse(pikmin_vec);
        }



        if(windbox){
            update_wind(*windbox, pikmin_vec);
            if(windbox->x() > 0 && !windbox->intersects(bn::fixed_rect(0,0,bn::display::width(), bn::display::height()))){
                windbox.reset();
            }
        }

        for(pikmin& p : pikmin_vec){
            p.update();
            if(enemy){
                p.attract_or_repel(enemy);
            }
        }

        if(enemy){
            enemy->update();
        }

        rand.update();
        bn::core::update();
    }
}


