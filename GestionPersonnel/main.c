//
//  main.c
//  GestionPersonnel
//
//  Created by Pierre Kettmus on 13/03/2018.
//  Copyright © 2018 Pierre Kettmus. All rights reserved.
//

#include "library.h"
#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, const char * argv[]) {
    //int FakeId = 0;
    Informations people;
    char * ch = malloc(200);
    int choice = 0;
    int index = 0;
    
    Restaurant* _restaurants = getRestaurant();
    do {
        printf("Restaurant: \n");
        while (_restaurants[index].id && _restaurants[index].Name) {
            printf("%d: ", index);
            printf("%s", _restaurants[index].Name);
            printf("\n");
            index++;
        }
        index = 0;
        
        printf("Choisiser un restaurant dans la liste: ");
        scanf("%d", &choice);
        if (_restaurants[choice].id || _restaurants[choice].Name) {
            people.idrestaurant = _restaurants[choice].id;
            people.Restaurant = _restaurants[choice].Name;
        } else {
            printf("Ce choix n'existe pas\n");
        }
        
    } while (!_restaurants[choice].id || !_restaurants[choice].Name);

    
    printf("Nom: ");
    people.Name = getString();
    
    ch[0] = '\0';
    printf("Prénom: ");
    people.FirstName = getString();

    printf("Age: ");
    scanf("%d", &people.Age);
    
    printf("\n");
    
    people.id = addUser(people);
    
    getTime(&people.Date);
    
    generateQR(xmlName(people));
    createXml(people, strcat(xmlName(people), ".xml"));
    free(ch);
    
    
    return 0;
}

