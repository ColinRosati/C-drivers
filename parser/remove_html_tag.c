#include <stdio.h>
#include <stdlib.h>

int remove_html(char* str){
	char* html_str = str;
	while(str){
		if(*html_str == '<')
			while(*html_str && *html_str != '>');
				*str++ = *html_str++;
	}
	return EXIT_SUCCESS;
}


int main(void){
	FILE *fp1, *fp2;
	fp2 = fopen("youtubehiaku.htm", "r"); 
	fp1 = fopen("website.txt", "w"); 

	char c;

	if (fp2 == NULL){
		printf("ERROR READING\n");
	}

	
      if (fp2) {
          while ((c = getc(fp2)) != EOF);
          //fputc(c, fp1); // puts writes the c to the location fp1
     }
     printf("c");
    fputc(c, fp1);
	//remove_html(c);
	//putc(c);

   fclose(fp1);
   fclose(fp2);


	return EXIT_SUCCESS;
}