#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leiturarq.h"

#define SIZE 50

//comentario no arquivo .h

double leituraArqDouble(char oQueBusca[SIZE],char file[SIZE]){
	double recebe=0;
	char v[136];

	FILE   *fp1;
	fp1=fopen(file,"r");

	if (fp1 == NULL) {
		printf("\arquivo nao pode ser aberto");
		return(0);
		}
	else printf(" ");

   do
    {
        fscanf(fp1,"%s",v);
        //printf ("%s\n", v);
    } while (strcmp(oQueBusca,v));

    fscanf(fp1,"%lf",&recebe);
  //printf ("\n%s:  %lf",oQueBusca,recebe);
	fclose(fp1);

	return (recebe);
	}

int leituraArqInt(char oQueBusca[SIZE],char file[SIZE]){
	int recebe=0;
	char v[136];

	FILE   *fp1;
	fp1=fopen(file,"r");

	if (fp1 == NULL) {
		printf("\arquivo nao pode ser aberto");
		return(0);
		}
	else printf(" ");

   do
    {
        fscanf(fp1,"%s",v);
      //  printf ("%s\n", v);
        } while (strcmp(oQueBusca,v));

  fscanf(fp1,"%d",&recebe);
  //printf ("\n%s:  %d",oQueBusca,recebe);
	fclose(fp1);
	return (recebe);
	}

void leituraArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE]){
char v[136];

	FILE   *fp1;
	fp1=fopen(file,"r");

	if (fp1 == NULL) {
		printf("\arquivo nao pode ser aberto");
		exit(0);
		}
	else printf(" ");
  do
    {
        fscanf(fp1,"%s",v);
    //    printf ("%s\n", v);
    } while (strcmp("begin_of_head",v));

   do
    {
        fscanf(fp1,"%s",v);
      //  printf ("%s\n", v);
        } while (strcmp(oQueBusca,v));

  fscanf(fp1,"%s",OndeGuarda);
  //printf ("\n%s:  %d",oQueBusca,recebe);

	fclose(fp1);
}

void lePrintArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE]){

    leituraArqChar(oQueBusca,file,OndeGuarda);
    printf ("\n%s        : %s ",oQueBusca,OndeGuarda);
    }




