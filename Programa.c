//Murilo Simionato Arnemann
//Matrícula: 18/0107453
//argv[1]->imagem 	argv[2]->tp de process. 	argv[3]->tamanho da media 		argv[4]->img output
#include <stdio.h>
#include <stdlib.h>

//FUNCA0 QUICKS0RT PARA CALCULAR A MEDIA 
void QuickSort(unsigned char *vetor, int inicio, int fim){

    int pivo, esq, dir, meio, aux;

//LIMITES D0 VET0R ANALISAD0
    esq = inicio;
    dir = fim;

//DEFINE 0S AUXILIARES N0 CENTR0 D0 VET0R
    meio = (int) ((esq + dir)/2);
    pivo = *(vetor+meio);

    while(dir > esq){

//VERIFICA SE 0 LAD0 ESQUERD0 D0 VET0R É MEN0R QUE 0 MEI0 
        while(*(vetor+esq) < pivo){
            esq = esq + 1;
        }

//VERIFICA SE 0 LAD0 DIREIT0 D0 VET0R É MAI0R QUE 0 MEI0
        while(*(vetor+dir) > pivo){
            dir = dir - 1;
        }

//VERIFICA SE 0 LAD0 DIREIT0 AINDA É MAI0R QUE O ESQUERD0
        if(esq <= dir){

    //TR0CA 0S VET0RES DE P0SIÇA0
            aux = *(vetor+esq);
            *(vetor+esq) = vetor[dir];
            *(vetor+dir) = aux;

    //ALINHA 0S AUXILIARES
            esq = esq + 1;
            dir = dir - 1;
        }
    }

//VERIFICA SE AINDA É NECESSÁRI0 R0DAR 0 PR0GRAMA
    if(inicio < dir){
        QuickSort(vetor, inicio, dir);
    }
    if(esq < fim){
        QuickSort(vetor, esq, fim);
    }

}


//STRUCT QUE ARMAZENA OS DADOS DO BITMAP
typedef struct dados_da_imagem{

	char 		id [2]  		;
	unsigned   int size    		;
    unsigned   int reserved		;
	unsigned   int offset  		;
	unsigned   int header  		;
	unsigned   int width 		;
	unsigned   int height  		;
	unsigned short int planes  	;
	unsigned short int bpp	   	;
	unsigned   int compres 		;
	unsigned   int dsize   		;
	unsigned   int horiRes 		;
	unsigned   int vertRes 		;
	unsigned   int colors  		;
	unsigned   int pallete 		;
	unsigned   int means   		;
} imagem;

int main(int argc, char *argv[]){

//VERIFICA SE O USUARIO COLOCOU A QUANTIDADE CORRETA DE PARAMETROS
	if(argc !=5){
		printf("Argumentos insuficientes!");
		exit(1);
	}

	if((atoi(argv[3])%2)==0){
		printf("Escolha um numero impar para a media na proxima vez!\nAperte enter para continuar!\n");
		//exit(2);  //Caso o programador aceite apenas numeros impares
		getchar();
	}

//DEFININDO OS PONTEIROS DE PONTEIROS PARA GERAR AS MATRIZES
	unsigned char **matR,**matG,**matB;
	unsigned char **matRfilt,**matGfilt,**matBfilt;
//DEFININDO O VETOR PRO QUICKSORT
	unsigned char *vetorR, *vetorG, *vetorB;
//DEFININDO AS VARIAVEIS AUXILIARES
	unsigned int i,j;
	int k,l,x, media, borda, meiov, mediav,teste;
//CRIANDO O VETOR DE PADDING
	char padding[4];

//DEFININDO A VARIAVEL DO STRUCT
	imagem bmp;
//DEFININDO UM PONTEIRO DO TIPO FILE PARA OS ARQUIVOS DE ENTRADA E DE SAIDA
	FILE *file;
	FILE *nfile;
//ABRINDO/CRIANDO OS ARQUIVOS DE INPUT DO USUARIO
	nfile = fopen(argv[4], "wb");
	file = fopen(argv[1], "rb");

//ARMAZENANDO OS DADOS DO BITMAP NO STRUCT
	fread(&bmp.id[0]   , 1,1,file);
	fread(&bmp.id[1]   , 1,1,file);
	fread(&bmp.size, 4,1,file);
	fread(&bmp.reserved, 4,1,file);
	fread(&bmp.offset  , 4,1,file);
	fread(&bmp.header  , 4,1,file);
	fread(&bmp.width , 4,1,file);
	fread(&bmp.height  , 4,1,file);
	fread(&bmp.planes  , 2,1,file);
	fread(&bmp.bpp     , 2,1,file);
	fread(&bmp.compres , 4,1,file);
	fread(&bmp.dsize   , 4,1,file);
	fread(&bmp.horiRes , 4,1,file);
	fread(&bmp.vertRes , 4,1,file);
	fread(&bmp.colors  , 4,1,file);
	fread(&bmp.pallete , 4,1,file);
	fread(&bmp.means   , 4,1,file);

//IMPRIMINDO NA TELA OS DADOS DO BITMAP
	printf("Magic Number:%c\n",bmp.id[0]);
	printf("Magic Number:%c\n",bmp.id[1]);
	printf("reserved:%i\n",bmp.reserved);
	printf("offset:%i\n",bmp.offset);
	printf("header:%i\n",bmp.header);
	printf("width:%i\n",bmp.width);
	printf("height:%i\n",bmp.height);
	printf("planes:%d\n",bmp.planes);
	printf("bpp:%d\n",bmp.bpp);
	printf("compres:%i\n",bmp.compres);
	printf("dsize:%i\n",bmp.dsize);
	printf("horiRes:%i\n",bmp.horiRes);
	printf("vertRes:%i\n",bmp.vertRes);
	printf("colors:%i\n",bmp.colors);
	printf("pallete:%i\n",bmp.pallete);
	printf("means:%i\n",bmp.means);

//DEFINE A BORDA E A MARGEM DAS MATRIZES A PARTIR DO INPUT DO USUARIO
	media = atoi(argv[3]);
	borda = media / 2;
	mediav = media*media;

//ALOCANDO OS VETORES
	vetorR = (unsigned char*)calloc(mediav, sizeof(unsigned char));
	vetorG = (unsigned char*)calloc(mediav, sizeof(unsigned char));
	vetorB = (unsigned char*)calloc(mediav, sizeof(unsigned char));

//GERA AS MATRIZES R, G, B, R(FILTRADA), B(FILTRADA) E G(FILTRADA) JA LEVANDO EM CONSIDERAÇAO A BORDA PARA AS MEDIAS 
	matR = (unsigned char**)calloc(bmp.height+(borda*2), sizeof(unsigned char*));
	matG = (unsigned char**)calloc(bmp.height+(borda*2), sizeof(unsigned char*));
	matB = (unsigned char**)calloc(bmp.height+(borda*2), sizeof(unsigned char*));

	for (i = 0; i <= ((bmp.height)+(borda*2))-1; ++i){
		*(matR+i) = (unsigned char*)calloc(bmp.width+(borda*2), sizeof(unsigned char));
		*(matG+i) = (unsigned char*)calloc(bmp.width+(borda*2), sizeof(unsigned char));
		*(matB+i) = (unsigned char*)calloc(bmp.width+(borda*2), sizeof(unsigned char));
	}

	matRfilt = (unsigned char**)calloc(bmp.height+(borda*2), sizeof(unsigned char*));
	matGfilt = (unsigned char**)calloc(bmp.height+(borda*2), sizeof(unsigned char*));
	matBfilt = (unsigned char**)calloc(bmp.height+(borda*2), sizeof(unsigned char*));

	for (i = 0; i <= ((bmp.height)+(borda*2))-1; ++i)	{
		*(matRfilt+i) = (unsigned char*)calloc(bmp.width+(borda*2), sizeof(unsigned char));
		*(matGfilt+i) = (unsigned char*)calloc(bmp.width+(borda*2), sizeof(unsigned char));
		*(matBfilt+i) = (unsigned char*)calloc(bmp.width+(borda*2), sizeof(unsigned char));
	}


//COPIA A IMAGEM ORIGINAL NAS MATRIZES 
	for(i=borda;i<(bmp.height+borda);i++){
		for(j=borda;j<(bmp.width+borda);j++){
			fread(*(matB+i)+j,1,1,file);
			fread(*(matG+i)+j,1,1,file);
			fread(*(matR+i)+j,1,1,file);
		}
		if(bmp.width%4 !=0){
			for (k =0;k<4-(bmp.width%4);++k){
				fread(&padding[k],1,1,file);
			}
		}
	}

//MENU DE SELEÇAO DO TIPO DE FILTRAGEM
	if(atoi(argv[2]) == 0){
	//FILTRAGEM POR MEDIA
		for(i=borda;i<((bmp.height)+(borda));i++){
			for(j=borda;j<((bmp.width)+(borda));j++){
				for(k=-1*borda;k<=borda;k++){
					for(l=-1*borda;l<=borda;l++){
						*(*(matBfilt+i)+j)+=(*(*(matB+(i+k))+(j+l)))/(media*media);
						*(*(matGfilt+i)+j)+=(*(*(matG+(i+k))+(j+l)))/(media*media);
						*(*(matRfilt+i)+j)+=(*(*(matR+(i+k))+(j+l)))/(media*media);
					}
				}
			}
		}
	}else if(atoi(argv[2]) == 1){
	//FILTRAGEM POR MEDIANA
		for(i=borda;i<((bmp.height)+(borda));i++){
			for(j=borda;j<((bmp.width)+(borda));j++){
				for(k=-1*borda;k<=borda;k++){
					for(l=-1*borda;l<=borda;l++){
						*(vetorB+((borda+l)+(media*(borda+k))))=(*(*(matB+(i+k))+(j+l)));
						*(vetorG+((borda+l)+(media*(borda+k))))=(*(*(matG+(i+k))+(j+l)));
						*(vetorR+((borda+l)+(media*(borda+k))))=(*(*(matR+(i+k))+(j+l)));
					}
				}
				QuickSort(vetorB, vetorB[0], mediav);
				QuickSort(vetorG, vetorG[0], mediav);
				QuickSort(vetorR, vetorR[0], mediav);
				*(*(matBfilt+i)+j) = *(vetorB+((int)(mediav)/2));
				*(*(matGfilt+i)+j) = *(vetorG+((int)(mediav)/2));
				*(*(matRfilt+i)+j) = *(vetorR+((int)(mediav)/2));
			}
		}
		
	}else{
		printf("Argumento de Filtragem Invalido\n");
		exit(1);
	}

//COPIA NO ARQUIVO DE SAIDA OS DADOS DO BITMAP DE ENTRADA
	fwrite(&bmp.id[0]   , 1,1,nfile);
	fwrite(&bmp.id[1]   , 1,1,nfile);
	fwrite(&bmp.size 	, 4,1,nfile);
	fwrite(&bmp.reserved, 4,1,nfile);
	fwrite(&bmp.offset  , 4,1,nfile);
	fwrite(&bmp.header  , 4,1,nfile);
	fwrite(&bmp.width , 4,1,nfile);
	fwrite(&bmp.height  , 4,1,nfile);
	fwrite(&bmp.planes  , 2,1,nfile);
	fwrite(&bmp.bpp     , 2,1,nfile);
	fwrite(&bmp.compres , 4,1,nfile);
	fwrite(&bmp.dsize   , 4,1,nfile);
	fwrite(&bmp.horiRes , 4,1,nfile);
	fwrite(&bmp.vertRes , 4,1,nfile);
	fwrite(&bmp.colors  , 4,1,nfile);
	fwrite(&bmp.pallete , 4,1,nfile);
	fwrite(&bmp.means   , 4,1,nfile);

//COPIA NO ARQUIVO DE SAIDA A IMAGEM FILTRADA
	for(i=borda;i<(bmp.height+borda);i++){	
		for(j=borda;j<(bmp.width+borda);j++){
			fwrite(*(matBfilt+i)+j,1,1,nfile);
			fwrite(*(matGfilt+i)+j,1,1,nfile);
			fwrite(*(matRfilt+i)+j,1,1,nfile);
		}

		if(bmp.width%4 !=0){	
			for(k=0;k<4-(bmp.width%4);k++){
				fwrite(&padding[k],1,1,nfile);
			}
		}
	}

//FECHA OS ARQUIVOS
	fclose(file);
	fclose(nfile);

//LIBERA A ALOCAÇAO DAS MATRIZES		
	for(i=0;i<=bmp.height-1;i++){
		free(*(matR+i));
		free(*(matG+i));
		free(*(matB+i));
		free(*(matRfilt+i));
		free(*(matGfilt+i));
		free(*(matBfilt+i));
	}

	free(matR);
	free(matG);
	free(matB);
	free(matRfilt);
	free(matGfilt);
	free(matBfilt);
	free(vetorB);
	free(vetorG);
	free(vetorR);

	return 0;
}

