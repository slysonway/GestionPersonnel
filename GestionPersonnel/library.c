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
#include "PNGUtils.h"

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
    //strcat(dst, ".xml");
    
    free(tmp);
    return  dst;
}


/*---- Demo suite ----*/

// Creates a single QR Code, then prints it to the console.
void generateQR(char * info) {
    // The structure to manage the QR code
    QRCode qrcode;
    int border = 1;
    int **buffer;
    int **qrcodeBorder = NULL;
    int i, x, y;
    int size;

    
    // Allocate a chunk of memory to store the QR code
    uint8_t qrcodeBytes[qrcode_getBufferSize(1)];
    
    qrcode_initText(&qrcode, qrcodeBytes, 2, ECC_LOW, info);
    
    size = qrcode.size + (border * 2);
    qrcodeBorder = (int **)malloc(sizeof(int*) * size);
    for (i = 0; i < size; i++) {
        *(qrcodeBorder + i) = (int *) malloc(sizeof(int) * size);
     }
    
    for (x = 0; x < size; x++) {
        for (y = 0; y < size; y++) {
            qrcodeBorder[x][y] = 0;
            //printf("%s", qrcode_getModule(&qrcode, x, y)? "##" : "  ");
        }
        //printf("\n");
    }
    //printf("\n");
    
    
    for (x = border; x < (size - border); x++) {
        for (y = border; y < (size - border); y++) {
            qrcodeBorder[x][y] = qrcode_getModule(&qrcode, (x - border), (y - border));
            //printf("%s", qrcodeBorder[x][y]? "##": "  ");
            //printf("%s", qrcode_getModule(&qrcode, (x - border), (y - border))? "##" : "  ");
        }
        //printf("\n");
    }
    //printf("\n");
    
    
    buffer = (int**)malloc(sizeof(int *) * 270);
    
    for (i = 0; i < 270; i++) {
        *(buffer + i) = (int *)malloc(sizeof(int) * 270);
    }
    
    resizeBitMap(qrcodeBorder, 270, buffer, size);
    generatePNG(buffer, info);
}

