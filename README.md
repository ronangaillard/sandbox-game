# sandbox-game
FPGA based project ported on desktop computers using the SDL
(By Guilhem Codron and Ronan Gaillard)

## Principle

![Screenshot](/images/screenshot.jpeg "Screenshot")


This game is a sandbox game in 2D. Place blocks on the world using your mouse and see your own world come alive !
You have 6 different block (sand, water, plant, wood, fire and rock) that have different way of living and evolving. For instance sand and water are attracted by gravity, plant and wood grow and can take fire,...).

## Code status
This code is based on a FPGA project we had at school, we designed the hardware part to draw pixel using a VGA interface and connected a NIOS processor that was interfaced with that _graphic card_.
This code was ported to desktop computers using the SDL. Please note that this game was coded having low resources (300kbits of video RAM and 500 kbytes of RAM for the main system as well as a 50MHz clock) so the code is note optimized at all for modern PCs.
As this game was coded in relatively little time (one afternoon) code may sound very dirty ( that is because it actually is !).
We may improve it once we find some time !

## How to compile
This game was ported using the SDL 1.2, so get it (or recompile it) get your SDL.a and SDLmain.a (or SDL.lib and SDLmain.lib if using VS <3) and just compile it as you would with your favourite C programs !
