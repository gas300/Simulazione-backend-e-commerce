/*
 * Algoritmi_fondamentali.h
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


#ifndef ALGORITMI_FONDAMENTALI_H_
#define ALGORITMI_FONDAMENTALI_H_


prodotti_t* ricerca_codice_prodotto (FILE* file_prod);

/*
 * LA FUNZIONE RICERCA_CODICE_PRODOTTO RICHIEDE COME ARGOMENTO IL PUNTATORE AL FILE PRODOTTI ED EFFETTUA
 * UNA RICERCA ALL'INTERNO DEL FILE "PRODOTTI.dat" PER TROVARE IL PRODOTTO CON IL CODICE CORRISPONDENTE
 * A QUELLO INSERITO DALL'UTENTE E LO RESTITUISCE AL PROGRAMMA CHIAMANTE ATTRAVERSO
 * UN PUNTATORE
 */

prodotti_t* ricerca_categoria (FILE* file_prod);

/*
 * LA FUNZIONE RICERCA_CATEGORIA RICHIEDE COME ARGOMENTO IL PUNTATORE AL FILE PRODOTTI ED EFFETTUA
 * UNA RICERCA ALL'INTERNO DEL FILE "PRODOTTI.dat" PER TROVARE I PRODOTTI APPARTENETI ALLA STESSA CATEGORIA
 * DI QUELLA INSERITA DALL'UTENTE E LI RESTITUISCE AL PROGRAMMA CHIAMANTE ATTRAVERSO
 * UN PUNTATORE
 */

prodotti_t* ricerca_nome_prodotto (FILE* file_prod);

/*
 * LA FUNZIONE RICERCA_NOME_PRODOTTO RICHIEDE COME ARGOMENTO IL PUNTATORE AL FILE PRODOTTI ED EFFETTUA
 * UNA RICERCA ALL'INTERNO DEL FILE "prodotti.dat" PER TROVARE I PRODOTTI CON IL NOME (O UNA SUA PARTE)
 * CORRISPONDENTE A QUELLO INSERITO DALL'UTENTE E LI RESTITUISCE AL PROGRAMMA CHIAMANTE ATTRAVERSO
 * UN PUNTATORE
 */

prodotti_t* ricerca (FILE* file_prod);

/*
 * LA FUNZIONE RICERCA RICHIEDE COME ARGOMENTO IL PUNTATORE AL FILE PRODOTTI ED HA LA FUNZIONE DI
 * CHIAMARE LA RICERCA SELEZIONATA DALL'UTENTE, CHIAMARE LA FUNZIONE DI ORDINAMENTO, POI QUELLA DI VISUALIZZAZIONE
 * E RESTITUISCE AL PROGRAMMA CHIAMANTE UN PUNTATORE ALL'AREA DI MEMORIA CONTENTE IL PRODOTTO FINALE
 * SCELTO DALL'UTENTE
 */

prodotti_t* ordinamento (prodotti_t* risultati_ricerca);

/*
 * LA FUNZIONE ORDINAMENTO RICHIEDE COME ARGOMENTO IL PUNTATORE ALL'AREA DI MEMORIA CONTENTE I PRODOTTI RICERCATI,
 * NE EFFETUA L'ORDINAMENTO IN BASE AL PREZZO CRESCENTE E RESTITUISCE AL PROGRAMMA CHIAMANTE UN PUNTATORE AD
 * UN AREA DI MEMORIA CONTENENTE I PRODOTTI RICERCATI E ORDINATI
 */

prodotti_t* visualizzazione (prodotti_t* risultati_ordinamento);

/*
 * LA FUNZIONE VISUALIZZAZIONE RICHIEDE COME ARGOMENTO IL PUNTATORE ALL'AREA DI MEMORIA CONTENENTE I PRODOTTI RICERCATI
 * ED ORDINATI, NE EFFETTUA LA VISUALIZZAZIONE E RICHIEDE ALL'UTENTE DI SCEGLIERNE UNO, POI RESTITUISCE AL PROGRAMMA
 * CHIAMANTE UN PUNTATORE ALL'AREA DI MEMORIA CONTENTE IL PRODOTTO SCELTO DALL'UTENTE
 */


#endif /* ALGORITMI_FONDAMENTALI_H_ */
