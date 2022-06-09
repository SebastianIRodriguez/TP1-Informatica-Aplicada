/*
 ============================================================================
 Name        : TP1-Informatica-Aplicada.c
 Author      : Leonel Lingotti - Luciano Raffagnini - Sebastian Ignacio Rodriguez
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

void imprimir_lista(Evento *lista)
{
    /**
     * Imprime la lista de eventos generados con los valores de los sensores asociados a cada evento.
     **/
    Evento *p = lista;
    while (p->sig != NULL)
    {
        printf("S1:%d S2:%d\n", p->s1, p->s2);
        p = p->sig;
    }
    printf("S1:%d S2:%d\n", p->s1, p->s2);
}

void liberar_memoria(Evento *evento)
{
    /*
     * Función recursiva que toma como parámetro un puntero a un evento de la lista,
     * si no es el último se llama a si misma pasando como parámetro el puntero al próximo elemento.
     * De esta forma se va liberando la memoria desde el ultimo elemento al primero.
     */

    if (evento->sig != NULL)
    {
        liberar_memoria(evento->sig);
    }
    free(evento);
}

void correr_simulacion(Evento *eventos)
{
    /**
        Funcion que itera hasta recibir una entrada valida S o N.

        Si se ingresa S, se repetira la simulacion.
        Si se ingresa N, se finaliza la ejecucion del programa.

        recibir_entrada() retorna el caracter 'S' o 'N' ingresado.
    **/
    Evento *p = eventos;
    Estado estado_actual = ALTA_VELOCIDAD;

    printf("Cinta a Alta Velocidad: \t\t\t C1 = 1 C0 = 1\t\trequiere_ensanche = 0\n");
    requiere_ensanche = 0;
    cinta = 3;

    while (p->sig != NULL)
    {
        // Se detecta vela
        if (p->s1 == 1 && p->s2 == 0 && estado_actual == ALTA_VELOCIDAD)
        {
            estado_actual = BAJA_VELOCIDAD;
        }
        // Hay que ensanchar la vela
        else if (estado_actual == BAJA_VELOCIDAD && p->s1 == 0 && p->s2 == 0)
        {
            estado_actual = DETENIDO_ENSANCHANDO;
        }
        // Si no hay que ensanchar la vela
        else if (p->s1 == 1 && p->s2 == 1 && estado_actual == BAJA_VELOCIDAD)
        {
            estado_actual = BAJA_VELOCIDAD_ENSANCHADO;
        }
        // Se terminó de ensanchar la vela
        else if (estado_actual == DETENIDO_ENSANCHANDO && p->s1 == 1 && p->s2 == 1)
        {
            estado_actual = BAJA_VELOCIDAD_ENSANCHADO;
        }
        // La vela salió del proceso
        else if (p->s1 == 0 && p->s2 == 0 && estado_actual == BAJA_VELOCIDAD_ENSANCHADO)
        {
            // Cortar la simulacion
            printf("La vela abandono el puesto de control\n");
            printf("Cinta a Alta Velocidad: \t\t\t C1 = 1 C0 = 1\t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 3;
            break;
        }
        else
        {
            // Estado imposible o irrelevante
            p = p->sig;
            continue;
        }

        switch (estado_actual)
        {

        case BAJA_VELOCIDAD:
            printf("Cinta a Baja Velocidad: \t\t\t C1 = 1 C0 = 0 \t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 2;
            break;

        case BAJA_VELOCIDAD_ENSANCHADO:
            printf("Cinta a Baja Velocidad, vela correcta:\t\t C1 = 1 C0 = 0 \t\trequiere_ensanche = 0\n");
            requiere_ensanche = 0;
            cinta = 2;
            break;

        case ALTA_VELOCIDAD:
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
    printf("Fin de la simulacion\n\n");
}

char recibir_entrada()
{
    /**
        Funcion que itera hasta recibir una entrada valida S o N.

        Si se ingresa S, se repetira la simulacion.
        Si se ingresa N, se finaliza la ejecucion del programa.

        recibir_entrada() retorna el caracter 'S' o 'N' ingresado.
    **/
    char c;
    while (true)
    {
        printf("Ingrese su respuesta (S/N): ");
        scanf("%c", &c);
        getchar();

        c = toupper(c);

        if (c == 'N' || c == 'S')
        {
            return c;
        }
        else
        {
            printf("Opcion invalida, intente otra vez:\n");
        }
    }
}

Evento *crear_lista_eventos(int cantidad)
{
    /**
    Crea una lista de eventos del largo adecuado, con informacion generada en forma aleatoria, en forma recursiva
    **/
    Evento *lista = malloc(sizeof(Evento));
    lista->s1 = rand() % 2;
    lista->s2 = rand() % 2;
    lista->sig = (cantidad > 1) ? crear_lista_eventos(cantidad - 1) : NULL;
    return lista;
}

int main(void)
{
    setbuf(stdout, 0);
    int c_eventos;
    bool imprimir = false;

    // Utilizar diferente semilla en cada llamada a rand()
    srand(time(NULL));

    printf("\n\n\tBienvenido a la simulacion de fabrica de velas\n\n");
    printf("  Desea ver las listas de eventos aleatorios que se generen? \n  Aplica a todas las simulaciones\n\n");

    if (recibir_entrada() == 'S')
    {
        imprimir = true;
    }

    while (true)
    {
        printf("Ingrese la cantidad de eventos aleatorios que desea crear: ");

        // Leemos la cantidad de eventos
        scanf("%d", &c_eventos);
        getchar(); // Descarta el \n

        Evento *lista = crear_lista_eventos(c_eventos);

        if (imprimir)
            imprimir_lista(lista);

        correr_simulacion(lista);

        liberar_memoria(lista);

        printf("Desea realizar otra simulacion?\n");

        if (recibir_entrada() == 'N')
        {
            break;
        }
    }
    return EXIT_SUCCESS;
}
