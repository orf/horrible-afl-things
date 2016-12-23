#!/bin/bash
rm a.out
AFL_INST_RATIO=100 AFL_HARDEN=1 ~/afl-2.35b/afl-clang-fast prog.c $(python3.5-config --libs) $(python3.5-config --includes) $(python3.5-config --ldflags)
./a.out < Pillow/Tests/images/hopper.pcd
