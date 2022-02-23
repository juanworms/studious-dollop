#ifndef STRING_MANIPULATION
#define STRING_MANIPULATION
#include <stdbool.h>

/*PRE: Recibe un arreglo de punteros a CHAR validos, y una posicion de ese arreglo, debe ser valido
POST: Coloca un '\0' en la posicion indicada
Coloca un '\0' en el index del buffer*/
void borrar_char_colocar_zero (char* buffer, size_t index);

/*PRE: recibe un vector de chars
Post: Devuelve TRUE si todos sus componentes son numeros, o False si alguno no lo es
*Verifica si el buffer contiene solo numeros*/
int buffer_es_numerico(char* buffer);

/*
PRE: Recibe un buffer de caracteres y las secciona en cadenas de 10, colocandole los CRLF finales
Post: Devuleve 1 cadena por llamada o NULL si la cadena recibida empieza en 0 
*/
char* copiarDiezCaracteres(char (*buffer)[255], size_t* indexOfBuffer, bool* zeroDetected, bool* fin);
/*  STRING_MANIPULATION */
#endif 
