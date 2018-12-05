/*
使用Cache降低拷贝时间
使用time命令计时
*/

#include <stdio.h>
#include <string.h>

#define SMART

#define CHARSIZE 1000000

#define LOOPTIME 10000

#define DUMBCOPY for(int i=0;i<CHARSIZE;i++)\
                        dest[i]=sour[i]

#define SMARTCOPY memcpy(dest,sour,CHARSIZE)

int main(int argc,char **argv){

    char sour[CHARSIZE],dest[CHARSIZE];

    int i,j;
    for(j=0;j<10000;j++)
#ifdef SMART
        SMARTCOPY;                      //realtime: 0m0.221s
#else
        DUMBCOPY;                       //realtime: 0m21.177s
#endif

    return 0;
}