#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leiturarq.h"
#include "cabecalhostructs.h"

#define SIZE 50

//comentario no arquivo .h

double ArqGeop_leituraArqDouble(char oQueBusca[SIZE],char file[SIZE])
    {
	double recebe = 0;
	char v[136];

	FILE   *fp1;

	if((fp1 = fopen(file,"r")) == NULL)
		{
		printf("o arquivo nao pode ser aberto 1-1 ");
		exit(1);
		}
	else printf(" ");

    do
        {
        fscanf(fp1,"%s",v);
        } while (strcmp(oQueBusca,v));

    fscanf(fp1,"%le",&recebe);

	fclose(fp1);
	return (recebe);
	}

int ArqGeop_leituraArqInt(char oQueBusca[SIZE],char file[SIZE])
    {
	int recebe = 0;
	char v[136];

	FILE   *fp1;

		if((fp1 = fopen(file,"r")) == NULL)
		{
		printf("o arquivo nao pode ser aberto 1-2 ");
		exit(1);
		}

	else printf(" ");

    do
        {
        fscanf(fp1,"%s",v);
        } while (strcmp(oQueBusca,v));

    fscanf(fp1,"%d",&recebe);
    fclose(fp1);
		fflush(fp1);
	return (recebe);
	}

void ArqGeop_leituraArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE])
    {
    char v[136];

	FILE   *fp1;
	if((fp1 = fopen(file,"r")) == NULL)
		{
		printf("o arquivo nao pode ser aberto 1-3 ");
		exit(1);
		}

	else printf(" ");

    do
        {
        fscanf(fp1,"%s",v);
        } while (strcmp("begin_of_head",v));

    do
        {
        fscanf(fp1,"%s",v);
        } while (strcmp(oQueBusca,v));

    fscanf(fp1,"%s",OndeGuarda);

	fclose(fp1);
    }

void ArqGeop_lePrintArqChar(char oQueBusca[SIZE],char file[SIZE],char OndeGuarda[SIZE])
    {
    ArqGeop_leituraArqChar(oQueBusca,file,OndeGuarda);
    printf ("\n%s        : %s ",oQueBusca,OndeGuarda);
    }

	FILE *ArqGeop_guardaCabecalho(struct Parametros cabe,struct dados nomes, struct Dimensoes bound,char nome_arq[SIZE],FILE *Resul1 ){

	if((Resul1=fopen(nome_arq,"w"))==NULL)
	{
		printf("o arquivo nao pode ser aberto 1-4 ");
		exit(1);
	}

	fprintf (Resul1,"Modelo do Geopotencial\n\n");
	//fprintf (Resul1,"Arquivo                 : %s\n",nomearq);
	fprintf (Resul1,"Model Name              : %s \n",nomes.ModName);
	fprintf (Resul1,"Product Type            : %s\n",nomes.ProdTyp);
	fprintf (Resul1,"Earth_Gravity_Constant  : %le\n",cabe.GMg);
	fprintf (Resul1,"Radius                  : %le\n",cabe.R);
	fprintf (Resul1,"Max_Degree              : %d\n",cabe.maxdeg);
	fprintf (Resul1,"Errors                  : %s\n",nomes.err);
	fprintf (Resul1,"Norm                    : %s\n",nomes.norm);
	fprintf (Resul1,"Tide System             : %s\n",nomes.TideSys);

	fprintf (Resul1,"gridsize: %le",bound.gridSize);
	fprintf (Resul1,"\nAchatamento: %le",cabe.achatamento);
	fprintf (Resul1,"  Primeira Exentricidade: %le\n",cabe.pextc);

	fprintf (Resul1,"\n\nbound sizelat : %d \nbound sizelon : %d",bound.SizeLat,bound.SizeLon);
	fprintf (Resul1,"\n\n  Latitude     Longitude         Ondulacao Goidal            Anomalia Goidal\n\n");

	fclose(Resul1);
	fflush(Resul1);
	return Resul1;
	}



