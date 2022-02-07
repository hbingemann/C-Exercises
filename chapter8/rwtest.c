#include <unistd.h>
#include <string.h>

int main()
{
    write(1, "hello world\n", strlen("hello world\n"));
    return 0;
}
