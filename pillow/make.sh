#!/bin/bash

pushd Pillow/
make clean
AFL_INST_RATIO=100 AFL_HARDEN=1 CC=~/afl-2.35b/afl-clang-fast python3 setup.py bdist -d ../
popd

tar xvzf Pillow-3.5.0.dev0.linux-x86_64.tar.gz
rm -rf PIL || true
cp -r usr/local/lib/python3.5/dist-packages/PIL .

rm Pillow-3.5.0.dev0.linux-x86_64.tar.gz
rm -rf usr/
