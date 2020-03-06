from PIL import Image
import argparse
import random
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file")
    parser.add_argument("output_file")
    parser.add_argument("y")
    parser.add_argument("x")
    parser.add_argument("color")

    args = parser.parse_args()
    im = Image.open(args.input_file)
    data = list(im.getdata(0))
    # print(data)
    width = im.size[0]
    height = im.size[1]

    im = im.convert('RGB')
    impixcels = im.load()

    #Try to clean the old entrance of the maze
    #If there are any entrance on Left, top, right, clear all
    for x in range(1, width-1):
        if data[x] > 0:
            impixcels[x, 0] = (0, 0, 0)
    for y in range(1, height -1):
        if data[y * width] > 0:
            impixcels[0, y] = (0, 0, 0)
        if data[y*width + width - 1] > 0:
            impixcels[width - 1, y] = (0, 0, 0) 
    color = args.color
    px = (255, 255, 255)
    if color == "black":
        px = (0,0,0)
    elif color == "white":
        px = (255, 255, 255)
    else:
        pass
    
    if args.y != "rand":
        y = int(args.y)
        x = int(args.x)
    else:
        if args.x == "top":
            y = 0
            x = random.randint(1, width - 2)
        elif args.x == "left":
            y = random.randint(1, height - 2)
            x = 0
        elif args.x == "right":
            y = random.randint(1, height - 2)
            x = width - 1
    impixcels[x, y] = px
    im.save(args.output_file)

main()

