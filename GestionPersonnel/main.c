//
//  main.c
//  GestionPersonnel
//
//  Created by Pierre Kettmus on 13/03/2018.
//  Copyright © 2018 Pierre Kettmus. All rights reserved.
//

#include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, const char * argv[]) {
    
    //int FakeId = 0;
    Informations people;
    char * ch = malloc(200);
    int choice = 0;
    
    printf("id: ");
    scanf("%d", &people.id);
    
    printf("Nom: ");
    people.Name = getString();
    
    ch[0] = '\0';
    printf("Prénom: ");
    people.FirstName = getString();
    
    printf("Choisissez un restaurant: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            people.Restaurant = "bastille";
            break;
        
        case 2:
            people.Restaurant = "republique";
            break;
            
        default:
            break;
    }

    printf("Age: ");
    scanf("%d", &people.Age);
    
    getTime(&people.Date);
    
    generateQR(xmlName(people));
    createXml(people, strcat(xmlName(people), ".xml"));
    free(ch);
    
    
    return 0;
}

