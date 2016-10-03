#include <LiquidCrystal.h>
//Global variables
namespace Global{
    int USSensorIn  = 4;
    int USSensorOut = 5;
    int LCD_RS = 12;
    int LCD_Enable = 11;
    int LCD_D4 = 5;
    int LCD_D5 = 4;
    int LCD_D6 = 3;
    int LCD_D7 = 2;
    int LCD_Columns = 16;
    int LCD_Rows = 2;
}

LiquidCrystal lcd(Global::LCD_RS,Global::LCD_Enable,Global::LCD_D4,Global::LCD_D5,  Global::LCD_D6, Global::LCD_D7);

//Function that will be run during initialization
void setup(){
    //Initialize the pins for the ultrasonic sensor
    pinMode(Global::USSensorIn,INPUT);
    digitalWrite(Global::USSensorIn,LOW);
    pinMode(Global::USSensorOut,OUTPUT);

    //Initialize the LCD Display
    lcd.begin(Global::LCD_Columns, Global::LCD_Rows);
    lcd.setCursor(0,0);
    lcd.print("Awesome distance");
    lcd.setCursor(0,1);
    lcd.print("detector on!");
}

void loop(){
    double Distance = MeasureDistance(Global::USSensorIn,Global::USSensorOut);
    WriteDistanceToDisplay(Distance);

}


double MeasureDistance(int Trigger,int Listner){
    // Put the trigger low for security (maybe we can remove that line, as it is already initialized to be 0)
    digitalWrite(Trigger,LOW);
    delayMicroseconds(2);
    //Set the trigger high for 10 microseconds
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger, LOW);
    // Listen how long it took for the pulse to be returned and calculate the distance in meters
    double duration = pulseIn(Listner, HIGH, 1);
    double distance = duration*343/2;

    return distance;
}

void WriteDistanceToDisplay(double Distance){
    char buf[16] = {0};

    lcd.clear();
    lcd.setCursor(0,0);
    sprintf(buf,"Distance: ");
    lcd.print(buf);

    lcd.setCursor(0,1);
    sprintf(buf,"2.0%f cm",Distance);
    lcd.print(buf);
}

