#include <stdio.h>
#include <stdlib.h>

struct erkezes_idopont_tipus{
    unsigned int ora,perc;
};

struct erkezes_idopont_tipus BekerVonatIdo(){
    struct erkezes_idopont_tipus ido;
    do{
        printf("Ora: (0-23) ");
        scanf("%u", &ido.ora);
    }while (ido.ora>23);
    do{
        printf("Perc: (0..59) ");
        scanf("%u", &ido.perc);
    }while (ido.perc>59);
    return ido;
};

void KiirVonatIdo(struct erkezes_idopont_tipus ido){
	printf("%02u:%02u",ido.ora, ido.perc);
}

#define VONAT_SZAM_MAX 20

struct menetrend_tipus{
    unsigned int vonatok_szama;
    struct erkezes_idopont_tipus idopontok[VONAT_SZAM_MAX];
};

struct menetrend_tipus BekerVonatok(){
    struct menetrend_tipus vonatok;
    do{
        printf("Kerem a vonatok szamat (0..%d)\n", VONAT_SZAM_MAX);
        scanf("%u", &vonatok.vonatok_szama);
    }while (vonatok.vonatok_szama>VONAT_SZAM_MAX);
    unsigned int i=0;
    while (i<vonatok.vonatok_szama){
        printf("Kerem a(z) %u. vonat erkezesi idejet! ",i+1);
        vonatok.idopontok[i] = BekerVonatIdo();
        i++;
    }
    return vonatok;
}

void KiirVonatok(struct menetrend_tipus vonatok){
    int i;
    for (i=0; i<vonatok.vonatok_szama; i++){
        printf("A(z) %u. vonat erkezesi ideje: ", i+1);
        KiirVonatIdo(vonatok.idopontok[i]);
        printf("\n");
    }
}

int main()
{
    struct menetrend_tipus v;
    v = BekerVonatok();
    KiirVonatok(v);
    return 0;
}
