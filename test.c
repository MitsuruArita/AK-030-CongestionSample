#include <stdio.h>

void func(const char *server)
{
    printf("SERVER:%s", server);
    return;
}

int main(void)
{
    func("SAKANA");
}