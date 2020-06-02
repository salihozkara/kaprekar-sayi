#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int kacBasamakli(int);
int kaprekarMi(int);
void siralama(int,int,int**);
void siralama2(int,int,int**);
void kontrol(int,int,int**);
void transpoze(int,int,int**);
void matrisyap(int,int,int***);
void matrisGeriVer(int,int**);
void matrisDosyaYaz(int,int,int**);
int main() {
    int sutun,satir,**matris;
    printf("satir degeri:");
    scanf("%d",&satir);
    printf("sutun degeri:");
    scanf("%d",&sutun);
    srand(time(NULL));
    matrisyap(satir,sutun,&matris);
    siralama(satir,sutun,matris);
    siralama2(satir,sutun,matris);
    kontrol(sutun,satir,matris);
    matrisDosyaYaz(satir,sutun,matris);
    transpoze(sutun,satir,matris);
    matrisGeriVer(satir,matris);
    return 0;
}
void matrisyap(int satir,int sutun,int ***matris)
{
    *matris=(int **)malloc(satir*sizeof(int));
    if(*matris==NULL) {
        printf("yer ayrilamadi!\n");
        system("pause");
        exit(1);
    }
    for (int i = 0; i <satir ; ++i) {
        *(*matris+i)= (int*)malloc(sizeof(int)*sutun);
        if(*(*matris+i)==NULL)
        {
            printf("yer ayrilamadi!\n");
            system("pause");
            exit(1);
        }
    }
    for (int i = 0; i <satir ; ++i) {
        for (int j = 0; j <sutun ; ++j) {
            *(*(*matris+i)+j)=5+rand()%39995;
        }
    }
}
void matrisDosyaYaz(int satir,int sutun,int **matris)
{
    FILE *dosya;
    dosya=fopen("transpoze.txt","w");
    for (int i = 0; i <satir ; ++i) {
        for (int j = 0; j <sutun ; ++j) {
            fprintf(dosya,"%d",*(*(matris+i)+j));
            for (int k = 0; k < 6-kacBasamakli(*(*(matris+i)+j)); ++k) {
                fprintf(dosya," ");
            }
        }
        fprintf(dosya,"\n");
    }
    for (int l = 0; l <sutun ; ++l) {
        fprintf(dosya,"------");
    }
    fclose(dosya);
    printf("matris yazma islemi tamamlandi!\n");
}
void matrisGeriVer(int satir,int **matris)
{
    for (int i = 0; i <satir ; ++i) {
        free(*matris+i);
    }
    free(matris);
}

int kacBasamakli(int sayi)
{
    int kacBasamak=0;
    do{
        sayi= sayi / 10;
        kacBasamak++;
    }while(sayi >= 1) ;
    return kacBasamak;
}
int kaprekarMi(int sayi)
{
    int karesi=sayi*sayi;
    for (int i = 1; i <kacBasamakli(karesi) ; ++i) {
        int bolen=10;
        for (int j = 1; j <i ; ++j) {
            bolen*=10;
        }
        if(sayi==bolen)
            return 0;
        if(karesi/bolen+karesi%bolen==sayi)
            return 1;
    }
    return 0;
}
void siralama(int satir,int sutun,int **matris) {
    for (int j = 0; j <satir ; ++j) {
        for (int k = 0; k < sutun; ++k) {
            for (int i = 0; i < sutun-1; ++i) {
                int tut;
                if (*(*(matris+j)+i) > *(*(matris+j)+(i + 1))) {
                    tut = *(*(matris+j)+i);
                    *(*(matris+j)+i) = *(*(matris+j)+(i + 1));
                    *(*(matris+j)+(i + 1)) = tut;
                }
            }
        }
    }
}
void siralama2(int satir,int sutun,int **matris)
{
    int tut;
    for (int i = 0; i <sutun ; ++i) {
        for (int j = 0; j <satir ; ++j) {
            for (int k = 0; k <satir-1 ; ++k) {
                if(*(*(matris+k)+i)>*(*(matris+(k+1))+i))
                {
                    tut=*(*(matris+k)+i);
                    *(*(matris+k)+i)=*(*(matris+(k+1))+i);
                    *(*(matris+(k+1))+i)=tut;
                }
            }
        }
    }
}

void kontrol(int sutun,int satir,int **matris)
{
    FILE *dosya;
    dosya=fopen("kaprekare.txt","w");
    int sayac=0;
    for (int i = 0; i <satir ; ++i) {
        for (int j = 0; j <sutun ; ++j) {
            if(kaprekarMi(*(*(matris+i)+j)))
            {
                sayac++;
                fprintf(dosya, "%d\t", *(*(matris+i)+j));
            }
        }
    }
    if(sayac==0) {
        printf("kaprekar sayi yok\n");
        fprintf(dosya, "kaprekar sayi yok\n");
    }
    fclose(dosya);
}
void transpoze(int sutun,int satir,int **matris)
{
    FILE *fp;
    fp=fopen("transpoze.txt", "a");
    fprintf(fp, "\n");
    for (int j = 0; j <sutun ; ++j) {
        for (int i = 0; i <satir ; ++i) {
            fprintf(fp, "%d", *(*(matris + i) + j));
            for (int k = 0; k < 6-kacBasamakli(*(*(matris+i)+j)); ++k) {
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("transpoze yazma islemi tamamlandi!\n");
    system("pause");
}
