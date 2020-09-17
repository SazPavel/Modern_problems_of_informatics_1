#include "spi1.h"

long long int code_f_0(int num, int *size)
{
    *size = num + 1;
    return 1;
}

long long int code_f_1(int num, int *size)
{
    int tmp_num = num, i = 1;
    long long int result = num;
    if (num == 0)
    {
        *size = 1;
        return 1;
    }
    for ( ;tmp_num > 1; tmp_num /= 2, i++);
    *size = 2*i;
    return result;
}

long long int code_f_2(int num, int *size)
{
    int size_tmp = 0, tmp_num = num, i = 1;
    long long int tmp;
    if (num == 0)
    {
        *size = 1;
        return 1;
    }
    for ( ;tmp_num > 1; tmp_num /= 2, i++);
    tmp = code_f_1(i, &size_tmp);
    i--;
    num ^= (1 << i);
    tmp = (tmp << i) | num;
    *size = i + size_tmp;
    return tmp;
}

void code1_to_file(int *size, long long int *out, int *out_size, FILE *fout)
{
    if (*out_size + *size < LL_INT_SIZE)
    {
        *out = (*out << *size) | 1;
        *out_size += *size;
        *size = 0;
    }
    else
    {
        int tmp_size = LL_INT_SIZE - *out_size;
        *out = (*out << tmp_size);
        fwrite(out, sizeof(long long int), 1, fout);
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" WRITE\n", TWO_BYTE_TO_BINARY(*out));
#endif
        *out = 0;
        *size -= tmp_size;
        *out_size = 0;
    }
}

void code_to_file(long long int result, int *size, long long int *out, int *out_size, FILE *fout)
{
    if (*out_size + *size < LL_INT_SIZE)
    {
        *out = (*out << *size) | result;
        *out_size += *size;
        *size = 0;
    }
    else
    {
        long long int tmp = result;
        int tmp_size = LL_INT_SIZE - *out_size;
        *out = (*out << tmp_size) | (tmp >> (*size - tmp_size));
        fwrite(out, sizeof(long long int), 1, fout);
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" WRITE\n", TWO_BYTE_TO_BINARY(*out));
#endif
        *out = 0;
        *size -= tmp_size;
        *out_size = 0;
    }
}

int coder()
{
    int num, size = 0, out_size = 0;
    long long int result, out = 0;
    FILE *fin = NULL, *fout = NULL;
    if ((fin = fopen(fin_name, "r")) == NULL)
    {
        printf("Unable to open file %s\n", fin_name);
        return -1;
    }
        
    if ((fout = fopen(fout_name, "wb")) == NULL)
    {
        printf("Unable to open file %s\n", fout_name);
        fclose(fin);
        return -1;
    }

    switch (code_type)
    {
        case 1:
        {
            while (fscanf (fin, "%d", &num) != EOF)
            {
                result = code_f_0(num, &size);
#if DEBUG == 2
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 48));
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 32));
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 16));
                printf(""TWO_BYTE_TO_BINARY_PATTERN"\n size = %d\n", TWO_BYTE_TO_BINARY(result), size);
#endif
                while (size > 0)
                    code1_to_file(&size, &out, &out_size, fout);
            }
                break;
        }
        case 2:
        {
            while (fscanf (fin, "%d", &num) != EOF)
            {
                result = code_f_1(num, &size);
#if DEBUG == 2
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 48));
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 32));
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 16));
                printf(""TWO_BYTE_TO_BINARY_PATTERN"\n size = %d\n", TWO_BYTE_TO_BINARY(result), size);
#endif
                while (size > 0)
                    code_to_file(result, &size, &out, &out_size, fout);
            }
            break;
        }
        case 3:
        {
            while (fscanf (fin, "%d", &num) != EOF)
            {
                result = code_f_2(num, &size);
#if DEBUG == 2
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 48));
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 32));
                printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 16));
                printf(""TWO_BYTE_TO_BINARY_PATTERN"\n size = %d\n", TWO_BYTE_TO_BINARY(result), size);
#endif
                while (size > 0)
                    code_to_file(result, &size, &out, &out_size, fout);
            }
            break;
        }
    }
    if (out != 0)
    {
        out <<= (LL_INT_SIZE - out_size);
#if DEBUG == 2
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(out >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(out >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(out >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" WRITE\n", TWO_BYTE_TO_BINARY(out));
#endif
        fwrite(&out, sizeof(long long int), 1, fout);
        out = out_size = 0;
    }
    fclose(fout);
    fclose(fin);
    
    return 1;
}
