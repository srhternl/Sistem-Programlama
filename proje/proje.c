#include "fields.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeChar(char *str, char garbage) {

    	char *src, *dst;
    	for (src = dst = str; *src != '\0'; src++) 
		{
        	*dst = *src;
        	if (*dst != garbage) dst++;
    	}
    	*dst = '\0';
}

int main(void) 
{    
	IS is;
  	is = new_inputstruct(NULL); // NULL ise stdin(standard input)
    	
  	while(get_line(is) >= 0) // yada getline "!= -1" de olabilir.
  	{
   		printf("Satır %d.\n", is->line);

    	for(int i = 0; i < is->NF; i++)
       	if(i == 0)
       	{
			char* key = is->fields[i];
			removeChar(key, '\"');
			removeChar(key, ':');
			printf("key:%s\n", key);
       	}
       	else if(i == 1)
       	{
			char* value = is->fields[i];
			removeChar(value, '\"');
			removeChar(value, ',');
			printf("value:%s\n", value);
       	}

  } 

  	// Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  	jettison_inputstruct(is);

  	return 0;
}