#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "structs.h"

#define MAX_CARACTERES 200

/* Coloca un '\0' en la posicion index del string */
void borrar_char_colocar_zero(char (*buffer)[200], size_t index)
{
  char *p_char = *buffer;
  p_char[index] = '\0';
}

char *convertirAmonto(char (*buffer)[200], size_t tamanio)
{
  size_t index = 0;
  size_t cerosAcolocar = (12 - tamanio);
  char *montoConvertido = NULL;
  montoConvertido = malloc(sizeof(char) * 13);

  char *p_char = *buffer;
  //llenar de 0 el frente
  for (; index < cerosAcolocar; index++)
  {
    montoConvertido[index] = '0';
  }

  for (size_t index2 = 0; index2 <= tamanio; index2++)
  {

    montoConvertido[index + index2] = p_char[index2];
  }

  return montoConvertido;
}

bool buffer_es_numerico(char (*buffer)[200], size_t bufferSize)
{
  size_t index = 0;

  //puntero que recorre de char en char
  char *p_char = *buffer;
  while ((p_char[index] != '\0') && (p_char[index] != '\n') && (p_char[index] != '\r'))
  {
    if (!isdigit(p_char[index]))
      return false;
    index++;
  }
  return true;
}

char *extraerLabel(char (*buffer)[200]){
  char *labelARetornar = NULL;
  FILE *pf;
  range_t rangueTemp;
  int idEncontrado = 0;
  card_t cardTemp;
  //verificar el rango, la longitud y sustraer el id
  pf = fopen("rango.dat", "rb");
  if (pf == NULL) {
    printf("\nArchivo rango.dat no encontrado, se genero previamente?\n");
    return labelARetornar;
  }
  while (!feof(pf) && !ferror(pf) && (idEncontrado == 0))
  {
    fread(&rangueTemp, sizeof(range_t), 1, pf);

    //Verificar si esta en el rango
    if ((strncmp(rangueTemp.rangeLow, *buffer, 8) <= 0) && (strncmp(rangueTemp.rangeHigh, *buffer, 8) >= 0))
    {
      //comparar las Longitudes
      if (((int)rangueTemp.len) == ((int)strlen(*buffer))){

        idEncontrado = rangueTemp.id;
        
      }
    }
  }
  fclose(pf);

  pf = fopen("card.dat", "rb");
  if (pf == NULL) {
    printf("\nArchivo card.dat no encontrado, se genero previamente?\n");
    return labelARetornar;
  }
  while (!feof(pf) && !ferror(pf) && (labelARetornar == NULL))
  {
    fread(&cardTemp, sizeof(card_t), 1, pf);

    //buscar quien posee el ID
    if (cardTemp.id == idEncontrado)
    {
      //Sustraer el label
      labelARetornar = malloc(sizeof(char) * (strlen(cardTemp.label) + 1));
      strcpy(labelARetornar, cardTemp.label);
    }
  }

  fclose(pf);

  return labelARetornar;
}

char* formatearNumero(char (*buffer)[200], size_t bufferSize){
  char* cardNumber = malloc(sizeof(char)* (bufferSize + 4));
  char* p_char = *buffer;

  snprintf(cardNumber, (bufferSize + 3), "%zu", bufferSize);

  for (size_t index = 0; index < bufferSize; index++){
   
    cardNumber[2+index] = p_char[index];
  }

  cardNumber[2+bufferSize] = '\0';
  return cardNumber;
}