#ifndef spi1_H
#define spi1_H

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define INT_SIZE sizeof(int) * 8
#define LL_INT_SIZE sizeof(long long int) * 8

#define TWO_BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define TWO_BYTE_TO_BINARY(byte)  \
  (byte & 0x8000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'), \
  (byte & 0x1000 ? '1' : '0'), \
  (byte & 0x800 ? '1' : '0'), \
  (byte & 0x400 ? '1' : '0'), \
  (byte & 0x200 ? '1' : '0'), \
  (byte & 0x100 ? '1' : '0'), \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x8 ? '1' : '0'), \
  (byte & 0x4 ? '1' : '0'), \
  (byte & 0x2 ? '1' : '0'), \
  (byte & 0x1 ? '1' : '0') 

typedef struct list_s
{
	int num;
	struct list_s *ptr; 
} list_t;

int code_type;
int act;
char fin_name[64];
char fout_name[64];

long long int code_f_0(int num, int *size);
long long int code_f_1(int num, int *size);
long long int code_f_2(int num, int *size);
void code_to_file(long long int result, int *size, long long  int *out, int *out_size, FILE *fout);
int coder();
list_t * decode_f_0(FILE *fin);
list_t * decode_f_1(FILE *fin);
list_t * decode_f_2(FILE *fin);
int decoder();
#endif 
