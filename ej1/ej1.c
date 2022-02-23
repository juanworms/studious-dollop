#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_manipulation.h"
#include "lista_se.h"
#define MAX_BUFFER 255

//talvez hacer una lista que es dinamica

int main(){

    void *actualPointer;
    lista_se_t *dataInMemory;
    dataInMemory = crear_lista();
    char buffer[MAX_BUFFER];
    bool zeroDetected = false;
    bool endOfBuffer = false;
    while (!zeroDetected){
        endOfBuffer = false;
		printf("\nIngrese numeros enteros, cualquier 0 sera tratado como endOfBuffer de entrada\n");
        fgets(buffer, MAX_BUFFER, stdin);
        
        size_t indexOfBuffer = 0;
        do{

            actualPointer = (void*)copiarDiezCaracteres(&buffer, &indexOfBuffer, &zeroDetected, &endOfBuffer);
            insertar(dataInMemory, actualPointer);

        } while (!endOfBuffer);
    }
	printf("\nColoque el nombre del archivo a guardar: ");
    //Descargar la memoria en un txt
    fgets(buffer, MAX_BUFFER, stdin);
    FILE *pf;
    strtok(buffer, "\r");
    borrar_char_colocar_zero(buffer, strlen(buffer) - 1);
    pf = fopen(buffer, "wt");
    //verificar si se abrio el archivo
    if (pf == NULL){
        printf("\nNo se pudo crear el archivo, abortando\n");
        return 1;
    }
    else{
        while (!vacia(dataInMemory)){
            fprintf(pf, "%s", (char *)elemento_en_posicion(dataInMemory, 0));
            free(elemento_en_posicion(dataInMemory, 0));
            borrar_de_posicion(dataInMemory, 0);
        }
        destruir_lista(dataInMemory);
        fclose(pf);
        printf("\nFinalizado\n");
    }
    return 0;
}