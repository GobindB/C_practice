#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// return 1 if char is vowel and 0 if not
int isVowel(int ch)
{
  int c = toupper(ch);
 
  return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

double getPercentage(int total, int char_count)
{
    return (double) char_count/total *100;;
}

// return number of non-whitespace characters in file
void getCharsInFile(FILE *fptr, int *total_counts)
{
    // total, consonants, punc, a, e, i, o, u,
    int count=0, punc=0, whitespace=0, newline=0;
    char ch;
    while((ch=fgetc(fptr))!=EOF) {
            if(ispunct(ch))
               punc++;
            else if(isspace(ch))
                whitespace++;
            else if (isVowel(ch))
            {
                if(toupper(ch) == 'A')
                    total_counts[3]++;
                else if(toupper(ch) == 'E')
                    total_counts[4]++;
                else if(toupper(ch) == 'I')
                    total_counts[5]++;
                else if(toupper(ch) == 'O')
                    total_counts[6]++;
                else if(toupper(ch) == 'U')
                    total_counts[7]++;
            }
            if(ch == '\n')
                newline++;
            count++;
        }
    // totals
    int vowels = total_counts[3] + total_counts[4] + total_counts[5] + total_counts[6] + total_counts[7];
    total_counts[0] = count - newline;
    total_counts[1] = count - punc - whitespace - vowels;
    total_counts[2] = punc;
}

int main(int argc, const char * argv[]) {
    
    char filename[20], outputs[7] = {'a', 'e', 'i', 'o', 'u'};
    int total_counts[8] = {0,0,0,0,0,0};
    
    printf("Please enter a filename: ");
    scanf("%s", filename);
    
    // try to open file exit with error code 1 if not found
    FILE *fptr, *outputPtr;
    if((fptr = fopen(filename, "r")) == NULL)
    {
        printf("Invalid filename. Please try again.\n");
        exit(1);
    }
    
    getCharsInFile(fptr, total_counts);
    printf("Chars\tQuantities\tPercentages\n");
    for(int i=0; i<5; i++)
    {
        printf("%c\t\t\t\t%d\t\t\t%.1f%%\n",outputs[i], total_counts[i+3],getPercentage(total_counts[0], total_counts[i+3]));
    }
    
    printf("Consonants\t\t%d\t\t\t%.1f%%\n",total_counts[1], getPercentage(total_counts[0], total_counts[1]));
    printf("Punctuations\t%d\t\t\t%.1f%%\n",total_counts[2], getPercentage(total_counts[0], total_counts[2]));
    
    fclose(fptr);
    
    // output to file
    if((outputPtr = fopen("output.txt", "w")) == NULL)
    {
        printf("Error creating file. Please try again.\n");
        exit(1);
    }
    
    fprintf(fptr,"a\te\ti\to\tu\tconsonants punct\n%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\t%.1f%%\t   %.1f%%", \
            getPercentage(total_counts[0],total_counts[3]),getPercentage(total_counts[0],total_counts[4]), \
            getPercentage(total_counts[0],total_counts[5]),getPercentage(total_counts[0],total_counts[6]), \
            getPercentage(total_counts[0],total_counts[7]),getPercentage(total_counts[0],total_counts[1]), \
            getPercentage(total_counts[0],total_counts[2]));
    
    fclose(outputPtr);
    return 0;
}
