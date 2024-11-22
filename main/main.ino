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

int IN1 = 5;
int IN2 = 4;
int IN3 = 3;
int IN4 = 2;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);

  stopMotors();
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == 'f') {
      moveForward();
      Serial.println("Moving Forward");
    }
    else if (input == '0') {
      stopMotors();
      Serial.println("Motors Stopped");
    }
    else if (input == 'b') {
      moveBack();
      Serial.println("Moving Backward");
    }
    else if (input == 'r') {
      turnRight();
      Serial.println("Turning Right");
    }
    else if (input == 'l') {
      turnLeft();
      Serial.println("Turning Right");
    }
  }
}

void moveBack() {
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH);   

  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH);   
}

void moveForward() {
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);   

  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);   
}

void turnRight() {
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH);   

  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);   
}

void turnLeft() {
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);   

  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH);   
}

void stopMotors() {
  digitalWrite(IN1, LOW);   
  digitalWrite(IN2, LOW);   

  digitalWrite(IN3, LOW);   
  digitalWrite(IN4, LOW);   
}