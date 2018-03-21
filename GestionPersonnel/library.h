//
//  library.h
//  GestionPersonnel
//
//  Created by Pierre Kettmus on 13/03/2018.
//  Copyright © 2018 Pierre Kettmus. All rights reserved.
//

#ifndef library_h
#define library_h

#include <stdio.h>

typedef struct Date {
    int Day;
    int Month;
    int Year;
} Date;

typedef struct informations {
    int id;
    char * Name;
    char * FirstName;
    char * Restaurant;
    int idrestaurant;
    Date Date;
    int Age;
} Informations;

typedef struct restaurant {
    int id;
    char * Name;
} Restaurant;

char * getString(void);
void generateQR(char * info);
void getTime(Date * date);
void createXml(Informations information, char * name);
char * xmlName(Informations information);
static void printQr(const uint8_t qrcode[]) ;
#endif /* library_h */
