#include "Arduino.h"
#include "Motor.h"

/**
 * Sınıfı oluştur.
 */
Motor::Motor(const int ENA_OUT_PIN, const int IN1_OUT_PIN, const int IN2_OUT_PIN, const int MOTOR_SPEED) {
    this->ENA_OUT_PIN = ENA_OUT_PIN;
    this->IN1_OUT_PIN = IN1_OUT_PIN;
    this->IN2_OUT_PIN = IN2_OUT_PIN;
    this->MOTOR_SPEED = MOTOR_SPEED;
}

/**
 * Motoru sola döndür.
 * (Motora ucundan bakıncaki sol.)
 */
void Motor::Left() {
    if (this->bIsTurningLeft && this->bIsRunning) return;

    // Motoru çalıştır
    analogWrite(this->ENA_OUT_PIN, this->MOTOR_SPEED);
    digitalWrite(this->IN1_OUT_PIN, HIGH);
    digitalWrite(this->IN2_OUT_PIN, LOW);

    this->bIsTurningLeft = true;
    this->bIsRunning = true;
}

void Motor::Right() {
    if (!this->bIsTurningLeft && this->bIsRunning) return;

    // Motoru çalıştır
    analogWrite(this->ENA_OUT_PIN, this->MOTOR_SPEED);
    digitalWrite(this->IN1_OUT_PIN, LOW);
    digitalWrite(this->IN2_OUT_PIN, HIGH);

    this->bIsTurningLeft = false;
    this->bIsRunning = true;
}

void Motor::Stop() {
    if (!this->bIsRunning) return;

    analogWrite(this->ENA_OUT_PIN, 0);

    this->bIsTurningLeft = false;
    this->bIsRunning = false;
}

