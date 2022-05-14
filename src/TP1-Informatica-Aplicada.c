/*
 ============================================================================
 Name        : TP1-Informatica-Aplicada.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

bool requiere_ensanche;
unsigned char cinta;

typedef struct TEvento
{
    bool s1;
    bool s2;
    struct TEvento *sig;
} Evento;

typedef enum
{
    ALTA_VELOCIDAD,
    BAJA_VELOCIDAD,
    DETENIDO_ENSANCHANDO,
    BAJA_VELOCIDAD_ENSANCHADO,
} Estado;

void agregarEvento(Evento *lista)
{
    Evento *nuevo_evento = malloc(sizeof(Evento));
    nuevo_evento->s1 = rand() % 2;
    nuevo_evento->s2 = rand() % 2;
    nuevo_evento->sig = NULL;

    Evento *p = lista;
    while (p->sig != NULL)
    {
        p = p->sig;
    }
    p->sig = nuevo_evento;
}

void imprimir_lista(Evento *lista)
{
    Evento *p = lista;
    while (p->sig != NULL)
    {
        printf("S1:%d S2:%d\n", p->s1, p->s2);
        p = p->sig;
    }
}

void liberar_memoria(Evento *evento)
{
    if (evento->sig == NULL)
    {
        free(evento);
    }
    else
    {
        liberar_memoria(evento->sig);
    }
}

void correr_simulacion(Evento *eventos)
{
    // De movida, S1 y S2 son 0 en el primer evento
    Evento *p = eventos;
    Estado estado_actual = ALTA_VELOCIDAD;

    while (p->sig != NULL)
    {
        if (p->s1 == 1 && p->s2 == 0 && estado_actual == ALTA_VELOCIDAD)
        {
            estado_actual = BAJA_VELOCIDAD;
        }

        else if (estado_actual == BAJA_VELOCIDAD && p->s1 == 0 && p->s2 == 0)
        {
            estado_actual = DETENIDO_ENSANCHANDO;
        }
        // Si no hay que ensanchar la vela
        else if (p->s1 == 1 && p->s2 == 1 && estado_actual == BAJA_VELOCIDAD)
        {
            estado_actual = BAJA_VELOCIDAD_ENSANCHADO;
        }

        else if (estado_actual == DETENIDO_ENSANCHANDO && p->s1 == 1 && p->s2 == 1)
        {
            estado_actual = BAJA_VELOCIDAD_ENSANCHADO;
        }

        else if (p->s1 == 0 && p->s2 == 0 && estado_actual == BAJA_VELOCIDAD_ENSANCHADO)
        {
            // Cortar la simulacion
            printf("Fin de la simulacion. La vela llego al final de la cinta\n");
            break;
        }
        else
        {
            p = p->sig;
            continue;
        }

        switch (estado_actual)
        {

        case BAJA_VELOCIDAD:
            printf("Cinta a Baja Velocidad: \t\t\t C1 = 1 C2 = 0 \t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 2;
            break;

        case BAJA_VELOCIDAD_ENSANCHADO:
            printf("Cinta a Baja Velocidad, vela correcta:\t\t C1 = 1 C2 = 0 \t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 2;
            break;

        case ALTA_VELOCIDAD:
            printf("Cinta a alta velocidad: \t\t\t C1 = 1 C0 = 1\t\t requiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 3;
            break;

        case DETENIDO_ENSANCHANDO:
            printf("Cinta detenida: \t\t\t\t C1 = 0 C0 = 0 \t\trequiere_ensanche = 1\n");
            requiere_ensanche = 1;
            cinta = 0;
            break;

        default:
            break;
        }

        p = p->sig;
    }
}

int main(void)
{
    bool continuar = true;
    char c;
    bool valido = false;
    char enter;
    int c_eventos;

    printf("\n\n\tBienvenido a la simulacion de fabrica de velas\n\n");

    while (continuar)
    {
        srand(time(NULL));
        Evento *lista = malloc(sizeof(Evento));
        lista->s1 = 0;
        lista->s2 = 0;
        lista->sig = NULL;

        printf("Ingrese la cantidad de eventos aleatorios que desea crear: ");

        scanf("%d", &c_eventos);
        scanf("%c", &enter); // se come el \n

        for (int i = 0; i < c_eventos; i++)
            agregarEvento(lista);

        imprimir_lista(lista);

        correr_simulacion(lista);

        // Una vez mostrada realizada la simulaci�n, se libera la memoria
        liberar_memoria(lista);

        valido = false;

        while (!valido)
        {
            printf("Desea realizar otra simulacion? (S/N)\n");
            scanf("%c", &c);
            scanf("%c", &enter); // se come el \n

            c = toupper(c);

            if (c == 'N')
            {
                continuar = false;
                valido = true;
            }
            else if (c == 'S')
            {
                continuar = true;
                valido = true;
            }
            else
            {
                valido = false;
                printf("Opcion invalida, intente otra vez:\n");
            }
        }
    }
    return EXIT_SUCCESS;
}
