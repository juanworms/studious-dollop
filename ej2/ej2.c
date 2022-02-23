#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "socket.h"
#include "herramientas.h"

#define MAX_BUFFER 200
#define DESTIP "127.0.0.1"

int main () {
    char buffer[MAX_BUFFER];
    request_t requestData;
    response_t respuesta;
    char* label = NULL;
    
    printf("\nIngrese el monto: ");
    fgets(buffer, MAX_BUFFER, stdin);
    borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
    
    while (!buffer_es_numerico(&buffer,strlen(buffer)) || !(strlen(buffer) <= 12)){
        printf("\nCaracteres invalidos o monto mayor a 12 caracteres");
        fgets(buffer, MAX_BUFFER, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
    }
    //setear monto
    char* montoTemp = convertirAmonto(&buffer,strlen(buffer));
    
    strcpy(requestData.amount,montoTemp);
    free(montoTemp);

    
    printf("\nIngrese numero de tarjeta\n");
    fgets(buffer, MAX_BUFFER, stdin);
    borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
    
     while (!buffer_es_numerico(&buffer,strlen(buffer)) || !(strlen(buffer) >= 13))
     {
        printf("\nNumero de tarjeta no es numerico o longitud menor a 13\n");
        fgets(buffer, MAX_BUFFER, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
     }
    

    requestData.cardNumber = formatearNumero(&buffer, strlen(buffer));
    
    //Verificar que es una tarjeta valida
    label = extraerLabel(&buffer);
    
    if ( label == NULL ) {
        printf("\nTARJETA NO SOPORTADA\n");
        free(requestData.cardNumber);
        return 1;
    }
    
    
    printf("Tarjeta presentada: %s", label);
    free(label);
    
    //meterle al request mensaje 2 digitos len, el resto de los numeros

    printf("\nColoque los 3 digitos de seguridad\n");
    fgets(buffer, MAX_BUFFER, stdin);
    borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
    while (!buffer_es_numerico(&buffer,strlen(buffer)) || !(strlen(buffer) == 3)){
        printf("\nEl codigo de seguridad debe ser 3 digitos\n");
        fgets(buffer, MAX_BUFFER, stdin);
        borrar_char_colocar_zero(&buffer, strlen(buffer)-1);
     }
     printf("Codigo de Seguridad: %s\n", buffer);

    //copiar el codigo de seguridad
    strncpy(requestData.securityCode, buffer,3);
    
    //Colocar la cabecera al request
    strcpy(buffer,"0200");
    strncpy(requestData.typeMesagge, buffer,4);

    //enviar el request msg
    
    int handle = socketCreate();

    if ( (int)handle == -1) {
        printf("\nERROR DE COMUNICACION\n");
        free(requestData.cardNumber);
        return -1;
    }

    if (socketConnect(handle,DESTIP,8080) == -1){
        printf("\nERROR DE COMUNICACION\n");
        free(requestData.cardNumber);
        return -1;
    }

    
    if (socketWrite(handle, (unsigned char*) &respuesta)){
        printf("\nERROR DE COMUNICACION\n");
        free(requestData.cardNumber);
        return -1;
    };

    if (socketRead(handle, (unsigned char*) &requestData, 5000)){
        printf("\nERROR DE COMUNICACION\n");
        free(requestData.cardNumber);
        return -1;
    };
    
    if (socketClose(handle)){
        printf("\nERROR DE COMUNICACION\n");
        free(requestData.cardNumber);
        return -1;
    };
    

    strcpy(buffer,"0210");
    strncpy(respuesta.responseCode, buffer,4);
   
    
    if ( (rand() % 1) == 0 ){
        printf("\n APROBADO\n");
    }
    else{
        printf("\n RECHAZADA\n");
    }

    free(requestData.cardNumber);
    return 0;
}