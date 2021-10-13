# pt-sim

Tests and resources for the PT-sim project.


The files `pt-sim.sh` and `pt-sim-clock.sh` are wrapper files you should modify to call your executables.

You should add Makefile logic so that your program can be run with commands like:

    $ make ptsim
    $ make ptsim-clock
    $ sh ptsim tests/aPageTableFile < test/anInputFile
    $ sh ptsim-clock tests/aPageTableFile < test/anInputFile

What works:
Part A and outputs correctly until a certain point

What doesn't work:
Virt2phys_clock works until a certain point.