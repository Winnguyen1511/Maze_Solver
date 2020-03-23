#!/bin/bash
#*****************************************
# Nguyen Huynh Dang Khoa -Victor Nguyen
# February 2020
# Maze-solver
# Reference: Computerphile
# Description: _Python read and save image
#              _C run Dijkstra algorithm
#*****************************************   

THIS_DIR=$PWD/
CACHE_DIR=$PWD/"cache"

PREPROCESS_PATH="prog/pre_process.py"
READER_PATH="prog/mazeReader.py"
SAVER_PATH="prog/mazeSaver.py"
DIJKSTRA_PATH="prog/dijkstra"

CACHE_ORGIN_PATH=$PWD/"cache/maze_origin.txt"
CACHE_SOLUTION_PATH=$PWD/"cache/maze_solution.txt"

SOLUTION_IMAGE_DIR=$PWD/"solution/"
RESOURCE_DIR=$PWD/"resources/"
helpFunction()
{
    echo "Usage: ./maze_solver.sh [input_file] "
    echo "Usage: ./maze_solver.sh -p [reduce_percent] [input_file] "
}

if [ "$1" == "--help" ]; then
    helpFunction
    exit
fi
READER_INPUT=$1
while [ -n "$1" ]; do
    case "$1" in
    -p) echo "Preprocess acquired."
        if [ "$3" == "" ];then
            echo "Arguments required"
            helpFunction
            exit
        fi
        python3 $PREPROCESS_PATH $THIS_DIR/$3 $RESOURCE_DIR $2
        BASE=$(basename "$3")
        NAME="resources/processed_"$BASE
        READER_INPUT=$NAME
        ;;
    *) 
        break;;
    esac
    shift
done

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
    python3 $READER_PATH $THIS_DIR/$READER_INPUT $CACHE_ORGIN_PATH 
    sleep 1
    if [ ! -f $DIJKSTRA_PATH ];then
        gcc $DIJKSTRA_PATH.c -o $DIJKSTRA_PATH
    fi
    ./$DIJKSTRA_PATH $CACHE_ORGIN_PATH $CACHE_SOLUTION_PATH
    sleep 1
    python3 $SAVER_PATH $THIS_DIR/$READER_INPUT $CACHE_SOLUTION_PATH $SOLUTION_IMAGE_DIR
    exit
fi
