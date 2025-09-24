#include <DigiMouse.h>
#include <math.h>

const int baseDelaySec = 240; // 4 minutes
const int jitterNegSec = -120;  // up to -2 minutes
const int jitterPosSec = 30;    // up to +30 seconds

const int baseDelayMs = 10;
const int minArcSteps = 30;
const int maxArcSteps = 60;
const int minStep = 2;
const int maxStep = 10;

bool hasPerformedInitialWiggle = false;

void setup() {
    DigiMouse.begin();
    randomSeed(analogRead(0));
}

void loop() {
    if (!hasPerformedInitialWiggle) {
        initialWiggle();
        hasPerformedInitialWiggle = true;
    }

    int jitterSec = random(jitterNegSec, jitterPosSec);
    int delaySec = baseDelaySec + jitterSec;

    DigiMouse.delay((unsigned long)delaySec * 1000UL);

    for (int i = 0; i < 3; i++) {
        moveRandomArc();
    }
}

void initialWiggle() {
    for (int i = 0; i < 10; i++) {
        moveRandomArc();
    }
}

void moveRandomArc() {
    int steps = random(minArcSteps, maxArcSteps + 1);

    float angle = random(0, 6283) / 1000.0; // 0 to ~2*pi

    for (int i = 0; i < steps; i++) {
        int stepSize = random(minStep, maxStep + 1);

        float offset = random(-314, 315) / 10000.0; // -0.0314 to 0.0314 rad

        int dx = round(stepSize * cos(angle + offset));
        int dy = round(stepSize * sin(angle + offset));

        DigiMouse.moveX(dx);
        DigiMouse.moveY(dy);
        DigiMouse.delay(baseDelayMs + random(-5, 6));
    }
}
