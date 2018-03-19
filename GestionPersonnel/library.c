//
//  library.c
//  GestionPersonnel
//
//  Created by Pierre Kettmus on 13/03/2018.
//  Copyright © 2018 Pierre Kettmus. All rights reserved.
//

#include "library.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "qrcode/qrcodegen.h"

char * getString() {
    char * ch = malloc(200);
    fpurge(stdin);
    fgets(ch, 200, stdin);
    ch[strlen(ch) - 1] = '\0';
    
    ch = realloc(ch, strlen(ch) + 1);
    
    return ch;
}

void getTime(Date * date) {
    time_t currentTime = time(NULL);
    struct tm tm = * localtime(&currentTime);
    char buffer[128];
    
    strftime(buffer, 128, "%d/%m/%Y", &tm);
    sscanf(buffer, "%d/%d/%d", &date -> Day, &date -> Month, &date -> Year);
}


void createXml(Informations information, char * name) {
    char * dst = malloc(1024);
    char * tmp = malloc(1024);
    FILE * pf = fopen(name, "w");

    
    
    if (pf != NULL) {
        
        fprintf(pf, "%s", "<?xml version=\"1.0\"?>\n");
        fprintf(pf, "%s", "<information>\n");
        sprintf(tmp, "%d", information.id);
        dst[0] = '\0';
        fprintf(pf, "%s", strcat(strcat(strcat(dst, "\t<id>"), tmp), "</id>\n"));
        dst[0] = '\0';
        fprintf(pf, "%s", strcat(strcat(strcat(dst, "\t<Name>"), information.Name), "</Name>\n"));
        dst[0] = '\0';
        fprintf(pf, "%s", strcat(strcat(strcat(dst, "\t<FirstName>"), information.FirstName), "</FirstName>\n"));
        dst[0] = '\0';
        sprintf(tmp, "%d", information.Age);
        fprintf(pf, "%s", strcat(strcat(strcat(dst, "\t<Age>"), tmp), "</Age>\n"));
        dst[0] = '\0';
        fprintf(pf, "%s", strcat(strcat(strcat(dst, "\t<Restaurant>"), information.Restaurant), "</Restaurant>\n"));
        fprintf(pf, "%s", "</information>\n");
    }
    
    free(tmp);
    free(dst);
    
    fclose(pf);
}

char * xmlName(Informations information) {
    char * dst = malloc(1024);
    char * tmp = malloc(1024);
    
    sprintf(tmp, "%d", information.id);
    strcat(dst, tmp);
    strcat(dst, information.Restaurant);
    sprintf(tmp, "%d", information.Date.Month);
    strcat(dst, tmp);
    sprintf(tmp, "%d", information.Date.Year);
    strcat(dst, tmp);
    strcat(dst, ".xml");
    
    free(tmp);
    return  dst;
}


/*---- Demo suite ----*/

// Creates a single QR Code, then prints it to the console.
void generateQR(char * info) {
    const char *text = info;  // User-supplied text
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level
    
    // Make and print the QR Code symbol
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (ok)
        printQr(qrcode);
}

/*---- Utilities ----*/
//Will change by generate a bitmap image
// Prints the given QR Code to the console.
void printQr(const uint8_t qrcode[]) {
    FILE *pf;
    pf = fopen("file", "w" );
    int size = qrcodegen_getSize(qrcode);
    int border = 4;
    char test[2] = {'1', '1'};
    
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 25; x++) {
            //fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
            fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
            fwrite((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), 1, 2, pf);
        }
        fputs("\n", stdout);
        fwrite("\n", 1, 1, pf);
    }
    
    fputs("\n", stdout);
    fwrite("\n", 1, 1, pf);
    fclose(pf);
}



