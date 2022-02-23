# Ej2

## Estrategia

Al inicio se solicitan todos los datos para realizar la operacion, se validan las entradas. Luego se verifica la presencia del numero de tarjeta en rangos.dat, si se encuentra, se identifica el Label dentro de los card.dat. Despues de esto, se envian los datos y se lee la respuesta.

## Supuestos

- al usar los generadores, el usuario conoce previamente los IDs intervinientes
- Los IDs de las tarjetas son numeros positivos
- SocketRead devuelve -1 si se excede el TimeOut


## Compilación

Se incluye un makefile para con los comandos:
 - build
 - run
 - crearRango
 - crearTarjeta
 - debug

## Incluye
- Un generador de rangos.dat
- Un generador de card.dat

# Uso del Generador de Rangos y Tarjetas
Luego de compilar cualquiera de ambos, ejecutar y seguir las intrucciones por pantalla. 
Se generara un archivo rangos.dat para el generador de rangos o card.dat para el generador de tarjetas.
Ambos archivos estan Hardcodeados para usarse en el ej2

## Simulador vs Realidad
### Lo que el simulador realiza
- No hay envio y recepcion "Real" de datos.
- El codigo de respuesta no se lee desde el socket, esta mockeado en el main del ej2
- No se usa realmente el codigo de respuesta(socketWrite no escribe sobre el), se genera uno en el main.
- Abrir y cerrar el socket se llaman una vez, el proceso de lectura y escritura puede ser un loop, aqui no lo es.
- Todos los llamados a las funciones de socket, tienen un 5% de probabilidad de fallar


# Mejoras
- Nombres mas descriptivos y respetar camelCase or snake_case




 
