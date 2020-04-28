//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
 * Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
 * Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
 * Con ayuda de: José Guerra
 * IE3027: Electrónica Digital 2 - 2019
 */
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"
#include <SPI.h>
#include <SD.h>

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
File myFile;
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};  
//*********************************************************************************
const int buttonPin1 = PUSH1;     // the number of the pushbutton pin
const int ledPinBLUE =  BLUE_LED;      // the number of the LED pin
int buttonState1 = 0;
const int buttonPin2 = PUSH2;     // the number of the pushbutton pin
const int ledPinGREEN =  GREEN_LED;      // the number of the LED pin
int buttonState2 = 0;
//*********************************************************************************
int x = 90;   // ubicacion jugador 
//**********************************************************
int y = 0;
int z = 1;      //tiempos
int z2 = 0;
//******************************************
int animacion=0;    
int anim1;          //animacion 
int anim2;
//*******************************************
 int PX1; int PX2; int PX3;int PX4;int PX5;int PX6;int PX7;int PX8;int PX9;int PX10;int PX11;int PX12;int PX13;int PX14;int PX15;int PX16;int PX17;int PX18;int PX19;int PX20;int PX21;int PX22;int PX23;int PX24;int PX25;int PX26;int PX27;int PX28;int PX29;int PX30;int PX31;int PX32;int PX33;int PX34;int PX35;int PX36;int PX37;int PX38;int PX39;int PX40;int PX41;int PX42;int PX43;int PX44;int PX45;int PX46;
 int P1; int P2; int P3;int P4;int P5;int P6;int P7;int P8;int P9;int P10;int P11;int P12;int P13;int P14;int P15;int P16;int P17;int P18;int P19;int P20;int P21;int P22;int P23;int P24;int P25;int P26;int P27;int P28;int P29;int P30;int P31;int P32;int P33;int P34;int P35;int P36;int P37;int P38;int P39;int P40;int P41;int P42;int P43;int P44;int P45;int P46;
 int PY1; int PY2; int PY3;int PY4;int PY5;int PY6;int PY7;int PY8;int PY9;int PY10;int PY11;int PY12;int PY13;int PY14;int PY15;int PY16;int PY17;int PY18;int PY19;int PY20;int PY21;int PY22;int PY23;int PY24;int PY25;int PY26;int PY27;int PY28;int PY29;int PY30;int PY31;int PY32;int PY33;int PY34;int PY35;int PY36;int PY37;int PY38;int PY39;int PY40;int PY41;int PY42;int PY43;int PY44;int PY45;int PY46;
unsigned char LIMPIEZA[46]={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};
int AL1 ; int AL2; int AL3; int AL4; int AL5; int AL6; int AL7; int AL8; int AL9; int AL10; int AL11; int AL12; int AL13; int AL14; int AL15; int AL16; int AL17; int AL18; int AL19; int AL20; int AL21; int AL22; int AL23; int AL24; int AL25; int AL26; int AL27; int AL28; int AL29; int AL30; int AL31; int AL32; int AL33; int AL34; int AL35; int AL36; int AL37; int AL38; int AL39; int AL40; int AL41; int AL42; int AL43; int AL44; int AL45; int AL46;
int AN1; int AN2; int AN3; int AN4; int AN5; int AN6; int AN7; int AN8; int AN9; int AN10; int AN11; int AN12; int AN13; int AN14; int AN15; int AN16; int AN17; int AN18; int AN19; int AN20; int AN21; int AN22; int AN23; int AN24; int AN25; int AN26;int AN27;int AN28; int AN29; int AN30; int AN31; int AN32; int AN33; int AN34; int AN35; int AN36; int AN37; int AN38; int AN39; int AN40; int AN41; int AN42; int AN43; int AN44; int AN45; int AN46;
unsigned char ENEMIGO[46]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
unsigned char ATAQUE[46]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char escuadron[10]={0,0,0,0,0,0,0,0,0,0};
//****************************************************
int alto_amarillo = 11;
int ancho_amarillo = 11;
int alto_bicho = 8;             //dimensiones 
int ancho_bicho = 12;
int alto_j = 20;
int ancho_j= 20;

//****************************************************
int VA=0;
int lider1 = 1;


int REMOVE =1;
int CONTADOR=0;

//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
void ANIMACIOON(void);
void TIEMPOS(void);
void CONTROLES(void);
//void ATAQUE_ENEMIGO1(int caso,int escuadron, int ATTACK, int LIMP, int enemy1,int enemy2, int enemy3, int enemy4,);
void ATAQUE_ENEMIGO1(void);
void ATAQUE_ENEMIGO3(void);
void MUERTE_ENEMIGO(void);
void GALAXIAN(void);

//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
    SPI.setModule(0);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(10, OUTPUT);

  if (!SD.begin(32)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);
  
  //FillRect(0, 0, 319, 319, 0x421b);
 // String text1 = "GALAXIAN!";
 // LCD_Print(text1, 80, 20, 2, 0xffff, 0x421b);

     
    
  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  
 /* 
  for(int x = 0; x <319; x++){
    LCD_Bitmap(x, 52, 16, 16, tile2);
    LCD_Bitmap(x, 68, 16, 16, tile);
    
    LCD_Bitmap(x, 207, 16, 16, tile);
    LCD_Bitmap(x, 223, 16, 16, tile);
    x += 15;
 }
  */
    // initialize the LED pin as an output:
  pinMode(ledPinBLUE, OUTPUT);
  pinMode(ledPinGREEN, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP); 
}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {

 escuadron[0] = ENEMIGO[0]+ENEMIGO[1]+ENEMIGO[2]+ENEMIGO[3];
 escuadron[1] = ENEMIGO[4]+ENEMIGO[5]+ENEMIGO[6]+ENEMIGO[7];
 escuadron[2] = ENEMIGO[8]+ENEMIGO[9]+ENEMIGO[10]+ENEMIGO[11];
 escuadron[3] = ENEMIGO[12]+ENEMIGO[13]+ENEMIGO[14]+ENEMIGO[15];
 escuadron[4] = ENEMIGO[16]+ENEMIGO[17]+ENEMIGO[18]+ENEMIGO[19];
 escuadron[5] = ENEMIGO[20]+ENEMIGO[21]+ENEMIGO[22]+ENEMIGO[23];
 escuadron[6] = ENEMIGO[24]+ENEMIGO[25]+ENEMIGO[26]+ENEMIGO[27];
 escuadron[7] = ENEMIGO[28]+ENEMIGO[29]+ENEMIGO[30]+ENEMIGO[31];
 escuadron[8] = ENEMIGO[32]+ENEMIGO[33]+ENEMIGO[34]+ENEMIGO[35];
 escuadron[9] = ENEMIGO[36]+ENEMIGO[37]+ENEMIGO[38]+ENEMIGO[39];
 
 ANIMACIOON();
 TIEMPOS();
 CONTROLES();
 GALAXIAN();
 ATAQUE_ENEMIGO1();                 
                                   
                                    
 MUERTE_ENEMIGO();
 

 
  }



//***********************************************************************************************************************************************************  
  void CONTROLES(void){
      buttonState1 = digitalRead(buttonPin1);
if (buttonState1 == LOW) {     
    // turn LED on:   
    x = x-1;
    ENEMIGO[0]=0;
    delay(15);
    
    digitalWrite(ledPinBLUE, HIGH); 
    LCD_Bitmap(x, 200, 20, 20, PLAYER1); 
   
}
buttonState2 = digitalRead(buttonPin2);
if (buttonState2 == LOW) {     
    // turn LED on:   
    x = x+1;
    ENEMIGO[0]= 1;
    ATAQUE[0] = 1;
    delay(15);
    
    digitalWrite(ledPinGREEN, HIGH); 
     
   
}
  if (buttonState1 == HIGH) {digitalWrite(ledPinBLUE, LOW); }
  if (buttonState2 == HIGH) {digitalWrite(ledPinGREEN, LOW); }
    return;
  }
//**********************************************************************************************************************************************************
void ANIMACIOON(void){
   animacion++;
     anim1 = (animacion/10)%2;
     anim2 = (animacion/20)%2; 
    return;
}
//**********************************************************************************************************************************************************
void MUERTE_ENEMIGO(void){
  if(ENEMIGO[0] == 0 & LIMPIEZA[0] != 0){
  LIMPIEZA[0]--;
      LCD_Sprite(P1, 65, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
      
  }
  if(ENEMIGO[0] == 0 & LIMPIEZA[0] == 0){
    if(REMOVE == 1){
    FillRect(P1,65,11,11,0x00);
    REMOVE = 0;
    }
    FillRect(y+130, 65, 10, 11, 0x00);
  }
  return;
}
//***********************************************************************************************************************************************************
void ATAQUE_ENEMIGO1(void){
  if(ENEMIGO[0] == 1 & LIMPIEZA[0] == 15 & ATAQUE[0] == 0){
  
    LCD_Bitmap(PX1=130+y,PY1=65,alto_amarillo, ancho_amarillo, YELLOW);
    P1 = PX1;
     LCD_Sprite(PX3=y+110, PY3=80, ancho_bicho, alto_bicho, REDBUG,2, anim1, 0, 0);     
    P3 = PX3;
    
    LCD_Sprite(PX4=y+130, PY4=80, ancho_bicho, alto_bicho, REDBUG,2, anim2, 0, 0);
    P4 = PX4;
       
    LCD_Sprite(PX5 = y+150, PY5= 80, ancho_bicho, alto_bicho, REDBUG,2, anim1, 0, 0);
    P5 = PX5;
}


if(ENEMIGO[0]==1 & LIMPIEZA[0] == 15 & ATAQUE[0] == 1 ){

if(CONTADOR == 0){

if(PX1!= 50){
  PX1 = PX1 - 1;
}
if(PX3!= 30){
  PX3 = PX3 - 1;
}
if(PX4!= 50){
  PX4 = PX4 - 1;
}
if(PX5!= 70){
  PX5 = PX5 - 1;
}

if(PY1!= 30){
  PY1= PY1-1;
}
if(PY3!= 45){
  PY3= PY3-1;
}
if(PY4!= 45){
  PY4= PY4-1;
}
if(PY5!= 45){
  PY5= PY5-1;
}
  
    
    
   if(PX1 == 50 & PX3==30 & PX4==50 & PX5==70 & PY1 == 30 & PY3==45 & PY4 == 45 & PY5 == 45){
    CONTADOR = 1;
   }
}

if(CONTADOR == 1){

 if(PX1!= 30){
  PX1 = PX1 - 1;
}
if(PX3!= 10){
  PX3 = PX3 - 1;
}
if(PX4!= 30){
  PX4 = PX4 - 1;
}
if(PX5!= 50){
  PX5 = PX5 - 1;
}
if(PY1!= 120){
  PY1= PY1+1;
}
if(PY3!= 135){
  PY3= PY3+1;
}
if(PY4!= 135){
  PY4= PY4+1;
}
if(PY5!= 135){
  PY5= PY5+1;
}

   if(PX1 == 30 & PX3==10 & PX4==30 & PX5==50 & PY1 == 120 & PY3==135 & PY4 == 135 & PY5 == 135){
    CONTADOR = 2;
   }
}

if(CONTADOR == 2){

  if(PX1!= 250){
  PX1 = PX1 + 1;
}
if(PX3!= 230){
  PX3 = PX3 + 1;
}
if(PX4!= 250){
  PX4 = PX4 + 1;
}
if(PX5!= 270){
  PX5 = PX5 + 1;
}
if(PY1!= 160){
  PY1= PY1+1;
}
if(PY3!= 175){
  PY3= PY3+1;
}
if(PY4!= 175){
  PY4= PY4+1;
}
if(PY5!= 175){
  PY5= PY5+1;
}

   if(PX1 == 250 & PX3==230 & PX4==250 & PX5==270 & PY1 == 160 & PY3==175 & PY4 == 175 & PY5 == 175){
    CONTADOR = 3;
   }
}

if(CONTADOR == 3){
if(PY1 != 70){
  PY1 = PY1 - 1;
}
if(PY3!= 85){
  PY3= PY3-1;
}
if(PY4!= 85){
  PY4= PY4-1;
}
if(PY5!= 85){
  PY5= PY5-1;
}
if(PX1 != 260){
  PX1 = PX1 +1;
}
if(PX3!= 240){
  PX3 = PX3 + 1;
}
if(PX4!= 260){
  PX4 = PX4 + 1;
}
if(PX5!= 280){
  PX5 = PX5 + 1;
}

   if(PY1 == 70 & PY3==85 & PY4 == 85 & PY5 == 85 & PX3==240 & PX4==260 & PX5==280 & PX1 == 260){
    CONTADOR = 4;
   }
}

if(CONTADOR == 4){

if(PX1 != P1){
  PX1 = PX1-1;
}
if(PX3 != P3){
  PX3 = PX3-1;
}
if(PX4 != P4){
  PX4 = PX4-1;
}
if(PX5 != P5){
  PX5 = PX5-1;
}
if(PY1 != 40){
  PY1 = PY1-1;
}
if(PY3 != 55){
  PY3 = PY3-1;
}
if(PY4 != 55){
  PY4 = PY4-1;
}
if(PY5 != 55){
  PY5 = PY5-1;
}


   if(PX1 == P1& PX3==P3 & PX4 == P4 & PX5==P5 & PY1 == 40 & PY3 == 55 & PY4 == 55 & PY5 == 55 ){
    CONTADOR = 5;
   }
}
  if(CONTADOR == 5){
  
 
  PY1 = PY1 +1;
  PY3 = PY3 +1;
  PY4 = PY4 +1;
  PY5 = PY5 +1;
  

   if(PY1 == 65 & PY3 == 80 & PY4 == 80 & PY5 == 80){
    CONTADOR = 0;
    ATAQUE[0] = 0;    // COLOCAR FUERA DE LA FUNCION PARA TODOS
   }
}
 LCD_Bitmap(PX1, PY1,alto_amarillo, ancho_amarillo,YELLOW);
 H_line(PX3,PY1-4, 50, 0x00);
 H_line(PX3-10,PY1-6, 70, 0x00);
 H_line(PX3,PY4+10, 50, 0x00);
 H_line(PX3-10,PY4+18, 70, 0x00);
 V_line(PX3-5, PY3-17, 25, 0x00);
 V_line(PX3-8, PY3-25, 40, 0x00);
 V_line(PX5+15,PY5-17, 25, 0x00);
 V_line(PX5+17,PY5-25, 40, 0x00);
 V_line(PX3+12,PY1, 25, 0x00);
 V_line(PX1+12,PY1, 25, 0x00);

 
  //V_line(PX1-2,PY1, 25, 0x00);
  // V_line(PX5-2,PY1, 25, 0x00);
 LCD_Sprite(PX3, PY3, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
 LCD_Sprite(PX4, PY4, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
 LCD_Sprite(PX5, PY5, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0); 
}
  return;
}
//***********************************************************************************************************************************************************
void TIEMPOS(void){
     
  if(z==0){
    z2++;
    if(z2==6){ 
    y=y-1;
    z2=0;  
    }
    if(y==-7){
      z = 1;    
    }    
    }
  
  if(z==1){
    z2++;
    if(z2==6){     
    y=y+1;   
    z2=0;  
    }
    if(y==7){
      z = 0;    
    }   
    }
  return;
}
//*****************************************************************************************************************************************************
void GALAXIAN(void){
   


    LCD_Bitmap(PX2=y+190, PY2=65, ancho_amarillo, alto_amarillo, YELLOW);
  //  LCD_Bitmap(20, 20, 12, 8, MUERTITO);
 
   
   
    
    LCD_Sprite(PX6=y+170, PY6=80, ancho_bicho, alto_bicho, REDBUG,2, anim2, 0, 0);
//LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX7=y+190, PY7=80, ancho_bicho, alto_bicho, REDBUG,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(PX8=y+210, PY8=80, ancho_bicho, alto_bicho, REDBUG,2, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX9=y+90,PY9=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX10=y+110, PY10=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX11=y+130, PY11=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX12=y+150, PY12=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX13=y+170, PY13=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX14=y+190, PY14=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX15=y+210, PY15=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX16=y+230, PY16=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX17=y+70, PY17=100, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX18=y+90, PY18=100, ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);

    LCD_Sprite(PX19=y+110, PY19=100, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX20=y+130, PY20=100, ancho_bicho, alto_bicho, BICHOA,2,anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX21=y+150, PY21=100,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(PX22=y+170, PY22=100,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(PX23=y+190, PY23=100,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX24=y+210, PY24=100,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX25=y+230, PY25=100, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX26=y+250, PY26=100,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX27=y+70, PY27=110, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX28=y+90, PY28=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX29=y+110, PY29=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(PX30=y+130, PY30=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX31=y+150, PY31=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX32=y+170, PY32=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX33=y+190, PY33=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX34=y+210, PY34=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX35=y+230, PY35=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(PX36=y+250, PY36=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX37=y+70, PY37=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX38=y+90, PY38=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX39=y+110, PY39=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX40=y+130, PY40=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX41=y+150, PY41=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX42=y+170, PY42=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX43=y+190, PY43=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX44=y+210, PY44=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX45=y+230, PY45=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(PX46=y+250, PY46=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    //LCD_Bitmap(y+250, 120, 12, 8, MUERTITO);
   
     
     LCD_Bitmap(x, 200, ancho_j, alto_j, PLAYER1);
    // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
     LCD_Bitmap(185, 200, ancho_j,alto_j, PLAYER2);
   //  LCD_Bitmap(20, 20, 12, 8, MUERTITO);
     
   
  return;
}
//***********************************************************************************************************************************************************







   


//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER) 
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40|0x80|0x20|0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
//  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on 
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);   
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);   
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);   
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);   
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c){  
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);   
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
    }
  digitalWrite(LCD_CS, HIGH);
} 
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i,j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8); 
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);  
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background) 
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;
  
  if(fontSize == 1){
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if(fontSize == 2){
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }
  
  char charInput ;
  int cLength = text.length();
  Serial.println(cLength,DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength+1];
  text.toCharArray(char_array, cLength+1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1){
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2){
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      //LCD_DATA(bitmap[k]);    
      k = k + 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset){
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 

  unsigned int x2, y2;
  x2 =   x+width;
  y2=    y+height;
  SetWindows(x, y, x2-1, y2-1);
  int k = 0;
  int ancho = ((width*columns));
  if(flip){
  for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width -1 - offset)*2;
      k = k+width*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k - 2;
     } 
  }
  }else{
     for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width + 1 + offset)*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k + 2;
     } 
  }
    
    
    }
  digitalWrite(LCD_CS, HIGH);
}
