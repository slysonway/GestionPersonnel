//
//  database.c
//  GestionPersonnel
//
//  Created by Pierre Kettmus on 20/03/2018.
//  Copyright © 2018 Pierre Kettmus. All rights reserved.
//

#include "database.h"
#include <my_global.h>
#include <mysql.h>
#include "library.h"
#include <stdlib.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

Restaurant * getRestaurant()
{
    Restaurant * _restaurant = NULL;
    MYSQL *con = mysql_init(NULL);
    int i = 0;
    
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    
    
    if (mysql_real_connect(con, "localhost", "root", "root",
                           "2A2_test", 8889, "/Applications/MAMP/tmp/mysql/mysql.sock", 0) == NULL)
    {
        finish_with_error(con);
    }
    
    if (mysql_query(con, "SELECT id_restaurant, nom FROM restaurant"))
    {
        finish_with_error(con);
    }
    
    
    MYSQL_RES *result = mysql_store_result(con);
    
    if (result == NULL)
    {
        finish_with_error(con);
    }
    
    _restaurant = malloc(sizeof(Restaurant) * result->row_count);
    
    int num_fields = mysql_num_fields(result);
    
    MYSQL_ROW row;
    
    while ((row = mysql_fetch_row(result)))
    {
        _restaurant[i].id = atoi(row[0]);
        _restaurant[i].Name = row[1];
        i++;
    }
    
    //mysql_free_result(result);
    mysql_close(con);
    
    return _restaurant;
}
