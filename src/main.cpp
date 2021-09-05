#include <Arduino.h>
#include <Motor.h>
#include <HCSR04.h>

/**
 * L298N Sürücü Pinleri
 */
const int IN1_OUT_PIN = 7;
const int IN2_OUT_PIN = 6;
const int IN3_OUT_PIN = 5;
const int IN4_OUT_PIN = 4;

const int ENA_OUT_PIN = 9;
const int ENB_OUT_PIN = 3;

/**
 * Motorların hızını ayarlar.
 * (Bu değer 255 ile 0 arasında olmalıdır.)
 */
const int MOTOR_SPEED = 50;

/**
 * HCSR04 Ultrasonik Mesafe Sensörü Pinleri
 */
const int LEFT_TRIGGER_PIN = 13;
const int LEFT_ECHO_PIN = 12;
const int RIGHT_TRIGGER_PIN = 11;
const int RIGHT_ECHO_PIN = 10;
const int FRONT_TRIGGER_PIN = 8;
const int FRONT_ECHO_PIN = 2;

/**
 * Yardımcı motor kütüphanemiz.
 */
Motor LEFT_MOTOR(
    ENA_OUT_PIN,
    IN1_OUT_PIN,
    IN2_OUT_PIN,
    MOTOR_SPEED
);
Motor RIGHT_MOTOR(
    ENB_OUT_PIN,
    IN3_OUT_PIN,
    IN4_OUT_PIN,
    MOTOR_SPEED
);

// O tarafa dönmesi için minimum uzaklık.
const float MIN_DISTANCE_CM = 15.0;

/**
 * Mesafe sensörü yardımcı kütüphanesi.
 */
UltraSonicDistanceSensor LEFT_DISTANCE_SENSOR(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN);
UltraSonicDistanceSensor RIGHT_DISTANCE_SENSOR(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN);
UltraSonicDistanceSensor FRONT_DISTANCE_SENSOR(FRONT_TRIGGER_PIN, FRONT_ECHO_PIN);


void setup() {
    Serial.begin(9600);

    // L298N Pinlerini ata.
    pinMode(IN1_OUT_PIN, OUTPUT);
    pinMode(IN2_OUT_PIN, OUTPUT);
    pinMode(IN3_OUT_PIN, OUTPUT);
    pinMode(IN4_OUT_PIN, OUTPUT);
    pinMode(ENB_OUT_PIN, OUTPUT);
    pinMode(ENA_OUT_PIN, OUTPUT);
}

void loop() {
    // Uzaklık sensörlerini oku.
    bool bGoLeft  = LEFT_DISTANCE_SENSOR.measureDistanceCm() >= 0 && LEFT_DISTANCE_SENSOR.measureDistanceCm() <= MIN_DISTANCE_CM;
    bool bGoRight = RIGHT_DISTANCE_SENSOR.measureDistanceCm() >= 0 && RIGHT_DISTANCE_SENSOR.measureDistanceCm() <= MIN_DISTANCE_CM;
    bool bGoFront = FRONT_DISTANCE_SENSOR.measureDistanceCm() >= 0 && FRONT_DISTANCE_SENSOR.measureDistanceCm() <= MIN_DISTANCE_CM;

    // Önünde engel varsa ileri git.
    if (bGoFront) {
        LEFT_MOTOR.Left();
        RIGHT_MOTOR.Right();
        return;
    }

    // Önünde engel varsa sağa git.
    if (bGoRight) {
        LEFT_MOTOR.Left();
        RIGHT_MOTOR.Left();
        return;
    }

    // Önünde engel varsa sola git.
    if (bGoLeft) {
        LEFT_MOTOR.Right();
        RIGHT_MOTOR.Right();
        return;
    }
}