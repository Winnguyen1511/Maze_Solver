from PIL import Image
from mazes import *
#imagePath = "combo400.png"

import argparse

def mazeReader(input_path, cache_map, cache_start_end, start, end):
    im = Image.open(input_path)
    #data = im.getdata(0)
    maze = Maze(im, cache_map, cache_start_end, start, end)
    return maze

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("input_file")
    parser.add_argument("cache_map")
    parser.add_argument("cache_start_end")
    parser.add_argument("start")
    parser.add_argument("end")

    args = parser.parse_args()
    print("Reading Image...")
    myMaze = mazeReader(args.input_file, args.cache_map, args.cache_start_end, args.start, args.end);
    if(myMaze == None):
        print("Error creating maze")
        return -1
    print("Maze generated in memory success!")
    return 0
    
main()