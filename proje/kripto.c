#include "./libfdr/fields.h"
#include "./libfdr/jrb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Json formatındaki karakterleri silen fonksiyonumuz.
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

// Oluşan encode decode ağaçlarına atama yapıyoruz.
void trees(JRB encode,JRB decode,IS is)
{
	while(get_line(is) >= 0) // yada getline "!= -1" de olabilir.
  	{
   		//printf("Satır %d.\n", is->line);
		char* key;
		char* value;
		//süslü parentez kontrolü.
    		if (strstr(is->text1, "}") == NULL && strstr(is->text1, "{") == NULL)
		{
			for(int i = 0; i < is->NF; i++)
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
		}		
		
		// Değer null değilse ağaca atama yapma.
		if (key != NULL && value != NULL)
		{
			jrb_insert_str(encode, strdup(key), new_jval_s(strdup(value)));
			jrb_insert_str(decode, strdup(value), new_jval_s(strdup(key)));
		}	
			
  	} 
}

// parametre ve dosyaya yazdırma işlemleri.
void print(FILE* file, char* arg,IS input,JRB encode,JRB decode)
{
		
		if(strcmp(arg, "-d") == 0 || strcmp(arg, "-e") == 0)
		{
			while(get_line(input) >= 0) // yada getline "!= -1" de olabilir.
  			{
				char* key;
				char* value;
    			
				for(int i = 0; i < input->NF; i++)
				{
					key = input->fields[i];
				
					// "-e" parametresinin dosyaya yazdırma işlemi.
					if (strcmp(arg, "-e") == 0)
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
					
					// "-d" parametresinin dosyaya yazdırma işlemi.
					else if (strcmp(arg, "-d") == 0)
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


void controls(int argc,IS is, IS argv)
{
	// parametre kontrolü.
	if (argc != 4)
	{
		fprintf(stderr, "Parametreyi yanlış girdiniz.");
		exit(1);
	}
	// kilit dosyasının kontrolü.
	if (is == NULL) 
	{
    		perror((".kilit"));
    		exit(1);
  	}
	// giriş metninin kontrolü.
	if (argv == NULL) 
	{
    		perror(("ornek_metin"));
    		exit(1);
  	}
	
}

int main(int argc, char **argv) 
{    
	IS is, input;
    	JRB encode, decode;
	encode = make_jrb();
	decode = make_jrb();
	is = new_inputstruct(".kilit");
 	input = new_inputstruct(argv[2]);
	FILE *file;
	file = fopen(argv[3], "a");
	
  	
	controls(argc,is, input);
  	trees(encode,decode,is);	
	print(file,argv[1],input,encode,decode);

  	// Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  	jettison_inputstruct(is);

  	return 0;
}
