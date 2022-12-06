/*
    Este código usou como base a ideia do jogo cross de matrix, o adaptando para a utilização 
    do algoritmo de Dijkstra e melhorando a modularização.
    A versão base está disponível em: https://github.com/projeto-de-algoritmos/Grafos2_Cross_The_Matrix
*/

#include <Solution.h>
#include <unistd.h>
#include <iostream>
#include <Settings.h>

using namespace sf;

//Mostra o caminho vencedor calculador pelo algoritimo de Dijkstra
void show_winner_path(std::vector<int> path, int m[10][10], RectangleShape* r, RenderTexture* t, Font f){
    for(auto node : path){
        int i = node/10, j=node%10;
        int x = i*48, y = j*48;
        r->setPosition(x, y);
        r->setFillColor(Color::Green);
        r->setOutlineColor(Color(0, 0, 0));
        r->setOutlineThickness(2);
        std::string value = "";
        int n = m[i][j];
        value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);
        Text text = Text(value, f, 23);
        text.setPosition(x+10, y+10);
        text.setFillColor(Color(248, 24, 148));
        t->draw(*r);
        t->display();
        t->draw(text);
        t->display();
    }
}

int main (){

    Solution *sol = new Solution();
    int minPath = sol->getSolution();

    Settings *sets = new Settings();
    int trys = 1, playerValue = 0, bestRun = 9999999;
    int playerX=0, playerY=0;
    bool isPlaying = true;

    RenderWindow window(VideoMode(sets->width, sets->height), "CrossField");
	auto desktop = VideoMode::getDesktopMode();
	Vector2i v2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
	window.setPosition(v2i);
	window.setFramerateLimit(60);

    Sprite sprite;
	RenderTexture t;
	t.create(sets->width, sets->height);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	window.draw(sprite);
	window.display();

    t.display();
    window.draw(sprite);
	window.display();

    const Vector2f v2f(46.0, 46.0);
    RectangleShape r;
    r = RectangleShape(v2f);

    Text textMenorCaminho = Text(sets->shortest_path+std::to_string(minPath), sets->font, 20);
    textMenorCaminho.setFillColor(Color(255, 255, 255));
    textMenorCaminho.setPosition(510, 50);
    t.draw(textMenorCaminho);
    t.display();

    Text textEncontrado = Text(sets->current_value+std::to_string(playerValue), sets->font, 20);
    textEncontrado.setFillColor(Color(255, 255, 255));
    textEncontrado.setPosition(510, 140);
    t.draw(textEncontrado);
    t.display();

    Text textNumeroTentativas = Text(sets->try_number+std::to_string(trys), sets->font, 20);
    textNumeroTentativas.setFillColor(Color(255, 255, 255));
    textNumeroTentativas.setPosition(510, 230);
    t.draw(textNumeroTentativas);
    t.display();

    Text textMelhorTentativa = Text(sets->best_try+"0", sets->font, 15);
    textMelhorTentativa.setFillColor(Color(255, 255, 255));
    textMelhorTentativa.setPosition(510, 320);
    t.draw(textMelhorTentativa);
    t.display();

    Text voceGanhou = Text(sets->victory, sets->font, 50);
    voceGanhou.setFillColor(Color(255, 255, 255));
    voceGanhou.setPosition(530, 380);

    for(int i=0; i<10; ++i){
        for(int j=0; j<10; ++j){

            int x = i*48, y = j*48;
            r.setPosition(x, y);
            r.setFillColor(Color::White);
            r.setOutlineColor(Color(0, 0, 0));
            r.setOutlineThickness(2);
            std::string value = "";

            int n = sol->gameMatrix[i][j];
            value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);

            Text text = Text(value, sets->font, 23);
            text.setPosition(x+10, y+10);
            text.setFillColor(Color(248, 24, 148));
            t.draw(r);
            t.display();
            t.draw(text);
            t.display();
        }
    }

    RectangleShape rRed;
    rRed = RectangleShape(v2f);

    rRed.setFillColor(Color::Transparent);
    rRed.setOutlineColor(Color(0, 173, 238));
    rRed.setOutlineThickness(-4);
    rRed.setPosition(0, 0);
    t.draw(rRed);
    t.display();

    window.draw(sprite);
    window.display();     

    while(window.isOpen())
    {
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == e.Closed){
                window.close();
            }
            else if(e.type == Event::KeyPressed && isPlaying){
                switch (e.key.code){
                    case Keyboard::Enter :{
                        if(playerX == 0 && playerY == 0){
                            continue;
                        }
                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";

                        int n = sol->gameMatrix[playerX][playerY];
                        value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);

                        Text text = Text(value, sets->font, 23);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerX = 0;
                        playerY = 0;
                        // TODO: Escrever na tela
                        playerValue = 0;
                        trys++;

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                        
						break;
					}
					case Keyboard::Right :{
						if(playerX >= 9){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";

                        int n = sol->gameMatrix[playerX][playerY];
                        value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);

                        Text text = Text(value, sets->font, 23);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerX++;
                        // TODO: Escrever na tela
                        playerValue+=sol->gameMatrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                        
						break;
					}
                    case Keyboard::Left :{
						if(playerX <= 0){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";

                        int n = sol->gameMatrix[playerX][playerY];
                        value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);

                        Text text = Text(value, sets->font, 23);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerX--;
                        // TODO: Escrever na tela
                        playerValue+=sol->gameMatrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                        
						break;
					}
                    case Keyboard::Down :{
						if(playerY >= 9){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";

                        int n = sol->gameMatrix[playerX][playerY];
                        value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);

                        Text text = Text(value, sets->font, 23);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerY++;
                        // TODO: Escrever na tela
                        playerValue+=sol->gameMatrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();

						break;
					}
                    case Keyboard::Up :{
						if(playerY <= 0){
                            continue;
                        }

                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";

                        int n = sol->gameMatrix[playerX][playerY];
                        value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);

                        Text text = Text(value, sets->font, 23);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        // Pinta proximo de vermelho
                        playerY--;
                        // TODO: Escrever na tela
                        playerValue+=sol->gameMatrix[playerX][playerY];

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();

						break;
					}
                    case Keyboard::G :{ //Ao desistir, mostra na tela o caminho vencedor                       
                            show_winner_path(sol->getPath(), sol->gameMatrix, &r, &t, sets->font);
                            isPlaying = false;
                        break;
                    }
					default:{
						continue;
						break;
					}
				}
                if(playerX == 9 && playerY == 9){
                    if(playerValue == minPath){
                        show_winner_path(sol->getPath(), sol->gameMatrix, &r, &t, sets->font);
                        t.draw(voceGanhou);
                        t.display();
                        isPlaying = false;
                    }
                    else{
                        // Redesenha anterior
                        int x = playerX*48, y = playerY*48;
                        r.setPosition(x, y);

                        std::string value = "";

                        int n = sol->gameMatrix[playerX][playerY];
                        value += (n/10 == 0) ? "0"+std::to_string(n) : std::to_string(n);

                        Text text = Text(value, sets->font, 23);
                        text.setPosition(x+10, y+10);
                        text.setFillColor(Color(248, 24, 148));
                        t.draw(r);
                        t.display();
                        t.draw(text);
                        t.display();

                        bestRun=std::min(bestRun, playerValue);

                        // Pinta proximo de vermelho
                        playerX = 0;
                        playerY = 0;
                        // TODO: Escrever na tela
                        playerValue = 0;
                        trys++;

                        rRed.setPosition(playerX*48, playerY*48);
                        t.draw(rRed);
                        t.display();
                    }
                    
                }
            }
            
            
        }
        
        const Vector2f v2fdeleteRect(500.0, 46.0);
        RectangleShape deleteRect;
        deleteRect = RectangleShape(v2fdeleteRect);
        deleteRect.setFillColor(Color::Black);

        deleteRect.setPosition(510, 140);
        t.draw(deleteRect);
        t.display();

        textEncontrado = Text(sets->current_value+std::to_string(playerValue), sets->font, 20);
        textEncontrado.setFillColor(Color(255, 255, 255));
        textEncontrado.setPosition(510, 140);
        t.draw(textEncontrado);
        t.display();

        deleteRect.setPosition(510, 230);
        t.draw(deleteRect);
        t.display();

        textNumeroTentativas = Text(sets->try_number+std::to_string(trys), sets->font, 20);
        textNumeroTentativas.setFillColor(Color(255, 255, 255));
        textNumeroTentativas.setPosition(510, 230);
        t.draw(textNumeroTentativas);
        t.display();

        deleteRect.setPosition(510, 320);
        t.draw(deleteRect);
        t.display();

        int bestRunValue = (bestRun == 9999999) ? 0 : bestRun;
        textMelhorTentativa = Text(sets->best_try+std::to_string(bestRunValue), sets->font, 20);
        textMelhorTentativa.setFillColor(Color(255, 255, 255));
        textMelhorTentativa.setPosition(510, 320);
        t.draw(textMelhorTentativa);
        t.display();        

        window.clear();
		window.draw(sprite);
		window.display();
    }
    
    return 0;
}