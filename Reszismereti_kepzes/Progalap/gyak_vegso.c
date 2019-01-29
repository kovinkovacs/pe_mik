#include <stdio.h>

struct erkezes_idopont_tipus{
    int ora;
    int perc;
};

#define VONATOK_MAX_SZAMA 20

struct menetrend_tipus{
    int vonatok_szama;
    struct erkezes_idopont_tipus idopontok [VONATOK_MAX_SZAMA];
};

void kiirVonatIdo(struct erkezes_idopont_tipus ido){
    printf("%02u:%02u",ido.ora,ido.perc);
}

void kiirVonatok(struct menetrend_tipus vonatok){
    int i=0;
    while (i<vonatok.vonatok_szama){
        if (vonatok.idopontok[i].ora>23 || vonatok.idopontok[i].perc>59) break;
        printf("A %u. vonat erkezesi ideje: ",i+1);
		kiirVonatIdo(vonatok.idopontok[i]);
		printf("\n");
		i++;
    }
}

struct menetrend_tipus BekerVonatok(){
    struct erkezes_idopont_tipus ido;
    struct menetrend_tipus vonatok;

    do{
        printf("Kérem a vonatok szamat 0..%d: ", VONATOK_MAX_SZAMA);
        scanf("%d",&vonatok.vonatok_szama);
    }while (vonatok.vonatok_szama>VONATOK_MAX_SZAMA);
    int i=0;
    while (i<vonatok.vonatok_szama){
        printf("Kerem az %d. vonat erkezesi idejet!\n", i+1);
        printf("Ora: ");
        scanf("%d",ido.ora);
        if (ido.ora == -1) break;
        printf("Perc: ");
        scanf("%d",vonatok.idopontok[i].perc);
        vonatok.idopontok[i]=ido;
        i++;
    }
    return vonatok;
}



int main(){
    struct menetrend_tipus m;
    m=BekerVonatok();
    kiirVonatok(m);
    return 0;
}
