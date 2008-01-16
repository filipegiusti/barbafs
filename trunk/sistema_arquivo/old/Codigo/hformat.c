/*
 *  hformat.c
 *  
 *
 *  Created by Joao on 3/25/07.
 *  
 *
 */

#include "hformat.h"

struct bootData
{
	char bootStart[12];
	char boot[2*TAM_SETOR];
	char bootEnd[12];
}Boot={"bootStart","BOOT","bootEnd"};

int main(int argc, char *argv[])
{
	if (argc !=2)
		{
		printf("\nQuantidade invalida de parametros.");
		printf("\nDigite: hformtat 'identificacao do Disco Virtual' para formatar o disco virtual\n\n");
		}
	else
		formatDisk(argv[1]);
	return 0;
}

void formatDisk(char *diskName)
{
	FILE *disk;
	int SOSize,bitmapAddress;
		
	//Cria Disco Virtual
	disk=createDisk(diskName);
	if(disk==NULL)
		Error(0);
		  
  //Grava o Sistema Operacional
	SOSize=saveSO(&disk);

	//Grava setor de Boot
	bitmapAddress=saveBoot(&disk,SOSize);

	//Grava Mapa de Bits
	saveBitmap(&disk,bitmapAddress);
	
	//Grava Diretório
	saveRootDirectory(&disk,bitmapAddress);
              
	fclose(disk);
}

FILE *createDisk(char *diskName)
{
	FILE *disk;
	char zero=0;
	int i;
	
	disk=fopen(diskName,"wb");
	if(disk!=NULL)
		{
		//Cria um Disco Virtual vazio de 2MB
		for (i=0;i<TAM_SETOR*4096;i++)
			fwrite(&zero,sizeof(char),1,disk);
		}
	return disk;
}

int saveBoot(FILE **disk,int SOSize)
{
	char boot[2*TAM_SETOR];
	char sign1={0x77};
	char sign2={0x33};
	short int bitmapAddress;
	int i,SOSectors;
	float auxSector=TAM_SETOR;
	float auxSOSize=SOSize;
	
	for(i=0; i<2*TAM_SETOR; i++)
		{
		boot[i] = Boot.boot[i];
		}
	boot[i] = '\0';
	
	//Quantidade de setores utilizada pelo Sistema Operacional mais uma quantidade extra de 20% para o caso de atualizacoes
	SOSectors=ceil((SOSize/auxSector));
	SOSectors=SOSectors+ceil(SOSectors*0.2);
	
	//Grava o Boot nos setores 0 e 1
	fseek(*disk,0,SEEK_SET);
	fwrite(&boot,sizeof(char),strlen(boot),*disk);
	
	//Grava a endereco do Mapa de Bits na antepenultima palavra do setor 1
	fseek(*disk,(TAM_SETOR)-(3*sizeof(short int)),SEEK_SET);
	bitmapAddress=2+SOSectors;
	fwrite(&bitmapAddress,sizeof(short int),1,*disk);

	//Salva o tamanho do Sistema Operacional na penultima palavra do setor 1
	fwrite(&SOSectors,sizeof(short int),1,*disk);
		
	//Insere as marcas no final do setor de boot
	fwrite(&sign1,sizeof(char),1,*disk);
	fwrite(&sign2,sizeof(char),1,*disk);

	return bitmapAddress;
}

int saveSO(FILE **disk)
{
	FILE *SO;
	int i;
	char tempSector[TAM_SETOR];
	struct stat file;
	float auxSector=TAM_SETOR;
	
	//Abre o arquivo executavel do Sistema Operacional
	SO=fopen("hpsys.exe","rb");
	stat("hpsys.exe",&file);
	if(SO==NULL)
		Error(1);
	
	//Posiciona e grava o Sistema Operacional no disco virtual
	fseek(*disk,2*TAM_SETOR,SEEK_SET);
	for(i=0;i<ceil(file.st_size/auxSector);i++)
		{
		fread(tempSector,sizeof(char),TAM_SETOR,SO);
		fwrite(tempSector,sizeof(char),TAM_SETOR,*disk);
		}
	fclose(SO);
	
	return file.st_size;
}

void saveBitmap(FILE **disk,int bitmapAddress)
{
	char bitmap[TAM_SETOR];
	char byte=255;
	int i,j=0;
	
	//Zera o Mapa de Bits
	for (i=0;i<TAM_SETOR;i++)
		bitmap[i]=255;
	
	//Marca como utilizados todos os setores ate o Mapa de Bits mais 2 setores do Diretorio Raiz
	for (i=0;i<=(bitmapAddress+2);i++)
		{
		if((i!=0)&&((i%(sizeof(char)*8))==0))
			{
			bitmap[j]=byte;
			byte=255;
			j++;
			}
		byte=(byte<<1);
		}
	bitmap[j]=byte;

	//Posiciona para gravacao do Mapa de Bits
	fseek(*disk,bitmapAddress*TAM_SETOR,SEEK_SET);
	fwrite (bitmap,sizeof(char),TAM_SETOR,*disk);
}

void saveRootDirectory(FILE **disk,int bitmapAddress)
{
	short int dirAddress=bitmapAddress+1;
	short int dirLength=2;
	short int aux;

	//Posiciona e grava o mapa de paginas do diretorio
	fseek(*disk,((dirAddress)*TAM_SETOR),SEEK_SET);
	fwrite (&dirLength,sizeof(short int),1,*disk);
	aux=(dirAddress);
	fwrite (&aux,sizeof(short int),1,*disk);
	aux=(dirAddress+1);
	fwrite (&aux,sizeof(short int),1,*disk);
}

int Error(int errorID)
{
	switch (errorID)
	{
		case	0:
			//Erro na criação do disco virtual
			printf("\n\tOcorreu um erro na criação do disco.\n");
		case	1:
			//Erro na leitura
			printf("\n\tOcorreu um erro na leitura.\n");
	}
	exit(1);
}

