#include "spi1.h"

list_t * decode_f_0(FILE *fin)
{
    int i, bit = 0, result = 0;
    long long int num;
    list_t *list = NULL, *curr = NULL, *first = NULL;
    
    while (fread (&num, sizeof(long long int), 1, fin) == 1)
    {
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
        for (i = LL_INT_SIZE; i > 0; i--)
        {
            bit = (num >> (i-1)) & 1;
            if (bit)
            {
                curr = malloc(sizeof(list_t));
                curr->num = result;
                curr->ptr = NULL;
                if (list == NULL)
                {
                    list = curr;
                    first = list;
                }
                else
                {
                    list->ptr = curr;
                    list = curr;
                }
                result = 0;
            }
            else
                result ++;
        }
    }
    return first;
}

list_t * decode_f_1(FILE *fin)
{    
    int i, j,  j1, bit = 0, size = 0, result = 0;
    long long int num;
    list_t *list = NULL, *curr = NULL, *first = NULL;
    
    while (fread (&num, sizeof(long long int), 1, fin) == 1)
    {
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
        for (i = LL_INT_SIZE; i > 0;)
        {
            bit = (num >> (i-1)) & 1;
            if (bit)
            {
                result = 0;
                if (size != 0)
                {
                    for (j = 0, j1 = 0; j < size; j++, j1++)
                    {
                        bit = (num >> (i-1-j1)) & 1;
                        result = (result << 1) | bit;
                        if (i-1-j1 == 0)
                        {
                            if (fread (&num, sizeof(long long int), 1, fin) != 1)
                            {
                                printf("Wrong code");
                                return first;
                            }
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
                            i = LL_INT_SIZE;
                            j1 = -1;
                        }
                    }
                    i -= j1;
                }
                else
                {
                    i--;
                    i -= size;
                }
                
                curr = malloc(sizeof(list_t));
                curr->num = result;
                curr->ptr = NULL;
                if (list == NULL)
                {
                    list = curr;
                    first = list;
                }
                else
                {
                    list->ptr = curr;
                    list = curr;
                }
                
                size = 0;
                result = 0;
            }
            else
            {
                size ++;
                i--;
            }
        }
    }
    return first;
}

list_t * decode_f_2(FILE *fin)
{
    int i, j, j1, bit = 0, size = 0, size_1 = 0, result = 0;
    long long int num;
    list_t *list = NULL, *curr = NULL, *first = NULL;
    
    while (fread (&num, sizeof(long long int), 1, fin) == 1)
    {
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
        for (i = LL_INT_SIZE; i > 0;)
        {
            bit = (num >> (i-1)) & 1;
            if (bit)
            {
                size_1 = 0;
                if (size != 0)
                {
                    result = 1;
                    for (j = 0, j1 = 0; j < size; j++, j1++)
                    {
                        bit = (num >> (i-1-j1)) & 1;
                        size_1 = (size_1 << 1) | bit;
                        if (i-1-j1 == 0)
                        {
                            if (fread (&num, sizeof(long long int), 1, fin) != 1)
                            {
                                printf("Wrong code");
                                return first;
                            }
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
                            i = LL_INT_SIZE;
                            j1 = -1;
                        }
                    }
                    i = i - j1+1;
                    for (j = 1, j1 = 1; j < size_1; j++, j1++)
                    {
                        bit = (num >> (i-1-j1)) & 1;
                        result = (result << 1) | bit;
                        if (i-1-j1 == 0)
                        {
                            if (fread (&num, sizeof(long long int), 1, fin) != 1)
                            {
                                printf("Wrong code");
                                return first;
                            }
#if DEBUG >= 1
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
        printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
        printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
                            i = LL_INT_SIZE;
                            j1 = -1;
                        }
                    }
                    i = i - j1;
                }
                else
                {
                    result = 0;
                    i--;
                }
                curr = malloc(sizeof(list_t));
                curr->num = result;
                curr->ptr = NULL;
                if (list == NULL)
                {
                    list = curr;
                    first = list;
                }
                else
                {
                    list->ptr = curr;
                    list = curr;
                }
                result = 0;
                size = 0;
                size_1 = 0;
            }
            else
            {
                size ++;
                i--;
            }
        }
    }
    return first;
}

int decoder()
{
    FILE *fin = NULL;
    list_t *list;
    if ((fin = fopen(fin_name, "rb")) == NULL)
    {
        printf("Unable to open file %s\n", fin_name);
        return -1;
    }
    switch (code_type)
    {
        case 1:
        {
            list = decode_f_0(fin);
            while (list)
            {
                printf("%d ", list->num);
                list = list->ptr;
            }
            break;
        }
        case 2:
        {
            list = decode_f_1(fin);
            while (list)
            {
                printf("%d ", list->num);
                list = list->ptr;
            }
            break;
        }
        case 3:
        {
            list = decode_f_2(fin);
            while (list)
            {
                printf("%d ", list->num);
                list = list->ptr;
            }
            break;
        }
    }
    printf("\n");
    fclose(fin);
    
    return 1;
}
