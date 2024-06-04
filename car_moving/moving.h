
void update_state(int new_state) {
  if (new_state != state) {
    state = new_state;
  }
}

void move(int rspeed, int lspeed){
  bool lforward = lspeed > 0 ^ spin_calibration_states[calibrationState][0];
  bool rforward = rspeed > 0 ^ spin_calibration_states[calibrationState][1];
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, abs(rspeed));
  analogWrite(SPEED_LEFT, abs(lspeed));
}

void set_new_state(int new_state) {
  state = new_state;
}

int to_drive() {
  move(255, 255);
  return State::Drive;
}

int to_revierse() {
  move(-255, -255);
  return State::Reverse;
}

int to_stop() {
  move(0, 0);
  return State::Stop;
}

int turn_to_left() {
  move(80, 255);
  return State::TurnToLeft;
}

int turn_to_right() {
  move(255, 80);
  return State::TurnToRight;
}

int rotate_to_left() {
  move(-255, 255);
  return State::RotateToLeft;
}

int rotate_to_right() {
  move(255, -255);
  return State::RotateToRight;
}

int get_state() {
  switch (state) {
    case State::Drive:
      return to_drive();
    case State::TurnToLeft:
      return turn_to_left();
    case State::TurnToRight:
      return turn_to_right();
    case State::RotateToLeft:
      return rotate_to_left();
    case State::RotateToRight:
      return rotate_to_right();
    case State::Stop:
      return to_stop();
    case State::Reverse:
      return to_revierse();
  }
}

void process() {
  int cur_state = get_state();
  update_state(cur_state);
}