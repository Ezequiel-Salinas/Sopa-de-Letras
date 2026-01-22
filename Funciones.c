#include "Funciones.h"

void bienvenida()
{
    printf("***************************************\n");
    printf("Bienvenido/a a la Sopa de letras.\n");
    printf("***************************************\n");
}

int crearTablero(Tablero *tab)
{
    int PosFalla = 0;
    printf("Ingrese el tamanio que debe tener el tablero (mayor o igual a 12): ");
    scanf("%d", &tab->tamanio);
    verificarTamanio(tab);

    tab->matriz = (char **)malloc(tab->tamanio * sizeof(char *));
    if(!tab->matriz)
    {
        printf("Error de programa. No hay memoria disponible.\n");
        return FALLA;
    }

    for(int i = 0; i < tab->tamanio; i++)
    {
        tab->matriz[i] = (char *)malloc(tab->tamanio * sizeof (char));
        if(!tab->matriz)
        {
            printf("Error de programa. No hay memoria disponible.\n");
            liberarTableroFalla(tab, PosFalla);
            return FALLA;
        }
        PosFalla++;
    }
    return TODO_OK;
}

int verificarTamanio(Tablero *tab)
{
    if(tab->tamanio >= DIMENSION)
    {
        limpiarBufferEntrada();
    }
    while(tab->tamanio < DIMENSION)
    {
        printf("\nEl tamanio debe ser mayor o igual a 12.\nIngrese nuevamente: ");
        scanf("%d", &tab->tamanio);
        limpiarBufferEntrada();
    }
    return tab->tamanio;
}

void liberarTableroFalla(Tablero *tab, int PosFalla)
{
    for(int i = PosFalla; i >= 0; i--)
    {
        free(tab->matriz[i]);
    }
    free(tab->matriz);
    tab->matriz = NULL;
}

void iniciarTablero(Tablero *tab)
{
    for(int i = 0; i < tab->tamanio; i++)
    {
        for(int j = 0; j < tab->tamanio; j++)
        {
            tab->matriz[i][j] = '\0';
        }
    }
}

void imprimirTablero(Tablero *tab)
{
    for(int i = 0; i < tab->tamanio; i++)
    {
        for(int j = 0; j < tab->tamanio; j++)
        {
            printf("%1c  ",tab->matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimirPista(Tablero *tab)
{
   for(int i = 0; i < tab->cantPal; i++)
   {
        if(*tab->pista[i] != '\0')
            printf("%s\n", tab->pista[i]);
   }
}

bool iniciarPalabras(Tablero *tab)
{
    int i = 0;

    FILE *archPal;
    archPal = fopen("Palabras.txt", "r");
    if(archPal == NULL)
    {
        printf("No se pudo abrir el archivo de las palabras.");
        return false;
    }
    if(cantidadPalabras(tab) == false)
    {
        printf("No se pudo abrir el archivo de las palabras.");
        return false;
    }
    if(tab->cantPal == 0)
    {
        printf("\nEl archivo de palabras esta vacio.\n");
        return false;
    }
    while(i < tab->cantPal && fscanf(archPal, "%15s", tab->pal[i]) == 1)
    {
        i++;
    }
    fclose(archPal);
    return true;
}

bool iniciarPistas(Tablero *tab)
{
    int i = 0;

    FILE *archPistas;
    archPistas = fopen("Pistas.txt", "r");
    if(archPistas == NULL)
    {
        printf("No se pudo abrir el archivo de las pistas.");
        return false;
    }
    if(cantidadPistas(tab) == false)
    {
        printf("No se pudo abrir el archivo de las pistas.");
        return false;
    }
    if(tab->cantPistas == 0)
    {
        printf("\nEl archivo de pistas esta vacio.\n");
        return false;
    }
    if(tab->cantPistas != tab->cantPal)
    {
        printf("\nNo hay igualdad en la cantidad de palabras y la cantidad de pistas de los archivos.\n");
        return false;
    }
    while(i < tab->cantPistas && fscanf(archPistas, "%100[^\n]\n", tab->pista[i]) == 1)
    {
        i++;
    }
    fclose(archPistas);

    printf("\n***************************************\n");
    printf("Su objetivo es encontrar %d palabras.\nComencemos.\n", tab->cantPal);
    printf("***************************************\n");
    return true;
}

bool cantidadPalabras(Tablero *tab)
{
    char aux [50];
    int i = 0;
    FILE *f;
    f = fopen("Palabras.txt", "r");
    if(f == NULL)
    {
        return false;
    }
    while(fscanf(f, "%20s", aux) == 1)
    {
        i++;
    }
    tab->cantPal = i;
    return true;
}

bool cantidadPistas(Tablero *tab)
{
    char aux [TAM];
    int i = 0;
    FILE *f;
    f = fopen("Pistas.txt", "r");
    if(f == NULL)
    {
        return false;
    }
    while(fscanf(f, "%100[^\n]\n", aux) == 1)
    {
        i++;
    }
    tab->cantPistas = i;
    return true;
}

void insertarPalabras(Tablero *tab)
{
    int longitud, orientacion;

    for(int i = 0; i < tab->cantPal; i++)
    {
        longitud = (int)strlen(tab->pal[i]);
        orientacion = rand()%2;
        ubicarPalabras(tab, tab->pal[i], longitud, orientacion);
    }
    insertarPalabrasRandom(tab);
}

void ubicarPalabras(Tablero *tab, char *palabra, int longitud, int orientacion)
{
    if(orientacion == 0) ///Horizontal
    {
        int fila = rand() % tab->tamanio;
        int columna = rand() % (tab->tamanio - longitud); ///Me aseguro que entre la palabra

        while(!espacioDisponibleHorizontal(tab, palabra, fila, columna))
        {
            fila = rand() % tab->tamanio;
            columna = rand() % (tab->tamanio - longitud);
        }
        escribirPalabraHorizontal(tab, palabra, longitud, fila, columna);
    }
    else ///Vertical
    {
        int columna = rand() % tab->tamanio;
        int fila = rand() % (tab->tamanio - longitud);

        while(!espacioDisponibleVertical(tab, palabra, fila, columna))
        {
            columna = rand() % tab->tamanio;
            fila = rand() % (tab->tamanio - longitud);
        }
        escribirPalabraVertical(tab, palabra, longitud, fila, columna);
    }
}

bool espacioDisponibleHorizontal(Tablero *tab, char *palabra, int fila, int columna)
{
    while(*palabra != '\0')
    {
        if(tab->matriz[fila][columna] == *palabra || esLetra(tab->matriz[fila][columna]))
        {
            return false;
        }
        columna++;
        palabra++;
    }
    return true;
}

bool espacioDisponibleVertical(Tablero *tab, char *palabra, int fila, int columna)
{
    while(*palabra != '\0')
    {
        if(tab->matriz[fila][columna] == *palabra || esLetra(tab->matriz[fila][columna]))
        {
            return false;
        }
        fila++;
        palabra++;
    }
    return true;
}

void escribirPalabraHorizontal(Tablero *tab, char *palabra, int longitud, int fila, int columna)
{
    for(int i = 0; i < longitud; i++)
        {
            tab->matriz[fila][columna + i] = *palabra;
            palabra++;
        }
}

void escribirPalabraVertical(Tablero *tab, char *palabra, int longitud, int fila, int columna)
{
    for(int i = 0; i < longitud; i++)
        {
            tab->matriz[fila + i][columna] = *palabra;
            palabra++;
        }
}

bool esLetra(char c)
{
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return true;
    }
    return false;
}

void insertarPalabrasRandom(Tablero *tab)
{
    for(int i = 0; i < tab->tamanio; i++)
    {
        for(int j = 0; j < tab->tamanio; j++)
        {
            if(tab->matriz[i][j] == '\0')
            {
                tab->matriz[i][j] = 'A' + rand()%('Z' - 'A' + 1);
            }
        }
    }
}

bool iniciaJuego(Tablero *tab)
{
    char entrada[TAMPAL] = {};
    int cantPal = tab->cantPal, cantPista = 0;
    time_t tiempoInicio, tiempoFin;

    tiempoInicio = time(NULL);
    ingresarPalabra(entrada);
    esComando(entrada);

    while(finalizarJuego(entrada) != true)
    {
        if(cantPista == 0 && pista(entrada))
        {
            printf("Pistas: \n");
            imprimirPista(tab);
            ingresarPalabraPostPista(entrada);
            cantPista = 1;
            esComando(entrada);

            while(pista(entrada))
            {
                printf("\nsolo puede pedir pista una vez.\n");
                ingresarPalabraPostPista(entrada);
                esComando(entrada);
            }
            if(finalizarJuego(entrada))
            {
                tiempoFin = time(NULL);
                tiempoTranscurrido(tiempoInicio, tiempoFin);
                return true; ///vuelve a main
            }
        }

        aMayuscula(entrada);

        if(verificarPalabraEstablecida(tab, entrada) == true)
        {
            cantPal--;
            printf("\nPalabra correcta.\nFalta acertar %d palabras.\n\n", cantPal);
            buscarUbicacion(tab, entrada);
            ocultarPalabraEncontrada(tab, entrada);
            if(cantPal == 0)
            {
                printf("\nFelicidades!! Encontraste todas las palabras. \nGracias por participar.\n");
                tiempoFin = time(NULL);
                tiempoTranscurrido(tiempoInicio, tiempoFin);
                return true; ///vuelve a main
            }
        }
        else
        {
            printf("\nPalabra incorrecta, vuelva a intentarlo.\n");
        }

        if(cantPista == 1)
        {
            ingresarPalabraPostPista(entrada);
            esComando(entrada);
            while(pista(entrada))
            {
                printf("\nsolo puede pedir pista una vez.\n");
                ingresarPalabraPostPista(entrada);
                esComando(entrada);
            }
        }
        else
        {
            printf("\n");
            ingresarPalabra(entrada);
        }
        esComando(entrada);
    }
    tiempoFin = time(NULL);
    tiempoTranscurrido(tiempoInicio, tiempoFin);
    return true; ///vuelve a main
}

bool finalizarJuego(char *entrada)
{
    char cad[6]="#quit";

    if(strcmp(cad, entrada) == 0)
    {
        return true;
    }
    return false;
}

char* esComando(char *entrada)
{
    if(*entrada == '#')
    {
        entrada++;
        aMinuscula(entrada);
    }
    return entrada;
}

bool pista(char *entrada)
{
    char cad[6]="#clue";

    if(strcmp(cad, entrada) == 0)
    {
        return true;
    }
    return false;
}

char* aMayuscula(char *entrada)
{
    char *p = entrada;

    while(*p != '\0')
    {
        if(*p >= 'a' && *p <= 'z')
        {
            *p = *p - ('a' - 'A');
        }
        p++;
    }
    return entrada;
}

char* aMinuscula(char *entrada)
{
    char *p = entrada;

    while(*p != '\0')
    {
        if(*p >= 'A' && *p <= 'Z')
        {
            *p = *p + ('a' - 'A');
        }
        p++;
    }
    return entrada;
}

bool verificarPalabraEstablecida(Tablero *tab, char *entrada)
{
    for(int i = 0; i < tab->cantPal; i++)
    {
        if(strcmp(tab->pal[i], entrada) == 0)
        {
            return true;
        }
    }
    return false;
}

bool buscarUbicacion(Tablero *tab, char *entrada)
{
    char *p = entrada;
    int rta;

    for(int i = 0; i < tab->tamanio; i++)
    {
        for(int j = 0; j < tab->tamanio; j++)
        {
            if(tab->matriz[i][j] == *p)
            {
                rta = verificarPalabra(tab, entrada, i, j);
                if( rta != NO_ENCONTRADO)
                {
                    ocultarPalabra(tab, entrada, i, j, rta);
                    return true;
                }
            }
        }
    }
    return false;
}

int verificarPalabra(Tablero *tab, char *entrada, int fila, int columna)
{
    int j = columna;
    char *p = entrada;

    while(columna < tab->tamanio && tab->matriz[fila][columna] == *p) ///Verifico Horizontal
    {
        columna++;
        p++;
    }
    if(*p == '\0')
    {
        return HORIZONTAL;
    }

    p = entrada; ///Reinicio el puntero
    columna = j; /// Reinicio columna

    while(fila < tab->tamanio && tab->matriz[fila][columna] == *p) ///Verifico vertical
    {
        fila++;
        p++;
    }
    if(*p == '\0')
    {
        return VERTICAL;
    }

    return NO_ENCONTRADO;
}

void ocultarPalabra(Tablero *tab, char *entrada, int fila, int columna, int rta)
{
    if(rta == HORIZONTAL)
    {
        while(tab->matriz[fila][columna] == *entrada && *entrada != '\0')
        {
            tab->matriz[fila][columna] = ' ';
            entrada++;
            columna++;
        }
        imprimirTablero(tab);
    }
    else ///Vertical
    {
        while(tab->matriz[fila][columna] == *entrada && *entrada != '\0')
        {
            tab->matriz[fila][columna] = ' ';
            entrada++;
            fila++;
        }
        imprimirTablero(tab);
    }
}

void ocultarPalabraEncontrada(Tablero *tab, char *entrada)
{
    int i = 0;
    while(strcmp(entrada, tab->pal[i] ) != 0)
    {
        i++;
    }

    for(int j = 0; j < TAMPAL; j++)
    {
        tab->pal[i][j] = '\0';
    }
    ocultarPista(tab, i);
}

void ocultarPista(Tablero *tab, int i)
{
    for(int j = 0; j < TAM; j++)
    {
        tab->pista[i][j] = '\0';
    }
}

void ingresarPalabra(char *entrada)
{
    int largoPal;

    printf("#quit para finalizar / #clue para pista.\nIngrese una palabra: ");
    fgets(entrada, TAMPAL, stdin);
    largoPal = strlen(entrada);
    if(largoPal > 1 && entrada[largoPal - 1] == '\n')
    {
        entrada[largoPal - 1] = '\0';
    }
    else
    {
        if(largoPal == TAMPAL - 1 && entrada[largoPal - 1] != '\n')
        {
            limpiarBufferEntrada();
        }
    }
}

void ingresarPalabraPostPista(char *entrada)
{
    int largoPal;

    printf("\n#quit para finalizar.\nIngrese una palabra: ");
    fgets(entrada, TAMPAL, stdin);
    largoPal = strlen(entrada);
    if(largoPal > 1 && entrada[largoPal - 1] == '\n')
    {
        entrada[largoPal - 1] = '\0';
    }
    else
    {
        if(largoPal == TAMPAL - 1 && entrada[largoPal - 1] != '\n')
        {
            limpiarBufferEntrada();
        }
    }
}

void tiempoTranscurrido(time_t tiempoInicio, time_t tiempoFin)
{
    int minutos = 0;
    double diferencia;

    diferencia = difftime(tiempoFin, tiempoInicio);
    while(diferencia > 60)
    {
        diferencia = diferencia - 60;
        minutos++;
    }
    if(minutos == 0)
    {
        printf("Tiempo total de juego: %2.0f segundos.\n", diferencia);
    }
    else
    {
        if(minutos == 1)
        {
            printf("Tiempo total de juego: %d minuto y %2.0f segundos.\n", minutos, diferencia);
        }
        else
        {
            printf("Tiempo total de juego: %d minutos y %2.0f segundos.\n", minutos, diferencia);
        }
    }
}

void liberarTablero(Tablero *tab)
{
    for(int i = 0; i < tab->tamanio; i++)
    {
        free(tab->matriz[i]); ///libero las filas
    }
    free(tab->matriz);   ///libero el puntero a las filas
    tab->matriz = NULL;
}

void limpiarBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
