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
