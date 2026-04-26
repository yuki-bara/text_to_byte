// SPDX-License-Identifier: 0BSD
// Author: Makkhawan Sardlah

#include "lib.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int writefile(const char *mode, const char **out , const char **in) {
    if (*mode == 'w')
    {
        FILE *fin = fopen(*in, "rb");
        FILE *fout;
        char buffer[512];
        char target[64];
        char byte;
        size_t size;
        size_t full_size = 0;
        size_t r = 0;
        if (out == NULL)
        {
            fout = fopen("a.out", "wb");
        }
        else {
            fout = fopen(*out, "wb");
        }
        if (fin == NULL || fout == NULL)
        {
            return 1;
        }
        fseek(fin, 0, SEEK_END);
        full_size = ftell(fin);
        fseek(fin, 0, SEEK_SET);
        while (1)
        {
            size = fread(buffer, 1, 512, fin);
            if (size == 0)
            {
                break;
            }
            for (size_t i = 0; i < size; i++)
            {
                if (buffer[i] == '0')
                {
                    byte = byte << 1 | 0x00;
                }
                else if (buffer[i] == '1')
                {
                    byte = byte << 1 | 0x01;
                }
                else {
                    printf("\r\033[0;31m[ err% \033[31m] error reading\033[0m");
                    fclose(fout);
                    remove(*out);
                    fclose(fin);
                    return 1;
                }
                if ((i + 1) % 8 == 0)
                {
                    printf("\r\033[0;32m[ %.1f% \033[32m] write\033[0m", ( (size + (512.0 * r)) / full_size) * 100 );
                    target[i / 8] = byte;
                }
            }
            if ((int)size > 0)
            {
                fwrite(target, 1, (int)size, fout);
            }
            r ++;
        }
        fclose(fout);
        fclose(fin);
        return 0;
    }
}