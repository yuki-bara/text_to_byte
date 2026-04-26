// SPDX-License-Identifier: 0BSD
// Author: Makkhawan Sardlah

#include "lib.h"

#include <string.h>

int main(int argc, char const *argv[])
{
    const char *out = NULL;
    const char *in = NULL;
    char mode = '\0';
    const char *argv_now;
    for (size_t i = 1; i < argc; i++)
    {
        argv_now = argv[i];
        if (strncmp(argv_now, "-", 1) == 0)
        {
            for (size_t v = 1; v < strlen(argv[i]); v++)
            {
                if (argv_now[v] == 'o' && out == NULL)
                {
                    i ++;
                    out = argv[i];
                }
                else if (argv_now[v] == 'f' && in == NULL)
                {
                    i ++;
                    in = argv[i];
                }
                else if (argv_now[v] == 'w' && mode == '\0')
                {
                    mode = 'w';
                }
            }
        }
    }
    if ((in && mode) == 0)
    {
        return 1;
    }
    int rt = writefile(&mode, &out, &in);
    return rt;
}
