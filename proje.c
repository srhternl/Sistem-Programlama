#include "fields.h"  //tırnak içinde yazarsak kaynak dosyası ile aynı yerde olduğu anlamına gelir.

int main()
{
  IS is;

  // yeni bir dosya okuyucusu tanımla
  is = new_inputstruct(NULL); // NULL ise stdin(standard input)

  while(get_line(is) >= 0) // yada getline "!= -1" de olabilir.
  {
    printf("Satır %d.\n", is->line);

    for(int i = 0; i < is->NF; i++)
       printf("%s\n", is->fields[i]);

    /*
    if(is->NF >= 2)
      printf("İkinci kelime: %s\n", is->fields[1]); // fields'ın 2.elemanı için dizinin 1.elemanını yazdırıoz.
    else
      printf("İkinci kelime yok\n");
    */

  }
  
  //printf("Kelime sayısı: %d\n", is->NF);
 

  // Çıkmadan önce bellekte kullanılan yerlerin geri bırakılması
  jettison_inputstruct(is);
  

}

//yönlendirmeyi fields.c dosyası için yaparsak orada ikinci kelime yok hata mesajı verir.
//yönlendirme gösterim: "./p3 < fields.c" konsola bunu yazınca hata mesajını verecek.