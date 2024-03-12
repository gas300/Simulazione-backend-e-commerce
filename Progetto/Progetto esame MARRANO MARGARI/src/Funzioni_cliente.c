/*
 * Funzioni_cliente.c
 *
 *  Created on: 26 giu 2021
 *      Author: Gabriele
 */


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "Strutture.h"
#include "Algoritmi_fondamentali.h"

void acquista_prodotto (FILE* file_prod, FILE* file_ord)
{
	int seed = time(NULL), i = 0;
	prodotti_t* risultati_ricerca =  NULL;
	ordini_t ordine = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	prodotti_t prodotto = { 0, 0, 0, 0, 0, ""};
	bool flag = 0;

	//CHIAMATA ALLA FUNZIONE RICERCA
	risultati_ricerca = ricerca (file_prod);

	//COMPILAZIONE ORDINE
	srand (seed);
	ordine.codice_ord =  rand() % 1001 + 1000 ;
	ordine.codice_prod = (risultati_ricerca)->codice_prod;
	ordine.stato = 0;

	for (i=0; i<LUNGH_NOME_PROD; i++)
	{
		ordine.nome_prod[i] = ((risultati_ricerca)->nome_prod[i]);
	}

	//CONTROLLO DISPONIBILITA' QUANTITA
	flag = 0;
	while (flag == 0)
	{
		flag = 1;
		printf ("\n Inserisci la quantita desiderata : ");
		scanf ("%d", &ordine.quantita);
		if ( ordine.quantita > (risultati_ricerca)->quantita_disp )
		{
			flag = 0;
			printf ("\n !!! ERRORE, quantita' non disponibile , la quantita' disponibile per questo prodotto e' attualmente di : %d pezzi \n ", (risultati_ricerca)->quantita_disp );
		}
	}

	ordine.prezzo = ( (risultati_ricerca)->prezzo ) * ordine.quantita;

	printf (" Inserisci il tuo numero di cellulare : ");
	scanf ("%d", &ordine.num_cell);

	//CONTROLLO INSERIMENTO CITTA
	flag = 0;
	while ( flag == 0 )
	{
		flag = 1;
		printf (" Scegli la tua citta inserendo in base al numero corrispondente :  ");
		printf ("\n 1) Roma \n 2) Napoli \n 3) Milano \n 4) Torino \n 5) Bari\n Inserimento : ");
		scanf ("%u", &ordine.citta);
		if (ordine.citta < 1 || ordine.citta > 5 )
		{
			flag = 0;
			printf ("\n !!! ERRORE, inserimento non valido, riprova !!! \n\n");
		}
	}


	printf (" Inserisci il tuo nome : ");
	scanf ("%19s", ordine.cliente);

	printf (" Inserisci l'indirizzo di spedizione : ");
	scanf ("%29s", ordine.indirizzo);

	//AGGIORNAMENTO QUANTITA PRODOTTO
	rewind (file_prod);
	fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
	flag = 0;
	while ( flag == 0 )
	{
		if (prodotto.codice_prod == (risultati_ricerca)->codice_prod)
		{
			prodotto.quantita_disp = prodotto.quantita_disp - ordine.quantita;
			prodotto.quantita_vend = prodotto.quantita_vend + ordine.quantita;
			fseek (file_prod, (-1)*sizeof (prodotti_t), SEEK_CUR );
			fwrite (&prodotto, sizeof(prodotti_t), 1, file_prod);
			flag = 1;
		}
		else
		{
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		}
	}

	//SCRITTURA ORDINE NEL FILE
	rewind (file_ord);
	fseek (file_ord, (0)*sizeof (ordini_t), SEEK_END );
	fwrite (&ordine, sizeof(ordini_t), 1, file_ord);

	//SCRITTURA ORDINI A SCHERMO
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n ORDINI :\n");
	rewind (file_ord);
	fread (&ordine, sizeof(ordini_t), 1, file_ord);
	i = 0;
	while (!feof(file_ord))
	{
		printf ("\n %d) \t Nome prodotto : %-19s \t Codice ordine : %d\tPrezzo : %.2f $",i+1, ordine.nome_prod, ordine.codice_ord, ordine.prezzo);
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
		i++;
	}
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
	printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
}

void modifica_ordine (FILE* file_prod, FILE* file_ord)
{
	int scelta_visualizzazione = 0;
	ordini_t* array_ricerca =  NULL;
	ordini_t ordine = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	ordini_t ordine_nullo = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	bool flag = 0;
	int i = 0;
	char cliente [LUNGH_NOME_CLIENTE] = "";

	//RICERCA PER NOME CLIENTE
	//CALCOLO MEMORIA STRETTAMENTE NECESSARIA AL PUNTATORE array_ricerca
	while (flag == 0)
	{
		rewind (file_ord);
		printf ("\n Inserisci il tuo nome : ");
		scanf ("%19s", cliente);
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
		while ( !feof(file_ord) )
		{
			if ( strcmp(ordine.cliente ,cliente) == 0 )
			{
				i++;
				flag = 1;
			}
			fread (&ordine, sizeof(ordini_t), 1, file_ord);
		}

		//ALLOCAZIONE MEMORIA AL PUNTATORE array_ricerca
		if (i!=0)
		{
			array_ricerca = (ordini_t*) calloc(i+1, sizeof(ordini_t));
			i = 0;

			//RICERCA PER NOME CLIENTE E RIEMPIMENTO MEMORIA DEL PUNTATORE array_ricerca
			while (i == 0)
			{
				rewind (file_ord);
				fread (&ordine, sizeof(ordini_t), 1, file_ord);
				while ( !feof(file_ord) )
				{
					if ( strcmp(ordine.cliente ,cliente) == 0 )
					{
						*(array_ricerca + i) = ordine;
						i++;
						flag = 1;
					}
					fread (&ordine, sizeof(ordini_t), 1, file_ord);
				}
			}
		}
	}

		//VISUALIZZAZIONE ORDINI
		i = 0;
		printf ("\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while ( (array_ricerca + i)->codice_ord != 0)
		{
			printf ("\n %d) Prodotto : %-19s Quantita' ordine : %d\t\t\t Prezzo : %.2f $", i+1, (array_ricerca + i)->nome_prod, (array_ricerca + i)->quantita, (array_ricerca + i)->prezzo);
			switch ( (array_ricerca+i)->stato)
			{
			case 0:		printf ("\t stato ordine : 'da consegnare'\n");
			break;
			case 1:		printf ("\t stato ordine : 'in transito'\n");
			break;
			case 2:		printf ("\t stato ordine : 'consegnato'\n");
			break;
			}
			i++;
		}
		printf ("\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------");

		//SCELTA ORDINE
		flag = 0;
		while (flag == 0)
		{
			printf ("\n Scegli un ordine inserendo il numero corrispondente posto di fianco al prodotto : ");
			scanf ("%d", &scelta_visualizzazione);
			if (scelta_visualizzazione < 1 || scelta_visualizzazione > i )
			{
				printf ("\n !!! ERRORE, valore inserito non valido, riprova !!!");
			}
			else
			{
				flag = 1;
			}
			if ( (array_ricerca+scelta_visualizzazione-1)->stato == 0)
			{
				flag = 1;
			}
			else
			{
				printf ("\n !!! ERRORE, valore inserito non valido, riprova !!!");
			}
		}

		printf ("\n Inserisci la quantita' aggiornata del tuo ordine ( Inserisci 0 per cancellare l'ordine ) : ");
		scanf ("%d", &(array_ricerca+scelta_visualizzazione-1)->quantita);


		// AGGIORNAMENTO QUANITA PRODOTTI DISPONIBILI E VENDUTI
		if ( (array_ricerca+scelta_visualizzazione-1)->quantita == 0 )
		{
			//SCRITTURA ORDINE NULLO NEL FILE
			flag = 0;
			rewind (file_ord);
			fread (&ordine, sizeof(ordini_t), 1, file_ord);
			while ( flag == 0 )
			{
				if (ordine.codice_ord == (array_ricerca+scelta_visualizzazione-1)->codice_ord )
				{
					fseek (file_ord, (-1)*sizeof (ordini_t), SEEK_CUR );
					fwrite (&ordine_nullo, sizeof(ordini_t), 1, file_ord);
					flag = 1;
				}
				else
				{
					fread (&ordine, sizeof(ordini_t), 1, file_ord);
				}
			}
		}
		else
		{
			//SCRITTURA ORDINE NEL FILE
			flag = 0;
			rewind (file_ord);
			fread (&ordine, sizeof(ordini_t), 1, file_ord);
			while ( flag == 0 )
			{
				if (ordine.codice_ord == (array_ricerca+scelta_visualizzazione-1)->codice_ord )
				{
					ordine.prezzo = (ordine.prezzo/ordine.quantita) * (array_ricerca+scelta_visualizzazione-1)->quantita;
					ordine.quantita = (array_ricerca+scelta_visualizzazione-1)->quantita;
					fseek (file_ord, (-1)*sizeof (ordini_t), SEEK_CUR );
					fwrite (&ordine, sizeof(ordini_t), 1, file_ord);
					flag = 1;
				}
				else
				{
					fread (&ordine, sizeof(ordini_t), 1, file_ord);
				}
			}
		}
		//SCRITTURA ORDINI A SCHERMO
		i = 0;
		printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n ORDINI :\n");
		rewind (file_ord);
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
		while (!feof(file_ord))
		{
			printf ("\n %d) Prodotto : %-19s Codice ordine : %d\t\t\t Prezzo : %.2f $\t\t N. articoli : %d",i+1, ordine.nome_prod, ordine.codice_ord, ordine.prezzo, ordine.quantita);
			i++;
			fread (&ordine, sizeof(ordini_t), 1, file_ord);
		}
		printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
		printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
}
