#include <stdio.h>
#include <ctype.h>

char prod[10][20];
char result[100];
int n, count = 0;

void add(char c)
{
    int i;
    for (i = 0; i < count; i++)
        if (result[i] == c)
            return;

    result[count++] = c;
}

void FIRST(char c)
{
    int i, j;

    if (!isupper(c))
    {
        add(c);
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (prod[i][0] == c && prod[i][1] == '=')
        {
            for (j = 2; prod[i][j] != '\0'; j++)
            {
                char x = prod[i][j];

                if (!isupper(x))
                {
                    add(x);
                    break;
                }

                FIRST(x);
                break;
            }
        }
    }
}

int main()
{
    FILE *in, *out;
    char c;
    int i;

    in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("Cannot open input.txt\n");
        return 1;
    }

    fscanf(in, "%d", &n);

    for (i = 0; i < n; i++)
        fscanf(in, "%19s", prod[i]);

    fscanf(in, " %c", &c);
    fclose(in);

    FIRST(c);

    out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Cannot create output.txt\n");
        return 1;
    }

    fprintf(out, "FIRST(%c) = { ", c);
    for (i = 0; i < count; i++)
        fprintf(out, "%c ", result[i]);

    fprintf(out, "}\n");
    fclose(out);

    printf("Result written to output.txt\n");
    return 0;
}