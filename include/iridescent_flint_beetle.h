#include "controllable.h"
#include <bn_optional.h>
#include <bn_sprite_actions.h>

class iridescent_flint_beetle : public controllable {
    private:
        bn::optional<bn::sprite_rotate_loop_action> _rotation;

    public:
        iridescent_flint_beetle(bn::fixed xcor, bn::fixed ycor);

        void update() final;
};
