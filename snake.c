#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

static int** mat;
static struct Serpente* serpente;
static struct Serpente* testaSerpente;
static int n, m, punteggio /*, frutta[2]*/;
static char ultimaKey;

void creaSerpente(int start) {
  if(start) {
    testaSerpente = (struct Serpente *) malloc(sizeof(struct Serpente));
    serpente = (struct Serpente *) malloc(sizeof(struct Serpente));
    serpente -> coda = NULL;
    testaSerpente = serpente;
    serpente -> coordinate.x = (int)(m-1)/2;
    serpente -> coordinate.y = (int)(n-1)/2;
  }
  else {
    int x, y;
    struct Serpente* tmp = (struct Serpente *) malloc(sizeof(struct Serpente));
    tmp = testaSerpente;
    while(tmp != NULL) {
      if(tmp -> coda == NULL) {
        x = tmp -> coordinate.x;
        y = tmp -> coordinate.y;
      }
      tmp = tmp -> coda;
    }
    tmp = (struct Serpente *) malloc(sizeof(struct Serpente));
    serpente = tmp;
    serpente -> coordinate.x = x;
    serpente -> coordinate.y = y;
    if(ultimaKey == "w") {
      serpente -> coordinate.y--;
    }
    else if(ultimaKey == "a") {
      serpente -> coordinate.x--;
    }
    else if(ultimaKey == "s") {
      serpente -> coordinate.y++;
    }
    else {
      serpente -> coordinate.x++;
    }
  }
}

int aggiornaMatrice() {
  struct Serpente* tmp = (struct Serpente *) malloc(sizeof(struct Serpente));
  tmp = testaSerpente;
  if(ultimaKey == "w") {
    while (tmp != NULL) {
      if((tmp -> coordinate.y-1) < 0) {
        tmp -> coordinate.y = (n-1);
      }
      else {
        tmp -> coordinate.y--;
      }
      tmp = tmp -> coda;
    }
  }
  else if(ultimaKey == "a") {
    while (tmp != NULL) {
      if((tmp -> coordinate.x-1) < 0) {
        tmp -> coordinate.x = (m-1);
      }
      else {
        tmp -> coordinate.x--;
      }
      tmp = tmp -> coda;
    }
  }
  else if(ultimaKey == "s") {
    while (tmp != NULL) {
      if((tmp -> coordinate.y+1) > n) {
        tmp -> coordinate.y = 0;
      }
      else {
        tmp -> coordinate.y++;
      }
      tmp = tmp -> coda;
    }
  }
  else {
    while (tmp != NULL) {
      if((tmp -> coordinate.x+1) > m) {
        tmp -> coordinate.x = 0;
      }
      else {
        tmp -> coordinate.x++;
      }
      tmp = tmp -> coda;
    }
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      mat[i][j] = 95;
    }
  }
  tmp = testaSerpente;
  while(tmp != NULL) {
    mat[tmp -> coordinate.y][tmp -> coordinate.x] = 48;
    tmp = tmp -> coda;
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      printf("%c", (char) mat[i][j]);
    }
    printf("\n");
  }
  return 0;
}

int spostaSerpente(char direzione) {
  int esito = 0;
  if(direzione == "w" && ultimaKey != "s") {
    esito = aggiornaMatrice();
    ultimaKey = "w";
  }
  else if(direzione == "a" && ultimaKey != "d") {
    esito = aggiornaMatrice();
    ultimaKey = "a";
  }
  else if(direzione == "s" && ultimaKey != "w") {
    esito = aggiornaMatrice();
    ultimaKey = "s";
  }
  else if(direzione == "d" && ultimaKey != "a") {
    esito = aggiornaMatrice();
    ultimaKey = "d";
  }
  else if(direzione == "e") {
    esito = 1;
  }
  else {
    esito = aggiornaMatrice();
  }
  system("clear");
  return punteggio == (n*m) ? 1 : esito;
}


void creaMatrice(int n, int m) {
  mat = (int**)malloc(n*sizeof(int *));
  mat[0] = (int*)malloc(n*m*sizeof(int));
  for(int i = 1; i < n; i++)
    mat[i] = mat[0] + i*m;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      mat[i][j] = 95;
}

void snakeGame() {
  //srand(time(NULL));
  //frutta[0] = rand() % n;
  //frutta[1] = rand() % m;
  ultimaKey = "d";
  int flag = 0;
  punteggio = 0;
  printf("Inserisci la dimensione della mappa di gioco NxM\n");
  printf("Inserisci N: ");
  scanf("%d", &n);
  printf("Inserisci M: ");
  scanf("%d", &m);
  system("clear");
  creaMatrice(n,m);
  //mat[frutta[0]][frutta[1]] = 64;
  creaSerpente(1);
  do {
    flag = spostaSerpente("s");
  } while(!flag);
  if(punteggio == (n*m)) {
    printf("Hai vinto!\n");
  }
  else {
    printf("Hai perso!\n");
  }
  free(mat);
}
