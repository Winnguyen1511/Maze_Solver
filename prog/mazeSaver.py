from PIL import Image
import argparse
import os
# originImagePath = "combo400.png"
# solvedImagePath = "solve_"+originImagePath
# solutionPath = "maze_solution.txt"
def mazeSaver(originPath, solutionPath, output_file):
    print("Saving Image...")
    im = Image.open(originPath)
    im = im.convert('RGB')
    impixcels = im.load()

    solutionFd = open(solutionPath)
    line = solutionFd.readline()
    solutionStack = []
    while line:
        #print(line)
        line = line.strip('\n')
        
        tmp = line.split(' ')
        tmp = [int(tmp[0]), int(tmp[1])]
        solutionStack.append(tmp)
        line = solutionFd.readline()
    solutionFd.close()
    #print(solutionStack)
    length = len(solutionStack)
    for i in range(0, length - 1): 
        a = solutionStack[i]
        b = solutionStack[i+1]
        #print(a)
        #print(b)
        #Blue-Red
        r = int((i / length) * 255)
        px = (255 - r, 0,  r)
        if a[0] == b[0]:
            for x in range(min(a[1], b[1]), max(a[1], b[1])+1):
                impixcels[x, a[0]] = px
        elif a[1] == b[1]:
            for y in range(min(a[0], b[0]), max(a[0], b[0])+1):
                impixcels[a[1], y] = px
        
    im.save(output_file)


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("input_file")
    parser.add_argument("cache")
    parser.add_argument("solution_image_dir")
    args = parser.parse_args()
    input_file_path = args.input_file
    cache_path = args.cache
    solution_image_path = args.solution_image_dir
    solution_image_path += "solve_"+ os.path.basename(input_file_path)
    mazeSaver(input_file_path, cache_path, solution_image_path)
    #mazeSaver(originImagePath, solvedImagePath, args.solution_file)
    print(">>Image Save success!")

main()
