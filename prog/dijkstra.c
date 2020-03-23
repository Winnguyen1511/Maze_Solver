#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//#define LONG
//#define MONODIR
#define INPUT_MAP   


#define MAX_BUFFER_SIZE     1024
#define HEADER_LEN          14
#define PERMS                   S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
#define MAZE_ORIGIN_FLAGS       O_RDONLY
#define MAZE_SOLUTION_FLAGS     O_WRONLY | O_CREAT | O_TRUNC
  
#define MAZE_ORIGIN_PATH    "maze_origin.txt"
#define MAZE_SOLUTION_PATH  "maze_solution.txt"
#define SUCCESS     1
#define ERROR       0
typedef struct node_struct {
    int this_node;
    int y, x;
    int path_len;
    int prev_node;
}node_t;
node_t min_node;
int**map;
//int*min_arr;
int count=0;
int num_node=0, start_node = 0, tmp_node_num;
int* N_prime_set;

int creatMazeOrigin(int *fdIn, int*num, char*pathIn);
int readMazeOrigin(int *fdIn, int**maze, node_t* dijkstra_list);
int writeSolution(int *fdOut, int *num, node_t* dijkstra_list, char* pathOut);
void swap(char *a, char* b);
int itoa(int num, char* str);
void reverse(char *str, int length);
int main(int argc, char**argv)
{
    int i;
    int fdIn, fdOut;

    printf("Dijkstra solving...\n");
    #ifdef INPUT_MAP
    if(argc < 3)
    {
        printf(">>Dijkstra: Usage: ./dijkstra [cache_origin] [cache_solution]\n");
        return ERROR;
    }
    if(!creatMazeOrigin(&fdIn, &num_node, argv[1]))
    {
        printf(">>Dijkstra: Cannot create maze from %s\n", argv[1]);
        return ERROR;
    }
    #else
    //num_node = 6;
    num_node = 9;

    #endif
    //printf("numnode=%d\n", num_node);
    map = (int**)malloc((num_node)* sizeof(int*));
    N_prime_set = (int*)malloc(num_node * sizeof(int));
    N_prime_set[0] = -1;
    node_t* list = (node_t*)malloc(num_node * sizeof(node_t));
    for(i = 1; i < num_node; i++)
    {
        N_prime_set[i] = 0;
    }
    #ifdef MONODIR
    //do another time :v
    #else
    for(i=1; i < num_node; i++)
    {
        map[i] = (int*)malloc(i * sizeof(int));
        if(map[i] == NULL)
            printf("end\n");
    }
    #endif

    #ifdef INPUT_MAP
    if(!readMazeOrigin(&fdIn, map, list))
    {
        printf(">>Dijkstra: Cannot read maze origin\n");
        return ERROR;
    }
    #else
    // map[1][0] = 1; map[5][0] = 2;
    // map[2][1] = 4; map[4][1] = 3; map[5][1] = 2;
    // map[3][2] = 2; map[4][2] = 1; map[4][3] = 5;
    // map[5][4] = 1;
    map[1][0] = 4; map[1][7] = 11; map[7][0] = 8;
    map[2][1] = 8; map[8][2] = 2; map[8][7] = 7; map[7][6] = 1;
    map[3][2] = 7; map[5][2] = 4; map[6][5] = 2; map[5][3]=14;
    map[4][3]=4; map[5][4] = 10;

    // if(map[5][4] == NULL)
    //     printf("null\n");
    start_node = 0;
    #endif

    
    //Init list
    // min_arr_num_node = num_node;
    // min_arr = (int*)malloc(min_arr_num_node * sizeof(int));
    min_node.path_len = 0;
    min_node.prev_node = 0;
    for(i = 1; i < num_node; i++)
    {
        if(map[i][0] != 0)
        {
            list[i].this_node = i;
            list[i].path_len = map[i][0];
            list[i].prev_node = 0;
            //printf("0->%d:len=%d, prev=%d\n", i, list[i].path_len, list[i].prev_node);
            //min_arr_cnt++;
            if(min_node.path_len == 0 || min_node.path_len > list[i].path_len)
            {
                min_node.this_node = i;
                min_node.path_len = list[i].path_len;
                min_node.prev_node = list[i].prev_node;
            }
        }      
    }
    //printf("Finished 1st round\n");
    //printf("min_node #%d: len=%d, prev=%d\n",min_node.this_node, min_node.path_len, min_node.prev_node);
    N_prime_set[min_node.this_node] = -1;
    tmp_node_num = min_node.this_node;

    count = num_node - 2;
    while(count--)
    {
        min_node.this_node = 0;
        min_node.path_len = 0;
        min_node.prev_node = 0;
        for(i = 1; i < num_node ; i++)
        {
            int map_index=i;
            int swap_tmp = tmp_node_num;
            if(map_index < tmp_node_num)
            {
                map_index = tmp_node_num;
                tmp_node_num = i;
            }
            if(N_prime_set[i] == -1)
            {
                tmp_node_num =swap_tmp;
                continue;
            }
            if(list[i].path_len == 0)
            {
                if(map[map_index][tmp_node_num] != 0)
                {
                    list[i].this_node = i;
                    list[i].path_len = map[map_index][tmp_node_num] + list[swap_tmp].path_len;
                    list[i].prev_node = swap_tmp;
                    if(min_node.path_len == 0 || min_node.path_len > list[i].path_len)
                    {
                        min_node.this_node = i;
                        min_node.path_len = list[i].path_len;
                        min_node.prev_node = list[i].prev_node;                        
                    }
                }
            }
            else{
                int tmp_path_len = list[i].path_len;
                int tmp_prev_node = list[i].prev_node;
                int tmp_this_node = i;
                if(map[map_index][tmp_node_num] != 0)
                {
                    int tmp_val = map[map_index][tmp_node_num] + list[swap_tmp].path_len;

                    if(list[i].path_len < tmp_val)
                    {
                        tmp_path_len = list[i].path_len;
                        tmp_prev_node = list[i].prev_node;
                        tmp_this_node = i;
                    }
                    else{
                        tmp_path_len = tmp_val;
                        tmp_prev_node = swap_tmp;
                        tmp_this_node = i;
                    }
                    list[i].this_node = tmp_this_node;
                    list[i].path_len = tmp_path_len;
                    list[i].prev_node = tmp_prev_node;
                }
                if(min_node.path_len == 0 || min_node.path_len > tmp_path_len)
                {
                    min_node.this_node = tmp_this_node;
                    min_node.path_len = tmp_path_len;
                    min_node.prev_node = tmp_prev_node;                        
                }
            }
            tmp_node_num = swap_tmp;
        }
        N_prime_set[min_node.this_node] = -1;
        tmp_node_num = min_node.this_node;
    }
    // for(i = 0; i < num_node; i++)
    // {
    //     printf("#%d , (%d, %d): len=%d, prev=%d\n", list[i].this_node,list[i].y, list[i].x, list[i].path_len, list[i].prev_node);
    // }
    free(map);
    #ifdef INPUT_MAP
    if(!writeSolution(&fdOut,&num_node, list, argv[2]))
    {
        printf(">>Dijkstra: Cannot write solution to %s\n", argv[2]);
        return ERROR;
    }
    #else
    if(!writeSolution(&fdOut,&num_node, list, MAZE_SOLUTION_PATH))
    {
        printf("Cannot write solution to %s\n", MAZE_SOLUTION_PATH);
        return ERROR;
    }
    #endif
    printf(">>Dijkstra: Dijkstra solve success!\n");
    //close(fdIn); close(fdOut);
    return SUCCESS;
}

int creatMazeOrigin(int *fdIn, int*num, char*pathIn)
{
    *fdIn = open(pathIn, MAZE_ORIGIN_FLAGS, PERMS);
    if(*fdIn < 0)
    {
        printf("Error: Cannot open %s\n", pathIn);
        return ERROR;
    }
    char readBuffer[HEADER_LEN];
    if(read(*fdIn, readBuffer, HEADER_LEN) != HEADER_LEN)
    {
        printf("Error: read header failed\n");
        return ERROR;
    }

    char numNodeChar[HEADER_LEN];
    int i;
    for(i = 0; i < HEADER_LEN; i++)
    {
        if(readBuffer[i] == '*')
        {
            break;
        }
        numNodeChar[i] = readBuffer[i];
    }
    #ifdef LONG

    #else
    *num = atoi(numNodeChar);
    #endif

    return SUCCESS;
}

int readMazeOrigin(int *fdIn, int**maze, node_t* dijkstra_list)
{
    if(*fdIn < 0)
    {
        return ERROR;        
    }
    int fd = *fdIn, i, offset = 0;
    char state = 0, done = 0;
    char readBuffer[MAX_BUFFER_SIZE];
    char *firstNumNodeChar, *secondNumNodeChar, *lenChar;
    char *firstYChar, *firstXChar;
    char *secondYChar, *secondXChar;
    char firstNumNodeCharIndex = 0, secondNumNodeCharIndex = 0, lenCharIndex = 0;
    char firstYCharIndex = 0, firstXCharIndex=0, secondYCharIndex = 0, secondXCharIndex = 0;

    int  firstNumNodeInt, secondNumNodeInt, lenInt;
    int  firstYInt, firstXInt, secondYInt, secondXInt;
    firstNumNodeChar = (char*)malloc(HEADER_LEN * sizeof(char));
    secondNumNodeChar = (char*)malloc(HEADER_LEN * sizeof(char));    
    lenChar = (char*) malloc(HEADER_LEN * sizeof(char));

    firstYChar = (char*)malloc(HEADER_LEN * sizeof(char));
    firstXChar = (char*)malloc(HEADER_LEN * sizeof(char));

    secondYChar =(char*)malloc(HEADER_LEN * sizeof(char));
    secondXChar = (char*)malloc(HEADER_LEN * sizeof(char));

    int read_size = read(fd, readBuffer, MAX_BUFFER_SIZE);
    
    while(read_size > 0)
    {
        if(read_size < MAX_BUFFER_SIZE)
        {
            done = 1;
        }
        
        for(i = 0; i < read_size; i++)
        {
            char newData = readBuffer[i];

            if(newData != '\n')
            {
                if(newData == ' ')
                {
                    firstNumNodeCharIndex = 0, secondNumNodeCharIndex = 0, lenCharIndex = 0;
                    firstYCharIndex = 0, firstXCharIndex=0, secondYCharIndex = 0, secondXCharIndex = 0;
                    state = (state + 1) % 7;
                    offset++;
                    continue;
                }
                if(state == 0)
                {
                    firstNumNodeChar[firstNumNodeCharIndex++] = newData;
                }
                else if(state == 1)
                {
                    firstYChar[firstYCharIndex++] = newData;
                }
                else if(state == 2)
                {
                    firstXChar[firstXCharIndex++] = newData;
                }
                else if(state == 3)
                {
                    secondNumNodeChar[secondNumNodeCharIndex++] = newData;
                }
                else if(state == 4)
                {
                    secondYChar[secondYCharIndex++] = newData;
                }
                else if(state == 5)
                {
                    secondXChar[secondXCharIndex++] = newData;
                }
                else if(state == 6)
                {
                    lenChar[lenCharIndex++] = newData;
                }
                else{
                    //do nothing ?
                }
                offset++;
            }   
            else{
                offset = 0;
                #ifdef LONG

                #else
                    firstNumNodeInt = atoi(firstNumNodeChar);
                    secondNumNodeInt = atoi(secondNumNodeChar);
                    lenInt = atoi (lenChar);

                    firstYInt = atoi(firstYChar);
                    firstXInt = atoi(firstXChar);

                    secondYInt = atoi(secondYChar);
                    secondXInt = atoi(secondXChar);
                    maze[firstNumNodeInt][secondNumNodeInt] = lenInt;
                    if(dijkstra_list[firstNumNodeInt].y == 0 && dijkstra_list[firstNumNodeInt].x == 0)
                    {
                        dijkstra_list[firstNumNodeInt].y = firstYInt;
                        dijkstra_list[firstNumNodeInt].x = firstXInt;
                    }

                    if(dijkstra_list[secondNumNodeInt].y == 0 && dijkstra_list[secondNumNodeInt].x == 0)
                    {
                        dijkstra_list[secondNumNodeInt].y = secondYInt;
                        dijkstra_list[secondNumNodeInt].x = secondXInt;
                    }
                    

                #endif
                free(firstNumNodeChar);
                free(secondNumNodeChar);
                free(lenChar);

                free(firstYChar); free(firstXChar); free(secondYChar); free(secondXChar);
                firstNumNodeChar = (char*)malloc(HEADER_LEN * sizeof(char));
                secondNumNodeChar = (char*)malloc(HEADER_LEN * sizeof(char));
                lenChar = (char*) malloc(HEADER_LEN * sizeof(char));

                firstYChar = (char*)malloc(HEADER_LEN * sizeof(char));
                firstXChar = (char*)malloc(HEADER_LEN * sizeof(char));

                secondYChar =(char*)malloc(HEADER_LEN * sizeof(char));
                secondXChar = (char*)malloc(HEADER_LEN * sizeof(char));
                firstNumNodeCharIndex = 0, secondNumNodeCharIndex = 0, lenCharIndex = 0, state = 0;
                firstYCharIndex = 0, firstXCharIndex=0, secondYCharIndex = 0, secondXCharIndex = 0;
            }
        }
        if(done == 1)
            break;
        if(offset > 0)
        {
            lseek(fd, -offset, SEEK_CUR);
            offset = 0;
            free(firstNumNodeChar);
            free(secondNumNodeChar);
            free(lenChar);
            free(firstYChar); free(firstXChar); free(secondYChar); free(secondXChar);
            firstNumNodeChar = (char*)malloc(HEADER_LEN * sizeof(char));
            secondNumNodeChar = (char*)malloc(HEADER_LEN * sizeof(char));
            lenChar = (char*) malloc(HEADER_LEN * sizeof(char));

            firstYChar = (char*)malloc(HEADER_LEN * sizeof(char));
            firstXChar = (char*)malloc(HEADER_LEN * sizeof(char));

            secondYChar =(char*)malloc(HEADER_LEN * sizeof(char));
            secondXChar = (char*)malloc(HEADER_LEN * sizeof(char));

            firstNumNodeCharIndex = 0, secondNumNodeCharIndex = 0, lenCharIndex = 0, state = 0;
            firstYCharIndex = 0, firstXCharIndex=0, secondYCharIndex = 0, secondXCharIndex = 0;
        }
        read_size = read(fd, readBuffer, MAX_BUFFER_SIZE);
    }
    if(close(fd) < 0)
    {
        return ERROR;
    }
    return SUCCESS;
}
int writeSolution(int *fdOut,int *num, node_t* dijkstra_list, char* pathOut)
{
    
    *fdOut = open(pathOut, MAZE_SOLUTION_FLAGS, PERMS);
    char writeBuffer[MAX_BUFFER_SIZE];
    int writeBufferCount = 0, i;
    int offset = 0;
    if(*fdOut < 0)
    {
        printf("Error: Cannot open %s\n", pathOut);
        return ERROR;
    }
    int numNode = *num;
    int prev = dijkstra_list[numNode -1].prev_node;
    int cur = dijkstra_list[numNode - 1].this_node;
    //Write from the end Node
    while(dijkstra_list[cur].this_node != 0)
    {
        char YChar[HEADER_LEN];
        char XChar[HEADER_LEN];
        int YCharLen = itoa(dijkstra_list[cur].y, YChar);
        int XCharLen = itoa(dijkstra_list[cur].x, XChar);
        if(writeBufferCount + YCharLen + XCharLen + 2 > MAX_BUFFER_SIZE)
        {
            if(write(*fdOut, writeBuffer, writeBufferCount) < writeBufferCount)
            {
                printf("Error: partial write\n");
                return ERROR;
            }
            writeBufferCount = 0;
            continue;
        }
        else
        {
            for(i = 0; i < YCharLen ; i++)
            {
                writeBuffer[writeBufferCount + i] = YChar[i];
            }
            writeBufferCount += YCharLen;
            writeBuffer[writeBufferCount++] = ' ';
            for(i = 0; i < XCharLen; i++)
            {
                writeBuffer[writeBufferCount + i] = XChar[i];
            }
            writeBufferCount += XCharLen;
            writeBuffer[writeBufferCount++] = '\n';
        }
        cur = dijkstra_list[prev].this_node;
        prev = dijkstra_list[cur].prev_node;
    }
    if(write(*fdOut, writeBuffer, writeBufferCount) < writeBufferCount)
    {
        printf("Error: Partial write\n");
        return ERROR;
    }

    //Write the start Node:
    writeBufferCount = 0;
    char YChar[HEADER_LEN];
    char XChar[HEADER_LEN];
    int YCharLen = itoa(dijkstra_list[0].y, YChar);
    int XCharLen = itoa(dijkstra_list[0].x, XChar);
    for(i = 0; i < YCharLen ; i++)
    {
        writeBuffer[writeBufferCount + i] = YChar[i];
    }
    writeBufferCount += YCharLen;
    writeBuffer[writeBufferCount++] = ' ';
    for(i = 0; i < XCharLen; i++)
    {
        writeBuffer[writeBufferCount + i] = XChar[i];
    }
    writeBufferCount += XCharLen;
    writeBuffer[writeBufferCount++] = '\n';
    if(write(*fdOut, writeBuffer, writeBufferCount) < writeBufferCount)
    {
        printf("Error: Partial write\n");
        return ERROR;
    }
    close(*fdOut);
    return SUCCESS;
}

int itoa(int num, char* str)
{
    int base = 10;
    int i = 0;
    int isNegative = 0;
    if(num == 0)
    {
        str[i++] = '0';
        return i;
    }

    if(num < 0)
    {
        isNegative = 1;
        num = -num;
    }

    while(num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem-10) + 'a' : rem + '0';
        num = num / base;
    }
    if(isNegative)
        str[i++] = '-';

    reverse(str, i);
    return i;
}

void swap(char *a, char* b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(char *str, int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        swap((str+start), (str+end)); 
        start++; 
        end--; 
    } 
} 