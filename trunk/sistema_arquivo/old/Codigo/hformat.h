/*
 *  hformat.h
 *  
 *
 *  Created by Joao on 3/25/07.
 * 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>

//Definicoes
#define TAM_SETOR 512

//Prototipos
void formatDisk(char *diskName);
FILE *createDisk(char *diskName);
int saveSO(FILE **disk);
int saveBoot(FILE **disk,int SOSize);
void saveBitmap(FILE **disk,int bitmapAddress);
void saveRootDirectory(FILE **disk,int bitmapAddress);
int Error(int errorID);

