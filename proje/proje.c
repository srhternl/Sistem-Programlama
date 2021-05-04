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

int main(int argc, char **argv) 
{    
<<<<<<< Updated upstream
	IS is, input, output;
=======
	int kelimeSayac = 0;
	IS is, input,inputSayac;
>>>>>>> Stashed changes
    	JRB encode, decode, tmp_e, tmp_d, tmp;
	encode = make_jrb();
	decode = make_jrb();
	int sayac = 0;
	is = new_inputstruct(".kilit");
 	input = new_inputstruct(argv[2]);
<<<<<<< Updated upstream
	output = new_inputstruct(argv[3]);
	FILE *file;
	file = fopen(argv[3], "w");
=======
	inputSayac = new_inputstruct(argv[2]);
	FILE *file;
	file = fopen(argv[3], "a");
	
>>>>>>> Stashed changes
  	
	if (argc != 4)
	{
		fprintf(stderr, "usage: printwords filename\n");
		exit(1);
	}
	if (is == NULL) 
	{
    		perror((argv[1]));
    		exit(1);
  	}
	
  	while(get_line(is) >= 0) // yada getline "!= -1" de olabilir.
  	{
   		//printf("Satır %d.\n", is->line);
		char* key;
		char* value;
		//süslü parentez kontrolü.
    		if (strstr(is->text1, "}") == NULL && strstr(is->text1, "{") == NULL)
		{
			for(int i = 0; i < is->NF; i++)
<<<<<<< Updated upstream
		{
       		if(i == 0)
       		{
			key = is->fields[i];
			removeChar(key, '\"');
			removeChar(key, ':');
			//printf("key:%s\n", key);
       		}
       		else if(i == 1)
       		{
			value = is->fields[i];
			removeChar(value, '\"');
			removeChar(value, ',');
			//printf("value:%s\n", value);
       		}
		}
=======
			{
       				if(i == 0)
       				{
					key = is->fields[i];
					removeChar(key, '\"');
					removeChar(key, ':');
       				}
       				else if(i == 1)
       				{
					value = is->fields[i];
					removeChar(value, '\"');
					removeChar(value, ',');
       				}
			}
>>>>>>> Stashed changes
		}		
		
		if (key != NULL && value != NULL)
		{
			jrb_insert_str(encode, strdup(key), new_jval_s(strdup(value)));
			jrb_insert_str(decode, strdup(value), new_jval_s(strdup(key)));
		}	
		sayac ++;	
  	} 
<<<<<<< Updated upstream
	/*
	for (int i = 0; i < sayac - 2; i++)
	{
		encode = jrb_next(encode);
		decode = jrb_next(decode);

		
		printf("encode key: %s\n", encode->key.v);
		printf("encode value: %s\n", encode->val.v);
		printf("decode key: %s\n", decode->key.v);
		printf("decode value: %s\n", decode->val.v);
		
	}
	*/
	
	while(get_line(input) >= 0) // yada getline "!= -1" de olabilir.
  	{
		char* key;
		char* value;
    		
		for(int i = 0; i < input->NF; i++)
		{
			key = input->fields[i];
			printf("keys: %s\n",key);
			if (strcmp(argv[1], "-e") == 0)
			{
				JRB node = jrb_find_str(encode, key);
				if (node != NULL)
				{
					fprintf(file, node->val.s);
					fprintf(file, " ");
				}
				else
				{
					printf("key: %s\n",key);
				}
			}
			
			else if (strcmp(argv[1], "-d") == 0)
			{
				JRB node2 = jrb_find_str(decode, key);
				if (node2 != NULL)
				{
					fprintf(file, node2->val.s);
					fprintf(file, " ");
				}
				else
				{
					printf("key: %s\n",key);
				}
				
			}
		}
		
	}
	
  	// Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  	jettison_inputstruct(is);

  	return 0;
}
=======
	
	while(get_line(inputSayac) >= 0)
	{
		for(int i = 0; i < inputSayac->NF; i++)
		{
			kelimeSayac++;
		}
	}
	if(kelimeSayac <= 500)
	{	
		if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-e") == 0)
		{
			while(get_line(input) >= 0) // yada getline "!= -1" de olabilir.
  			{
				char* key;
				char* value;
    			
				for(int i = 0; i < input->NF; i++)
				{
					key = input->fields[i];
				
					if (strcmp(argv[1], "-e") == 0)
					{
						JRB node = jrb_find_str(encode, key);
						if (node != NULL)
						{
							fprintf(file, node->val.s);
							fprintf(file, " ");
						}
						else
						{	
							fprintf(file,key);
							fprintf(file, " ");
						}
					}
			
					else if (strcmp(argv[1], "-d") == 0)
					{
						JRB node2 = jrb_find_str(decode, key);
						if (node2 != NULL)
						{
							fprintf(file, node2->val.s);
							fprintf(file, " ");
						}
						else
						{
							fprintf(file,key);
							fprintf(file, " ");
						}
				
					}
				
				}	
		
			}
		}
		else
		{	
			printf("Yanlış parametre kullanımı!\n");
		}
	}
	else
	{
		printf("Giriş dosyasında 500\'den fazla sayıda kelime var daha küçük bir örnek kullanınız!");
	}
  	// Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  	jettison_inputstruct(is);

  	return 0;
}
>>>>>>> Stashed changes
