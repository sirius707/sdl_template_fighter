maybe add call backs to input.c later
proper from rate capping function with ability to change frame rate

movement buttons are continous
action buttons act only once on hit, can be accomplished by just turning the boolean of the desired key (prog.keyboard[x]) to false after taking its value


it seems each module (render, input, game.. etc) should have POINTERS to data it's suppsoed to work on, instead of extern refs
in some cases(like render) the pointers should point to constant data 

diagonal jump

delta time needs a lot of work

add delta time to jump and gravity

combo input system

fix delta time erratic behavior when jumping

goto state function

done:
animation, attacks,
animation frame rate,
multiple renderers for layers
fix chain attacks physics, also controls are very stiff
reduce speed when walking backwards,
delay on hit
transition table
crouch

todo:
combo system,  
sounds, back ground music
load from files, 
attack after effect, boom
make different hits produce different animations
low parry
data files
stage
buffered input
character creation tool

bugs: player keeps moving along x if you land while attacking: fixed
	we seem to need to set can_attack in fall and jump whicn isn't called for since it should be set and unset only by attack: this doesn't seem to be a bug, or an issue at all
	erratic frame rate
	
	don't caceh state when attacking, because in this case after an attack from a combo chain is finished the player might go back to previous attack (doesn't make sense)