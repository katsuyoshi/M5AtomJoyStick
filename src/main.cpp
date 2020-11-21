#include "M5Atom.h"
#include "GameHost.h"

// GGRRBB
#define BLACK   0x000000
#define BLUE    0x0000f0
#define GREEN   0xf00000
#define RED     0x00f000
#define WHITE   0xf0f0f0

float gain = 1.0 / 10.0;
double pitch, roll;
GameHost host;

void setup()
{
  M5.begin(true, true, true);
  M5.IMU.Init();
  host = GameHost();
  host.begin();
}

void drawCross()
{
  M5.dis.fillpix(BLACK);
  CRGB color = host.is_connected() ? BLUE : RED;
  for (int i = 0; i < 5; i++) {
    M5.dis.drawpix(2, i, color);
    M5.dis.drawpix(i, 2, color);
  }
}

void drawPoint(int x, int y)
{
  M5.dis.drawpix(x + 2, y + 2, WHITE);
}

void loop()
{
    delay(200);

    M5.IMU.getAttitude(&pitch, &roll);
    int x = -(int)(pitch * gain);
    int y = -(int)(roll * gain);
    x = min(max(x, -2), 2);
    y = min(max(y, -2), 2);
    
    drawCross();
    drawPoint(x, y);
    M5.update();

    host.update();
    host.set_direction(y <= -1, x <= -1, x >= 1, y >= 1);
}