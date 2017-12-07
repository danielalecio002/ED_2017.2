#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const int nl = 20;
const int nc = 60;

void mostrar(vector<string>& mat){
    cout << string(50, '\n');
    for(string s : mat)
        cout << s << endl;
    getchar();
}


int queimar(vector<string> &mat, int  l, int  c){

    int cont = 0;

    //retorno
    if(l < 0 || l >= nl)
        return cont;
    if(c < 0 || c >= nc)
        return cont;
    if(mat[l][c] != '#')
        return cont;

    //ação
    mat[l][c] = '.';

    mostrar(mat);
    cont += 1;

    //reduçao

    cont += queimar(mat,l,c+1);
    cont += queimar(mat,l,c-1);
    cont += queimar(mat,l-1,c);
    cont += queimar(mat,l+1,c);
    cont += queimar(mat,l+1,c+1);
    cont += queimar(mat,l+1,c-1);
    cont += queimar(mat,l-1,c+1);
    cont += queimar(mat,l-1,c-1);

    mat[l][c] = '*';
    mostrar(mat);

    return cont;
}


int main()
{
    int x = 0,y = 0;
    srand(time(NULL));
    cout << "Digite a posicão x e a posição y"<< endl;
    cin >> x ;
    cin >> y ;
    getchar();


    //os containers tem uma construção padrao
    //container<tipo> nome(qtd, elemento_default)
    //cria um vetor de string
    //com nl elementos da string default
    //a string default sao 30 char ' '
    vector<string> mat(nl, string(nc, ' '));
    int narvores = nl * nc * 1.5;
    //insere varias arvores em lugares aleatorios
    //muitas serao superpostas
    for(int i = 0; i < narvores; i++){
        mat[rand() % nl][rand() % nc] = '#';
    }
    int total = queimar(mat,x,y);
    mostrar(mat);
    cout << total << " arvores queimaram\n";

    return 0;
}

