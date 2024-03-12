/*
 * Strutture.h
 *
 *  Created on: 26 giu 2021
 *      Author: Gabriele
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#ifndef STRUTTURE_H_
#define STRUTTURE_H_

//DEFINIZIONE COSTANTI
#define LUNGH_NOME_PROD	20
#define LUNGH_NOME_CLIENTE	20
#define LUNGH_INDIRIZZO	30
#define LUNGH_PASSWORD 20
#define NUM_CITTA 5

//DEFINIZIONE TIPO ENUMERATIVO
typedef enum {Roma, Napoli, Milano, Torino, Bari} citta_t;

//DEFINIZIONE STRUCT
typedef struct {
	int categoria;
	int codice_prod;
	int quantita_disp;
	int quantita_vend;
	float prezzo;
	char nome_prod [LUNGH_NOME_PROD];
}prodotti_t;

typedef struct {
	int codice_ord;
	int	codice_prod;
	int stato;
	int quantita;
	int num_cell;
	float prezzo;
	citta_t citta;
	char cliente [LUNGH_NOME_CLIENTE];
	char indirizzo [LUNGH_INDIRIZZO];
	char nome_prod [LUNGH_NOME_PROD];
}ordini_t;

#endif /* STRUTTURE_H_ */
