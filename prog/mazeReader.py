from PIL import Image
from mazes import *
#imagePath = "combo400.png"

import argparse

def mazeReader(input_path, cache_file):
    im = Image.open(input_path)
    #data = im.getdata(0)
    maze = Maze(im, cache_file)
    return maze

def main():

    parser = argparse.ArgumentParser()

    parser.add_argument("input_file")
    parser.add_argument("cache")
    args = parser.parse_args()
    print("Reading Image...")
    myMaze = mazeReader(args.input_file, args.cache);

    print("Maze generated in memory success!")
    
main()