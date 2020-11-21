#include "GameHost.h"
#include <sstream>

#define SSID        "Pac-Man"
#define PASSWORD    "JOYM5ATOM"
#define HOST        "192.168.4.1"
#define PORT_NO     8888


GameHost::GameHost()
{
  _state = GAME_HOST_STATE_INITIAL;
}

void GameHost::begin()
{
  terminate();
  Serial.println("WiFi begin");
}

void GameHost::update()
{
  switch (_state)
  {
  case GAME_HOST_STATE_INITIAL:
    state_initial();
    break;
  case GAME_HOST_STATE_CONNECTING:
    state_connecting();
    break;
  case GAME_HOST_STATE_CONNECTED:
    state_connected();
    break;
  case GAME_HOST_STATE_CLOSED:
    state_closed();
    break;
  }
}

void GameHost::set_state(int state)
{
  _state = state;
}

void GameHost::state_initial()
{
  WiFi.begin(SSID, PASSWORD);
  set_state(GAME_HOST_STATE_CONNECTING);
}

void GameHost::state_connecting()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected");
    if (_client == false) {
        _client = WiFiClient();
    }
    _client.connect(HOST, PORT_NO);
    set_state(GAME_HOST_STATE_CONNECTED);
  }
}

void GameHost::set_direction(bool top, bool left, bool right, bool bottom)
{
  if (!is_connected()) return;
  
  char value = '5';
  if        (!top && left && !right && bottom) {
    value = '1';
  } else if (!top && !left && !right && bottom) {
    value = '2';
  } else if (!top && !left && right && bottom) {
    value = '3';
  } else if (!top && left && !right && !bottom) {
    value = '4';
  } else if (!top && !left && !right && !bottom) {
    value = '5';
  } else if (!top && !left && right && !bottom) {
    value = '6';
  } else if (top && left && !right && !bottom) {
    value = '7';
  } else if (top && !left && !right && !bottom) {
    value = '8';
  } else if (top && !left && right && !bottom) {
    value = '9';
  }
  _client.write(value);
  _client.flush();
  //Serial.print(value);
}

void GameHost::state_connected()
{
  if (!_client.connected())
  {
    set_state(GAME_HOST_STATE_CLOSED);
  }
}

void GameHost::state_closed()
{
  terminate();
  Serial.println("WiFi closed");
}

void GameHost::terminate()
{
  set_state(GAME_HOST_STATE_INITIAL);
  if (_client)
  {
    _client.stop();
    _client.~WiFiClient();
  }
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
  }
}
