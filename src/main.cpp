#include <bn_core.h>
#include <bn_log.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_fixed.h>
#include <bn_random.h>
#include <bn_math.h>
#include "bn_sprite_items_peasanthead.h"
#include "pikmin.h"
//debug settings for emulator
#define BN_LOG_BACKEND_MGBA true
#define NUM_PIKMIN 100

void disperse(bn::vector<pikmin, NUM_PIKMIN> &pikmin_vec){
    bn::fixed dist(200);
    bn::fixed pi(3.14159);
    for(int z = 0; z < pikmin_vec.size(); ++z){
        bn::fixed xtarget = bn::sin(pi * z * bn::fixed(0.1)) * dist;
        bn::fixed ytarget = bn::cos(pi * z * bn::fixed(0.1)) * dist;
        
        pikmin_vec.at(z).set_target(bn::fixed_point(xtarget, ytarget));
    }
}

int main()
{
    bn::core::init();
    BN_LOG("ok");
    bn::vector<pikmin, NUM_PIKMIN> pikmin_vec;
    bn::random rand;
    
    for(int z = 0; z < pikmin_vec.max_size(); ++z){
        pikmin_vec.emplace_back(0, -90, rand);
        pikmin_vec.at(z).set_target(bn::fixed_point(-120 + z * 2, 0));
    }

    short time_dispersed=0;
    

    while(true)
    {

        if(bn::keypad::r_pressed() || bn::keypad::l_pressed()) {
            disperse(pikmin_vec);
            time_dispersed=1;
        }

        if(time_dispersed) ++time_dispersed;



        for(pikmin& p : pikmin_vec){
            p.update();
            rand.update();
        }
        bn::core::update();
    }
}


