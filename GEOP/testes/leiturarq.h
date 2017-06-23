//
//  leiturarq.h
//  GEOP
//
//  Created by Clara on 25/05/17.
//
//

#ifndef leiturarq_h
#define leiturarq_h

#include "cabecalhostructs.h"
#define SIZE 50
//le o arquivo a procura de um item do formato da funcao
double ArqGeop_leituraArqDouble(char oQueBusca[SIZE],char file[SIZE]);
//le o arquivo a procura de um item do formato da funcao
int ArqGeop_leituraArqInt(char oQueBusca[SIZE],char file[SIZE]);
//le o arquivo a procura de um item do formato char
void ArqGeop_leituraArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE]);
//Printa as Strings que foram buscadas
void ArqGeop_lePrintArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE]);


FILE *ArqGeop_guardaCabecalho(struct Parametros cabe,struct dados nomes, struct Dimensoes bound,char nome_arq[SIZE],FILE *Resul1);

#endif /* leiturarq_h */
