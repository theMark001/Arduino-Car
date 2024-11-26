/* ​  																																⣇⣿⠘⣿⣿⣿⡿⡿⣟⣟⢟⢟⢝⠵⡝⣿⡿⢂⣼⣿⣷⣌⠩⡫⡻⣝⠹⢿⣿⣷																									 */
/* ​  																																⡆⣿⣆⠱⣝⡵⣝⢅⠙⣿⢕⢕⢕⢕⢝⣥⢒⠅⣿⣿⣿⡿⣳⣌⠪⡪⣡⢑⢝⣇ 																								 	 */
/* ​  																																⡆⣿⣿⣦⠹⣳⣳⣕⢅⠈⢗⢕⢕⢕⢕⢕⢈⢆⠟⠋⠉⠁⠉⠉⠁⠈⠼⢐⢕⢽ 																								   */
/*  																																​ ⡗⢰⣶⣶⣦⣝⢝⢕⢕⠅⡆⢕⢕⢕⢕⢕⣴⠏⣠⡶⠛⡉⡉⡛⢶⣦⡀⠐⣕⢕ 																								   */
/* ​ 																																  ⡝⡄⢻⢟⣿⣿⣷⣕⣕⣅⣿⣔⣕⣵⣵⣿⣿⢠⣿⢠⣮⡈⣌⠨⠅⠹⣷⡀⢱⢕ 																								   */
/*  																																 ⡝⡵⠟⠈⢀⣀⣀⡀⠉⢿⣿⣿⣿⣿⣿⣿⣿⣼⣿⢈⡋⠴⢿⡟⣡⡇⣿⡇⡀⢕ 																								  */
/* ​  																																⡝⠁⣠⣾⠟⡉⡉⡉⠻⣦⣻⣿⣿⣿⣿⣿⣿⣿⣿⣧⠸⣿⣦⣥⣿⡇⡿⣰⢗⢄ 																								   */
/* ​  																																⠁⢰⣿⡏⣴⣌⠈⣌⠡⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣬⣉⣉⣁⣄⢖⢕⢕⢕ 																								   */
/*  																																​ ⡀⢻⣿⡇⢙⠁⠴⢿⡟⣡⡆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣵⣵⣿ 																								   */
/*  																																​ ⡻⣄⣻⣿⣌⠘⢿⣷⣥⣿⠇⣿⣿⣿⣿⣿⣿⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ 																								   */
/*  																																​ ⣷⢄⠻⣿⣟⠿⠦⠍⠉⣡⣾⣿⣿⣿⣿⣿⣿⢸⣿⣦⠙⣿⣿⣿⣿⣿⣿⣿⣿⠟ 																								   */
/*  																																​ ⡕⡑⣑⣈⣻⢗⢟⢞⢝⣻⣿⣿⣿⣿⣿⣿⣿⠸⣿⠿⠃⣿⣿⣿⣿⣿⣿⡿⠁⣠ 																								   */
/*  																																​ ⡝⡵⡈⢟⢕⢕⢕⢕⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿⣿⣿⠿⠋⣀⣈⠙ 																								   */
/*  																																​ ⡝⡵⡕⡀⠑⠳⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⢉⡠⡲⡫⡪⡪⡣ 																								   */

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);
const int ledPin = 13;
String command = "";

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
  BTSerial.begin(9600);

  Serial.println("HC-05 Bluetooth LED Control");
  Serial.println("Commands:");
  Serial.println("ON - turn on LED");
  Serial.println("OFF - turn off LED");
}

void loop() {
  if (BTSerial.available()) {
    char c = BTSerial.read();
    if (c == '\n' || c == '\r') {
      processCommand(command);
      command = "";
    } else {
      command += c;
    }
  }

  if (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      processCommand(command);
      command = "";
    } else {
      command += c;
    }
  }
}

void processCommand(const String &cmd) {
  if (cmd == "ON") {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED is ON");
    BTSerial.println("LED is ON");
  } else if (cmd == "OFF") {
    digitalWrite(ledPin, LOW);
    Serial.println("LED is OFF");
    BTSerial.println("LED is OFF");
  } else {
    Serial.println("Unknown command: " + cmd);
    BTSerial.println("Unknown command: " + cmd);
  }
}