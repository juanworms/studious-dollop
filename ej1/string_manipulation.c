#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define MAX_CARACTERES 10


/* Coloca un '\0' en la posicion index del string */
void borrar_char_colocar_zero (char* buffer, size_t index){
  buffer[index] = '\0';
}


bool buffer_es_numerico(char* buffer){
  size_t index = 0;
  while ( (buffer[index] != '\0') && (buffer[index] != '\n')  && (buffer[index] != '\r')){
    printf("%c", buffer[index]);
    if(!isdigit(buffer[index]))
      return false;
    index++;
  }
  if (buffer[index] == '\n')
    borrar_char_colocar_zero(buffer, index);
  return true;
}


bool esDigito(char* caracter){
  if (isdigit(*caracter) && (*caracter != '0')) {
    return true;
  }
  else
    return false;
}

void* copiarDiezCaracteres(char (*buffer)[255], size_t* indexOfBuffer, bool* zeroDetected, bool* endOfBuffer){
  
  char* p_char = *buffer;

  if ((p_char[*indexOfBuffer] == '\0' ) || (p_char[*indexOfBuffer] == 0xa) ) {
     (*endOfBuffer) = true;
    return NULL;
  }
  //Si el buffer comienza con el caracter 0
  if ((p_char[*indexOfBuffer] == '0')  ) {
     (*zeroDetected)= true;
     (*endOfBuffer) = true;
    return NULL;
  }
  char* p_arreglo = malloc(sizeof(char) * 13);

  //CharsLeidos sera mi indice de caracteres escritos en mi memoria pedida
  size_t charsLeidos = 0;

  while (charsLeidos < 10) {
    //Si el caracter actual es un digito
    if(esDigito(&p_char[*indexOfBuffer]) ) {
      p_arreglo[charsLeidos] = p_char[*indexOfBuffer];
      charsLeidos++;
      (*indexOfBuffer)++;
    }
    //Si no es digito o es un 0
    else if ((p_char[*indexOfBuffer] == '0') || (p_char[*indexOfBuffer] == '\0') || (p_char[*indexOfBuffer] == '\n') || (p_char[*indexOfBuffer] == '\r')) {
        
        //si es exclusivamente 0 el buffer
        if (p_char[*indexOfBuffer] == '0') {
          (*zeroDetected)= true;
          (*endOfBuffer) = true;
        //Si es otro de los caracteres finales: \r, \0, \n
        }
        else {
          (*endOfBuffer) = true;
        //llenar el resto de la memoria solicitada con '0'
        }
        for (; charsLeidos < 10; charsLeidos++){
          p_arreglo[charsLeidos] = '0';
        }
        break;
      }
      //Es un caracter no numerico
    else {
    (*indexOfBuffer)++;
    }
  }
 
  // Agregar los caracteres finales
  p_arreglo[charsLeidos] = '\r'; //CR
  charsLeidos++;
  p_arreglo[charsLeidos] = '\n'; //LF
  charsLeidos++;
  p_arreglo[charsLeidos] = '\0'; // NULL CHAR
  
  return p_arreglo;
}


