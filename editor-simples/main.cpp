#include <iostream>
#include <list>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "sftext.h"

using namespace std;

struct Ambiente{
    list<char> texto;
    list<char>::iterator cursor;
    Ambiente(){
        cursor = texto.end();
    }

    string toString(){
        stringstream ss;
        for(auto it = texto.begin(); it != texto.end(); it++){
            if(it == cursor)
                ss << "|";
            ss << (*it);
        }
        if(cursor == texto.end())
            ss << "|";
        return ss.str();
    }

};

int main()
{

    int quebra = 39;
    Ambiente amb;
    amb.texto.push_back('a');
    amb.texto.push_back('m');
    amb.texto.push_back('o');
    amb.texto.push_back('r');

    sf::RenderWindow janela(sf::VideoMode(800, 600), "Janela");
    while(janela.isOpen()){
        sf::Event event;
        while(janela.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                janela.close();
            if(event.type == sf::Event::KeyPressed){
                if((event.key.code >= sf::Keyboard::A) &&
                        (event.key.code <= sf::Keyboard::Z)){
                    char tecla = 'a' + (event.key.code - sf::Keyboard::A);
                    amb.texto.insert(amb.cursor,tecla);
                }
                if(event.key.code == sf::Keyboard::Space){
                    amb.texto.push_back(' ');
                }
                if(event.key.code == sf::Keyboard::Z){
                    if(event.key.control)
                        amb.texto.pop_back();
                }
                if(event.key.code == sf::Keyboard::BackSpace){
                    if(amb.cursor != amb.texto.begin()){
                        auto elem = amb.cursor;
                        elem --;
                        amb.texto.erase(elem);
                    }
                }

                if(event.key.code == sf::Keyboard::Delete){
                    if(amb.cursor != amb.texto.end())
                        amb.texto.erase(amb.cursor++);
                }
                if(event.key.code == sf::Keyboard::Left){
                    amb.cursor--;
                }
                if(event.key.code == sf::Keyboard::Right){
                    amb.cursor++;
                }
                if(event.key.code == sf::Keyboard::Return){
                    amb.texto.insert(amb.cursor,'\n');
                    int t =  amb.texto.size() - quebra;
                    quebra = (quebra + (t - 1))+ 40;
                }
                int i =  amb.texto.size() - 40;
                if(event.key.code == sf::Keyboard::Up){
                    advance(amb.cursor, i);

                }
                if(event.key.code == sf::Keyboard::Down){
                    advance(amb.cursor,-i);
                }
            }
        }

        auto pos = sf::Vector2f(45, 50);
        janela.clear({255,255,255});
        janela.draw(sfText(pos, amb.toString(), sf::Color::Black, 30));
        janela.display();
    }
    return 0;
}




