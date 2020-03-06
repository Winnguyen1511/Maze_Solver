from PIL import Image
from mazes import *
#imagePath = "combo400.png"

import argparse

def mazeReader(input_path, cache_map):
    im = Image.open(input_path)
    data = list(im.getdata(0))
    width = im.size[0]
    height = im.size[1]
    # print(data)
    start = "top"
    for x in range(1, width-1):
        if data[x] > 0:
            start = "top"
            break
    for y in range(1, height -1):
        if data[y * width] > 0:
            start = "left"
            break
        if data[y*width + width - 1] > 0:
            #print("here")
            start = "right"
            break 

    maze = Maze(im, cache_map, start)
    return maze

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("input_file")
    parser.add_argument("cache_map")

    args = parser.parse_args()
    print("Reading Image...")
    myMaze = mazeReader(args.input_file, args.cache_map);
    if(myMaze == None):
        print("Error creating maze")
        return -1
    print("Maze generated in memory success!")
    return 0
    
main()