#include <stdio.h>
    

int main()
{
    
     FILE *fp1, *fp2;
     char c;   // stores the text from a file in a variable

     fp1 = fopen("website.txt", "w");  
     fp2 = fopen("html.txt", "r"); 

     if (fp1== NULL)
     {
          puts("Issue in opening the Output file");
     }
     if (fp2== NULL)
     {
          puts("Issue in opening the Output file");
     }

     printf("take this file and put it into that");

     if (fp2) {
          while ((c = getc(fp2)) != EOF)
          fputc(c, fp1); // puts writes the c to the location fp1
     }

 
   fclose(fp1);
   fclose(fp2);


     return 0;
}
