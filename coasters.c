#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct 
{
  char name[31];
  char world[31];
  int height;
  int time;  
}roll;

int cmp(const void *a, const void *b)
{
    roll *left = (roll*) a;
    roll *right = (roll*) b;

    if (left->time != right->time )
    {
        return left->time-right->time;//ascending
    }
    
    if (left->height != right->height)
    {
        return-(left->height-right->height);//desending
    }
    
    return strcmp(left->name, right->name);//ascending
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr,"Argument is missing.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");//how to open a file
    if (!file)//=null
    {
        fprintf(stderr, "This file cant be open.\n");
        return 2;
    }


char line[102]; // for \n and \0
roll coasters[20];
int lenght=0;

while (fgets(line, sizeof(line), file))
{
    line[strlen(line) - 1] = '\0';

    strcpy(coasters[lenght].name,
        strtok(line, ";"));
    strcpy(coasters[lenght].world,
        strtok(NULL,";"));
    coasters[lenght].height=
        atoi(strtok(NULL,";"));
    coasters[lenght].time=
        atoi(strtok(NULL,";"));
    lenght++;
}

fclose(file);

qsort(coasters,lenght,sizeof(roll),cmp);

if (argc == 2)
{
    fprintf(stderr, "the 2nd argument missing");
    return 3;
}

file = fopen(argv[2], "w");
if (!file)
{
    fprintf(stderr, "This file cant be opened.\n");
    return 4;
}

// echo %errorlevel% for check num of erorr

for (int i = 0; i < lenght; i++)
    {
      fprintf(file, "%s(%s):%d\n",coasters[i].name,coasters[i].world,coasters[i].time);
    }
    fclose(file);

}
