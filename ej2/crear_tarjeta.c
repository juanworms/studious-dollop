#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "herramientas.h"


int main () {
    FILE* pf = fopen("card.dat", "wb");
    char buffer[200];
    card_t temp;
    while (1)
    {
        
        printf("\nIngrese label\n");
        fgets(buffer, 255, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        while (!(strlen(buffer) <= 8)){
            printf("\nEl label debe ser maximo 8 chars\n");
            fgets(buffer, 200, stdin);
            borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
        }
        
        strcpy(temp.label, buffer);
        printf("Label de la tarjeta: %s", temp.label);
        
        
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
        fwrite(&temp,sizeof(card_t),1,pf);
        printf("\nresponder n or N para terminar\n");
        fgets(buffer, 255, stdin);
        if ( (buffer[0] == 'n') || (buffer[0] == 'N')) {break;}
    }
    fclose(pf);
    return 0;
}