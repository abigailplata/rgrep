#include <stdio.h>
#define MAXSIZE 4096

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
int i;
    int j = 0;
    
    for(i = 0; pattern[i] != '\0'; i++) //runs until it reaches the end of the pattern
    {
        if (line[j] == '\0') //if pattern continues and line ends then false
        {
            return 0;
        }
        else if (pattern[i+1] == '+' && pattern[i] != '\\')
        {
            if (pattern[i] == '.') //if '.+' then all following characters will work
            {
                while (line[j] != '\0') //this pattern will stop when line reaches the end
                {
                    j++;
                }
            }
            else if (pattern[i] == line[j]) //if anything before '+' other than '.' then run this
            {
                while(pattern[i] == line[j]) //otherwise, '+' will run until no more equal chars to the previous char in pattern
                {
                    j++;
                }
            }
            else
            {
                return 0;
            }
            i++;
        }
        else if (pattern[i+1] == '?' && pattern[i] != '\\') //looks ahead to see if there is a '?'
        {
            if(pattern[i] == line[j] || pattern[i] == '.')
            {
                i++;
                j++;
            }
            else
            {
                i++;
            }
        }
        else if (pattern[i] == '\\')    //if there is a backslash, then it will skip it and use next char as if it had usual effect
        {                               //this is mostly to make sure that effect is taken away from '\\', '?', '.', or '+'
            i++;
            if(pattern[i+1] == '?')
            {
                if(pattern[i] == line[j] || pattern[i] == '.')
                {
                    i++;
                    j++;
                }
                else
                {
                    i++;
                }
            }
            else if(pattern[i] == line[j]) //if they are equal than move on two spaces in pattern and once in line
            {
                j++;
            }
            else //if they do not match then return false
            {
                return 0;
            }
        }
        else if (pattern[i] == '.') //if '.' then continue as if both are equal
        {
            j++;
        }
        else if (pattern[i] == line[j])
        {
            j++;
        }
        else //last check, if they are not equal and none were special chars then they are not equal
        {
            return 0;
        }
    }
    //if (line[j] == '\0') //this is just in case if line is longer than the pattern (works with j+1 for some reason)
    //{
    //  return 1;
    //}
    return 1; //if it passes without fail then the pattern and line match
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
