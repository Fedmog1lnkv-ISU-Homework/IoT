// 47 - расстояние 56 - скорость / врепед - HIGH  назад - LEFT
#define DIR_RIGHT 4 
#define SPEED_RIGHT 5
#define DIR_LEFT 7 
#define SPEED_LEFT 6

const int spin_calibration_states[4][2] = { {0, 0}, {1, 1}, {0, 1}, {1, 0} };

State state = State::Stop;
State prevState = State::Stop;

bool drivingMode = false;
int calibrationState = 0;

int rotate_delay = 0;

unsigned long last_tick = 0;