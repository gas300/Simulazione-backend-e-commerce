/*
 * Algoritmi_fondamentali.c
 *
 *  Created on: 26 giu 2021
 *      Author: Gabriele
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "Strutture.h"


prodotti_t* ricerca_codice_prodotto (FILE* file_prod)
{

	prodotti_t* array_ricerca =  NULL;
	prodotti_t prodotto = { 0, 0, 0, 0, 0, ""};
	int codice = 0, i = 0;

	//RICERCA PER CODICE PRODOTTO
	//CALCOLO MEMORIA STRETTAMENTE NECESSARIA AL PUNTATORE array_ricerca
	while (i == 0)
	{
		rewind (file_prod);
		printf ("\n Inserisci il codice del prodotto ricercato : ");
		scanf ("%d", &codice);
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		while ( !feof(file_prod) )
		{
			if (prodotto.codice_prod == codice)
			{
				i++;
			}
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		}
		if ( i == 0)
		{
			printf ("\n !!!ERRORE, prodotto non trovato, riprova !!!");
		}
	}

	//ALLOCAZIONE MEMORIA AL PUNTATORE array_ricerca
	if (i!=0)
	{
		array_ricerca = (prodotti_t*) calloc(2, sizeof(prodotti_t));
		i = 0;
	}

	//RICERCA PER CODICE PRODOTTO E RIEMPIMENTO MEMORIA DEL PUNTATORE array_ricerca
	while (i == 0)
	{
		rewind (file_prod);
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		while ( !feof(file_prod) )
		{
			if (prodotto.codice_prod == codice)
			{
				*(array_ricerca) = prodotto;
				i++;
			}
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		}
	}
	return (array_ricerca);
}


prodotti_t* ricerca_categoria (FILE* file_prod)
{
	prodotti_t* array_ricerca =  NULL;
	prodotti_t prodotto = { 0, 0, 0, 0, 0, ""};
	int categoria = 0, i = 0;

	//RICERCA PER CATEGORIA
	//CALCOLO MEMORIA STRETTAMENTE NECESSARIA AL PUNTATORE array_ricerca
	while (i == 0)
	{
		rewind (file_prod);
		printf ("\n Scegli la categoria del prodotto da acquistare inserendo il numero corrispondente :  ");
		printf ("\n 1) VESTITI \n 2) ELETTRODOMESTICI \n 3) ELETTRONICA \n 4) BENESSERE \n 5) ALIMENTARI\n Inserimento : ");
		scanf ("%d", &categoria);
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		while ( !feof(file_prod) )
		{
			if (prodotto.categoria == categoria)
			{
				i++;
			}
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		}
		if ( i == 0)
		{
			printf ("\n !!!ERRORE, prodotto non trovato, riprova !!!");
		}
	}

	//ALLOCAZIONE MEMORIA AL PUNTATORE array_ricerca
	if (i!=0)
	{
		array_ricerca =  (prodotti_t*) calloc(i+1, sizeof(prodotti_t));
		i = 0;
	}


	//RICERCA PER CATEGORIA E RIEMPIMENTO MEMORIA DEL PUNTATORE array_ricerca
	while (i == 0)
	{
		rewind (file_prod);
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		while ( !feof(file_prod) )
		{
			if (prodotto.categoria == categoria)
			{
				*(array_ricerca + i) = prodotto;
				i++;
			}
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		}
	}
	return (array_ricerca);
}


prodotti_t* ricerca_nome_prodotto (FILE* file_prod)
{
	prodotti_t* array_ricerca =  NULL;
	prodotti_t prodotto = { 0, 0, 0, 0, 0, ""};
	bool flag = 0;
	int i = 0, j = 0, h = 0;
	char nome_prod [LUNGH_NOME_PROD] = "";

	//RICERCA PER NOME PRODOTTO
	//CALCOLO MEMORIA STRETTAMENTE NECESSARIA AL PUNTATORE array_ricerca
	while (flag == 0)
	{
		rewind (file_prod);
		printf ("\n Inserisci il nome del prodotto ricercato : ");
		scanf ("%19s", nome_prod);
		fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		while ( !feof(file_prod) )
		{
			if ( strcmp(prodotto.nome_prod ,nome_prod) == 0 )
			{
				i++;
				flag = 1;
			}
			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
		}

		//ALLOCAZIONE MEMORIA AL PUNTATORE array_ricerca
		if (i!=0)
		{
			array_ricerca = (prodotti_t*) calloc(i+1, sizeof(prodotti_t));
			i = 0;

			//RICERCA PER NOME PRODOTTO E RIEMPIMENTO MEMORIA DEL PUNTATORE array_ricerca
			while (i == 0)
			{
				rewind (file_prod);
				fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
				while ( !feof(file_prod) )
				{
					if ( strcmp(prodotto.nome_prod ,nome_prod) == 0 )
					{
						*(array_ricerca + i) = prodotto;
						i++;
						flag = 1;
					}
					fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
				}
			}
		}
			/*
			 * (se ricerca per nome prodotto non va a buon fine, viene effettuata la ricerca per sottostringhe)
			 * RICERCA PER SOTTOSTRINGHE
			 * CALCOLO MEMORIA STRETTAMENTE NECESSARIA AL PUNTATORE array_ricerca
			 */
		else
		{
			rewind (file_prod);
			i = 0;

			fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
			while ( !feof (file_prod ))
			{
				j = 0;
				h = 0;
				while (nome_prod[j] != '\0')
				{
					if (strchr (prodotto.nome_prod, nome_prod [j]) != NULL)
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
				fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
			}

			//ALLOCAZIONE MEMORIA AL PUNTATORE array_ricerca
			if (i!=0)
			{
				array_ricerca =  (prodotti_t*) calloc(i+1, sizeof(prodotti_t));

				//RICERCA PER SOTTOSTRINGHE E RIEMPIMENTO MEMORIA DEL PUNTATORE array_ricerca
				i = 0;
				rewind (file_prod);
				fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
				while ( !feof (file_prod ))
				{
					j = 0;
					h = 0;
					while (nome_prod[j] != '\0')
					{
						if (strchr (prodotto.nome_prod, nome_prod [j]) != NULL)
						{
							h++;
						}
						j++;
					}
					if (h == j)
					{
						*(array_ricerca + i) = prodotto;
						i++;
						flag = 1;
					}
					fread (&prodotto, sizeof(prodotti_t), 1, file_prod);
				}
			}
		}

		if (flag == 0)
		{
			printf ("\n !!! ERRORE, valore inserito non valido, riprova !!!");
		}
	}
	return (array_ricerca);
}


prodotti_t* ordinamento (prodotti_t* risultati_ricerca)
{
	int i = 0, j = 0, k = 0, min = 0;
	prodotti_t temp = { 0, 0, 0, 0, 0, ""};

	//ORDINAMENTO
	while ( (risultati_ricerca+i)->categoria != 0 )
	{
		min = (risultati_ricerca+i)->prezzo;
		k = i;
		j = i+1;
		while ( (risultati_ricerca+j)->categoria != 0 )
		{
			if (min > (risultati_ricerca+j)->prezzo)
			{
				min = (risultati_ricerca+j)->prezzo;
				k = j;
			}
			j++;
		}
		//SCAMBIO
		temp = *(risultati_ricerca+i);
		*(risultati_ricerca+i) = *(risultati_ricerca+k);
		*(risultati_ricerca+k) = temp;

		i++;
	}
	return (risultati_ricerca);
}



prodotti_t* visualizzazione (prodotti_t* risultati_ordinamento)
{
	int i = 0, scelta_visualizzazione = 0;
	bool flag = 0;

	//VISUALIZZAZIONE PRODOTTO
	printf ("\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
	while ( (risultati_ordinamento + i)->categoria != 0)
	{
		printf ("\n %d) Prodotto : %-19s Quantita' disponibili : %d\t\t\t Prezzo : %.2f $", i+1, (risultati_ordinamento + i)->nome_prod, (risultati_ordinamento + i)->quantita_disp, (risultati_ordinamento + i)->prezzo);
		i++;
	}
	printf ("\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------");

	//SCELTA PRODOTTO
	while (flag == 0)
	{
		printf ("\n Scegli un prodotto inserendo il numero corrispondente posto di fianco al prodotto : ");
		scanf ("%d", &scelta_visualizzazione);
		if (scelta_visualizzazione < 1 || scelta_visualizzazione > i )
		{
			printf ("\n !!! ERRORE, valore inserito non valido, riprova !!!");
		}
		else
		{
			flag = 1;
		}
	}

	return ( (risultati_ordinamento+(scelta_visualizzazione-1) ) );
}


prodotti_t* ricerca (FILE* file_prod)
{
	prodotti_t* risultati_ricerca = NULL;
	prodotti_t* risultati_ordinamento = NULL;
	prodotti_t* scelta_visualizzazione = NULL;
	int scelta_ricerca = 0;

	//SCELTA RICERCA
	while (scelta_ricerca == 0)
	{
		printf ("\n Inserisci :\n 1) per effettuare una ricerca per codice prodotto\n 2) per effettuare una ricerca per categoria\n 3) per effettuare una ricerca per nome prodotto\n Inserimento : ");
		scanf ("%d", &scelta_ricerca);

		if (scelta_ricerca<1 || scelta_ricerca>3)
		{
			printf ("\n !!! ERRORE, valore inserito non valido, riprova !!!");
			scelta_ricerca = 0;
		}
	}

	//CHIAMATA A RICERCA PER CODICE PRODOTTO --> ORDINAMENTO --> VISUALIZZAZIONE
	if (scelta_ricerca == 1)
	{
		risultati_ricerca = ricerca_codice_prodotto (file_prod);
		risultati_ordinamento = ordinamento (risultati_ricerca);
		scelta_visualizzazione = visualizzazione (risultati_ordinamento);
	}

	//CHIAMATA A RICERCA PER CATEGORIA --> ORDINAMENTO --> VISUALIZZAZIONE
	else if (scelta_ricerca == 2)
	{
		risultati_ricerca = ricerca_categoria (file_prod);
		risultati_ordinamento = ordinamento (risultati_ricerca);
		scelta_visualizzazione = visualizzazione (risultati_ordinamento);
	}

	//CHIAMATA A RICERCA PER NOME PRODOTTO --> ORDINAMENTO --> VISUALIZZAZIONE
	else if (scelta_ricerca == 3)
	{
		risultati_ricerca = ricerca_nome_prodotto (file_prod);
		risultati_ordinamento = ordinamento (risultati_ricerca);
		scelta_visualizzazione = visualizzazione (risultati_ordinamento);
	}

	return (scelta_visualizzazione);
}
