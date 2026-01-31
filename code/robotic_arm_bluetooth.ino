#include <Servo.h>
#include <SoftwareSerial.h>

/* =========================================================
 *                     BLUETOOTH SETUP
 * =========================================================
 * HC-06 Connections:
 * HC-06 TX → Arduino Pin 8
 * HC-06 RX → Arduino Pin 9
 */
SoftwareSerial BT(8, 9);   // RX, TX

/* =========================================================
 *                     SERVO OBJECTS
 * ========================================================= */
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo rotateServo;
Servo wristServo;
Servo gripperServo;

/* =========================================================
 *                     SERVO PINS
 * ========================================================= */
#define BASE_PIN      2
#define SHOULDER_PIN  3
#define ELBOW_PIN     4
#define ROTATE_PIN    5
#define WRIST_PIN     6
#define GRIPPER_PIN   7

/* =========================================================
 *                     HOME POSITIONS
 * ========================================================= */
int BASE_HOME     = 90;
int SHOULDER_HOME = 90;
int ELBOW_HOME    = 90;
int ROTATE_HOME   = 90;
int WRIST_HOME    = 90;

/* =========================================================
 *                     GRIPPER LIMITS
 * ========================================================= */
int GRIPPER_OPEN  = 160;
int GRIPPER_CLOSE = 100;

/* =========================================================
 *                  PICK & DROP POSITIONS
 * ========================================================= */
int SHOULDER_DOWN = 60;
int ELBOW_DOWN    = 170;
int WRIST_DOWN    = 60;
int BASE_DROP     = 170;
int ELBOW_DROP    = 130;

/* =========================================================
 *                     MOVEMENT SPEED
 * ========================================================= */
int MOVE_DELAY = 15;   // Smaller value = faster movement

/* =========================================================
 *            FUNCTION: SMOOTH SERVO MOVEMENT
 * ========================================================= */
void moveSmooth(Servo &servo, int from, int to) {
  if (from < to) {
    for (int pos = from; pos <= to; pos++) {
      servo.write(pos);
      delay(MOVE_DELAY);
    }
  } else {
    for (int pos = from; pos >= to; pos--) {
      servo.write(pos);
      delay(MOVE_DELAY);
    }
  }
}

/* =========================================================
 *            FUNCTION: MOVE ARM TO HOME POSITION
 * ========================================================= */
void goHome() {
  moveSmooth(gripperServo, gripperServo.read(), GRIPPER_CLOSE);
  moveSmooth(wristServo,   wristServo.read(),   WRIST_HOME);
  moveSmooth(rotateServo,  rotateServo.read(),  ROTATE_HOME);
  moveSmooth(elbowServo,   elbowServo.read(),   ELBOW_HOME);
  moveSmooth(shoulderServo,shoulderServo.read(),SHOULDER_HOME);
  moveSmooth(baseServo,    baseServo.read(),    BASE_HOME);
}

/* =========================================================
 *            GESTURES
 * ========================================================= */
void helloGesture() {
  for (int i = 0; i < 3; i++) {
    moveSmooth(wristServo, WRIST_HOME, 110);
    moveSmooth(wristServo, 110, 70);
  }
  goHome();
}

void danceGesture() {
  for (int i = 0; i < 2; i++) {
    moveSmooth(elbowServo, ELBOW_HOME, 130);
    moveSmooth(gripperServo, GRIPPER_CLOSE, GRIPPER_OPEN);
    moveSmooth(rotateServo, ROTATE_HOME, 160);
    moveSmooth(rotateServo, 160, ROTATE_HOME);
  }
  goHome();
}

void yesSign() {
  for (int i = 0; i < 2; i++) {
    moveSmooth(elbowServo, ELBOW_HOME, 120);
    moveSmooth(elbowServo, 120, ELBOW_HOME);
  }
  goHome();
}

void noSign() {
  for (int i = 0; i < 2; i++) {
    moveSmooth(baseServo, BASE_HOME, 60);
    moveSmooth(baseServo, 60, 120);
    moveSmooth(baseServo, 120, BASE_HOME);
  }
  goHome();
}

void gripperTest() {
  for (int i = 0; i < 2; i++) {
    moveSmooth(gripperServo, GRIPPER_CLOSE, GRIPPER_OPEN);
    delay(400);
    moveSmooth(gripperServo, GRIPPER_OPEN, GRIPPER_CLOSE);
    delay(400);
  }
}

void pickupAndDrop() {
  moveSmooth(gripperServo, GRIPPER_CLOSE, GRIPPER_OPEN);
  moveSmooth(wristServo, WRIST_HOME, WRIST_DOWN);
  moveSmooth(shoulderServo, SHOULDER_HOME, SHOULDER_DOWN);
  moveSmooth(elbowServo, ELBOW_HOME, ELBOW_DOWN);

  delay(500);
  moveSmooth(gripperServo, GRIPPER_OPEN, GRIPPER_CLOSE);
  delay(500);

  moveSmooth(elbowServo, ELBOW_DOWN, ELBOW_HOME);
  moveSmooth(shoulderServo, SHOULDER_DOWN, SHOULDER_HOME);
  moveSmooth(wristServo, WRIST_DOWN, WRIST_HOME);

  moveSmooth(baseServo, BASE_HOME, BASE_DROP);
  moveSmooth(shoulderServo, SHOULDER_HOME, SHOULDER_DOWN);
  moveSmooth(elbowServo, ELBOW_HOME, ELBOW_DROP);

  moveSmooth(gripperServo, GRIPPER_CLOSE, GRIPPER_OPEN);
  delay(500);

  goHome();
}

/* =========================================================
 *            COMMAND HANDLER (SERIAL / BLUETOOTH)
 * ========================================================= */
void handleCommand(char cmd) {
  if      (cmd == '1') { Serial.println("Hello Gesture"); helloGesture(); }
  else if (cmd == '2') { Serial.println("Dance Gesture"); danceGesture(); }
  else if (cmd == '3') { Serial.println("Pickup & Drop"); pickupAndDrop(); }
  else if (cmd == '4') { Serial.println("Yes Sign"); yesSign(); }
  else if (cmd == '5') { Serial.println("No Sign"); noSign(); }
  else if (cmd == '6') { Serial.println("Gripper Test"); gripperTest(); }
  else { Serial.println("Unknown command received"); }
}

/* =========================================================
 *                     SETUP
 * ========================================================= */
void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  baseServo.attach(BASE_PIN);
  shoulderServo.attach(SHOULDER_PIN);
  elbowServo.attach(ELBOW_PIN);
  rotateServo.attach(ROTATE_PIN);
  wristServo.attach(WRIST_PIN);
  gripperServo.attach(GRIPPER_PIN);

  // Improvement 1: Servo initialization safety
  baseServo.write(BASE_HOME);
  shoulderServo.write(SHOULDER_HOME);
  elbowServo.write(ELBOW_HOME);
  rotateServo.write(ROTATE_HOME);
  wristServo.write(WRIST_HOME);
  gripperServo.write(GRIPPER_CLOSE);
  delay(500);

  goHome();
  Serial.println("Bluetooth and Serial Ready");
}

/* =========================================================
 *                     MAIN LOOP
 * ========================================================= */
void loop() {
  if (Serial.available()) {
    handleCommand(Serial.read());
  }

  if (BT.available()) {
    handleCommand(BT.read());
  }
}
