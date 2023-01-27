#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Vector2f ballVelocity;
bool server = false;

const Keyboard::Key controls[4] = {
    Keyboard::A,   // Player1 UP
    Keyboard::Z,   // Player1 Down
    Keyboard::Up,  // Player2 UP
    Keyboard::Down // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

void Load() {
    // Set size and origin of paddles
    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin({ ballRadius / 2.0f, ballRadius / 2.0f }); //Should be half the ball width and height
    // reset paddle position
    paddles[0].setPosition(Vector2(10.f + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2(gameWidth - (10.0f + paddleSize.x / 2.f), gameHeight / 2.f));
    // reset Ball Position
    ball.setPosition(Vector2(gameWidth / 2.f, gameHeight / 2.f));
    
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void Reset() {

    // reset paddle position
    paddles[0].setPosition(Vector2(10.f + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2(gameWidth - (10.0f + paddleSize.x / 2.f), gameHeight / 2.f));
    // reset Ball Position
    ball.setPosition(Vector2(gameWidth / 2.f, gameHeight / 2.f));

    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // handle paddle movement
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(Vector2(0.f, direction * paddleSpeed * dt));

    direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[2])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        direction++;
    }
    paddles[1].move(Vector2(0.f, direction * paddleSpeed * dt));

    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { //bottom wall
      // bottom wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(Vector2(0.f, -10.f));
    }
    else if (by < 0) { //top wall
    // top wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(Vector2(0.f, 10.f));
    }
    else if (bx > gameWidth) {
        // right wall
        Reset();
    }
    else if (bx < 0) {
        // left wall
        Reset();
    }
    else if (
        //ball is inline or behind paddle
        bx < paddleSize.x &&
        //AND ball is below top edge of paddle
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //AND ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
        ) {
        // bounce off left paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(Vector2(10.f, 0.f));
    }
    else if (//ball is inline or behind paddle
        bx > (gameWidth - (paddleSize.x)*2) &&
        //AND ball is below top edge of paddle
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
        //AND ball is above bottom edge of paddle
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
        ) {
        // bounce off right paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(Vector2(-10.f, 0.f));
    }

    ball.move(ballVelocity * dt);
}

void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main() {
    RenderWindow window(VideoMode({ gameWidth, gameHeight }), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}