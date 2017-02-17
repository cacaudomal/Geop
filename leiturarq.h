#ifndef LEITURARQ_H_
#define LEITURARQ_H_
#define SIZE 50
//le o arquivo a procura de um item do formato da funcao
double leituraArqDouble(char oQueBusca[SIZE],char file[SIZE]);
//le o arquivo a procura de um item do formato da funcao
int leituraArqInt(char oQueBusca[SIZE],char file[SIZE]);
//le o arquivo a procura de um item do formato char
void leituraArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE]);

//Printa as Strings que foram buscadas
void lePrintArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE]);

#endif
