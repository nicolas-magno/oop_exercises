#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// abstract class Figure
class Figura {
protected:
    float x, y, dx, dy; // Position and velocity of Figure
public:
    Figura() : dx((rand() % 5) - 2), dy((rand() % 5) - 2) {} // random initicial moviment
    virtual ~Figura() {}
    void SetPosicao(float nx, float ny) { x = nx; y = ny; } 
    virtual void Desenha(sf::RenderWindow& window) const = 0; // abstract method
    void Atualiza() {
        x += dx;
        y += dy;
        
        // verify colision
        if (x <= 0 || x >= WINDOW_WIDTH - 50) dx = -dx;
        if (y <= 0 || y >= WINDOW_HEIGHT - 50) dy = -dy;
    }
    float getX() const { return x; }
    float getY() const { return y; }
};

// class Rectangle
class Quadrado : public Figura {
public:
    void Desenha(sf::RenderWindow& window) const override {
        sf::RectangleShape shape(sf::Vector2f(50, 50));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
    }
};

// class Triangle
class Triangulo : public Figura {
public:
    void Desenha(sf::RenderWindow& window) const override {
        sf::CircleShape shape(40, 3);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
        window.draw(shape);
    }
};

// class Circle
class Circulo : public Figura {
public:
    void Desenha(sf::RenderWindow& window) const override {
        sf::CircleShape shape(30);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Blue);
        window.draw(shape);
    }
};

// Function for update the window
void DisplayRefresh(sf::RenderWindow& window, vector<shared_ptr<Figura>>& figuras) {
    window.clear();
    for (auto& figura : figuras) {
        figura->Atualiza();
        figura->Desenha(window);
    }
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Figuras");
    vector<shared_ptr<Figura>> figuras;
    figuras.push_back(make_shared<Quadrado>());
    figuras.push_back(make_shared<Triangulo>());
    figuras.push_back(make_shared<Circulo>());

    // Posiciona as figuras inicialmente
    figuras[0]->SetPosicao(100, 100);
    figuras[1]->SetPosicao(300, 200);
    figuras[2]->SetPosicao(500, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        DisplayRefresh(window, figuras);
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return 0;
}
