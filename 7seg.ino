int a=7; 
int b=6; 
int c=5; 
int d=11; 
int e=10; 
int  f=8; 
int g=9; 
int dp=4; 
//display number H
void display1(void) 
{  
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
     digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
       digitalWrite(g,HIGH);
} 
//display number2
void  display2(void) 
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  
}  
// display number3
void display3(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
}
// display number4
// void display(void) 
// {  
//     digitalWrite(f,HIGH);
//     digitalWrite(b,HIGH);
//     digitalWrite(g,HIGH);
//   digitalWrite(c,HIGH);
  
// } 
// display number5
void display4(void)  
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
} 
// display number6
void  display5(void) 
{ 
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
     digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
       digitalWrite(g,HIGH);  
} 
// display number7
// void display7(void)  
// {   
//    digitalWrite(a,HIGH);
//     digitalWrite(b,HIGH);
//     digitalWrite(c,HIGH);
// }  
// // display number8
// void display8(void) 
// { 
//     digitalWrite(a,HIGH);
//     digitalWrite(b,HIGH);
//     digitalWrite(g,HIGH);
//   digitalWrite(c,HIGH);
//     digitalWrite(d,HIGH);  
//     digitalWrite(e,HIGH);  
//   digitalWrite(f,HIGH);  
// } 
void clearDisplay(void) 
{ 
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(g,LOW);
  digitalWrite(c,LOW);
    digitalWrite(d,LOW);  
    digitalWrite(e,LOW);  
  digitalWrite(f,LOW);  
} 
// void display9(void)  
// { 
//     digitalWrite(a,HIGH);
//     digitalWrite(b,HIGH);
//     digitalWrite(g,HIGH);
//   digitalWrite(c,HIGH);
//     digitalWrite(d,HIGH);  
//   digitalWrite(f,HIGH);  
// } 
// void display0(void) 
// { 
//     digitalWrite(a,HIGH);
//     digitalWrite(b,HIGH);
//   digitalWrite(c,HIGH);
//     digitalWrite(d,HIGH);  
//     digitalWrite(e,HIGH);  
//   digitalWrite(f,HIGH);  
// } 
void setup() 
{ 
    int i;
    for(i=4;i<=11;i++)  
        pinMode(i,OUTPUT);
} 
void loop() 
{     
     while(1) 
    {   clearDisplay();
  // display0(); 
  //       delay(1000); 
  //       clearDisplay();
        display1(); 
        delay(1500); 
        clearDisplay();
        display2();  
        delay(1000); 
        clearDisplay();
        display3(); 
        delay(1000);
        clearDisplay();
        display4(); 
        delay(1500);
        clearDisplay(); 
        display5(); 
        delay(1000);
        clearDisplay();  
        // display6(); 
        // delay(1000);
        // clearDisplay(); 
        // display7(); 
        // delay(1000); 
        // clearDisplay();
        // display8();  
        // delay(1000); 
        // clearDisplay();  
        // display9(); 
        // delay(1000);      
    }
}
