/*
 * Funzioni_operatore.c
 *
 *  Created on: 26 giu 2021
 *      Author: Gabriele
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "Strutture.h"
#include "Algoritmi_fondamentali.h"

void inserimento_prodotti (FILE* file_prod)
{
	prodotti_t* risultati_ricerca =  NULL;
	prodotti_t prodotto = { 0, 0, 0, 0, 0, ""};
	prodotti_t nuovo_prodotto = { 0, 0, 0, 0, 0, ""};
	int scelta_inserimento_prodotti = 0, i = 0;
	bool flag = 0;

	//SCELTA DI INSERIMENTO NUOVO PRODOTTO O PRODOTTO ESISTENTE
	while (scelta_inserimento_prodotti == 0)
	{
		printf ("\n Inserisci:\n 1) Per inserire un nuovo prodotto\n 2) Per aggiornare la quantita' di un prodotto esistente\n Inserimento : ");
		scanf ("%d", &scelta_inserimento_prodotti);

		if ( scelta_inserimento_prodotti < 1 || scelta_inserimento_prodotti > 2 )
		{
			printf ("\n !!! ERRORE, inserimento non valido, riprova !!!");
			scelta_inserimento_prodotti = 0;
		}
	}

	//INSERIMENTO NUOVO PRODOTTO
	//INSERIMENTO CATEGORIA NUOVO PRODOTTO
	if (scelta_inserimento_prodotti == 1)
	{
		flag = 0;
		while (flag == 0)
		{
			flag = 1;
			printf ("\n Inserisci la categoria del prodotto da acquistare inserendo il numero corrispondente :  ");
			printf ("\n 1) VESTITI \n 2) ELETTRODOMESTICI \n 3) ELETTRONICA \n 4) BENESSERE \n 5) ALIMENTARI\n Inserimento : ");
			scanf ("%d", &nuovo_prodotto.categoria);
			if ( nuovo_prodotto.categoria < 1 || nuovo_prodotto.categoria > 5 )
			{
				printf ("\n !!! ERRORE, inserimento non valido, riprova !!! \n");
				flag = 0;
			}
		}
		//CONTROLLO UNIVOCITA' DEL CODICE PRODOTTO
		flag = 0;
		while (flag == 0)
		{
			flag = 1;
			printf (" Inserisci il codice del prodotto : ");
			scanf ("%d", &nuovo_prodotto.codice_prod);
			rewind (file_prod);
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
			while (!feof(file_prod))
			{
				if ( prodotto.codice_prod == nuovo_prodotto.codice_prod )
					{
						flag = 0;
					}
					fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
			}
			if (flag == 0)
			{
				printf ("\n !!! ERRORE, codice prodotto gia' esistente, riprova !!! \n");
			}
		}

		//INSERIMENTO DATI PRODOTTO
		printf (" Inserisci la quantita' disponibile del prodotto : ");
		scanf ("%d", &nuovo_prodotto.quantita_disp);

		printf (" Inserisci la quantita' venduta del prodotto : ");
		scanf ("%d", &nuovo_prodotto.quantita_vend);

		printf (" Inserisci il prezzo del prodotto : ");
		scanf ("%f", &nuovo_prodotto.prezzo);

		printf (" Inserisci il nome del prodotto : ");
		scanf ("%19s", nuovo_prodotto.nome_prod);


		//SCRITTURA PRODOTTO NEL FILE
		rewind (file_prod);
		fseek (file_prod, (0)*sizeof (prodotti_t), SEEK_END );
		fwrite (&nuovo_prodotto, sizeof(prodotti_t), 1, file_prod);

		//SCRITTURA PRODOTTI A SCHERMO
		printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n PRODOTTI :\n");
		rewind (file_prod);
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		while (!feof(file_prod))
		{
			printf ("\n %d) \t Nome prodotto : %-19s \t Codice prodotto : %d",i+1, prodotto.nome_prod, prodotto.codice_prod);
			i++;
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		}
		printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
		printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");

	}

	//AGGIORNAMENTO QUANTITA' PRODOTTO ESISTENTE
	else
	{
		//CHIAMATA ALLA FUNZIONE RICERCA
		risultati_ricerca = ricerca(file_prod);

		//MODIFICA QUANTITA'
		printf ("\n Inserisci la quantita' aggiornata del prodotto : ");
		scanf ("%d", &(risultati_ricerca)->quantita_disp);

		rewind (file_prod);
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		flag = 0;
		//AGGIORNAMENTO FLE PRODOTTI
		while ( flag == 0 )
		{
			if (prodotto.codice_prod == (risultati_ricerca)->codice_prod)
			{
				prodotto.quantita_disp = (risultati_ricerca)->quantita_disp;
				fseek (file_prod, (-1)*sizeof (prodotti_t), SEEK_CUR );
				fwrite (&prodotto, sizeof(prodotti_t), 1, file_prod);
				flag = 1;
			}
			else
			{
				fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
			}
		}
		free (risultati_ricerca);
	}
}


void statistica_citta (FILE* file_ord)
{
	int i = 0;
	int frequenza[NUM_CITTA] = {0, };
	ordini_t ordine = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};

	//CALCOLO E VISUALIZZAZIONE STATISTICA
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	printf ("\t VISUALIZZAZIONE STATISTICA : Numero di ordini effettuati nelle 5 maggiori citta' italiane\n\n ");
	rewind (file_ord);
	fread (&ordine, sizeof(ordini_t), 1, file_ord);
	while (!feof(file_ord))
	{
		frequenza[ (ordine.citta-1) ]++;
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
	}

	for(i = 0; i < NUM_CITTA; i++)
	{
		switch (i)
		{
		case 0:	 printf("\n Citta' : Roma \t\t numero di ordini : %d \n", frequenza[i]);
		break;

		case 1:	 printf(" Citta' : Napoli \t\t numero di ordini : %d \n",  frequenza[i]);
		break;

		case 2:	 printf(" Citta' : Milano \t\t numero di ordini : %d \n",  frequenza[i]);
		break;

		case 3:	 printf(" Citta' : Torino \t\t numero di ordini : %d \n",  frequenza[i]);
		break;

		case 4:	 printf(" Citta' : Bari \t\t numero di ordini : %d \n",  frequenza[i]);
		break;
		}
	}
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

void statistica_prezzo (FILE* file_ord)
{
	int i = 0, j = 0, k = 0, min = 0;
	ordini_t temp = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	ordini_t ordine = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	ordini_t* ordine_punt = NULL;

	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	printf ("\t VISUALIZZAZIONE STATISTICA :  I 5 Ordini piu costosi\n\n ");

	//CARICAMENTO PUNTATORE
	rewind (file_ord);
	fread (&ordine, sizeof(ordini_t), 1, file_ord);
	while ( !feof(file_ord) )
	{
		i++;
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
	}


	ordine_punt = (ordini_t*) calloc(i+1, sizeof(ordini_t));
	i = 0;

	rewind (file_ord);
	fread (&ordine, sizeof(ordini_t), 1, file_ord);
	while ( !feof(file_ord) )
	{
		*(ordine_punt+i) = ordine;
		i++;
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
	}

	//ORDINAMENTO
	i = 0;
	j = 0;
	k = 0;
	while ( (ordine_punt+i)->codice_ord != 0 )
	{
		min = (ordine_punt+i)->prezzo;
		k = i;
		j = i+1;
		while ( (ordine_punt+j)->codice_ord != 0 )
		{
			if (min < (ordine_punt+j)->prezzo)
			{
				min = (ordine_punt+j)->prezzo;
				k = j;
			}
			j++;
		}
		//SCAMBIO
		temp = *(ordine_punt+i);
		*(ordine_punt+i) = *(ordine_punt+k);
		*(ordine_punt+k) = temp;

		i++;
	}

	i = 0;
	//VISUALIZZAZIONE STATISTICA
	while ( i < 5)
	{
		printf ("\n %d) Prodotto : %-19s Codice ordine : %d\t\t\t Prezzo : %.2f $", i+1, (ordine_punt + i)->nome_prod, (ordine_punt + i)->codice_ord, (ordine_punt + i)->prezzo);
		i++;
	}
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}


void statistica_quantita_vendute (FILE* file_prod)
{
	prodotti_t* prodotti_punt =  NULL;
	prodotti_t prodotto = { 0, 0, 0, 0, 0, ""};
	prodotti_t temp = { 0, 0, 0, 0, 0, ""};
	int i = 0, j = 0, k = 0, min = 0;

	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	printf ("\t VISUALIZZAZIONE STATISTICA :  I 5 prodotti piu' venduti\n\n ");

	//CARICAMENTO PUNTATORE
	rewind (file_prod);
	fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
	while ( !feof(file_prod) )
	{
		i++;
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
	}


	prodotti_punt = (prodotti_t*) calloc(i+1, sizeof(prodotti_t));
	i = 0;

	rewind (file_prod);
	fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
	while ( !feof(file_prod) )
	{
		*(prodotti_punt+i) = prodotto;
		i++;
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
	}

	//ORDINAMENTO
	i = 0;
	j = 0;
	k = 0;
	while ( (prodotti_punt+i)->codice_prod != 0 )
	{
		min = (prodotti_punt+i)->quantita_vend;
		k = i;
		j = i+1;
		while ( (prodotti_punt+j)->codice_prod != 0 )
		{
			if (min < (prodotti_punt+j)->quantita_vend)
			{
				min = (prodotti_punt+j)->quantita_vend;
				k = j;
			}
			j++;
		}
		//SCAMBIO
		temp = *(prodotti_punt+i);
		*(prodotti_punt+i) = *(prodotti_punt+k);
		*(prodotti_punt+k) = temp;

		i++;
	}

	i = 0;
	//VISUALIZZAZIONE
	while ( i < 5)
	{
		printf ("\n %d) Prodotto : %-19s Codice prodotto : %d\t\t\t N. articoli venduti : %d ", i+1, (prodotti_punt + i)->nome_prod, (prodotti_punt + i)->codice_prod, (prodotti_punt + i)->quantita_vend);
		i++;
	}
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}



void statistica_quantita_ordini (FILE* file_ord)
{
	int i = 0, j = 0, k = 0, min = 0;
	ordini_t temp = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	ordini_t ordine = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	ordini_t* ordine_punt = NULL;

	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	printf ("\t VISUALIZZAZIONE STATISTICA :  I 5 Ordini con maggior quantita'\n\n ");

	//CARICAMENTO PUNTATORE
	rewind (file_ord);
	fread (&ordine, sizeof(ordini_t), 1, file_ord);
	while ( !feof(file_ord) )
	{
		i++;
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
	}


	ordine_punt = (ordini_t*) calloc(i+1, sizeof(ordini_t));
	i = 0;

	rewind (file_ord);
	fread (&ordine, sizeof(ordini_t), 1, file_ord);
	while ( !feof(file_ord) )
	{
		*(ordine_punt+i) = ordine;
		i++;
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
	}


	//ORDINAMENTO
	i = 0;
	j = 0;
	k = 0;
	while ( (ordine_punt+i)->codice_ord != 0 )
	{
		min = (ordine_punt+i)->quantita;
		k = i;
		j = i+1;
		while ( (ordine_punt+j)->codice_ord != 0 )
		{
			if (min < (ordine_punt+j)->quantita)
			{
				min = (ordine_punt+j)->quantita;
				k = j;
			}
			j++;
		}
		//SCAMBIO
		temp = *(ordine_punt+i);
		*(ordine_punt+i) = *(ordine_punt+k);
		*(ordine_punt+k) = temp;

		i++;
	}

	i = 0;
	//VISUALIZZAZIONE
	while ( i < 5)
	{
		printf ("\n %d) Prodotto : %-19s Codice ordine : %d\t\t\t N. articoli ordine : %d", i+1, (ordine_punt + i)->nome_prod, (ordine_punt + i)->codice_ord, (ordine_punt + i)->quantita);
		i++;
	}
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}


void modifica_ordini_aperti (FILE* file_ord)
{
	int scelta_modifica_ordini_aperti = 0, i = 0, j = 0, h = 0;
	bool flag = 0, flag_stato = 0;
	ordini_t ordine = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};
	ordini_t* ordine_punt = NULL;
	char nome_prod [LUNGH_NOME_PROD] = "";

	//RICERCA PER NOME PRODOTTO (nel file ordini)
	//CALCOLO MEMORIA STRETTAMENTE NECESSARIA
	while (flag == 0)
	{
		rewind (file_ord);
		printf ("\n Inserisci il nome del prodotto ricercato : ");
		scanf ("%19s", nome_prod);
		fread (&ordine, sizeof(ordini_t), 1, file_ord);
		while ( !feof ( file_ord ) )
		{
			if ( strcmp(ordine.nome_prod ,nome_prod) == 0 )
			{
				i++;
				flag = 1;
				printf ("%d nomi uguali", i);
			}
			fread (&ordine, sizeof(ordini_t), 1, file_ord);
		}

		//ALLOCAZIONE MEMORIA AL PUNTATORE ordine_punt
		if (i!=0)
		{
			ordine_punt = (ordini_t*) calloc(i+1, sizeof(ordini_t));
			i = 0;

			//RICERCA PER NOME
			rewind (file_ord);

			fread (&ordine, sizeof(ordini_t), 1, file_ord);
			while ( !feof(file_ord) )
			{
				if ( strcmp(ordine.nome_prod ,nome_prod) == 0 )
				{
					*(ordine_punt + i) = ordine;
					i++;
					flag = 1;
				}
				fread (&ordine, sizeof(ordini_t), 1, file_ord);
			}
		}
		//RICERCA PER SOTTOSTRINGHE
		//CALCOLO MEMORIA STRETTAMENTE NECESSARIA AL PUNTATORE ordine_punt
		else
		{
			i = 0;
			rewind (file_ord);
			fread (&ordine, sizeof(ordini_t), 1, file_ord);
			while ( !feof ( file_ord ))
			{
				j = 0;
				h = 0;
				while (nome_prod[j] != '\0')
				{
					if (strchr (ordine.nome_prod, nome_prod [j]) != NULL)
					{
						h++;
					}
					j++;
				}
				if (h == j)
				{
					i++;
					flag = 1;
				}
				fread (&ordine, sizeof(ordini_t), 1, file_ord);
			}

			//ALLOCAZIONE MEMORIA AL PUNTATORE ordine_punt
			if (i!=0)
			{
				ordine_punt =  (ordini_t*) calloc(i+1, sizeof(ordini_t));

				//RICERCA PER SOTTOSTRINGHE
				i = 0;
				rewind (file_ord);
				fread (&ordine, sizeof(ordini_t), 1, file_ord);
				while ( !feof ( file_ord ))
				{
					j = 0;
					h = 0;
					while (nome_prod[j] != '\0')
					{
						if (strchr (ordine.nome_prod, nome_prod [j]) != NULL)
						{
							h++;
						}
						j++;
					}
					if (h == j)
					{
						*(ordine_punt + i) = ordine;
						i++;
						printf ("%d",i);
						flag = 1;
					}
					fread (&ordine, sizeof(ordini_t), 1, file_ord);
				}
			}
		}

		if (flag == 0)
		{
			printf ("\n !!! ERRORE, valore inserito non valido, riprova !!!\n");
		}
	}


	//VISUALIZZAZIONE ORDINI
	printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n ORDINI :\n");
	i = 0;
	while ( (ordine_punt + i)->codice_ord != 0 )
	{
		printf ("\n %d) \t Nome prodotto : %-19s \t Codice ordine : %d\t\t\t prezzo ordine : %.2f",i+1,(ordine_punt + i)->nome_prod, (ordine_punt + i)->codice_ord, (ordine_punt + i)->prezzo);
		switch ( (ordine_punt + i)->stato )
		{
		case 0:		printf ("\t\t\t stato ordine : 'da consegnare'\n");
		break;
		case 1:		printf ("\t\t\t stato ordine : 'in transito'\n");
		break;
		case 2:		printf ("\t\t\t stato ordine : 'consegnato'\n");
		break;
		}
		i++;
	}
	printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
	printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");

	//SCELTA ORDINE
	flag = 0;
	while (flag == 0)
	{
		printf ("\n Scegli un ordine inserendo il numero corrispondente posto di fianco all'ordine \n inserimento : ");
		scanf ("%d", &scelta_modifica_ordini_aperti);
		if (scelta_modifica_ordini_aperti < 1 || scelta_modifica_ordini_aperti > i )
		{
			printf ("\n !!! ERRORE, valore inserito non valido, riprova !!!\n");
		}
		else
		{
			//MODIFICA STATO ORDINE
			rewind (file_ord);
			fread (&ordine, sizeof(ordini_t), 1, file_ord);
			while ( !feof(file_ord)  &&  flag_stato == 0 )
			{
				if (ordine.codice_ord == (ordine_punt + scelta_modifica_ordini_aperti - 1)->codice_ord)
				{
					while ( flag_stato == 0)
					{
						printf ("\n Per modificare lo stato dell'ordine inserisci :\n 0 --> Per modificare lo stato in ' da consegnare '\n 1 --> Per modificare lo stato in ' in transito '\n 2 --> Per modificare lo stato in ' consegnato '\n ( lo stato può essere cambiato soltanto in uno stato successivo ES: 'da consegnare' --> 'consegnato' ma non viceversa ) \n Inserimento : ");
						scanf ("%d", &ordine.stato);
						if ( ordine.stato >= (ordine_punt + scelta_modifica_ordini_aperti - 1)->stato && ordine.stato > -1 && ordine.stato < 3)
						{
							fseek (file_ord, (-1)*sizeof (ordini_t), SEEK_CUR );
							fwrite (&ordine, sizeof(ordini_t), 1, file_ord);
							printf ("\n || STATO ORDINE MODIFICATO CON SUCCESSO ||\n");
							flag_stato = 1;
						}
						else
						{
							printf ("\n !!! ERRORE, inserimento non valido, rirpova !!! \n");
						}
					}
				}
				else
				{
					fread (&ordine, sizeof(ordini_t), 1, file_ord);
				}
			}
			flag = 1;
		}
	}
}

void ricerca_e_gestione_ordine (FILE* file_ord)
{
	int scelta_ricerca_e_gestione_ordine = 0, i = 0;
	ordini_t ordine = { 0, 0, 0, 0, 0, 0, 0, "", "", ""};

	//SCELTA
	while (scelta_ricerca_e_gestione_ordine == 0)
	{
		rewind (file_ord);
		printf ("\n Inserisci :\n 1) Per visualizzare gli ordini aperti\n 2) Per visualizzare gli ordini chiusi\n 3) Per modificare lo stato di un ordine aperto\n 4) Per terminare ricerca e gestione ordini\n Inserimento : ");
		scanf ("%d", &scelta_ricerca_e_gestione_ordine);

		//CONTROLLO SCELTA
		if (scelta_ricerca_e_gestione_ordine < 1 || scelta_ricerca_e_gestione_ordine > 4)
		{
			printf ("\n !!! ERRORE, inserimento non valido, riprova !!!");
			scelta_ricerca_e_gestione_ordine = 0;
		}
		else
		{
			//VISUALIZZA ORDINI APERTI
			if (scelta_ricerca_e_gestione_ordine == 1)
			{
				printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n ORDINI APERTI :\n");
				i = 0;
				rewind (file_ord);
				fread (&ordine, sizeof(ordini_t), 1, file_ord);
				while (!feof(file_ord))
				{
					if (ordine.stato != 2)
					{
						printf ("\n %d) \t Nome prodotto : %-19s \t Codice ordine : %d\t\t\t  N. articoli ordine : %d",i+1, ordine.nome_prod, ordine.codice_ord, ordine.quantita);
						switch ( ordine.stato )
						{
						case 0:		printf ("\t\t\t stato ordine : 'da consegnare'\n");
						break;
						case 1:		printf ("\t\t\t stato ordine : 'in transito'\n");
						break;
						case 2:		printf ("\t\t\t stato ordine : 'consegnato'\n");
						break;
						}
						i++;
					}
					fread (&ordine, sizeof(ordini_t), 1, file_ord);
				}
				printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
				printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
				scelta_ricerca_e_gestione_ordine = 0;
			}
			//VISUALIZZA ORDINI CHIUSI
			else if (scelta_ricerca_e_gestione_ordine == 2)
			{
				printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf ("------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n ORDINI CHIUSI :\n");
				i =0;
				rewind (file_ord);
				fread (&ordine, sizeof(ordini_t), 1, file_ord);
				while (!feof(file_ord))
				{
					if (ordine.stato == 2)
					{
						printf ("\n %d) \t Nome prodotto : %-19s \t Codice ordine : %d\t\t\t  N. articoli ordine : %d",i+1, ordine.nome_prod, ordine.codice_ord, ordine.quantita);
						switch ( ordine.stato )
						{
						case 0:		printf ("\t\t\t stato ordine : 'da consegnare'\n");
						break;
						case 1:		printf ("\t\t\t stato ordine : 'in transito'\n");
						break;
						case 2:		printf ("\t\t\t stato ordine : 'consegnato'\n");
						break;
						}
						i++;
					}
					fread (&ordine, sizeof(ordini_t), 1, file_ord);
				}
				printf ("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
				printf ("\n------------------------------------------------------------------------------------------------------------------------------------------------------------");
				scelta_ricerca_e_gestione_ordine = 0;
			}
			//MODIFICA STATO ORDINI APERTI
			else if (scelta_ricerca_e_gestione_ordine == 3)
			{
				modifica_ordini_aperti (file_ord);
				scelta_ricerca_e_gestione_ordine = 0;
			}
		}
	}
}
