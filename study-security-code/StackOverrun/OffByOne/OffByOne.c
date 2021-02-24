#include <stdio.h>
#include <string.h>

void foo(const char* in)
{
    char buf[64];
   
    if(strlen(in)< sizeof(buf))
    {
        strncpy(buf,in, sizeof(buf));
        buf[sizeof(buf)] = '\0';
        printf("%s\n, buff");
    }
    
  

}

void bar(const char* in)
{
    printf("Augh! I've been hacked!\n");
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf ("Usage is %s [string]\n", argv[0]);

    }
    printf("Address of foo is %p, address of bar is %p\n", foo,bar);
    foo(argv[1]);
    return 0;

}