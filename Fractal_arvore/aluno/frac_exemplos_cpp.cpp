#include <lib/pen.h>
#include <iostream>

void tree(Pen &p, int dist,   int &qtd ){
    int angulo = (30 + rand() % 15);



    //ponto de parada
    if(dist < 5)
        return;
    //acao
    p.setColor(255, 255, 255);
    p.walk(dist);


    if (qtd == 3){
        tree(p,dist - 10,qtd);
        p.right(angulo);
        p.setThickness(2);
        tree(p, dist - 10,qtd);
        p.left(2 * angulo);
        tree(p,dist -10,qtd);
        p.right(angulo);

        p.setColor(0, 255, 0);
        p.walk(-dist);
    }
    if(qtd == 2){

        p.right(angulo);
        p.setThickness(2);
        tree(p,dist - 10,qtd);
        p.left(2*angulo);
        tree(p, dist - 10,qtd);
        p.right(angulo);
        p.setColor(0, 255, 0);
        p.walk(-dist);
    }
}



void fractal(){
    int qtd = (2 + rand() % 2);
    Pen p(800, 600);
    //coloca o pincel na posicao x 300 y 500
    p.setXY(200 + rand() % 400,300 + rand () % 300);

    p.setThickness(4);

    //faz o pincel apontar pra direita
    p.setHeading(90);
    //se speed = 0 entao ele faz o mais rapido possivel
    //se foi a partir de 1 ele controla a velocidade
    p.setSpeed(100);


    tree(p,40 + rand()%50,qtd);

    p.wait();
}

int main(){

    srand(time(NULL));

    fractal();




    return 0;
}
