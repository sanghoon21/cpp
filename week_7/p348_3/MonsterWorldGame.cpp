#include "MonsterWorld.h"
#include <ctime>

int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;

    MonsterWorld game(w, h);
    Monster m("괴물", "👾", rand() % w, rand() % h);
    game.add(m);
    game.add(Monster("고블린", "👹", rand() % w, rand() % h));
    game.add(Monster("드래곤", "🐲", rand() % w, rand() % h));
    game.add(Monster("유령", "👻", rand() % w, rand() % h));

    game.play(500, 100);

    printf("------게임 종료-------------------\n");
}
