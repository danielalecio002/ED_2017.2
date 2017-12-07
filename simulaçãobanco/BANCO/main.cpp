#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include <iostream>
#include <sstream>

#include <cstdlib>

//A paciencia maxima pode ser alterada.
//Ela é usada para criar o efeito de cores
//na visualização da simulação.
const int MAX_PACIENCIA = 20;

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <time.h>//funcao time
#include <stdlib.h> //funcao srand
#include <queue>
#include <list>


using namespace std;



struct Cliente
{
    int paciencia;
    int documentos;

    Cliente(int paciencia, int documentos){

        this->paciencia = paciencia;
        this->documentos = documentos;
    }

};


//Cada dia possui 6 horas de trabalho
//60 minutos x 6 horas = 360 minutos
//cada minuto eh um turno.
const int TURNOS_DIA = 360;

//A quantidade máxima de caixas não pode ser alterada.
const int MAX_CAIXAS = 10;

//Esse valor determina o quanto o banco por caixa por dia de trabalho
const int CUSTO_CAIXA_DIA = 100;

//Define o nuemro maximo de clientes
const int  Max_Clientes = 20;

int rand_mm(int min, int max){
    static int init = 1;
    if(init){
        init = 0;
        srand(time(NULL));
    }
    return rand() % (max - min + 1) + min;
}

int qtd_banco = 0;
void simulacao(int min_pac, int max_pac, int min_doc, int max_doc, int min_cli, int max_cli, int dias){

    //Pintor pintor;

    int qtd_banco = 0;

    // Tempo da simulação

    int numCaixas = 10;//5 caixas no banco

    // Estruturas para representar os clientes
    // no caixa e na fila

    list<Cliente*> fila_clientes;  // cria a galera pra ver se entra ou não no banco
    list<Cliente*> espera; // fila de espera, galera que tá no banco
    list<Cliente*> saida; // fila de saida

    std::vector<Cliente*> caixa(numCaixas);
    int lucro[10]; //lista de lucro
    int lucro_total[10] = {0,0,0,0,0,0,0,0,0,0};
    int saldo = 0;

    /*--------------------laço para verificar a médias em tantos *dias-------------*/
    for(int d = 0; d < dias; d++){
        for(numCaixas = 1; numCaixas <= MAX_CAIXAS; numCaixas++) {
            /*----------------laço que varia o numero de caixas-----------------*/
            qtd_banco = 0;
            saldo = 0;

            for(int i = 0; i < TURNOS_DIA; i++){
                /*----------laço que movimenta o banco-------------------*/
                //criando clientes
                int qtd_Clientes_chegando = rand_mm(min_cli,max_cli);
                for(int i = 0; i < qtd_Clientes_chegando; i++){
                    fila_clientes.push_back(new Cliente(rand_mm(min_pac, max_pac),
                                                  rand_mm(min_doc, max_doc)));
                }
                //---------------------------------------------

                //colocando os clientes no banco
                while(!fila_clientes.empty()){
                    if(qtd_banco <= Max_Clientes){
                        qtd_banco++;
                        espera.push_back(fila_clientes.front());
                        fila_clientes.pop_front();
                    }else{
                        fila_clientes.pop_front();
                    }
                }
                //----------------------------------------------

                //tirando os clientes sem paciência
                for(int i = 0; i < (int)espera.size(); i++){
                    if(espera.front()->paciencia < 1){
                        saida.push_back(espera.front());
                        espera.pop_front();
                    }else{
                        espera.front()->paciencia--;
                        espera.push_back(espera.front());
                        espera.pop_front();
                    }
                }
                //---------------------------------------------------

                //caixas atendendo e despachando clientes
                for(int i = 0; i < numCaixas; i++){
                    if(caixa[i] != nullptr){
                        if(caixa[i]->documentos >= 1){
                            caixa[i]->documentos--;
                            saldo++;
                        }else{
                            saida.push_back(caixa[i]);
                            caixa[i] = nullptr;
                        }
                    }else{
                        if(!espera.empty()){
                            caixa[i] = espera.front();
                            espera.pop_front();
                        }
                    }
                }
                //-----------------------------------------------------

                //tirar os clientes dos caixas
                while(!saida.empty()){
                    saida.pop_front();
                    qtd_banco--;

                }
            }
            /*-----fim do laço de turnos-----------*/

            lucro[numCaixas-1] = saldo - (numCaixas * 100);
        }
        /*---------------fim do laço de mudança no Nº de caixas-----------------*/

        //for(int i = 0; i < 10; i++) cout << "o lucro para " << i + 1 << "caixas é: " << lucro[i] << endl;
        for(int i = 0; i < 10; i++) lucro_total[i] += lucro[i];
    }
    /* fim do laço que conta dias*/
    for(int i = 0; i < 10; i++) cout << "o lucro medio para " << i + 1 << " caixas em " << dias <<" dias é: " << lucro_total[i] / dias << endl;
    int maior = lucro_total[0];
    int aux = 0;
    for(int i = 1;i < 10; i++){
        if(lucro_total[i] > maior){
            maior = lucro_total[i];
            aux = i;
        }

    }
    cout << "A quantidade de caixa ideal é: " << aux + 1 << " O lucro médio foi de " << lucro_total[aux] / dias << endl;

}
int main (){
    int min_cli = 0, max_cli = 0;
    int min_pac = 0, max_pac = 0;
    int min_doc = 0, max_doc = 0;

    cout << "Qtd clientes $mincli $max_cli"<< endl;
    cin >> min_cli >> max_cli;

    cout << "Qtd paciencia $min_pac $max_pac"<< endl;
    cin >> min_pac >> max_pac;

    cout << "Qtd documentos $min_doc $max_doc"<< endl;
    cin >> min_doc >> max_doc;

    simulacao(min_pac, max_pac, min_doc, max_doc, min_cli, max_cli,100);

    //cout << "maior lucro: " << simulacao(min_pac, max_pac, min_doc, max_doc, min_cli, max_cli) << endl;

    return 0;
}
