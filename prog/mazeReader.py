from PIL import Image
from mazes import *
#imagePath = "combo400.png"

import argparse

def mazeReader(input_path, cache_map, start):
    im = Image.open(input_path)
    #data = im.getdata(0)
    maze = Maze(im, cache_map, start)
    return maze

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("input_file")
    parser.add_argument("cache_map")
    parser.add_argument("start")

    args = parser.parse_args()
    print("Reading Image...")
    myMaze = mazeReader(args.input_file, args.cache_map, args.start);
    if(myMaze == None):
        print("Error creating maze")
        return -1
    print("Maze generated in memory success!")
    return 0
    
main()