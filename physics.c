#include "physics.h"

//external access will be to entities
extern CHARACTER entities[];

void s_physics(void)
{
    //entities
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){

        if(entities[i].processing_delay > 0)continue;//skip applying physics if player has on hit delay

        entities[i].grounded = false;
        //gravity
        //entities[i].vel_y += G * prog.delta_time;
        entities[i].dy += DEFAULT_FALLSPD * prog.delta_time;

        //i don't think we will need velocity in a fighting game
        //but what about jumping?
        entities[i].dy += prog.delta_time * entities[i].vel_y;
        entities[i].dx += prog.delta_time * entities[i].vel_x;

        //collision detection
        entities[i].y += entities[i].dy;
        if(entities[i].y + entities[i].height > GROUND_HEIGHT){
            entities[i].y = GROUND_HEIGHT - entities[i].height;
            entities[i].vel_y = 0;
            entities[i].dy = 0;
            entities[i].grounded = true;
        }

        //collision with other players and flipping
        if(entities[i].dx != 0){
            for(int j = 0; j < NUMBER_OF_PLAYERS; j++){
                if(j == i)continue;

                if(fabs(entities[i].y - entities[j].y) < entities[i].height/2){//if y collision
                    if(fabs(entities[i].x - entities[j].x) < entities[i].width*0.899){//if collision with other players
                       entities[i].dx *= 0.8;//damp walk speed
                       //displace other player
                       if(entities[i].x < entities[j].x){//if the other player is on the rgiht
                            entities[j].x = entities[i].x + entities[i].width + 0.2f;
                       }else{
                            entities[j].x = entities[i].x - entities[j].width - 0.2f;
                       }
                    }
                }
            }

            entities[i].x += entities[i].dx;
        }


    }
}

