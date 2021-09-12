#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "structs.h"
#include "animation.h"
#include <string.h>

int main()
{
    s_animation_init();
    int width;
    int height;
    int scale;
    int xdisplace;
    int ydisplace;

    char save_dir[100] = "f:\\";
    char choice = '0';

    puts("enter width height scale xdisplacement ydisplacement:");
    scanf("%d %d %d %d %d", &width, &height, &scale, &xdisplace, &ydisplace);
    fgetc(stdin);


    puts("enter animation name:");
    scanf("%s", animations[0].name);
    fgetc(stdin);

    strcat(save_dir, animations[0].name);

    animations[0].sprite_w = width;
    animations[0].sprite_h = height;
    animations[0].sprite_scale = scale;
    animations[0].sprite_x_displacement = xdisplace;
    animations[0].sprite_y_displacement = ydisplace;

    FILE *out_file = fopen(animations[0].name, "wb");
    assert(out_file != NULL);

    puts(save_dir);
    system("cls");
    while(choice != 'q' && choice != 'Q'){
            puts("_______________");
            puts("enter a choice: \nf)frame \nd)default sequence \nt)transition \na)attack  \nw)save \nq)quit");

            scanf("%c", &choice);
            fgetc(stdin);

            int a, b, c;
            float d;
            switch(choice){
                case 'a':
                case 'A':
                    puts("enter attack index:");
                    scanf("%d", &a);
                    fgetc(stdin);

                    puts("enter attack damage:");
                    scanf("%d", &b);
                    fgetc(stdin);
                    animations[0].attacks[a].damage = b;

                    puts("enter attack x:");
                    scanf("%d", &b);
                    fgetc(stdin);
                    animations[0].attacks[a].x = b;

                    puts("enter attack y:");
                    scanf("%d", &b);
                    fgetc(stdin);
                    animations[0].attacks[a].y = b;

                    puts("enter attack w:");
                    scanf("%d", &b);
                    fgetc(stdin);
                    animations[0].attacks[a].width = b;

                    puts("enter attack h:");
                    scanf("%d", &b);
                    fgetc(stdin);
                    animations[0].attacks[a].height = b;

                    puts("enter target dx(float):");
                    scanf("%f", &d);
                    fgetc(stdin);
                    animations[0].attacks[a].target_dx = d;

                    puts("enter target dy(float):");
                    scanf("%f", &d);
                    fgetc(stdin);
                    animations[0].attacks[a].target_dy = d;

                break;

                case 'd':
                case 'D':
                    puts("enter state ID:");
                    scanf("%d", &a);
                    fgetc(stdin);

                    puts("enter sequence index:");
                    scanf("%d", &b);
                    fgetc(stdin);

                    animations[0].default_seqs[a] = b;
                break;

                case 'w':
                    fwrite(&animations[0], sizeof(animations[0]), 1, out_file);
                    fclose(out_file);
                    return;
                    break;
                case 't':
                case 'T':
                    puts("enter state ID:");
                    scanf("%d", &a);
                    fgetc(stdin);

                    puts("enter interrupt state:");
                    scanf("%d", &b);
                    fgetc(stdin);

                    puts("enter sequence index:");
                    scanf("%d", &c);
                    fgetc(stdin);

                    animations[0].transition_table[a][b] = c;
                break;

                case 'f':
                    puts("enter seq index:");
                    scanf("%d", &a);
                    fgetc(stdin);

                    puts("enter frame index:");
                    scanf("%d", &b);
                    fgetc(stdin);

                    animations[0].frames[a][b].active = 1;

                    puts("enter frame x:");
                    scanf("%d", &c);
                    fgetc(stdin);
                    animations[0].frames[a][b].x = c*width;

                    puts("enter frame y:");
                    scanf("%d", &c);
                    fgetc(stdin);
                    animations[0].frames[a][b].y = c*height;

                    puts("enter frame data:");
                    scanf("%d", &c);
                    fgetc(stdin);
                    animations[0].frames[a][b].data = c;
                break;

            }

    }
    return 0;
}
