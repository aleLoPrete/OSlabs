#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");
    char character;

    if (fp == NULL)
    {
        printf("\nerrore apertura file\n");
        return -1;
    }

    while ((character = fgetc(fp)) != EOF)
    {
        fputc(character, fp2);
    }

    fclose(fp);
    fclose(fp2);
}
