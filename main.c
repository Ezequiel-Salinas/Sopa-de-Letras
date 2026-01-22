#include "Funciones.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));
    Tablero tab;

    bienvenida();
    if(crearTablero(&tab) == TODO_OK)
    {
        iniciarTablero(&tab);

        if(iniciarPalabras(&tab) && iniciarPistas(&tab))
        {
            insertarPalabras(&tab);
            imprimirTablero(&tab);

            if(iniciaJuego(&tab))
                printf("\nJuego finalizado.\n");
        }
        liberarTablero(&tab);
    }

    return 0;
}
