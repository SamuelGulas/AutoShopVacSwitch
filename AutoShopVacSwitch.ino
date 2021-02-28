/// *****        © ShopVacSwitch        ***** ///
///      Automated Vacuum Cleaner Switch      ///
///      Current sensor type: ACS 712-30      ///
///                                           ///
///         Last updated on 1/20/21           ///
///                                           ///
/// *****         Code by Jacob.        ***** ///


#define SAMPLES 300

// Change this values according to which pins ou have connected.
#define SENSOR_Pin A0
#define RELAY_Pin D0

// Change this value to increase or decrease delay until turning off. Value must be in millis e.g. 5000 = 5 seconds
const int delayTime = 5000;


#define RELAY_On LOW
#define RELAY_Off HIGH

float High_peak,Low_peak;
float Amps_Peak_Peak = 0;

unsigned long currentMillis, lastMillis;


void measureCurrent();

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_Pin, INPUT);
    pinMode(RELAY_Pin, OUTPUT);

    digitalWrite(RELAY_Pin, RELAY_Off);
}

void loop() {
    measureCurrent();

    if (Amps_Peak_Peak > 15.00) {
        digitalWrite(RELAY_Pin, RELAY_On);
        lastMillis = millis();
    } else {
        currentMillis = millis();
        if (currentMillis - lastMillis > delayTime) {
            digitalWrite(RELAY_Pin, RELAY_Off);
        }
    }


}

void measureCurrent() {
    int cnt;
    High_peak = 0;
    Low_peak = 1024;

    for(cnt = 0; cnt<SAMPLES; cnt++) {
        float ACS_Value = analogRead(SENSOR_Pin);

        if(ACS_Value > High_peak)
            High_peak = ACS_Value;

        if(ACS_Value < Low_peak)
            Low_peak = ACS_Value;
    }

    Amps_Peak_Peak = High_peak - Low_peak;
}
