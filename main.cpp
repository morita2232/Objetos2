#include "GameEngine.h"

int SDL_main(int argc, char* argv[]) {

    // TO DO
    /*
    GAMEPLAY V1
        - Hay asteroides en el mapa con colisiones funcionales. (TODAVIA NO TIENEN COLISIONES)
        - Todo elemento que sale por un lado de la pantalla aparece por el otro. (Esto ya funciona con la nave y asteroides)
        - Los asteroides se rompen correctamente cuando son tocados por una bala
            - Romper un asteroide grande genera dos pequeños
        - El jugador muere si toca un asteroide (y vuelve al menu)
        - Cuando no quedan asteroides, se generan nuevos asteroides.
            - Cada vez debe haber mas asteroides y deben ser mas rapidos.

    MENUS
        - Menu de highscores
            - Los 10 mejores highscores deben guardarse. No es necesario guardar el nombre del jugador.

    GAMEPLAY V2
         - Los asteroides medianos aparecen al destruir un asteroide grande
                -Su velocidad es la misma que el asteroide del que provienen, con una variacion aleatoria
            - Los asteroides pequeños aparecen al destruir un asteroide mediano. Su velocidad es la misma que el asteroide del que provienen, con una variacion aleatoria
            - El jugador tiene 3 vidas con su HUD respectivo
                - Cuando el jugador muere, se reproduce la animacion de muerte durante 3 s.
            - Aparecen enemigos (naves) de forma aleatoria cada 15 segundos.
                - Los enemigos se mueven en una direccion que cambia cada segundo.
                - Si un enemigo toca:
                    - Un asteroide: el asteroide se rompe y el enemigo se destruye
                    - El jugador: el jugador pierde una vida y el enemigo se destruye
                    - Una bala: la bala se destruye y el enemigo tambien
            - Contabilizar el score de una partida y mostrarlo en el HUD
                - 50 puntos por un asteroide grande
                - 30 puntos por un asteroide mediano
                - 20 puntos por un asteroide pequeño
                - 150 puntos por cada enemigo destruido
    */

	//Se crea una instancia del juego en una ventana de 500 x 500
	GameEngine myEngine(500, 500);

	//Bucle del juego
	myEngine.Updater();

	//Se limpian recursos y se finaliza el SDL
	myEngine.Finish();

	return 0;
}