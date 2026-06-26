using namespace std;

#include <cstdint>
#include <cmath>
#include <vector>

#include <raylib.h>

Sound clickSound;

Rectangle OffsetRect(Rectangle r, float dx, float dy)
{
    r.x += dx;
    r.y += dy;
    return r;
}

Color MultipliedColor(Color c, float multiplier) {
    c.r *= multiplier;
    c.g *= multiplier;
    c.b *= multiplier;
    return c;
}

float Clamp(float v, float min, float max)
{
    return (v < min) ? min : (v > max) ? max : v;
}

float Ramp(float t, float offset, float rate) {
    return (t * rate) + offset;
}

class Button
{
public:
    Rectangle r;
    Rectangle r1;
    Rectangle r2;
    Color c;
    Color c1;
    Color c2;
    Color c3;
    bool pressed = false;
    uint16_t framesHovered = 0;

    Button(Rectangle r, Color c)
        : r(r), c(c)
    {}

    void start()
    {
        r1 = OffsetRect(r, 5, -5);
        r2 = OffsetRect(r, 10, -10);
        c1 = MultipliedColor(c, 0.7f);
        c2 = MultipliedColor(c1, 0.7f);
        c3 = MultipliedColor(c2, 0.7f);
    }

    void update()
    {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, r))
            pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        
        if (pressed)
            PlaySound(clickSound);

        if (CheckCollisionPointRec(mouse, r)) {
            DrawRectangleRec(OffsetRect(r2, 0, -Clamp(Ramp(framesHovered, -15, 1), 0, 5)), c3);
            DrawRectangleRec(OffsetRect(r1, 0, -Clamp(Ramp(framesHovered, -5, 0.5f), 0, 5)), c2);
            DrawRectangleRec(OffsetRect(r, 0, -Clamp(Ramp(framesHovered, 0, 0.25f), 0, 5)), c1);
            framesHovered++;
        }
        else {
            DrawRectangleRec(r2, c2);
            DrawRectangleRec(r1, c1);
            DrawRectangleRec(r, c);
            framesHovered = 0;
        }
    }
};

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "windows xp vibes but raylib");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D wallpaper = LoadTexture("Bliss-1200x900.jpg");
    clickSound = LoadSound("click.wav");

    vector<Button> buttons;

    buttons.push_back(Button(
        {570, 490, 300, 100},
        {0, 70, 255, 255}
    ));

    for (Button& button : buttons)
        button.start();

    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawTexture(wallpaper, 0, 0, WHITE);

        for (Button& button : buttons)
            button.update();

        EndDrawing();
    }
}