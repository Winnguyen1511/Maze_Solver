import cv2
import argparse
import os

def preprocess(input_path, output_path, percent):
    image = cv2.imread(input_path)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    w = image.shape[1]; h = image.shape[0]
    print(">>Preprocessing: Read image with size=",w,"x",h)
    if(percent < 100 and percent > 0):
        w = int(w * percent / 100)
        h = int(h * percent / 100)
        dim = (w,h)
        image = cv2.resize(image,dim, interpolation=cv2.INTER_AREA)
        print(">>Preprocressing: Reduced image size=",w,"x",h)
    _, bi = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)
    cv2.imwrite(output_path, bi)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file")
    parser.add_argument("output_dir")
    parser.add_argument("reduce_percent")
    args = parser.parse_args()
    print("Preprocessing...")
    input_file_path = args.input_file
    output_file_path = args.output_dir
    reduce_percent = int(args.reduce_percent)
    # print(reduce_percent)
    output_file_path += "processed_"+ os.path.basename(input_file_path)
    preprocess(input_file_path, output_file_path, reduce_percent)
    print(">>Preprocess completed!!!")

main()
