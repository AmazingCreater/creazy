#!/bin/sh

build_path="build"
argc=$#
argv1=$1

if [ "$argc" -gt "0" -a "$argv1"x = "clean"x ]; then
  if [ -d "$build_path" ]; then
    echo "clean..."
    rm -rf "$build_path"
  fi
  exit
fi

if [ ! -d "$build_path" ]; then
  mkdir "$build_path"
fi

cp test.jpg build/
cd "$build_path"
cmake ..
make -j4

