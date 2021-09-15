#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "structs.h"
#include "animation.h"
#include <string.h>
#define MAX 20

typedef char MSTRING[50];
int search_string(const char *str, MSTRING array[], size_t size);
void print_string_arr(MSTRING strings[], size_t n);
void remove_nl(char *str);

MSTRING states[MAX];
MSTRING seqs[MAX];
MSTRING attacks[MAX];

int main()
{
    s_animation_init();
    int width;
    int height;
    int scale;
    int xdisplace;
    int ydisplace;


    puts("enter width height scale xdisplacement ydisplacement:");
    scanf("%d %d %d %d %d", &width, &height, &scale, &xdisplace, &ydisplace);
    fgetc(stdin);


    puts("enter animation name:");
    scanf("%s", animations[0].name);
    fgetc(stdin);

    animations[0].sprite_w = width;
    animations[0].sprite_h = height;
    animations[0].sprite_scale = scale;
    animations[0].sprite_x_displacement = xdisplace;
    animations[0].sprite_y_displacement = ydisplace;

    FILE *out_file = fopen(animations[0].name, "wb");
    assert(out_file != NULL);

    system("cls");
    memset(states, '\0', MAX*sizeof(MSTRING));
	memset(attacks, '\0', MAX*sizeof(MSTRING));
	memset(seqs, '\0', MAX*sizeof(MSTRING));

	FILE *fp = fopen("states.txt", "r");
	assert(fp != NULL);
	{
	for(int i = 0; i < MAX; i++){
		if(!fgets(states[i], 50, fp))break;
		size_t ln = strlen(states[i])-1;
		if (states[i][ln] == '\n')
			states[i][ln] = '\0';
	}
	}
	{
	fp = fopen("seqs.txt", "r");
	assert(fp != NULL);
	for(int i = 0; i < MAX; i++){
		if(!fgets(seqs[i], 50, fp))break;
		size_t ln = strlen(seqs[i])-1;
		if (seqs[i][ln] == '\n')
			seqs[i][ln] = '\0';
	}
	}
	{
	fp = fopen("attacks.txt", "r");
	assert(fp != NULL);
	for(int i = 0; i < MAX; i++){
		if(!fgets(attacks[i], 50, fp))break;
		size_t ln = strlen(attacks[i])-1;
		if (attacks[i][ln] == '\n')
			attacks[i][ln] = '\0';
	}
	}
	print_string_arr(states, MAX);
	puts("_______________");
	print_string_arr(attacks, MAX);
	puts("_______________");
	print_string_arr(seqs, MAX);

	char str[MAX];
	fp = fopen("code.txt", "r");
	while(fgets(str, MAX, fp)){
		remove_nl(str);

		if(!strcmp(str, "TRANS")){
			char sequencestr[MAX], interrupt_statestr[MAX], resultseqstr[MAX];
			int sequence, interrupt_state, resultseq;
			fscanf(fp, "%s %s %s", sequencestr, interrupt_statestr, resultseqstr);

			sequence = search_string(sequencestr, seqs, MAX);
			interrupt_state = search_string(interrupt_statestr, states, MAX);
			resultseq = search_string(resultseqstr, seqs, MAX);

			printf("transition [%s:%d %s:%d %s:%d]\n", sequencestr, sequence, interrupt_statestr, interrupt_state, resultseqstr, resultseq);
            animations[0].transition_table[sequence][interrupt_state] = resultseq;
			//fprintf(out_file, "%c\n%d\n%d\n%d\n", 't', sequence, interrupt_state, resultseq);

		}else if(!strcmp(str, "DEF")){
			char statestr[MAX], seqstr[MAX];
			int state, seq;
			fscanf(fp, "%s %s", statestr, seqstr);

			state = search_string(statestr, states, MAX);
			seq = search_string(seqstr, seqs, MAX);

			printf("default transition[ %s:%d %s:%d]\n", statestr, state, seqstr, seq);
            animations[0].default_seqs[state] = seq;
			//fprintf(out_file, "%c\n%d\n%d\n", 'd', state, seq);

		}else if(!strcmp(str, "ATK")){
			char atkstr[MAX];
			int atk;
			int dmg, x, y, w, h;
			float dx, dy;

			fscanf(fp, "%s %d %d %d %d %d %f %f", atkstr, &dmg, &x, &y, &w, &h, &dx, &dy);
			atk = search_string(atkstr, attacks, MAX);
			printf("attack[%s:%d]\n", atkstr, atk);

            animations[0].attacks[atk].damage = dmg;
            animations[0].attacks[atk].target_dx = dx;
            animations[0].attacks[atk].target_dy = dy;
            animations[0].attacks[atk].x = x;
            animations[0].attacks[atk].y = y;
            animations[0].attacks[atk].width = w;
            animations[0].attacks[atk].height = h;

			//fprintf(out_file, "%c\n%d\n%d\n%d\n%d\n%d\n%d\n%f\n%f\n", 'a', atk, dmg, x, y, w, h, dx, dy);

		}else if(!strcmp(str, "SEQ")){
			char seqstr[MAX];
			char data[MAX];
			int seq;
			int atk;
			int frame, x, y;

			fscanf(fp, "%s %d %d %d %s", seqstr, &frame, &x, &y, data);

			seq = search_string(seqstr, seqs, MAX);
			atk = search_string(data, attacks, MAX);
			if(atk != -1) atk++;//add one to atk because program subtratcts one, i am autistic
			else atk = 0;

			printf("seq[%s:%d frame:%d data:%d]\n", seqstr, seq, frame, atk);

            animations[0].frames[seq][frame].x = x;animations[0].frames[seq][frame].y = y;animations[0].frames[seq][frame].active = 1;animations[0].frames[seq][frame].data = atk;

			//fprintf(out_file, "%c\n%d\n%d\n%d\n%d\n%d\n", 'f', seq, frame, x, y, atk);

		}else if(!strcmp(str, "END")){
            fwrite(&animations[0], sizeof(animations[0]), 1, out_file);
			return 0;
		}
	}

}


void print_string_arr(MSTRING strings[], size_t n)
{
	for(int i = 0; i < n; i++){
		if(!strcmp(strings[i], "\0"))break;
		puts(strings[i]);
	}
}

void remove_nl(char *str)
{
	while(*str != '\n')str++;
	*str = '\0';
}

int search_string(const char *str, MSTRING array[], size_t size)
{

	for(int i = 0; i < size; i++){
		if(!strcmp(str, array[i])){
			return i;
		}
	}
	return -1;
}
