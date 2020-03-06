from PIL import Image
import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file")
    parser.add_argument("output_file")
    parser.add_argument("y")
    parser.add_argument("x")
    parser.add_argument("color")

    args = parser.parse_args()
    im = Image.open(args.input_file)
    im = im.convert('RGB')
    impixcels = im.load()
    color = args.color
    px = (255, 255, 255)
    if color == "black":
        px = (0,0,0)
    elif color == "white":
        px = (255, 255, 255)
    else:
        pass
    
    y = int(args.y)
    x = int(args.x)
    impixcels[x, y] = px
    im.save(args.output_file)

main()

