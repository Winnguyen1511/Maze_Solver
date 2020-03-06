North = 0; East = 1; South = 2; West = 3
#maze_origin_path = 'maze_origin.txt'
TOP_STR = "top"
BOTTOM_STR = "bottom"
LEFT_STR = "left"
RIGHT_STR = "right"
class Node:
    def __init__(self, numNode, position):
        super().__init__()
        self.numNode = numNode
        self.position  = position
        self.neighbours = [None, None, None, None]
        #self.Len = [0,0,0,0]

class Maze:
    def __init__(self, im, cache_map, cache_start_end, start, end):
        super().__init__()
        self.fd = open(cache_map, 'w')
        self.fd.write("*************\n")
        writeBuffer = None
        start_pos, end_pos = 0, 0
        start = str(start)
        end = str(end)
        
        if start == TOP_STR:
            start_pos = North
        elif start == BOTTOM_STR:
            start_pos = South
        elif start == LEFT_STR:
            start_pos = West
        elif start == RIGHT_STR:
            start_pos = East
        else:
            print("Error: start_str")
            return None
        if end == TOP_STR:
            end_pos = North
        elif end == BOTTOM_STR:
            end_pos = South
        elif end == LEFT_STR:
            end_pos = West
        elif end == RIGHT_STR:
            end_pos = East
        else:
            print("Error: end_str")
            return None

        width = im.size[0]
        height = im.size[1]
        nodeCount = 0;
        indexCount = 0;
        data = list(im.getdata(0))

        self.start = None
        self.end = None

        topnodes = [None] * width
        leftnodes = [None] * height
        rightnodes = [None] * height
        bottomnodes = [None] * width
        #Make the first node: Entrance
        if start_pos == North:
        #{      
            for i in range (1, width -1):
                if(data[i] > 0):
                    self.start = Node(0, (0, i))
                    topnodes[i] = self.start
                    nodeCount += 1
                    break
        #}
        elif start_pos == West:
        #{    
            for y in range(1, height - 1):
                if(data[y * width] > 0):
                    self.start = Node(0, (y, 0))
                    leftnodes[y] = self.start
                    nodeCount += 1
                    break
        #}
        elif start_pos == East:
            for y in range(1, height - 1):
                if(data[y * width + width - 1] > 0):
                    self.start = Node(0, (y, width - 1))
                    rightnodes[y] = self.start
                    nodeCount += 1
                    break
        elif start_pos == South:
            pass
        else:
            print("Error: start_pos")
            return None
        #Make nodes in size the maze:
        for y in range(1, height -1):
            
            rowOffset = y * width
            rowAboveOffset = rowOffset - width
            rowBelowOffset = rowOffset + width

            prv = False
            cur = False
            nxt = data[rowOffset + 1] > 0

            leftNode = None

            for x in range(1, width -1):
                prv = cur
                cur = nxt
                nxt = data[rowOffset + x + 1] > 0

                n = None

                if cur == False:
                    continue
                
                else:
                    pass
                if prv == True:
                    if nxt == True:
                        #PATH PATH PATH
                
                        if (data[rowAboveOffset + x] > 0) or (data[rowBelowOffset + x] > 0):
                        #{    
                            n = Node(nodeCount, (y,x))
                            if leftNode != None:
                                len = n.position[1] - leftNode.position[1]
                                writeBuffer = str(n.numNode) + " " + str(n.position[0]) + " " + str(n.position[1])\
                                                 + " " + str(leftNode.numNode) + " " + str(leftNode.position[0]) + " " + str(leftNode.position[1]) \
                                                 + " " + str(len) + "\n"
                                self.fd.write(writeBuffer)
                                writeBuffer = None
                            leftNode.neighbours[East] = n
                            n.neighbours[West] = leftNode
                            leftNode = n

                            #Try to handle right-allied entrance:
                            if x == width - 2:
                                if rightnodes[y] != None:
                                #{
                                    
                                    rightNode = rightnodes[y]
                                    len =  rightNode.position[1] - n.position[1] 
                                    writeBuffer = str(n.numNode) + " " + str(n.position[0]) + " " + str(n.position[1])\
                                        + " " + str(rightNode.numNode) + " " + str(rightNode.position[0]) + " " + str(rightNode.position[1]) \
                                        + " " + str(len) + "\n"
                                    self.fd.write(writeBuffer)
                                    writeBuffer = None
                                    n.neighbours[East] = rightNode
                                    rightNode.neighbours[West] = n
                                    rightNode = None   
                                #}
                        #}
                            #nodeCount += 1
                    else:
                    #PATH PATH WALL
                    #{    
                        n = Node(nodeCount, (y,x))
                        if leftNode != None:
                            len = n.position[1] - leftNode.position[1]
                            #writeBuffer = str(n.numNode) + " " + str(leftNode.numNode) + " " + str(len) + "\n"
                            writeBuffer = str(n.numNode) + " " + str(n.position[0]) + " " + str(n.position[1])\
                                            + " " + str(leftNode.numNode) + " " + str(leftNode.position[0]) + " " + str(leftNode.position[1]) \
                                            + " " + str(len) + "\n"
                            self.fd.write(writeBuffer)
                            writeBuffer = None
                        leftNode.neighbours[East] = n
                        n.neighbours[West] = leftNode
                        leftNode = None
                        #nodeCount += 1
                    #}
                else:
                #{    
                    if nxt == True:
                        #WALL PATH PATH
                        n = Node(nodeCount, (y,x))
                        if (x == 1):
                        #{
                            #Try to handle left-allied entrance:
                            if leftnodes[y] != None:
                                # print("Have the node:", leftnodes[y].numNode,"(",\
                                #     leftnodes[y].position[0], ", ", leftnodes[y].position[1],")")
                                leftNode = leftnodes[y]
                                len = n.position[1] - leftNode.position[1]
                                #writeBuffer = str(n.numNode) + " " + str(leftNode.numNode) + " " + str(len) + "\n"
                                writeBuffer = str(n.numNode) + " " + str(n.position[0]) + " " + str(n.position[1])\
                                            + " " + str(leftNode.numNode) + " " + str(leftNode.position[0]) + " " + str(leftNode.position[1]) \
                                            + " " + str(len) + "\n"
                                self.fd.write(writeBuffer)
                                writeBuffer = None
                                leftNode.neighbours[East] = n
                                n.neighbours[West] = leftNode
                        #}

                        #Try to handle right-allied entrance:
                        if x == width - 2:
                            if rightnodes[y] != None:
                            #{
                                
                                rightNode = rightnodes[y]
                                len = rightNode.position[1] - n.position[1]
                                writeBuffer = str(n.numNode) + " " + str(n.position[0]) + " " + str(n.position[1])\
                                    + " " + str(rightNode.numNode) + " " + str(rightNode.position[0]) + " " + str(rightNode.position[1]) \
                                    + " " + str(len) + "\n"
                                self.fd.write(writeBuffer)
                                writeBuffer = None
                                n.neighbours[East] = rightNode
                                rightNode.neighbours[West] = n
                                rightNode = None   
                            #}                                           
                        leftNode = n
                        #nodeCount += 1
                    else:
                        #WALL PATH WALL
                        if (data[rowAboveOffset + x] == 0) or (data[rowBelowOffset + x] == 0):
                            n = Node(nodeCount,(y,x))   
                            #nodeCount += 1

                        #Try to handle left-allied entrance:    
                        if (x == 1):
                        #{
                            if leftnodes[y] != None:
                            #{    
                                n = Node(nodeCount,(y,x)) 
                                # print("Have the node:", leftnodes[y].numNode,"(",\
                                #     leftnodes[y].position[0], ", ", leftnodes[y].position[1],")")
                                leftNode = leftnodes[y]
                                len = n.position[1] - leftNode.position[1]
                                #writeBuffer = str(n.numNode) + " " + str(leftNode.numNode) + " " + str(len) + "\n"
                                writeBuffer = str(n.numNode) + " " + str(n.position[0]) + " " + str(n.position[1])\
                                            + " " + str(leftNode.numNode) + " " + str(leftNode.position[0]) + " " + str(leftNode.position[1]) \
                                            + " " + str(len) + "\n"
                                self.fd.write(writeBuffer)
                                writeBuffer = None
                                leftNode.neighbours[East] = n
                                n.neighbours[West] = leftNode
                                leftNode = None
                            #}
                        #}                         
                #}
                if n != None:
                #{    
                    if(data[rowAboveOffset + x] > 0):
                        t = topnodes[x]
                        if t != None:
                            len = n.position[0] - t.position[0]
                            #writeBuffer = str(n.numNode) + " " + str(t.numNode) + " " + str(len) + "\n"
                            writeBuffer = str(n.numNode) + " " + str(n.position[0]) + " " + str(n.position[1])\
                                            + " " + str(t.numNode) + " " + str(t.position[0]) + " " + str(t.position[1]) \
                                            + " " + str(len) + "\n"
                            self.fd.write(writeBuffer)
                            writeBuffer = None
                        t.neighbours[South] = n
                        n.neighbours[North] = t

                    if(data[rowBelowOffset + x] > 0):
                        topnodes[x] = n
                    else:
                        topnodes[x] = None

                    nodeCount += 1
                #}
        #Make the last node: End node
        if end_pos == South:
        #{    
            rowOffset = (height - 1) * width
            for x in range(1, width - 1):
                if data[rowOffset + x] > 0:
                    self.end = Node(nodeCount, (height - 1, x))
                    t = topnodes[x]
                    if t != None:
                        len = self.end.position[0] - t.position[0]
                        #writeBuffer = str(self.end.numNode) + " " + str(t.numNode) + " " + str(len) + "\n"
                        writeBuffer = str(self.end.numNode) + " " + str(self.end.position[0]) + " " + str(self.end.position[1])\
                                        + " " + str(t.numNode) + " " + str(t.position[0]) + " " + str(t.position[1]) \
                                        + " " + str(len) + "\n"
                        self.fd.write(writeBuffer)
                        writeBuffer = None
                    t.neighbours[South] = self.end
                    self.end.neighbours[North] = t
                    nodeCount += 1
                    break
        #}
        self.nodeCount = nodeCount
        self.fd.seek(0, 0)
        self.fd.write(str(self.nodeCount))
        self.width = width
        self.height = height
        self.fd.close()



        
