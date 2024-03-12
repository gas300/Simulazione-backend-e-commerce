/*
 * Menu.c
 *
 *  Created on: 26 giu 2021
 *      Author: Gabriele
 */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Strutture.h"
#include "Funzioni_operatore.h"


int menu_gen()
{
	int scelta_menu_gen = 0;

	//VISUALIZZA MENU GENERALE
	printf ("\n\n \t\t\t\t\t---------------------------");
	printf ("\n \t\t\t\t\t|\t\t          |");
	printf ("\n \t\t\t\t\t|\t   MENU           |");
	printf ("\n \t\t\t\t\t|\t\t          |");
	printf ("\n \t\t\t\t\t---------------------------\n\n");

	while (scelta_menu_gen == 0)
	{
		printf ("\n Inserisci :\n 1) Per accedere al lato cliente\n 2) Per accedere al lato operatore\n 3) Per terminare il programma\n Inserimento : ");
		scanf ("%d", &scelta_menu_gen);

		if (scelta_menu_gen < 1|| scelta_menu_gen > 3)
		{
			printf ("\n !!! ERRORE, inserimento non valido, riprova !!!");
			scelta_menu_gen = 0;
		}
	}
	return (scelta_menu_gen);
}

int menu_op()
{
	int scelta_menu_op = 0;

	//VISUALIZZA MENU OPERATORE
	printf ("\n\n \t\t\t\t\t--------------------------------------");
		printf ("\n \t\t\t\t\t|\t\t\t             |");
		printf ("\n \t\t\t\t\t|\t   MENU OPERATORE            |");
		printf ("\n \t\t\t\t\t|\t\t\t             |");
		printf ("\n \t\t\t\t\t--------------------------------------\n\n");

	while (scelta_menu_op == 0)
	{
		printf ("\n Inserisci :\n 1) Per inserire un prodotto\n 2) Per la ricerca e gestione di un ordine\n 3) Per visualizzare le statistiche\n 4) Per terminare il lato operatore\n Inserimento : ");
		scanf ("%d", &scelta_menu_op);

		if (scelta_menu_op < 1|| scelta_menu_op > 4)
		{
			printf ("\n !!! ERRORE, inserimento non valido, riprova !!!");
			scelta_menu_op = 0;
		}
	}
	return (scelta_menu_op);
}

int menu_cli()
{
	int scelta_menu_cli = 0;

	//VISUALIZZA MENU CLIENTE
	printf ("\n\n \t\t\t\t\t----------------------------------");
		printf ("\n \t\t\t\t\t|\t\t                 |");
		printf ("\n \t\t\t\t\t|\t   MENU CLIENTE          |");
		printf ("\n \t\t\t\t\t|\t\t                 |");
		printf ("\n \t\t\t\t\t----------------------------------\n\n");

	while (scelta_menu_cli == 0)
	{
		printf ("\n Inserisci :\n 1) Per acquistare un prodotto\n 2) Per modificare un ordine\n 3) Per terminare il lato cliente\n Inserimento : ");
		scanf ("%d", &scelta_menu_cli);

		if (scelta_menu_cli < 1|| scelta_menu_cli > 3)
		{
			printf ("\n !!! ERRORE, inserimento non valido, riprova !!!");
			scelta_menu_cli = 0;
		}
	}
	return (scelta_menu_cli);
}

void lato_op ()
{
	char password_input [LUNGH_PASSWORD] = "";
	bool flag = 0;

	//CONTROLLO PASSWORD
	while (flag == 0)
	{
		printf ("\n Inserisci la password per accedre al lato operatore : ");
		scanf ("%19s", password_input);
		if ( strcmp (password_input, "30&lode") == 0)
		{
			flag = 1;
		}
		else
		{
			printf ("\n !!! PASSWORD ERRATA, riprova !!!");
		}
	}
}

void menu_statistica(FILE* file_prod, FILE* file_ord)
{
	int scelta_menu_statistica = 0;
	bool flag = 0;
	while (flag == 0)
	{
		scelta_menu_statistica = 0;
		while (scelta_menu_statistica == 0)
		{
			printf ("\n Inserisci :\n 1) Per visualizzare il numero di ordini in ogni citta' \n 2) Per visualizzare gli ordini più costosi \n 3) Per visualizzare il numero di pezzi venduti per ogni prodotto\n 4) Per visualizzare la grandezza degli ordini in termini di quantita'\n 5) Per tornare al lato operatore\n Inserimento : ");
			scanf ("%d", &scelta_menu_statistica);

			if (scelta_menu_statistica < 1|| scelta_menu_statistica > 5)
			{
				printf ("\n !!! ERRORE, inserimento non valido, riprova !!!");
				scelta_menu_statistica = 0;
			}
		}

		switch (scelta_menu_statistica)
		{
		case 1:		statistica_citta (file_ord);
		break;
		case 2:		statistica_prezzo (file_ord);
		break;
		case 3:		statistica_quantita_vendute (file_prod);
		break;
		case 4:		statistica_quantita_ordini (file_ord);
		break;
		case 5:		flag = 1;
		break;
		}
	}
}
