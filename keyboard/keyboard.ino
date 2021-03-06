#include "pitches.h"

// Buzzer pin
const int BUZZER_PIN  = 9;

// Key button pins
const int C = 2; // Button 1
const int D = 3; // Button 2
const int E = 4; // Button 3
const int F = 5; // Button 4
const int G = 6; // Button 5
const int A = 7; // Button 6
const int B = 8; // Button 7

// Modulation pins
const int RECORD_PIN = 10;
const int RESET_PIN = 11;
const int LOAD_PIN = 12;
const int STOP_PIN = 13;

// Indicator pin
const int LED_PIN = A0;

// Modulation memory
int counter = 0;
bool is_recording = false;
bool is_playing = false;
bool is_reset = false;

// Melody size and note duration
const int melody_size = 200;
int duration(50); // Every note lasts 50 milliseconds.

// Melody and individual notes arrays
int melody[melody_size] = {N_REST}; // Initialize empty melody
int c[] = {N_C5}; // Plays C Note
int d[] = {N_D5}; // Plays D Note
int e[] = {N_E5}; // Plays E Note
int f[] = {N_F5}; // Plays F Note
int g[] = {N_G5}; // Plays G Note
int a[] = {N_A5}; // Plays A Note
int b[] = {N_B5}; // Plays B Note

void setup() {
  Serial.begin (9600);
  //Set every button as an INPUT_PULLUP
  pinMode(C, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
  pinMode(F, INPUT_PULLUP);
  pinMode(G, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(RECORD_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(LOAD_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);
}

void loop() {
  // Modulation signals
  // Recording button pressed
  if (digitalRead(RECORD_PIN) == LOW) {
    Serial.println("Recording started");
    counter = 0;
    is_recording = true;
    is_playing = false;
    delay(200);
    analogWrite(LED_PIN, 1023); // Turn on LED
  }
  // Reset button pressed
  else if (digitalRead(RESET_PIN) == LOW) {
    Serial.println("Reset started");
    counter = 0;
    is_playing = false;
    is_recording = false;
    is_reset = true;
    delay(200);
    analogWrite(LED_PIN, 1023); // Turn on LED
  }
  // Play button pressed while not playing
  else if (digitalRead(LOAD_PIN) == LOW && is_playing == false) {
    Serial.println("Playing started");
    is_playing = true;
    is_recording = false;
    delay(200);
    analogWrite(LED_PIN, 1023); // Turn on LED
  }
  // Play button pressed while playing
  else if (digitalRead(LOAD_PIN) == LOW && is_playing == true) {
    Serial.println("Playing pauzed");
    is_playing = false; 
    is_recording = false;
    delay(200);
    analogWrite(LED_PIN, 0); // Turn off LED
  }
  // Stop button pressed
  else if (digitalRead(STOP_PIN) == LOW) {
    Serial.println("Playing stopped");
    counter = 0;
    is_playing = false;
    delay(200);
    analogWrite(LED_PIN, 0); // Turn off LED
  }
  event_handler();
}

  
void event_handler() {
  // Execute when program is in the reset state
  if (is_reset == true) {
    melody[counter] = N_REST;
    counter++;
    if (counter == melody_size - 1) {
      Serial.println("Reset finished");
      is_reset = false;
      counter = 0;
      analogWrite(LED_PIN, 0); // Turn off LED
    }
  }
  // Execute when the program is in the recording state
  if (is_recording == true) {
    if (digitalRead(C) == LOW) {
      tone(BUZZER_PIN, c[0], duration);
      melody[counter] = N_C5;
      Serial.println("Note: C");
    }
    else if (digitalRead(D) == LOW) {
      tone(BUZZER_PIN, d[0], duration);
      melody[counter] = N_D5;
      Serial.println("Note: D");
    }
    else if (digitalRead(E) == LOW) {
      tone(BUZZER_PIN, e[0], duration);
      melody[counter] = N_E5;
      Serial.println("Note: E");
    }
    else if (digitalRead(F) == LOW) {
      tone(BUZZER_PIN, f[0], duration);
      melody[counter] = N_F5;
      Serial.println("Note: F");
    }
    else if (digitalRead(G) == LOW) {
      tone(BUZZER_PIN, g[0], duration);
      melody[counter] = N_G5;
      Serial.println("Note: G");
    }
    else if (digitalRead(A) == LOW) {
      tone(BUZZER_PIN, a[0], duration);
      melody[counter] = N_A5;
      Serial.println("Note: A");
    }
    else if (digitalRead(B) == LOW) {
      tone(BUZZER_PIN, b[0], duration);
      melody[counter] = N_B5;
      Serial.println("Note: B");
    } else {
      melody[counter] = N_REST;
    }
    delay(duration);
    if (counter == melody_size - 1) {
      Serial.println("Recording stopped");
      is_recording = false;
      counter = 0;
      analogWrite(LED_PIN, 0); // Turn off LED
    }
    counter++;
  }
  // Execute when the program is in the play state
  if (is_playing == true) {
    tone(BUZZER_PIN, melody[counter], duration);
    switch (melody[counter]) {
      case N_C5:
        Serial.println("Note: C");
        break;
      case N_D5:
        Serial.println("Note: D");
        break;
      case N_E5:
        Serial.println("Note: E");
        break;
      case N_F5:
        Serial.println("Note: F");
        break;
      case N_G5:
        Serial.println("Note: G");
        break;
      case N_A5:
        Serial.println("Note: A");
        break;
      case N_B5:
        Serial.println("Note: B");
        break;
    }
    delay(50);
    if (counter == melody_size - 1) {
      // uncomment this to have no loop
      //is_playing = false;
      Serial.println("Playing repeat");
      counter = 0;
    }
    counter++;
  }
}
