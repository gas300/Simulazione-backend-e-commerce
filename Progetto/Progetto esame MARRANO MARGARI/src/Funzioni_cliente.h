/*
 * Funzioni_cliente.h
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

#ifndef FUNZIONI_CLIENTE_H_
#define FUNZIONI_CLIENTE_H_

void acquista_prodotto (FILE* file_prod, FILE* file_ord);

/*
 *  LA PROCEDURA ACQUISTA_PRODOTTO RICHIEDE COME PARAMETRI I PUNTATORI AI FILE "PRODOTTI.dat" E "ORDINI.dat",
 *  EFFETTUA UNA CHIAMATA ALLA FUNZIONE "RICERCA" E RICHIEDE ALL'UTENTE DI COMPILARE I CAMPI NECESSARI
 *  ALLA CREAZIONE DELL'ORDINE, POI LO SCRIVE SUL FILE "ORDINI.dat" E AGGIORNA LE QUANTITA' DISPONIBILI E VENDUTE
 *  DEL PRODOTTO COMPRATO NEL FILE "PRODOTTI.dat"
 */

void modifica_ordine (FILE* file_prod, FILE* file_ord);

/*
 *  LA PROCEDURA MODIFICA_ORDINE RICHIEDE COME PARAMETRI I PUNTATORI AI FILE "PRODOTTI.dat" E "ORDINI.dat",
 *  EFFETTUA UNA RICERCA PER NOME CLIENTE, RICHIEDE ALL'UTENTE LA SCELTA DI UN ORDINE E NE PERMETTE LA MODIFICA
 *  DELLA QUANTITA' DI PEZZI DEL PRODOTTO ORDINATI, POI AGGIORNA IL FILE "ORDINI.dat"
 */

#endif /* FUNZIONI_CLIENTE_H_ */
