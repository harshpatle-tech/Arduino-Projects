#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h> 

DS3231 rtc(SDA, SCL);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define Toggle_Up 4
#define Set_time 2
#define Set_date 3

String temp[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; //Full name days of Week
String shot_dow[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"}; //3First words days of week
bool check_inter_0, check_inter_1;

String day_of_week_display(){ 
  Time Return_time; 
  Return_time = rtc.getTime(); //Get time from DS3231

  return shot_dow[Return_time.dow - 1]; //Return_time.dow will return DEC(Mon = 1 ... Sun = 7) -> minus 1 to get from element 0 of array
  // Only get 3First words to enough space on LCD
}

int Convert_Str_To_Int_Months(String temp_month){ // Convert Month String to an array to process easily
  String months_str[12] = {"January", "February", "March", "April", "May",
                          "June", "July", "August", "September", "October", "November", "December"}; //Tháng trong 1 năm

  for (int i = 0; i < 12; i++){
    if (temp_month == months_str[i]) 
      return i + 1;
  } 
}

void Toggle_Up_Value(){  //Up
  check_inter_0 = true;
}

void Toggle_Down_Value(){ //Down (Only use for Year edit)
  check_inter_1 = true;
}

void set_date_button(){
  Time Return_time; 
  Return_time = rtc.getTime(); //Get time from DS3231
  
  int Test_case = 0;
  int ArrayOfValue[3] = {Return_time.date, Convert_Str_To_Int_Months(rtc.getMonthStr()) ,Return_time.year}; // Save date and month into an array
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Date:");
  
	while (Test_case < 3){ // When have done edited
    if (!digitalRead(Set_date)) { 
      while (!digitalRead(Set_date));
      Test_case++;
    }

    lcd.setCursor(3, 1);
    lcd.print(rtc.getDateStr()); //Print D/M/Y
    delay (500);

    switch (Test_case){ // Blink at editing position
      case 0:{          
        lcd.setCursor(3,1);
        lcd.print("  ");
        delay(500);
        break;
      }
  
      case 1:{
        lcd.setCursor(6,1);
        lcd.print("  ");
        delay(500);
        break;
      }
  
      default:{
        lcd.setCursor(9,1);
        lcd.print("    ");
        delay(500);
        break;
      }
    }

    lcd.setCursor(3, 1);
    lcd.print(rtc.getDateStr()); // Print D/M/Y

    if (!digitalRead(Set_date)) { 
      while (!digitalRead(Set_date));
      Test_case++;
    }
    
    if (check_inter_0) { 
      while (!digitalRead(Toggle_Up));

      if (Test_case == 0){ //Test_case 0 is day, 1 month, 2 is year
        if (ArrayOfValue[Test_case] == 31)
          ArrayOfValue[Test_case] = 1;
        else 
          ArrayOfValue[Test_case]++;
      }

      else if (Test_case == 1){
        if (ArrayOfValue[Test_case] == 12)
          ArrayOfValue[Test_case] = 1;
        else 
          ArrayOfValue[Test_case]++;
      }
      
      else
        ArrayOfValue[Test_case]++;
        
      rtc.setDate(ArrayOfValue[0], ArrayOfValue[1], ArrayOfValue[2]); // Set time ds3231
      check_inter_0 = false; 
    }

    if (Test_case == 2){  //Down (Only use for Year edit)
      if (check_inter_1){
        while(!digitalRead(Set_time));
        ArrayOfValue[Test_case]--; 
      }
      rtc.setDate(ArrayOfValue[0], ArrayOfValue[1], ArrayOfValue[2]); // Set time ds3231
      check_inter_1 = false;
    }
    
    if (!digitalRead(Set_date)) { 
      while (!digitalRead(Set_date));
      Test_case++;
    }
	}
 
  lcd.clear();
  lcd.print("Done!");
  delay(500);
  lcd.clear();
}

void set_dow_button(){
  Time Return_time;
  Return_time = rtc.getTime();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Day Of Week:");
  lcd.setCursor(5, 1);
  lcd.print(rtc.getDOWStr()); //Print Day of week on LCD
  
  int Test_case = 0, dow_target = Return_time.dow; //Get day_of_week from ds3231

  while (Test_case < 1){
    lcd.setCursor(0, 0);
    lcd.print("Set Day Of Week:");
    lcd.setCursor(5, 1);
    lcd.print(rtc.getDOWStr());//Print Day of week on LCD
    
    if (!digitalRead(Toggle_Up)){
      while (!digitalRead(Toggle_Up));
      if (dow_target == 7)
        dow_target = 1;
      else
        dow_target++;
      lcd.clear();
    }
    
    rtc.setDOW(dow_target); // set day of week ds3231 with dow_target = 1 is MON, dow_target = 7 is SUN

    if (!digitalRead(Set_date)){
      while (!digitalRead(Set_date));
      check_inter_0 = false;
      check_inter_1 = false;
      set_date_button(); // Set day before date
      Test_case++;
    }
  }
}

void set_time_button(){
  Time Return_time;
  Return_time = rtc.getTime();
  
  int Test_case = 0;
  int ArrayOfValue[3] = {Return_time.hour, Return_time.min, Return_time.sec}; // Save H/m/s into an array

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Time:");
  lcd.setCursor(4, 1);
  lcd.print(rtc.getTimeStr());

	while (Test_case < 3){
    if (!digitalRead(Set_time)) {
      while (!digitalRead(Set_time)){ // Avoid stopping time when press the button
        lcd.setCursor(4, 1);
        lcd.print(rtc.getTimeStr());

        Return_time = rtc.getTime();
        ArrayOfValue[0] = Return_time.hour;
        ArrayOfValue[1] = Return_time.min; 
        ArrayOfValue[2] = Return_time.sec;
      }
      Test_case++;
    }
    
    lcd.setCursor(4, 1);
    lcd.print(rtc.getTimeStr());
    delay (500);
    
    Return_time = rtc.getTime(); // Update time
    ArrayOfValue[0] = Return_time.hour;
    ArrayOfValue[1] = Return_time.min; 
    ArrayOfValue[2] = Return_time.sec;
    
    switch (Test_case){ // Blink at editing postition
      case 0:{
        lcd.setCursor(4,1);
        lcd.print("  ");
        delay(500);
        break;
      }
  
      case 1:{
        lcd.setCursor(7,1);
        lcd.print("  ");
        delay(500);
        break;
      }
  
      default:{
        lcd.setCursor(10,1);
        lcd.print("  ");
        delay(500);
        break;
      }
    }

    lcd.setCursor(4, 1);
    lcd.print(rtc.getTimeStr());
    
    if (!digitalRead(Set_time)) { //Pooling
      while (!digitalRead(Set_time)){
        lcd.setCursor(4, 1);
        lcd.print(rtc.getTimeStr());

        Return_time = rtc.getTime();
        ArrayOfValue[0] = Return_time.hour;
        ArrayOfValue[1] = Return_time.min; 
        ArrayOfValue[2] = Return_time.sec;
      }
      Test_case++;
    }
    
    
    
    if (check_inter_0) {
      while (!digitalRead(Toggle_Up)){
        lcd.setCursor(4, 1); // Avoid stopping time when press the button
        lcd.print(rtc.getTimeStr());

        Return_time = rtc.getTime();
        ArrayOfValue[0] = Return_time.hour;
        ArrayOfValue[1] = Return_time.min; 
        ArrayOfValue[2] = Return_time.sec;
      }
      
      if (Test_case == 0){ // Set hour
        if (ArrayOfValue[Test_case] == 23)
          ArrayOfValue[Test_case] = 0;
        else 
          ArrayOfValue[Test_case]++;
      }

      else if (Test_case == 1){ // Set minute
        if (ArrayOfValue[Test_case] == 59)
          ArrayOfValue[Test_case] = 0;
        else 
          ArrayOfValue[Test_case]++;
      }
      
      else //Set giây
        ArrayOfValue[Test_case] = 0;
        
      rtc.setTime(ArrayOfValue[0], ArrayOfValue[1], ArrayOfValue[2]); // Update time to ds3231
      check_inter_0 = false;
    }
    
    Return_time = rtc.getTime(); //Update time from ds3231
    ArrayOfValue[0] = Return_time.hour;
    ArrayOfValue[1] = Return_time.min; 
    ArrayOfValue[2] = Return_time.sec;
    
    if (!digitalRead(Set_time)) { //pooling
      while (!digitalRead(Set_time)){
        lcd.setCursor(4, 1);
        lcd.print(rtc.getTimeStr());

        Return_time = rtc.getTime();
        ArrayOfValue[0] = Return_time.hour;
        ArrayOfValue[1] = Return_time.min; 
        ArrayOfValue[2] = Return_time.sec;
      }
      Test_case++;
    }
	}
 
  lcd.clear();
  lcd.print("Done!");
  delay(500);
  lcd.clear();
}



void time_display(){
  lcd.setCursor(0, 0);
  lcd.print(rtc.getDateStr()); //Print D/M/Y
  
  lcd.setCursor(13, 0);
  lcd.print(day_of_week_display()); //Print 3First words of days of week

  lcd.setCursor(0, 1);
  lcd.print(rtc.getTimeStr()); //Print time
  
  lcd.setCursor(10, 1); 
  lcd.print(rtc.getTemp()); //Print temperature
  lcd.setCursor(14, 1);
  lcd.print((char)223);
  lcd.print("C");
  delay(1000);
}

void Init_button() {               
    pinMode(Toggle_Up, INPUT_PULLUP); 
    pinMode(Set_date, INPUT_PULLUP);
    pinMode(Set_time, INPUT_PULLUP);
}

void Init_lcd(){
	lcd.init();               
	lcd.backlight();          
	lcd.clear();

  lcd.setCursor(3,0);
  lcd.print("CLOCK BOX!");
  lcd.setCursor(5,1);
  lcd.print("HEL_LO");
  delay(1000);
  lcd.clear();
}

void Init_rtc(){
	rtc.begin(); 

	//The following lines can be uncommented to set the date and time
  //rtc.setDOW(3);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
}

void setup() { 
	Serial.begin(9600);
 
 	Init_rtc();
	Init_lcd();
  Init_button();

  attachInterrupt(0, Toggle_Up_Value, FALLING); 
  attachInterrupt(1, Toggle_Down_Value, FALLING); 
}

void loop() { 
  if (!digitalRead(Set_time)){
    while (!digitalRead(Set_time));
    check_inter_0 = false;
    set_time_button();
    lcd.clear();
  }

  
  if (!digitalRead(Set_date)){
    while (!digitalRead(Set_date));
    check_inter_0 = false;
    check_inter_1 = false;
    set_dow_button();
    lcd.clear();
  }

  time_display();
}