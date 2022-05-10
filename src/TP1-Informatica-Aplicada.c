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

typedef struct TEvento{
	bool s1;
	bool s2;
	struct TEvento* sig;
} Evento;

typedef enum {
	ALTA_VELOCIDAD,
	BAJA_VELOCIDAD,
	DETENIDO_ENSANCHANDO,
	BAJA_VELOCIDAD_ENSANCHADO,
} Estado;

void agregarEvento(Evento* lista) {
	Evento* nuevo_evento = malloc(sizeof(Evento));
	nuevo_evento->s1 = rand() % 2;
	nuevo_evento->s2 = rand() % 2;
	nuevo_evento->sig = NULL;

	Evento* p = lista;
	while(p -> sig != NULL) {
		p = p->sig;
	}
	p->sig = nuevo_evento;
}

void imprimir_lista(Evento* lista) {
	Evento* p = lista;
	while(p->sig != NULL) {
		printf("S1:%d S2:%d\n", p->s1, p->s2);
		p = p->sig;
	}
}

void liberar_memoria(Evento* evento) {
	if(evento->sig == NULL) {
		free(evento);
	}
	else {
		liberar_memoria(evento->sig);
	}
}

int main(void) {
    bool continuar = true;
    char c;
    bool valido = false;
    char enter;

    while(continuar){
        srand(time(NULL));
        Estado estado_actual = ALTA_VELOCIDAD;
        Evento* lista = malloc(sizeof(Evento));
        lista->s1 = 0;
        lista->s2 = 0;
        lista->sig = NULL;
        for(int i = 0; i < 20; i++)
            agregarEvento(lista);

        imprimir_lista(lista);

		liberar_memoria(lista);

        valido = false;

        while(!valido){
            printf("Desea realizar otra simulacion? (S/N)\n");
            scanf("%c",&c);
            scanf("%c",&enter); // se come el \n

            c = toupper(c);

            if(c == 'N'){
                continuar = false;
                valido = true;
            }
            else if(c == 'S'){
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
