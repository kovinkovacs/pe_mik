#include <stdio.h>

// Kiegészítések a feladathoz képest:
//	A járatszám csak 0-nál nagyobb lehet.
//	Egy megálló-szám csak egyszer szerepelhet.
//	Vagy mégjobb: csak növekvõ sorrendben jöhessenek a megállók számai.
//	Beolvasásnál is figyeljük az utasok számát, és egy megállónál se szálhasson le több, mint amennyi fent van.

#define MAXMERET 12

typedef struct megallo
{
	unsigned int megallo_szam;
	unsigned int felszallok;
	unsigned int leszallok;
} Megallo;

typedef struct jarat
{
	int jaratszam;
	Megallo tomb[MAXMERET];
	int megallo_darab;
} Jarat;

Jarat jaratBeolvas()
{
	Jarat j;

	printf("Jaratszam: ");
	scanf("%d", &j.jaratszam);
	while (j.jaratszam<=0)
	{
		printf("A jaratszam csak 0-nal nagyobb lehet!\n");
		printf("Jaratszam: ");
		scanf("%d", &j.jaratszam);
	}


	int i=0;
	unsigned int megallo_szam;
	do
	{
		printf("\n");
		printf("Megallo: ");
		scanf("%u", &megallo_szam);
		if (megallo_szam!=0)
		{
			j.tomb[i].megallo_szam=megallo_szam;
			printf("Felszallok: ");
			scanf("%u", &j.tomb[i].felszallok);
			printf("Leszallok: ");
			scanf("%u", &j.tomb[i].leszallok);
			i++;
		}
	} while (megallo_szam!=0 && i<MAXMERET);
	j.megallo_darab=i;

	return j;
}

Jarat jaratBeolvasExtra()
{
	Jarat j;

	printf("Jaratszam: ");
	scanf("%d", &j.jaratszam);
	while (j.jaratszam<=0)
	{
		printf("A jaratszam csak 0-nal nagyobb lehet!\n");
		printf("Jaratszam: ");
		scanf("%d", &j.jaratszam);
	}


	int i=0;
	unsigned int megallo_szam;
	// A sorrendeshez
	unsigned int elozo=0;
	// Az utasszámláshoz
	unsigned int osszutas=0;
	do
	{
		printf("\n");

//		// Ne legyen kettõ egyforma megálló azonosító!!
//		int ok=0;
//		do
//		{
//			printf("Megallo: ");
//			scanf("%u", &megallo_szam);
//			int k=0;
//			// Van-e már ilyen a tömbben?
//			while (k<i && j.tomb[k].megallo_szam
//							!=megallo_szam)
//			{
//				k++;
//			}
//			// Ha nincs, akkor ez a szám ok
//			if (k==i)
//				ok=1;
//			else
//			{
////				ok=0;
//				printf("Az azonosito mar letezik!\n");
//			}
//		} while (ok==0);

		// Csak növekvõ sorrendben jöhessenek!!
		do
		{
			printf("Megallo: ");
			scanf("%u", &megallo_szam);
			// Akkor rossz, ha nem 0, nem az elsõ, és nem nagyobb mint az elõzõ
//			if (megallo_szam!=0 && i>0 &&
//					megallo_szam <=
//					j.tomb[i-1].megallo_szam)
			if (megallo_szam!=0 &&
				megallo_szam<=elozo)
			{
				printf("Csak az elozonel nagyobb lehet!\n");
			}
//		} while(megallo_szam!=0 && i>0 &&
//					megallo_szam <=
//					j.tomb[i-1].megallo_szam);
		} while (megallo_szam!=0 &&
				 megallo_szam<=elozo);
		elozo=megallo_szam;

		if (megallo_szam!=0)
		{
			j.tomb[i].megallo_szam=megallo_szam;
			printf("Felszallok: ");
			scanf("%u", &j.tomb[i].felszallok);
			// Ne szállhasson le több, mint amennyi van
			printf("Leszallok: ");
			scanf("%u", &j.tomb[i].leszallok);
			while (osszutas < j.tomb[i].leszallok)
			{
				printf("Nincsenek ennyien a buszon!\n");
				printf("Leszallok: ");
				scanf("%u", &j.tomb[i].leszallok);
			}

			// Frissítsük hogy mennyi van.
			osszutas-=j.tomb[i].leszallok;
			osszutas+=j.tomb[i].felszallok;
			i++;
		}
	} while (megallo_szam!=0 && i<MAXMERET);
	j.megallo_darab=i;

	return j;
}

void jaratKiir(Jarat j)
{
	printf("A %d jarat utasai:\n", j.jaratszam);
	int i;
	for (i=0; i<j.megallo_darab; i++)
	{
		printf("%u. megallo: %u fel, %u le.\n",
			   j.tomb[i].megallo_szam,
			   j.tomb[i].felszallok,
			   j.tomb[i].leszallok);
	}
}

int main()
{
	Jarat egyjarat;
//	egyjarat=jaratBeolvas();
	egyjarat=jaratBeolvasExtra();
	printf("\n\n");
	jaratKiir(egyjarat);

	printf("\n\n");
	printf("Se felszallo, se leszallo:\n");
	int i;
	for (i=0; i<egyjarat.megallo_darab; i++)
	{
		if (egyjarat.tomb[i].felszallok==0 &&
			egyjarat.tomb[i].leszallok==0)
		{
			printf("%u. megallo\n",
				   egyjarat.tomb[i].megallo_szam);
		}
	}

	printf("\n\n");
	int utasszam=0;
	int maxutasidx=0;
	int maxutas=0;
	for (i=0; i<egyjarat.megallo_darab-1; i++)
	{
		utasszam-=egyjarat.tomb[i].leszallok;
		utasszam+=egyjarat.tomb[i].felszallok;
//		printf("%u. utan: %d utas\n",
//			   egyjarat.tomb[i].megallo_szam,
//			   utasszam);
		if (utasszam > maxutas)
		{
			maxutas=utasszam;
			maxutasidx=i;
		}
	}

	printf("A legtobben a %u es a %u megallo kozott voltak (%d utas).\n",
		   egyjarat.tomb[maxutasidx].megallo_szam,
		   egyjarat.tomb[maxutasidx+1].megallo_szam,
		   maxutas);


//	Megallo tomb[MAXMERET];
//	int megallo_darab=0;
//	int jaratszam;
//	printf("Jaratszam: ");
//	scanf("%d", &jaratszam);

//	int i=0;
//	int beolvasas=1;

//	for (i=0; i<MAXMERET && beolvasas==1; i++)
//	{
//		printf("\n");
//		printf("Megallo: ");
//		scanf("%u", &tomb[i].megallo_szam);
//		if (tomb[i].megallo_szam!=0)
//		{
//			printf("Felszallok: ");
//			scanf("%u", &tomb[i].felszallok);
//			printf("Leszallok: ");
//			scanf("%u", &tomb[i].leszallok);
//			megallo_darab++;
//		}
////		else break;
////		else i=MAXMERET;
//		else
//			beolvasas=0;
//	}

//	i=0;
//	unsigned int megallo_szam;
//	do
//	{
//		printf("\n");
//		printf("Megallo: ");
//		scanf("%u", &megallo_szam);
//		if (megallo_szam!=0)
//		{
//			tomb[i].megallo_szam=megallo_szam;
//			printf("Felszallok: ");
//			scanf("%u", &tomb[i].felszallok);
//			printf("Leszallok: ");
//			scanf("%u", &tomb[i].leszallok);
//			i++;
//		}
//	} while (megallo_szam!=0 && i<MAXMERET);
//	megallo_darab=i;

//	printf("\n\n");
//	printf("A %d jarat utasai:\n", jaratszam);
//	for (i=0; i<megallo_darab; i++)
//	{
//		printf("%u. megallo: %u fel, %u le.\n",
//			   tomb[i].megallo_szam,
//			   tomb[i].felszallok,
//			   tomb[i].leszallok);
//	}


	return 0;
}