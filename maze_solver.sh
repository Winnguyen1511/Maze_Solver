#!/bin/bash
#*****************************************
# Nguyen Huynh Dang Khoa -Victor Nguyen
# February 2020
# Maze-solver
# Reference: Computerphile
# Description: _Python read and save image
#              _C run Dijkstra algorithm
#*****************************************   

RESOURCE_DIR=$PWD/
CACHE_DIR=$PWD/"cache"

READER_PATH="prog/mazeReader.py"
SAVER_PATH="prog/mazeSaver.py"
DIJKSTRA_PATH="prog/dijkstra"

CACHE_ORGIN_PATH=$PWD/"cache/maze_origin.txt"
CACHE_SOLUTION_PATH=$PWD/"cache/maze_solution.txt"

SOLUTION_IMAGE_DIR=$PWD/"solution/"
helpFunction()
{
    echo "Usage: ./maze_solver.sh [input_file] [start] "
}
START="top"

if [ "$1" == "--help" ]; then
    helpFunction
    exit
fi
if [ "$2" != "" ]; then
    START=$2
fi 


if [ "$1" == "" ]; then
    echo "Arguments required"
    helpFunction
elif [ "$1" == "--clear" ]; then
    rm -rf $CACHE_DIR
    rm -f $DIJKSTRA_PATH
elif [ "$1" == "--clearall" ]; then
    rm -rf $CACHE_DIR
    rm -f $DIJKSTRA_PATH
    rm -f $SOLUTION_IMAGE_DIR/*
else
    if [ ! -d $CACHE_DIR ]; then
        mkdir $CACHE_DIR
    fi
    python3 $READER_PATH $RESOURCE_DIR/$1 $CACHE_ORGIN_PATH $START 
    sleep 1
    if [ ! -f $DIJKSTRA_PATH ];then
        gcc $DIJKSTRA_PATH.c -o $DIJKSTRA_PATH
    fi
    ./$DIJKSTRA_PATH $CACHE_ORGIN_PATH $CACHE_SOLUTION_PATH
    sleep 1
    python3 $SAVER_PATH $RESOURCE_DIR/$1 $CACHE_SOLUTION_PATH $SOLUTION_IMAGE_DIR
    exit
fi
