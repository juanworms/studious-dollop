#ifndef STRUCTS
#define STRUCTS

typedef struct request
{
  char typeMesagge[4];
  char *cardNumber;
  char amount[13];
  char securityCode[3];
} request_t;

typedef struct response
{

  char typeMessage;
  char responseCode[2];
} response_t;

typedef struct range
{
  char rangeLow[8 + 1];
  char rangeHigh[8 + 1];
  unsigned char len;
  int id;
} range_t;

typedef struct
{
  char label[12 + 1];
  int id;
} card_t;

#endif