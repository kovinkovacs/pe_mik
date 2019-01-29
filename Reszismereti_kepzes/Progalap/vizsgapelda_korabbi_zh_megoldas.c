#include <stdio.h>
#include <string.h>

#define MAXMERET 8

typedef struct diak
{
	char becenev[21];
	unsigned int orszag, korzet, telefonszam;
} Diak;

typedef struct diakok
{
	unsigned int darab;
	Diak tomb[MAXMERET];
} Diakok;

Diakok TaborBeker()
{
	Diakok tabor;
	tabor.darab=0;
	char nev[21];
	/*
	scanf("%s", nev);
	while (nev[0]!='*')
	{


		scanf("%s", nev);
	}*/
	do
	{
		printf("\nAdja meg a diak becenevet (ha nincs tobb, akkor: *): ");
		scanf("%s", nev);
		if (nev[0]!='*')
		{
			strcpy(tabor.tomb[tabor.darab].becenev, nev);
			printf("Telefonszam orszag hivoszama: ");
			scanf("%u", &tabor.tomb[tabor.darab].orszag);
			printf("Telefonszam korzetszama: ");
			scanf("%u", &tabor.tomb[tabor.darab].korzet);
			printf("Telefonszam korzeten beluli szama: ");
			scanf("%u", &tabor.tomb[tabor.darab].telefonszam);
			tabor.darab++;
		}
	} while (nev[0]!='*' && tabor.darab<MAXMERET);

	printf("\nKoszonom!\n\n");
	return tabor;
}

void TaborKiir(Diakok tabor)
{
	printf("A diakok es telefonszamuk:\n");
	unsigned int i;
	for (i=0; i<tabor.darab; i++)
	{
		 printf("%s: +%u-%u-%u\n", tabor.tomb[i].becenev, tabor.tomb[i].orszag, tabor.tomb[i].korzet, tabor.tomb[i].telefonszam);
	}
}

void EgyesultAllamok(Diakok tabor)
{
	printf("\nDiakok az Egyesult Allamokbol:\n");
	unsigned int i;
	for (i=0; i<tabor.darab; i++)
	{
		if (tabor.tomb[i].orszag==1)
		{
			printf("%s\n", tabor.tomb[i].becenev);
		}
	}
}
unsigned HivoszamDarab(Diakok tabor, unsigned int orszag)
{
	unsigned int i, darabszam=0;
	for (i=0; i<tabor.darab; i++)
	{
		if (tabor.tomb[i].orszag==orszag)
			darabszam++;
	}
	return darabszam;
}

void LeggyakoribbOrszag(Diakok tabor)
{
	unsigned int i;
	unsigned int maxdarab=0;
	unsigned int maxhivoszam=0;
	for (i=0; i<tabor.darab; i++)
	{
		unsigned int osszesen;
		osszesen=HivoszamDarab(tabor,tabor.tomb[i].orszag);
		if (osszesen>maxdarab)
		{
			maxdarab=osszesen;
			maxhivoszam=tabor.tomb[i].orszag;
		}
	}
	printf("\nLeggyakrabb orszag hivoszam: %d\n", maxhivoszam);
}

void TobbLeggyakoribbOrszag(Diakok tabor)
{
	unsigned int i;
	unsigned int maxdarab=0;
	unsigned int maxhivoszam=0;
	for (i=0; i<tabor.darab; i++)
	{
		unsigned int osszesen;
		osszesen=HivoszamDarab(tabor,tabor.tomb[i].orszag);
		if (osszesen>maxdarab)
		{
			maxdarab=osszesen;
			maxhivoszam=tabor.tomb[i].orszag;
		}
	}
	printf("\nLeggyakrabb orszag hivoszamok:");
	for (i=0; i<tabor.darab; i++)
	{
		unsigned int osszesen;
		osszesen=HivoszamDarab(tabor,tabor.tomb[i].orszag);
		if (osszesen==maxdarab/* && tabor.tomb[i].orszag!=maxhivoszam*/)
		{
			printf(" %d", tabor.tomb[i].orszag);
		}
	}
	printf("\n");
}

int main()
{
	Diakok tabor;
	tabor=TaborBeker();
	TaborKiir(tabor);
	EgyesultAllamok(tabor);
	LeggyakoribbOrszag(tabor);
	TobbLeggyakoribbOrszag(tabor);
	return 0;
}