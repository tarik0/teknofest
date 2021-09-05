#ifndef __MOTOR
#define __MOTOR 

/**
 * Motorları çalıştırmak için yardımcı kütüphane
 */
class Motor {
    private:
        int ENA_OUT_PIN;
        int IN1_OUT_PIN;
        int IN2_OUT_PIN;
        int MOTOR_SPEED;

        bool bIsRunning = false;
        bool bIsTurningLeft = false;


    public:
        Motor(const int ENA_OUT_PIN, const int IN1_OUT_PIN, const int IN2_OUT_PIN, const int MOTOR_SPEED);
        void Left();
        void Right();
        void Stop();

};

#endif