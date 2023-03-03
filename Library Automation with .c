#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>


typedef struct kitap 
{
    int barkod;
    char kitapAdi[50];
    char yazarAdi[50];
    char yayinEvi[50];
    char kitapTuru[50];
    char teminTuru[50];
    char teminTarihi[11];
    int stokSayisi;

} kitap;


typedef struct Uye {

  char tc[11];
    char adSoyad[20];
    char cinsiyet;
    char dogumTarihi[11];
    char telefon[11];
    char eposta[20];
    char uyelikTarihi[11];
    char adres[50];
    int durum;

} uye ;


typedef struct Emanet {
  
   char uyeTC[11];
    int kitapBarkod;
    time_t teslimTarihi; 
    int kullanacagiGunSayisi; 
    int kullandigiGunSayisi;
    time_t iadeTarihi ; 
    int gecikmeGunSayisi;
    int durum;

} emanet;

 void kitapEkle()
 {
    
    system("cls");
    printf("Kitap ekleme ekranina hosgeldiniz \n");

    kitap k1;

    printf("Barkod: ");
    scanf("%d",&k1.barkod);
    printf("Kitap Adi: ");
    scanf("%s",&k1.kitapAdi);
    printf("Yazar Adi: ");
    scanf("%s",&k1.yazarAdi);
    printf("Yayin Evi: ");
    scanf("%s",&k1.yayinEvi);
    printf("Kitap Turu: ");
    scanf("%s",&k1.kitapTuru);
    printf("Temin Turu: ");
    scanf("%s",&k1.teminTuru);
    printf("Temin Tarihi: ");
    scanf("%s",&k1.teminTarihi);
    printf("Stok Sayisi: ");
    scanf("%d",&k1.stokSayisi);

    FILE *ptr = fopen("kitapKayitlari.dat","a+b");
    fwrite(&k1,sizeof(kitap),1,ptr);
    fclose(ptr);
    printf("Kitap basariyla eklendi \n");

 }


void kitapSil()
{

  system("cls");
  printf("Kitap silme ekranina hosgeldiniz \n");

  kitap k1;
  int barkod;
  int sonuc = 0;

  printf("Silmek istediginiz kitabin barkodunu giriniz: ");
  scanf("%d",&barkod);
  
  FILE *ptr = fopen("kitapKayitlari.dat","r+b");
  FILE *yptr = fopen("yedek.dat","a+b");

  while(fread(&k1,sizeof(kitap),1,ptr))
  {
      if(barkod !=k1.barkod)
      fwrite(&k1,sizeof(kitap),1,yptr);
      else
      sonuc = 1;
}

fclose(ptr);
fclose(yptr);

if(sonuc==0)
{
    printf("%d no'lu kitap bulunamadi \n",barkod);
}
else
{
    remove("kitapKayitlari.dat"); // remove silme islemi yapar !!
    rename("yedek.dat","kitaplar.dat"); // rename ile isim güncllemesi yaptım
    printf("%d no'lu kitap basariyla silindi \n",barkod);
}

}

void kitapListele()
{

    system("cls");
    printf("Kitap listeleme ekranina hosgeldiniz \n");

    kitap k1;
    int kitapSayisi = 0;
    
    FILE *ptr = fopen("kitaplar.dat","r+b");
    printf("%-10s %-20s %-20s %-20s %-20s %-20s %-20s %-20s \n","BARKOD", "KITAP_ADI", "YAZAR_ADI", "YAYIN_EVI", "KITAP_TURU", "TEMIN_TURU", "TEMIN_TARIHI", "STOK_SAYISI");
    
    while( fread(&k1,sizeof(kitap),1,ptr) !=NULL)
    {
        printf("%-10d %-20s %-20s %-20s %-20s %-20s %-20s %-20d \n",k1.barkod,k1.kitapAdi,k1.yazarAdi,k1.yayinEvi,k1.kitapTuru,k1.teminTuru,k1.teminTarihi,k1.stokSayisi);
     
     kitapSayisi=kitapSayisi+k1.stokSayisi;
     
    }

    fclose(ptr);
    
    printf("\n Toplam %d kitap bulunmaktadir \n",kitapSayisi);

    
}


void kitapIslemleri()
{
    system("cls");
    printf("Kitap islemleri ekranina hosgeldiniz \n");

    int secim;
    printf("1-Kitap Ekle \n");
    printf("2-Kitap Sil \n");
    printf("3-Kitap Listele \n");
    printf("0-Ana Menuye don \n");
    printf("Seciminiz: ");
    scanf("%d",&secim);

    switch (secim)
    {
     
     case 1:
        kitapEkle();
        break;

    case 2:
        kitapSil();
        break;

    case 3:
        kitapListele();
        break;

     case 0:
        break;

    default:
        printf("Hatali secim yaptiniz Ana Menuye yonlendiriliyorsunuz..\n");
        break;
    }

}
 
void uyeEkle()
{
       
       system("cls");
       printf("Uye ekleme ekranina hosgeldiniz \n");

       uye u1;

            printf("Tc: ");
            scanf("%s",&u1.tc);
            printf("adSoyad: ");
            scanf("%s",&u1.adSoyad);
            printf("Telefon: ");
            scanf("%s",&u1.telefon);
            printf("Eposta: ");
            scanf("%s",&u1.eposta);
            printf("Adres: ");
            scanf("%s",&u1.adres);
            printf("Uyelik Tarihi: ");
            scanf("%s",&u1.uyelikTarihi);
            printf("dogumTarihi: ");
            scanf("%s",&u1.dogumTarihi);
            printf("cinsiyet: ");
            scanf("%s",&u1.cinsiyet);

            u1.durum=0;


    FILE *ptr = fopen("uyeler.dat","a+b");
    fwrite(&u1,sizeof(uye),1,ptr);
    fclose(ptr);
    printf("Uye basariyla eklendi \n");

}

void uyeSil()
{
   
   system("cls"); 
	printf("Uye silme ekrani.... \n\n") ; 
	
	uye u1; 
	int sonuc=0; 
	char tc[20]; 
	
	printf("TC     : ") ; scanf(" %[^\n]s", tc ); 
	
	FILE * ptr= fopen("uyeler.dat", "r+b"); 
	FILE * yptr= fopen("yedek.dat", "w+b"); 
	
	
	while( fread( &u1, sizeof(uye ), 1, ptr ) != NULL   )
	{
		if(  strcmp( tc, u1.tc ) !=0  )
		fwrite ( &u1, sizeof(uye), 1, yptr ) ; 
		else
		sonuc= 1; 		
	}
	
	fclose(ptr); 
	fclose(yptr); 
	if(sonuc==0)
	{
		printf("%s TC numarali kisi kaydi  bulunamadi \n", tc  ); 
	}
	else
	{
		remove("uyeler.dat"); 
		rename("yedek.dat", "uyeler.dat"); 
		printf("%s TC numarali uye kaydi silindi \n", tc ); 
	} 	
}


void uyeListele()
{

   system("cls"); 
	printf("Uye listeleme ekrani.... \n\n") ; 
	
	uye u1; 
	int kisiSayisi=0; 	
	FILE * ptr= fopen("uyeler.dat", "r+b"); 	
	
	printf("%-20s%-30s%-20s%-20s%-20s%-30s%-20s%-30s%-20s\n", "TC", "AD-SOYAD", "CINSIYET", "DOGUM-TARIH" ,"TELEFON", "E-POSTA", "UYELIK-TARIH", "ADRES", "DURUM"  ); 
	
	while( fread( &u1, sizeof(uye ), 1, ptr ) != NULL   )
	{
	printf("%-20s%-30s%-20c%-20s%-20s%-30s%-20s%-30s%-20d\n", u1.tc, u1.adSoyad, u1.cinsiyet, u1.dogumTarihi, u1.telefon, u1.eposta,u1.uyelikTarihi, u1.adres, u1.durum );    
	
	kisiSayisi++ ; 	 
	}
	
	fclose(ptr);	
	printf("\nToplam uye sayisi : %d \n",kisiSayisi ); 	

}



void uyeIslemleri()
{
	system("cls"); 
	printf("Uye islemleri ekrani.... \n\n") ; 
	
	int secim; 
	printf("1- Uye Ekle \n"); 
	printf("2- Uye Sil \n"); 
	printf("3- Uye Listele \n"); 
	printf("0- Ana menuye don \n"); 
	printf("Seciminiz : ");  scanf("%d", &secim); 
	
	switch(secim )
	{
		case 1: uyeEkle(); break; 
		case 2: uyeSil(); break; 
		case 3: uyeListele(); break; 
		case 0: break;
		default: printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz... \n") ; break; 
	}	
}

void stokGuncelle( int barkod, int sayi  )
{	
	kitap k1; 
	int sayac=0; 		
	FILE * ptr= fopen("kitaplar.dat", "r+b"); 	
	while( fread( &k1, sizeof(kitap), 1, ptr ) != NULL   )
	{
		if( barkod == k1.barkod  )
		break; 		
		sayac++;  		
	}	
	
	rewind(ptr) ; 
	
	fseek ( ptr, (sayac) * sizeof(kitap), 0 ) ; 
	
	k1.stokSayisi += sayi; 	
	fwrite ( &k1, sizeof(kitap), 1, ptr ) ; 
	fclose(ptr); 
	printf("stok guncellendi \n")			;		
}

void emanetKitapVer() 
{
	system("cls"); 
	printf("Emanet kitap verme ekrani ... \n\n"); 
	emanet e1; 
	uye u1; 
	kitap k1; 
	int usonuc=0, ksonuc=0; 
		
	printf("TC     : "); scanf("%s", e1.uyeTC ); 
	printf("Barkod : "); scanf("%d", &e1.kitapBarkod ); 
	FILE * uptr= fopen("uyeler.dat", "r+b"); 
	while( fread( &u1, sizeof(uye ), 1, uptr ) != NULL  )
	{
		if( strcmp( e1.uyeTC, u1.tc ) ==0 )
		{
			usonuc=1; 
			break; 
		}		
	}
	fclose(uptr); 
	if(usonuc==0)
	{
		printf("%s TC numarali uye yok, ana menuye yonlendiriliyorsunuz \n", e1.uyeTC ); 
		return ; 
	}
	if(u1.durum== -1 )
	{
		printf("%s TC numarali uye YASAKLI, ana menuye yonlendiriliyorsunuz \n", e1.uyeTC ); 
		return ; 
	}	
	
	FILE * kptr= fopen("kitaplar.dat", "r+b"); 
	while( fread( &k1, sizeof(kitap ), 1, kptr ) != NULL  )
	{
		if(  e1.kitapBarkod== k1.barkod  )
		{
			ksonuc=1; 
			break; 
		}		
	}
	fclose(kptr); 
	if(ksonuc==0)
	{
		printf("%d barkod numarali kitap kaydi yok , ana menuye yonlendiriliyorsunuz \n", e1.kitapBarkod ); 
		return ; 
	}
	if( k1.stokSayisi < 1 )
	{
		printf("%d barkod numarali kitaptan stokta kalmamis ! , ana menuye yonlendiriliyorsunuz \n", e1.kitapBarkod ); 
		return ; 
	}
	
	FILE * ptr= fopen("emanetler.dat", "a+b"); 
	printf("kac gun kullanacak : "); scanf(" %d", &e1.kullandigiGunSayisi); 
	e1.teslimTarihi= time(0); 	
	fwrite ( &e1, sizeof(emanet ), 1, kptr ) ; 
	fclose(ptr); 
	printf("Emanet kaydi tamam \n"); 
	stokGuncelle( e1.kitapBarkod, -1 ); 	
	
}
void uyeGuncelle( char *tcPtr  )
{
	uye u1; 
	int sonuc=0, sayac=0; 
	
	FILE * ptr= fopen("uyeler.dat", "r+b"); 	
	
	while( fread( &u1, sizeof(uye ), 1, ptr ) != NULL   )
	{
		if(  strcmp( tcPtr, u1.tc ) ==0  )
		{
			sonuc=1; 
			break; 
		} 
		sayac++;  		
	}
	if( sonuc == 1 )
	{
	rewind(ptr); 	
	fseek ( ptr, (sayac)*  sizeof(uye), 0  ) ; 	
	u1.durum=-1; 
	fwrite ( &u1, sizeof(uye), 1, ptr ) ;	
	printf("Uye durumu guncellendi \n"); 
	} 	
	fclose(ptr); 	
}

void emanetKitabiIadeAl() 
{
	system("cls"); 
	printf("Emanet kitap IADE alma ekrani ... \n\n"); 
	emanet e1; 
	uye u1; 
	kitap k1; 
	int sonuc=0, sayac=0 ; 
	char uyeTC[20]; 
	int kitapBarkod; 
		
	printf("TC     : "); scanf(" %[^\n]s", uyeTC ); 
	printf("Barkod : "); scanf("%d", &kitapBarkod ); 
	FILE * ptr= fopen("emanetler.dat", "r+b"); 
	while( fread( &e1, sizeof( emanet ), 1, ptr ) != NULL  )
	{
		if( strcmp( e1.uyeTC, uyeTC   ) ==0 && kitapBarkod == e1.kitapBarkod   )
		{
			sonuc=1; 
			break; 
		}
		sayac++; 		
	} 	
	
	if(sonuc==0)
	{
		fclose(ptr);
		printf("%s TC veya %d barkod numarali emanet kaydi bulunamadi !\n\n", uyeTC, kitapBarkod ); 
		return ; 
	}
	else
	{
		rewind(ptr); 
	e1.iadeTarihi = time(0); 
	float saniye, dakika, saat, gun; 
	saniye= difftime( e1.iadeTarihi, e1.teslimTarihi ) ; 
	dakika= saniye/60; 
	saat= dakika/60; 
	gun= saat/24; 		
	e1.kullandigiGunSayisi =     gun; 
	printf("kullandiginiz saniye:  %.2f\n", saniye)	; 
	printf("kullandiginiz dakika:  %.2f\n", dakika)	; 
	printf("kullandiginiz saat  :  %.2f\n", saat )	; 
	printf("kullandiginiz gun   :  %.2f\n", gun)	; 
	
	e1.gecikmeGunSayisi = e1.kullandigiGunSayisi- e1.kullandigiGunSayisi; 
	
	
	if( e1.gecikmeGunSayisi > 10  )  	
		e1.durum= -1; 
	else
	e1.durum= 1; 
		
	fseek ( ptr,(sayac) *sizeof(emanet ), 0 ) ; 	
	fwrite ( &e1, sizeof(emanet ), 1, ptr ) ; 
	fclose(ptr); 
	printf("Emanet IADE kaydi tamam \n"); 
	
	
	stokGuncelle( e1.kitapBarkod, 1 );
	 	
	if(e1.durum==-1 )
	uyeGuncelle(uyeTC); 			
		
	}	
	
}
void emanettekiKitaplariListele ()
{
	system("cls")  ; 
	printf("Emanet kitap listeleme ekrani ... \n\n"); 
	emanet e1; 
	int sayac=0; 
	FILE * ptr= fopen("emanetler.dat", "r+b") ; 
	printf("%-20s%-20s%-20s%-20s\n", "TC", "BARKOD", "TARIH", "DURUM" ) ; 
	while( fread(&e1, sizeof(emanet) ,1, ptr ) !=NULL  )
	{
		struct tm *tbilgi= localtime(&e1.teslimTarihi); 
		char tarih[20]; 
		strftime( tarih, sizeof(tarih), "%d.%m.%Y", tbilgi ); 
		
		if( e1.durum==0 )
		{
			printf("%-20s%-20d%-20s%-20d\n" , e1.uyeTC, e1.kitapBarkod, tarih, e1.durum);  
			sayac++; 
		}		
	}
	fclose(ptr); 
	printf("Emanet kayit sayisi : %d \n", sayac) ; 	
}

void emanetKitapIslemleri() 
{
	system("cls"); 
	printf("Emanet Kitap islemleri ekrani.... \n\n") ; 
	
	int secim; 
	printf("1- Emanet Kitap Ver \n"); 
	printf("2- Emanet Kitabi IADE al \n"); 
	printf("3- Emanetteki Kitaplari Listele \n"); 
	printf("0- Ana menuye don \n"); 
	printf("Seciminiz : ");  scanf("%d", &secim); 
	
	switch(secim )
	{
		case 1: emanetKitapVer(); break; 
		case 2: emanetKitabiIadeAl(); break; 
		case 3: emanettekiKitaplariListele(); break; 
		case 0: break;
		default: printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz... \n") ; break; 
	}	
}

int menu()
{


     int secim; 
	printf("\n\tKUTUPHANE OTOMASYONU \n\n") ; 
	printf("\t1- KITAP ISLEMLERI \n"); 
	printf("\t2- UYE ISLEMLERI \n"); 
	printf("\t3- EMANET KITAP ISLEMLERI \n"); 
	printf("\t0- PROGRAMI KAPAT \n\n"); 	
	printf("\tSeciminiz : ");  	scanf("%d", &secim); 
	return secim; 	

}     


int main() 
{
	int secim= menu(); 
	
	while( secim != 0 )
	{
		switch(secim )
		{
			case 1: 
            kitapIslemleri(); 
            break; 

			case 2: 
            uyeIslemleri();
            break; 

			case 3: 
            emanetKitapIslemleri(); 
            break; 

			case 0: 
            break; 

			default : 
            printf("Hatali secim yapziniz  ! \n"); 			
		}
		secim= menu(); 
	}	
	
	printf("Programi kapattiniz... ") ; 

	return 0; 
}
