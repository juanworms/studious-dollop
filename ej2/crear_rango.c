#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "herramientas.h"
#include "structs.h"


int main(){
    FILE* pf = fopen("rango.dat", "wb");
    char buffer[200];
    
    range_t temp;
    while (1){
        
        printf("\nIngrese rangelow\n");
        fgets(buffer, 200, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        while (!buffer_es_numerico(&buffer,strlen(buffer)) || !(strlen(buffer) == 8)){
        printf("\nRangeLow debe ser 8 digitos\n");
        fgets(buffer, 200, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        }
        
        strcpy(temp.rangeLow , buffer);
        printf("RANGELOW: %s", temp.rangeLow);


        printf("\nIngrese rangehigh\n");
        
        fgets(buffer, 200, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        while (!buffer_es_numerico(&buffer,strlen(buffer)) || !(strlen(buffer) == 8)){
            printf("\nRangeHigh debe ser 8 digitos\n");
            fgets(buffer, 200, stdin);
            borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        }
        
        strcpy(temp.rangeHigh , buffer);
        printf("RANGEHight: %s", temp.rangeHigh);

        


        printf("\nIngrese longitud \n");
        fgets(buffer, 200, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);

        while (!buffer_es_numerico(&buffer,strlen(buffer))){
            printf("\nLongitud debe ser numero\n");
            fgets(buffer, 200, stdin);
            borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        }

        temp.len = (unsigned char)atoi(buffer);
        
        printf("\nLongitud escrita: %i\n", temp.len);
        
        
        
        printf("\nIngrese ID \n");
        fgets(buffer, 200, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);

        while (!buffer_es_numerico(&buffer,strlen(buffer))){
            printf("\nId debe ser mayor a 0 y numerico\n");
            fgets(buffer, 200, stdin);
            borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        }

        temp.id = (unsigned char)atoi(buffer);
        
        printf("\nID escrita: %i\n", temp.id);

        // Worki
        fwrite(&temp,sizeof(range_t),1,pf);
        printf("\nresponder n or N para terminar\n");
        fgets(buffer, 200, stdin);
        if ( (buffer[0] == 'n') || (buffer[0] == 'N')) {break;}
    }
    fclose(pf);

    return 0;
}