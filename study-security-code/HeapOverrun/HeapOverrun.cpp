#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class BadStringBuf
{
private:
    char* m_buf;
public:
    BadStringBuf(void);
    ~BadStringBuf(void);
};

BadStringBuf::BadStringBuf(void)
{
    m_buf = NULL;
}

BadStringBuf::~BadStringBuf(void)
{
    if(m_buf != NULL)
    {
        free(m_buf);
    }
}

void Init(char* buf)
{
    
}
