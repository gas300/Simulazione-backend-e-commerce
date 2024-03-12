/*
 ============================================================================
 Name        : Progetto.c
 Author      : Gabriele Marrano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// LIBRERIE CREATE
#include "Menu.h"
#include "Funzioni_operatore.h"
#include "Funzioni_cliente.h"
#include "Strutture.h"



int main(void)
{
	setvbuf(stdout, NULL,_IONBF, 0);
	system ("color F5");


	//CREAZIONE e INIZIALIZZAZIONE VARIABILI
	FILE* file_prod = NULL;
	FILE* file_ordine = NULL;
	bool flag = 0, flag_op = 0, flag_cli = 0;
	int scelta_gen = 0, scelta_op = 0, scelta_cli = 0;


	if (( file_ordine = fopen ("ORDINI.dat", "rb+") ) == NULL)
	{
		printf ("\n !!! ERRORE NELL'APERTURA DEL FILE ORDINE !!!");
	}
	else
	{
		printf ("\n FILE ORDINI APERTO!\n");
		if (( file_prod = fopen ("PRODOTTI.dat", "rb+") ) == NULL)
		{
			printf ("\n !!! ERRORE NELL'APERTURA DEL FILE PRODOTTI !!!");
		}
		else
		{
			printf ("\n FILE PRODOTTI APERTO!\n");

			do
			{
					//MENU GENERALE e SELEZIONE MODALITA' D'ACCESSO
				scelta_gen = menu_gen ();

					//LATO CLIENTE
				if (scelta_gen == 1)
				{
					flag_cli = 0;
					while (flag_cli == 0)
					{
						scelta_cli = menu_cli ();
						switch (scelta_cli)
						{
						case 1:		acquista_prodotto (file_prod, file_ordine);
						break;
						case 2:		modifica_ordine (file_prod, file_ordine);
						break;
						case 3:		flag_cli = 1;
						break;
						}
					}
				}

				else
				{
					//LATO OPERATORE
					if (scelta_gen == 2)
					{
						lato_op();
						flag_op = 0;
						while (flag_op == 0)
						{
							scelta_op = menu_op ();
							switch (scelta_op)
							{
							case 1:		inserimento_prodotti (file_prod);
							break;
							case 2:		ricerca_e_gestione_ordine (file_ordine);
							break;
							case 3:		menu_statistica (file_prod, file_ordine);
							break;
							case 4:		flag_op = 1;
							break;
							}
						}
					}
					else
						flag = 1;
				}


			} while (flag == 0);

		}
		//CHIUSURA FILE
		if(!fclose(file_prod))
			printf ("\n FILE PRODOTTI CHIUSO CORRETTAMENTE!");
	}
	if(!fclose(file_ordine))
		printf ("\n FILE ORDINI CHIUSO CORRETTAMENTE!");
	return(0);
}
