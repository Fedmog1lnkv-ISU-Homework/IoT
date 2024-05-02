#define DIR_RIGHT 4 
#define SPEED_RIGHT 5
#define DIR_LEFT 7 
#define SPEED_LEFT 6

#define PIN_TRIG_1 9
#define PIN_ECHO_1 10

#define PIN_TRIG_2 12
#define PIN_ECHO_2 11

long forward_duration, forward_sm;
long left_duration, left_sm;

unsigned long lastTurnTime = 0;

int turnDuration = 1380;
int quarterTurnDuration = turnDuration / 4;

void setup() {
  for(int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(PIN_TRIG_1, OUTPUT);
  pinMode(PIN_ECHO_1, INPUT);
  pinMode(PIN_TRIG_2, OUTPUT);
  pinMode(PIN_ECHO_2, INPUT);
  Serial.begin(9600); 
}

void move(bool left, bool right, int left_speed, int rignt_speed){
  digitalWrite(DIR_RIGHT, right);
  analogWrite(SPEED_RIGHT, rignt_speed);

  digitalWrite(DIR_LEFT, left);
  analogWrite(SPEED_LEFT, left_speed);
}

void forward(int speed){
  move(false, true, speed * 1.02, speed);
}

void back(int speed){
  move(true, false, speed, speed);
}

void stop(){
  move(true, false, 0, 0);
}

void turn(bool direction, int speed) {
  if (direction) { // if true - is left
    move(true, true, speed, speed);
    analogWrite(SPEED_RIGHT, speed);
  } else { // if faslse - is right
    move(false, false, speed, speed);
    analogWrite(SPEED_LEFT, speed);
  }

  while (millis() - lastTurnTime < 3 * quarterTurnDuration) {} // wait for turning
  
  stop(); 
}

void going(int triger_dist){
   if (forward_duration < triger_dist && left_duration < triger_dist) {
    turn(false, 255); // turn right

  } else if (forward_duration < triger_dist && left_duration >= triger_dist) {
    turn(true, 255); // turn left

  } else if ( forward_duration >= triger_dist && left_duration < triger_dist) {
    forward(100); // drive forward

  } else if (forward_duration > triger_dist && left_duration > triger_dist) {
    delay(750);
    turn(true, 255); // turn left
    forward(100);
    delay(3000);
  }
}

long processDuration(int duration) {
  return (duration / 2) / 29.1;
}

void loop() {
  digitalWrite(PIN_TRIG_1, LOW);
  delayMicroseconds(5);

  digitalWrite(PIN_TRIG_1, HIGH);
  delayMicroseconds(10);

  digitalWrite(PIN_TRIG_1, LOW);
  forward_duration = pulseIn(PIN_ECHO_1, HIGH);
  forward_sm = processDuration(forward_duration);

  Serial.print("Forward distance: ");
  Serial.print(forward_sm);
  Serial.println(" sm.");

  digitalWrite(PIN_TRIG_2, LOW);
  delayMicroseconds(5);

  digitalWrite(PIN_TRIG_2, HIGH);
  delayMicroseconds(10);

  digitalWrite(PIN_TRIG_2, LOW);
  left_duration = pulseIn(PIN_ECHO_2, HIGH);
  left_sm = processDuration(left_duration);

  Serial.print("Left distance: ");
  Serial.print(left_sm);
  Serial.println(" sm.");

  going(20); 
}