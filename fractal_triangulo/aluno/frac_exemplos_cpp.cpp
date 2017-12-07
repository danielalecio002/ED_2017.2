#include <lib/pen.h>
#include <iostream>

void Triangulo(Pen &p, int dist ){

    //ponto de parada
    if(dist < 5)
        return;
    //acao
    p.setColor(255, 255, 255);

    for(int i =0; i<3;i++){
        p.walk(dist);
        p.right(120);

        Triangulo(p, dist /2);
    }
}

void fractal(){

    Pen p(800, 600);
    //coloca o pincel na posicao x 300 y 500
    p.setXY(100 ,100);

    p.setThickness(2);

    //faz o pincel apontar pra direita
    p.setHeading(0);
    //se speed = 0 entao ele faz o mais rapido possivel
    //se foi a partir de 1 ele controla a velocidade
    p.setSpeed(10);

    Triangulo(p,600);

    p.wait();
}

int main(){

    srand(time(NULL));

    fractal();

    return 0;
}
