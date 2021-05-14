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

// 500 kelime sınırını, sayaca atadığımız fonksiyon.
int border(IS inputSayac)
{
	int kelimeSayac;
	while(get_line(inputSayac) >= 0)
	{
		for(int i = 0; i < inputSayac->NF; i++)
		{
			kelimeSayac++;
		}
	}
	return kelimeSayac; 		
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
					if(strlen(key) >= 100)
					{
						printf("100 karakter sınırını aştınız. \n");
						exit(1);
					}
       				}
       				else if(i == 1)
       				{
					value = is->fields[i];
					removeChar(value, '\"');
					removeChar(value, ',');
					if(strlen(value) >= 100)
					{
						printf("100 karakter sınırını aştınız. \n");
						exit(1);
					}
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

// parametre ve kelime kontrolü, dosyaya yazdırma işlemleri.
void print(FILE* file,int kelimeSayac,char* arg,IS input,JRB encode,JRB decode)
{
	//500 kelime kontrolü.
	if(kelimeSayac <= 500)
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
	
	//500 kelime kontrolünün hata mesajı.
	else
	{
		printf("Giriş dosyasında 500\'den fazla sayıda kelime var daha küçük bir örnek kullanınız!");
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
	int kelimeSayac = 0;
	IS is, isSayac, input, inputSayac;
    	JRB encode, decode;
	encode = make_jrb();
	decode = make_jrb();
	is = new_inputstruct(".kilit");
	isSayac = new_inputstruct(".kilit");
 	input = new_inputstruct(argv[2]);
	inputSayac = new_inputstruct(argv[2]);
	FILE *file;
	file = fopen(argv[3], "a");
	
  	
	controls(argc,is, input);
  	trees(encode,decode,is);	
	kelimeSayac=border(inputSayac);
	print(file,kelimeSayac,argv[1],input,encode,decode);
  	// Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  	jettison_inputstruct(is);

  	return 0;
}
