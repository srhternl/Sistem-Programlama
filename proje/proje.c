#include "fields.h"
#include "jrb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeChar(char *str, char garbage) 
{
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
    	JRB encode, decode, tmp_e, tmp_d, tmp;
	encode = make_jrb();
	decode = make_jrb();
	int sayac = 0;
	
  	while(get_line(is) >= 0) // yada getline "!= -1" de olabilir.
  	{
   		//printf("Satır %d.\n", is->line);
		char* key;
		char* value;
    		if (strstr(is->text1, "}") == NULL && strstr(is->text1, "{") == NULL)
		{
			for(int i = 0; i < is->NF; i++)
			{
	       			if(i == 0)
	       			{	
				key = is->fields[i];
				removeChar(key, '\"');
				removeChar(key, ':');
				printf("key:%s\n", key);
	       			}
	       			else if(i == 1)
	       			{
				value = is->fields[i];
				removeChar(value, '\"');
				removeChar(value, ',');
				printf("value:%s\n", value);
       				}
			}
		}		
		
		if (key != NULL && value != NULL)
		{
			jrb_insert_str(encode, strdup(key), new_jval_s(strdup(value)));
			jrb_insert_str(decode, strdup(value), new_jval_s(strdup(key)));
		}	
		sayac ++;	
  	} 
	
	/*
	jrb_traverse(tmp_e, encode) 
	{
    		printf("key: %s\n", tmp_e->key.v);
		printf("encode value: %s\n", tmp_e->val.v);
	}
	jrb_traverse(tmp_d, decode) 
	{
    		printf("key: %s\n", tmp_d->key.v);
		printf("decode value: %s\n", tmp_d->val.v);
	}
	*/

	for (int i = 0; i < sayac - 2; i++)
	{
		encode = jrb_next(encode);
		decode = jrb_next(decode);
		printf("encode key: %s\n", encode->key.v);
		printf("encode value: %s\n", encode->val.v);
		printf("decode key: %s\n", decode->key.v);
		printf("decode value: %s\n", decode->val.v);
	}

  	// Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  	jettison_inputstruct(is);

  	return 0;
}