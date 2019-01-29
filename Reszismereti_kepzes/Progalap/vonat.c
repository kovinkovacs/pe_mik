#include <stdio.h>

struct vonat_ido_tipus{
	unsigned int ora;
	unsigned int perc;
};

struct vonat_ido_tipus bekerVonatIdo(){
	struct vonat_ido_tipus ido;
	do{
		printf("Ora (0-23): ");
		scanf("%u",&ido.ora);
	}while (ido.ora>23);
	do{
		printf("Perc (0-59): ");
		scanf("%u",&ido.perc);
	}while (ido.perc>59);
	return ido;
}

void kiirVonatIdo(struct vonat_ido_tipus ido){ //23:45 formatumban
	//printf("%u:%u",ido.ora, ido.perc);
	printf("%02u",ido.ora);
	printf(":");
	printf("%02u", ido.perc);
}

unsigned int VonatIdoPercben(struct vonat_ido_tipus ido){
	return ido.ora*60+ido.perc;
}

#define VONATOK_MAX_SZAMA 20

struct vonatok_tipus {
	unsigned int vonatok_szama;
	struct vonat_ido_tipus vonat_idok[VONATOK_MAX_SZAMA];
};

struct vonatok_tipus bekerVonatok(){
	struct vonatok_tipus vonatok;
	do{
		printf("Kerem a vonatok szamat (0..%d): ",VONATOK_MAX_SZAMA);
		scanf("%u", &vonatok.vonatok_szama);
	}while (vonatok.vonatok_szama>VONATOK_MAX_SZAMA);
		//for(unsigned int i=0;i<vonatok.vonatok_szama;i++)
	unsigned int i=0;
	while (i<vonatok.vonatok_szama){
		printf("Kerem a %u. vonat erkezesi idejet:\n",i+1);
		vonatok.vonat_idok[i]=bekerVonatIdo();
		i++;
	}
	return vonatok;
}

void kiirVonatok(struct vonatok_tipus vonatok){
	//for(unsiged int i=0;i<vonatok.vonatok_szama;i++)
	int i;
	i=0;
	while(i<vonatok.vonatok_szama){
		printf("A %u. vonat erkezesi ideje: ",i+1);
		kiirVonatIdo(vonatok.vonat_idok[i]);
		printf("\n");
		i++;
	}
}

unsigned int LegkorabbiVonatSorszama(struct vonatok_tipus vonatok){
	unsigned int legkorabbi_sorszama=0;
	//for(unsiged int i=1;i<vonatok.vonatok_szama;i++)
	int i;
	i=1;
	while(i<vonatok.vonatok_szama){
		if (VonatIdoPercben(vonatok.vonat_idok[i])<
			VonatIdoPercben(vonatok.vonat_idok[legkorabbi_sorszama]))
			legkorabbi_sorszama=i;
		i++;
	}
	return legkorabbi_sorszama;
}

unsigned int LegkesobbiVonatSorszama(struct vonatok_tipus vonatok){
	unsigned int legkesobbi_sorszama=0;
	//for(unsiged int i=1;i<vonatok.vonatok_szama;i++)
	int i;
	i=1;
	while(i<vonatok.vonatok_szama){
		if (VonatIdoPercben(vonatok.vonat_idok[i])>
			VonatIdoPercben(vonatok.vonat_idok[legkesobbi_sorszama]))
			legkesobbi_sorszama=i;
		i++;
	}
	return legkesobbi_sorszama;
}

int main(){
	struct vonatok_tipus v;
	v=bekerVonatok();
	kiirVonatok(v);
	printf("A legkorabbi vonat sorszama: %u\n",
			LegkorabbiVonatSorszama(v)+1);
	printf("A baketer munkaideje percben: %u\n",
			VonatIdoPercben(
			 v.vonat_idok[LegkesobbiVonatSorszama(v)])-
			VonatIdoPercben(
			 v.vonat_idok[LegkorabbiVonatSorszama(v)]));
	return 0;
}
