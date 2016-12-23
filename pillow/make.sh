#!/usr/bin/bash

pushd Pillow/
make clean
AFL_HARDEN=0 CC=~/afl-2.35b/afl-clang-fast python3 setup.py bdist -d ../
popd

tar xvzf Pillow-3.5.0.dev0.linux-x86_64.tar.gz
rm -rf PIL
cp -r usr/lib64/python3.4/site-packages/PIL .

rm Pillow-3.5.0.dev0.linux-x86_64.tar.gz
rm -rf usr/
