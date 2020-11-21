#ifndef game_host_h
#define game_host_h

#include <WiFi.h>
#include <WiFiAP.h>

#define GAME_HOST_STATE_INITIAL       0
#define GAME_HOST_STATE_CONNECTING    1
#define GAME_HOST_STATE_CONNECTED     2
#define GAME_HOST_STATE_CLOSED        3

class GameHost
{
  public:
    GameHost();
    void begin();
    void update();
    void set_direction(bool top, bool left, bool right, bool bottom);
    bool is_connected() { return _state == GAME_HOST_STATE_CONNECTED; }

  private:
    WiFiClient _client;
    int _state;

    void set_state(int state);
    void state_initial();
    void state_connecting();
    void state_listen();
    void state_connected();
    void state_closed();
    bool check_connection();
    void terminate();

};

#endif
