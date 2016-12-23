#!/usr/bin/bash
rm a.out
gcc prog.c $(python3.4-config --libs) $(python3.4-config --includes) $(python3.4-config --ldflags)
./a.out Pillow.tmp/Tests/images/hopper.pcd
