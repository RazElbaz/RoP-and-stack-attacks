#include <stdio.h>
#include <string.h>

void copy_and_echo(const char* p)
{
    int length = strlen(p);
    char buffer[length + 1]; // Add space for null terminator
    int i, j = 0;

    for (i = 0; i < length; i++)
    {
        if (p[i] >= 32 && p[i] <= 126)
        {
            buffer[j++] = p[i];
        }
    }
    buffer[j] = '\0'; // Null terminate the buffer

    printf("%s\n", buffer);
}

int main(int argc, const char* argv[])
{
    if (argc < 2)
        return -1;
    copy_and_echo(argv[1]);
    return 0;
}
