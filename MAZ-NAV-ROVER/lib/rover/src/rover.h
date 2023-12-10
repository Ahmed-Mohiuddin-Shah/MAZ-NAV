class Rover
{
private:
    AccelStepper rightStepper;
    AccelStepper leftStepper;
    MultiStepper steppers;
    long globalPosition[2];

    void setGlobalPosition(int x, int y)
    {
        globalPosition[0] = x;
        globalPosition[1] = y;
    }

public:
    Rover(int rightStep, int rightDir, int leftStep, int leftDir, int maxSpeed, int maxAccel)
    {
        globalPosition[0] = 0;
        globalPosition[1] = 0;

        rightStepper = (AccelStepper::DRIVER, rightStep, rightDir);
        leftStepper = (AccelStepper::DRIVER, leftStep, leftDir);
        rightStepper.setMaxSpeed(maxSpeed);
        rightStepper.setAcceleration(MOTOR_ACCELERATION);

        leftStepper.setMaxSpeed(maxSpeed);
        leftStepper.setAcceleration(maxAccel);
        steppers.addStepper(rightStepper);
        steppers.addStepper(leftStepper);
    }

    void move(int x, int y)
    {
        setGlobalPosition(x, y);
        steppers.moveTo(globalPosition);
        steppers.runSpeedToPosition();
    }
};