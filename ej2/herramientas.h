#ifndef HERRAMIENTAS
#define HERRAMIENTAS
#include <stdbool.h>
#include "herramientas.c"

/*PRE: Recibe un arreglo de punteros a CHAR validos, y una posicion de ese arreglo, debe ser valido
POST: Coloca un '\0' en la posicion indicada
Coloca un '\0' en el index del buffer*/
void borrar_char_colocar_zero(char (*buffer)[200], size_t index);

/*PRE: recibe un vector de chars
Post: Devuelve TRUE si todos sus componentes son numeros, o False si alguno no lo es
*Verifica si el buffer contiene solo numeros*/
bool buffer_es_numerico(char (*buffer)[200], size_t bufferSize);

/*
PRE: recibe un vector de solo digitos
POST: devuelve un vector de 12 caracteres en memoria dinamica con "leading zeros"
*/
char *convertirAmonto(char (*buffer)[200], size_t tamanio);


/*
PRE: recibe un vector (string) que contiene el numero de una tarjeta
POST: devuelve NULL si no existe ningun registro/tarjeta o un vector dinamico con un puntero char* (el label de la tarjeta)
*/
char *extraerLabel(char (*buffer)[200]);

/*PRE: recibe un vector de numeros y la longitus del mismo
POST: devuelve un vector cuyo 2 primeros caracteres son la longitud del numero de tarjeta. termina en caracter Nulo
*/
char* formatearNumero(char (*buffer)[200],size_t tamanio);
/*  HERRAMIENTAS */
#endif 