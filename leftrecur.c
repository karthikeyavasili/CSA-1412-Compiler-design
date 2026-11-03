#include <stdio.h>
#include <string.h>

int main()
{
    FILE *in, *out;
    char line[100], lhs, alpha[10][30], beta[10][30];
    int i, j, a, b, k;

    in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("Cannot open input.txt\n");
        return 1;
    }

    out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Cannot create output.txt\n");
        fclose(in);
        return 1;
    }

    while (fgets(line, sizeof(line), in))
    {
        line[strcspn(line, "\r\n")] = '\0';

        lhs = line[0];
        a = 0;
        b = 0;

        char *token = strtok(line + 2, "|");

        while (token != NULL)
        {
            if (token[0] == lhs)
            {
                strcpy(alpha[a++], token + 1);
            }
            else
            {
                strcpy(beta[b++], token);
            }

            token = strtok(NULL, "|");
        }

        if (a == 0)
        {
            fprintf(out, "%c=", lhs);

            for (i = 0; i < b; i++)
            {
                if (i > 0)
                    fprintf(out, "|");

                fprintf(out, "%s", beta[i]);
            }

            fprintf(out, "\n");
        }
        else
        {
            fprintf(out, "%c=", lhs);

            for (i = 0; i < b; i++)
            {
                if (i > 0)
                    fprintf(out, "|");

                fprintf(out, "%s%c'", beta[i], lhs);
            }

            fprintf(out, "\n%c'=", lhs);

            for (i = 0; i < a; i++)
            {
                if (i > 0)
                    fprintf(out, "|");

                fprintf(out, "%s%c'", alpha[i], lhs);
            }

            fprintf(out, "|#\n");
        }
    }

    fclose(in);
    fclose(out);

    printf("Left recursion eliminated. Check output.txt\n");

    return 0;
}
