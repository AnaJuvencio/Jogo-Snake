#include <stdio.h>
#include <stdlib.h>   //biblioteca para as funções system() e srand()
#include <windows.h> //biblioteca para a função SetConsoleCursorPosition
#include <conio.h>  //biblioteca para a função getch() e kbhit()
#include <time.h>  //bibliotecapara a função rand()

int c[300][2], pontos = 1, cx = 2, cy = 2, alimento[2], velo = 150;

void gotoxy(int x, int y){//mover cursor
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void desenhar(){//desenhar a cobra
    int i;
    for(i=0; i < pontos; i++){
        gotoxy(c[i][0], c[i][1]);
        printf("%c", 219);
    }
}
void atualiza(){//atualiza a posição da cobra
    int j;
    gotoxy(c[pontos][0],c[pontos][1]);
    printf(" ");
    for(j=pontos; j >= 0; j--){
        c[j+1][0] = c[j][0];
        c[j+1][1] = c[j][1];
    }
}
int bater_no_proprio_corpo(){//verificar se a cobra bateu no seu proprio corpo
    int i, retorno=0;
    for(i=1; i < pontos; i++){
        if(cx == c[i][0] && cy == c[i][1])
            retorno = 1;
    }
    return retorno;
}

void gerarAlimento(){ //gerar um alimento em posição aleatória
    gotoxy(alimento[0], alimento[1]);
    printf(" "); //apaga a última comida
    srand(time(NULL));
    alimento[0] = (rand() % 48) + 1;
    alimento[1] = (rand() % 18) + 1;
    gotoxy(alimento[0], alimento[1]);
    printf("%c", 4);//imprime a comida

}
int main()
{
    int i, gameOver = 0;
    char tecla;

    for(i = 0; i < 50; i++){//coluna direita
        gotoxy(i,0);
        printf("%c", 219);
        Sleep(5); //pausa o progrma por 5 milissegundos para ficar com um efeito
    }
    for(i = 0; i < 20; i++){//linha direita
      gotoxy(50,i);
      printf("%c",219);
      Sleep(5);
    }
    for(i = 50; i >= 0; i--){//linha inferior
        gotoxy(i, 20);
        printf("%c", 219);
        Sleep(5);
    }
    for(i = 20; i > 0; i--){//coluna da esquerda
        gotoxy(0,i);
        printf("%c", 219);
        Sleep(5);
    }
    gerarAlimento(); //gera a primeira comida
    desenhar(); // desenha a cobra
    tecla = 'd'; //direção começa pela direita

    while(gameOver == 0){
        gotoxy(52,2);
        printf("Pontos: %d\t", pontos);
        gotoxy(52,4);
        c[0][0] = cx;
        c[0][1] = cy;
        if(kbhit())
            tecla= getch();
        if(tecla == 'w' || tecla == 'W' || tecla == 72){
            cy--;
            if(cy == 0)break; // se bater na parede superior o jogo acaba
        }
        if(tecla == 'a' || tecla == 'A' || tecla == 75){
            cx--;
            if(cx == 0)break; // se bater na parede superior o jogo acaba
        }
        if(tecla == 's' || tecla == 'S' || tecla == 80){
            cy++;
            if(cy == 20)break; // se bater na parede superior o jogo acaba
        }
        if(tecla == 'd' || tecla == 'D' || tecla == 77){
            cx++;
            if(cx >= 50)break; // se bater na parede superior o jogo acaba
        }
        if(cx == alimento[0] && cy == alimento[1]){
            pontos++;
            if(velo > 50) velo-=10;
            gerarAlimento();
        }
        gameOver = bater_no_proprio_corpo();
        atualiza(); //atualiza a posição da cobra
        desenhar(); //desenha cobra
        gotoxy(50,20);//cursor não atrapalhar o visão da cobra
        Sleep(velo); //pausa o jogo
    }
    system("cls");
    printf("Game Over! Voce fez %d pontos.\n", pontos);
    system("pause");
    //return 0;
}
