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
int x2 = 120; 
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
 int PA1; int PA2; int PA3;int PA4;int PA5;int PA6;int PA7;int PA8;int PA9;int PA10;int PA11;int PA12;int PA13;int PA14;int PA15;int PA16;int PA17;int PA18;int PA19;int PA20;int PA21;int PA22;int PA23;int PA24;int PA25;int PA26;int PA27;int PA28;int PA29;int PA30;int PA31;int PA32;int PA33;int PA34;int PA35;int PA36;int PA37;int PA38;int PA39;int PA40;int PA41;int PA42;int PA43;int PA44;int PA45;int PA46;
 int PB1; int PB2; int PB3;int PB4;int PB5;int PB6;int PB7;int PB8;int PB9;int PB10;int PB11;int PB12;int PB13;int PB14;int PB15;int PB16;int PB17;int PB18;int PB19;int PB20;int PB21;int PB22;int PB23;int PB24;int PB25;int PB26;int PB27;int PB28;int PB29;int PB30;int PB31;int PB32;int PB33;int PB34;int PB35;int PB36;int PB37;int PB38;int PB39;int PB40;int PB41;int PB42;int PB43;int PB44;int PB45;int PB46;
 int PY1; int PY2; int PY3;int PY4;int PY5;int PY6;int PY7;int PY8;int PY9;int PY10;int PY11;int PY12;int PY13;int PY14;int PY15;int PY16;int PY17;int PY18;int PY19;int PY20;int PY21;int PY22;int PY23;int PY24;int PY25;int PY26;int PY27;int PY28;int PY29;int PY30;int PY31;int PY32;int PY33;int PY34;int PY35;int PY36;int PY37;int PY38;int PY39;int PY40;int PY41;int PY42;int PY43;int PY44;int PY45;int PY46;
unsigned char LIMPIEZA[46]={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};
int AL1 ; int AL2; int AL3; int AL4; int AL5; int AL6; int AL7; int AL8; int AL9; int AL10; int AL11; int AL12; int AL13; int AL14; int AL15; int AL16; int AL17; int AL18; int AL19; int AL20; int AL21; int AL22; int AL23; int AL24; int AL25; int AL26; int AL27; int AL28; int AL29; int AL30; int AL31; int AL32; int AL33; int AL34; int AL35; int AL36; int AL37; int AL38; int AL39; int AL40; int AL41; int AL42; int AL43; int AL44; int AL45; int AL46;
int AN1; int AN2; int AN3; int AN4; int AN5; int AN6; int AN7; int AN8; int AN9; int AN10; int AN11; int AN12; int AN13; int AN14; int AN15; int AN16; int AN17; int AN18; int AN19; int AN20; int AN21; int AN22; int AN23; int AN24; int AN25; int AN26;int AN27;int AN28; int AN29; int AN30; int AN31; int AN32; int AN33; int AN34; int AN35; int AN36; int AN37; int AN38; int AN39; int AN40; int AN41; int AN42; int AN43; int AN44; int AN45; int AN46;
unsigned char ENEMIGO[46]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
unsigned char REMOVE[46]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//unsigned char ATAQUE[10]= {0,0,0,0,0,0,0,0,0,0};
unsigned char ATAQUE[46]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char escuadron[10]={0,0,0,0,0,0,0,0,0,0};
unsigned char ATAMUERTEX[46]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char ATAMUERTEY[46]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//****************************************************
int alto_amarillo = 11;
int ancho_amarillo = 11;
int alto_bicho = 8;             //dimensiones 
int ancho_bicho = 12;
int alto_j = 20;
int ancho_j= 20;

//****************************************************
int xx1;
int xx2;
int xx3;
int xx4;
int yy1;
int yy2;
int yy3;
int yy4;

int xxx1;
int xxx2;
int xxx3;
int xxx4;
int yyy1;
int yyy2;
int yyy3;
int yyy4;

int pa1;
int pa2;
int pa3;
int pa4;
int pb1;
int pb2;
int pb3;
int pb4;
int copy = 1;
int lider1 = 1;
//*************************************************************************************************************************
int deploy=0;
int enablee=0;
int segundos=0;

int misil=0;
int misil2=0;
int enable_copy=1;
int enable_copy2=1;
int enable_copy3=1;
int enable_copy4=1;
int enable_copy5=1;
int copyx;
int copyy= 200;
int copyx2;
int copyy2= 200;
int copyx3;
int copyy3= 175;
int copyx4;
int copyy4= 175;
int copyx5;
int copyy5= 175;
int perdedor1=1;
int perdedor2=1;

int valana=1;
int valana2=1;
int valana3=1;

int PLAYER_1LIFE=3;
int PLAYER_2LIFE=3;
int PLAYERA=1;
int PLAYERB=1;
int CONTADOR=0;
int LIMPIEZA_J1=15;
int LIMPIEZA_J2=15;
//---------------------------------------------
int musica1_j1=1;
int musica1_j2=1;
int musica2=1;
int musica3=1;
int musica4=1;
int musica5=1;

//********************* variables de limpieza 
int misilito1=0;
int misilito2=0;
int misilito3=0;
//******************************************************************************************************************************
const int BP1 = 28;     // the number of the pushbutton pin PE2
const int BP2 = 29;     // the number of the pushbutton pin PE3
const int BP3 = 9;     // the number of the pushbutton pin PA6
const int BP4 = 10;     // the number of the pushbutton pin PA7
const int BP5 = 5;     // the number of the pushbutton pin PE4
const int BP6 = 6;     // the number of the pushbutton pin PE5
const int LEDV = 33;
const int LEDA = 32;

const int MUX1 = 37;
const int MUX2 = 36;
const int MUX3 = 35;

const int LP1 =  GREEN_LED;      // the number of the LED pin
const int LP2 =  BLUE_LED;      // the number of the LED pin
const int LP3 =  RED_LED;      // the number of the LED pin
const int LP4 =  GREEN_LED;      // the number of the LED pin
const int LP5 =  BLUE_LED;      // the number of the LED pin
const int LP6 =  RED_LED;      // the number of the LED pin

// anti-turbo shootting variable
int AR1 = 0;
int AR2 = 0;

// variables will change:
int BS1 = 0;         // variable for reading the pushbutton status
int BS2 = 0;         // variable for reading the pushbutton status
int BS3 = 0;         // variable for reading the pushbutton statu
int BS4 = 0;         // variable for reading the pushbutton status
int BS5 = 0;         // variable for reading the pushbutton status
int BS6 = 0;         // variable for reading the pushbutton status
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
void ATAQUE_ENEMIGO1(int referencia_1,int referencia_2, int referencia_3, int referencia_4, int ataquee,int squad,int casee, int xx1, int xx2, int xx3, int xx4, int yy1, int yy2, int yy3, int yy4, int pa1, int pa2, int pa3, int pa4, int pb1, int pb2, int pb3, int pb4 );
//void ATAQUE_ENEMIGO1(void);
void MUERTE_ENEMIGO(void);
void MUERTE_ENEMIGO2(void);
void GALAXIAN(void);
void TIEMPOS_DE_ATAQUE(void);
void DISPARO1(void);
void DISPARO2(void);
void CHOQUE(void);
void MISIL_ENEMIGO1(void);
void MISIL_ENEMIGO2(void);
void MISIL_ENEMIGO3(void);

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
//--------------------------------------------------------------
   // initialize the LED pin as an output:
  pinMode(LP1, OUTPUT);   
  pinMode(LP2, OUTPUT);
  pinMode(LP3, OUTPUT);
  pinMode(LP4, OUTPUT);
  pinMode(LP5, OUTPUT);
  pinMode(LP6, OUTPUT);   
  pinMode(LEDV,OUTPUT);
  pinMode(LEDA,OUTPUT);
  pinMode(MUX1,OUTPUT);
  pinMode(MUX2,OUTPUT);
  pinMode(MUX3,OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BP1, INPUT_PULLDOWN);     
  pinMode(BP2, INPUT_PULLDOWN);     
  pinMode(BP3, INPUT_PULLDOWN);     
  pinMode(BP4, INPUT_PULLDOWN);     
  pinMode(BP5, INPUT_PULLDOWN);     
  pinMode(BP6, INPUT_PULLDOWN);
  digitalWrite(LEDV,HIGH);
  digitalWrite(LEDA,HIGH);
  
}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {


 
 musica2=1;
 musica3=1;
 musica4=1;
 musica5=1;
  


 escuadron[0] = ENEMIGO[0]+ENEMIGO[2]+ENEMIGO[3]+ENEMIGO[4];
 escuadron[1] = ENEMIGO[1]+ENEMIGO[5]+ENEMIGO[6]+ENEMIGO[7];
 escuadron[2] = ENEMIGO[8]+ENEMIGO[9]+ENEMIGO[10]+ENEMIGO[11];
 escuadron[3] = ENEMIGO[12]+ENEMIGO[13]+ENEMIGO[14]+ENEMIGO[15];
 escuadron[4] = ENEMIGO[16]+ENEMIGO[17]+ENEMIGO[18]+ENEMIGO[19];
 escuadron[5] = ENEMIGO[20]+ENEMIGO[21]+ENEMIGO[22]+ENEMIGO[23]; 
 escuadron[6] = ENEMIGO[26]+ENEMIGO[27]+ENEMIGO[28]+ENEMIGO[29]; //
 escuadron[7] = ENEMIGO[30]+ENEMIGO[31]+ENEMIGO[32]+ENEMIGO[33];  //
 escuadron[8] = ENEMIGO[36]+ENEMIGO[37]+ENEMIGO[38]+ENEMIGO[39];  // 
 escuadron[9] = ENEMIGO[40]+ENEMIGO[41]+ENEMIGO[42]+ENEMIGO[43]; //
 
 ANIMACIOON();
 TIEMPOS();
 CONTROLES();
 CONTROLES();
 CHOQUE(); 
 MUERTE_ENEMIGO();
 GALAXIAN();           
 TIEMPOS_DE_ATAQUE(); 
                                                                      
 if(PLAYERA==1){
  LCD_Bitmap(x, 200, ancho_j, alto_j, PLAYER1);
 }
 DISPARO1();
 DISPARO1();
 DISPARO1();
 if(misil==1 & musica1_j1==1){
  digitalWrite(MUX1,LOW);   // DISPAROS 
  digitalWrite(MUX2,LOW);
  digitalWrite(MUX3,HIGH);

 
  musica1_j1=0;
 }

   if(misil==0 & musica1_j1==0){
    musica1_j1=1;
    
  }
 
 
 if(PLAYERB==1){
  LCD_Bitmap(x2, 200, ancho_j,alto_j, PLAYER2);
 }
 DISPARO2();
 DISPARO2();
 DISPARO2();
 
  if(misil2==1 & musica1_j2==1){
  digitalWrite(MUX1,LOW);   // DISPAROS 
  digitalWrite(MUX2,LOW);
  digitalWrite(MUX3,HIGH);

  musica1_j2=0;
 }
  if(misil2==0 & musica1_j2==0){
    musica1_j2=1;
  }

 
 
if(misilito1==1){
 MISIL_ENEMIGO1();
}
if(misilito2==1){
 MISIL_ENEMIGO2();
}
if(misilito3==1){
 MISIL_ENEMIGO3();
}

   

  }

//*********************************************************************************************************************************

  void MISIL_ENEMIGO1(void){
     

       

  copyy3++;
  LCD_Bitmap(xx2,copyy3, 4, 9, MISIL2);
 
  if(copyy3==220){
  FillRect(xx2, 220, 4,9, 0x00);
  misilito1=0;
  copyy3=175;
  enable_copy3=1;
  valana=1;
  
 
 }


  return;
 }
  void MISIL_ENEMIGO2(void){
         

       

  copyy4++;
  LCD_Bitmap(xx3,copyy4, 4, 9, MISIL2);
 
  if(copyy4==220){
  FillRect(xx3, 220, 4,9, 0x00);
  misilito2=0;
  copyy4=175;
  enable_copy4=1;
 valana2=1;
 }

  return;
 }
  void MISIL_ENEMIGO3(void){

         

       

  copyy5++;
  LCD_Bitmap(xx4,copyy5, 4, 9, MISIL2);
 
  if(copyy5==220){
  FillRect(xx4, 220, 4,9, 0x00);
  misilito3=0;
  copyy5=175;
  enable_copy5=1;
 valana3=1;
 }


  return;
 }
//*********************************************************************************************************************************
void CHOQUE(void){

        if(PLAYERA == 0 & LIMPIEZA_J1 != 0){        
    LIMPIEZA_J1--;
      LCD_Sprite(x, 200, 28, 30, PLAYERDEATH,4, anim1, 0, 0);  
  }
  if(LIMPIEZA_J1==0 & PLAYER_1LIFE!=0){
    FillRect(x,200,28,30,0x00);
    LIMPIEZA_J1= 15;
    PLAYERA=1;
    digitalWrite(LEDV,HIGH);
  }
        if(PLAYERB == 0 & LIMPIEZA_J2 != 0){        
    LIMPIEZA_J2--;
      LCD_Sprite(x2, 200, 28, 30, PLAYERDEATH,4, anim1, 0, 0);  
  } 
    if(LIMPIEZA_J2==0 & PLAYER_2LIFE!=0){
    FillRect(x2,200,28,30,0x00);
    LIMPIEZA_J2= 15;
    PLAYERB=1;
    digitalWrite(LEDA,HIGH);
  }
  if(PLAYER_2LIFE==0 & perdedor2==1 & LIMPIEZA_J2==0){
    FillRect(x2,200,28,30,0x00);
    perdedor2=0;
  }
    if(PLAYER_1LIFE==0 & perdedor1==1 & LIMPIEZA_J1==0){
    FillRect(x,200,28,30,0x00);
    perdedor1=0;
  }
  

  if( copyy3 <= 200 & copyy3 >= 200-10 & xx2 >= x & xx2 <= x+10 &  PLAYERA== 1 ){
    FillRect(xx2,copyy3,4,9,0x00);
    PLAYERA=0; 
    PLAYER_1LIFE--;
    misilito1 = 0;
    copyy3 = 175;
    enable_copy3=1;  
    valana=1;
    digitalWrite(LEDV,LOW);
    
  }

  
    if( copyy3 <= 200 & copyy3 >= 200-10 & xx2 >= x2 & xx2 <= x2+10 &  PLAYERB== 1 ){
     FillRect(xx2,copyy3,4,9,0x00);
    PLAYERB=0;
    PLAYER_2LIFE--; 
    misilito1 = 0;
    copyy3 = 175;
    enable_copy3=1;
    valana=1;
    digitalWrite(LEDA,LOW);
  }

    if( copyy4 <= 200 & copyy4 >= 200-10 & xx3 >= x & xx3 <= x+10 &  PLAYERA== 1 ){
    FillRect(xx3,copyy4,4,9,0x00);
    PLAYERA=0; 
    PLAYER_1LIFE--;
    misilito2 = 0;
    copyy4 = 175;
    enable_copy4=1;
    valana2=1;
    digitalWrite(LEDV,LOW);
    
  }
    if( copyy4 <= 200 & copyy4 >= 200-10 & xx3 >= x2 & xx3 <= x2+10 &  PLAYERB== 1 ){
    FillRect(xx3,copyy4,4,9,0x00);
    PLAYERB=0; 
    PLAYER_2LIFE--;
    misilito2 = 0;
    copyy4 = 175;
    enable_copy4=1;
    valana2=1;
    digitalWrite(LEDA,LOW);
    
  }

    if( copyy5 <= 200 & copyy5 >= 200-10 & xx4 >= x & xx4 <= x+10 &  PLAYERA== 1 ){
      FillRect(xx4,copyy5,4,9,0x00);
    PLAYERA=0;
    PLAYER_1LIFE--; 
    misilito3 = 0;
    copyy5 = 175;
    enable_copy5=1;
    valana3=1;
    digitalWrite(LEDV,LOW);
    
  }
    if( copyy5 <= 200 & copyy5 >= 200-10 & xx4 >= x2 & xx4 <= x2+10 &  PLAYERB== 1 ){
      FillRect(xx4,copyy5,4,9,0x00);
    PLAYERB=0; 
    PLAYER_2LIFE--;
    misilito3 = 0;
    copyy5 = 175;
    enable_copy5=1;
    valana3=1;
    digitalWrite(LEDA,LOW);
  }



  
  //------------------------------------------------------------------------------------- NAVE AMARILLA
  if(escuadron[0]!=0 & ATAQUE[0]==0){  // ESTATICOS 
  if( copyy <= PB1 & copyy >= PB1-5 & copyx >= PA1-9 & copyx <= PA1+2 &  ENEMIGO[0]== 1 ){
    ENEMIGO[0]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB1 & copyy2 >= PB1-5 & copyx2 >= PA1-9 & copyx2 <= PA1+2 &  ENEMIGO[0]== 1 ){
    ENEMIGO[0]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ ROJO 1
    if( copyy <= PB3 & copyy >= PB3-5 & copyx >= PA3-9 & copyx <= PA3+2 &  ENEMIGO[2]== 1){
    ENEMIGO[2]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB3 & copyy2 >= PB3-5 & copyx2 >= PA3-9 & copyx2 <= PA3+2 &  ENEMIGO[2]== 1){
    ENEMIGO[2]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- ROJO 2
       if( copyy <= PB4 & copyy >= PB4-5 & copyx >= PA4-9 & copyx <= PA4+2 &  ENEMIGO[3]== 1){
    ENEMIGO[3]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB4 & copyy2 >= PB4-5 & copyx2 >= PA4-9 & copyx2 <= PA4+2 &  ENEMIGO[3]== 1 ){
    ENEMIGO[3]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- ROJO 3
       if( copyy <= PB5 & copyy >= PB5-5 & copyx >= PA5-9 & copyx <= PA5+2 &  ENEMIGO[4]== 1){
    ENEMIGO[4]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB5 & copyy2 >= PB5-5 & copyx2 >= PA5-9 & copyx2 <= PA5+2 &  ENEMIGO[4]== 1){
    ENEMIGO[4]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

//------------------------------------------------------------------------------------- NAVE AMARILLA 2
  if(escuadron[1]!=0 & ATAQUE[1]==0){  // ESTATICOS 
  if( copyy <= PB2 & copyy >= PB2-5 & copyx >= PA2-9 & copyx <= PA2+2 &  ENEMIGO[1]== 1){
    ENEMIGO[1]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB2 & copyy2 >= PB2-5 & copyx2 >= PA2-9 & copyx2 <= PA2+2 &  ENEMIGO[1]== 1){
    ENEMIGO[1]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ ROJO 4
    if( copyy <= PB6 & copyy >= PB6-5 & copyx >= PA6-9 & copyx <= PA6+2 &  ENEMIGO[5]== 1){
    ENEMIGO[5]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB6 & copyy2 >= PB6-5 & copyx2 >= PA6-9 & copyx2 <= PA6+2 &  ENEMIGO[5]== 1){
    ENEMIGO[5]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- ROJO 5
       if( copyy <= PB7 & copyy >= PB7-5 & copyx >= PA7-9 & copyx <= PA7+2 &  ENEMIGO[6]== 1){
    ENEMIGO[6]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB7 & copyy2 >= PB7-5 & copyx2 >= PA7-9 & copyx2 <= PA7+2 &  ENEMIGO[6]== 1){
    ENEMIGO[6]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- ROJO 6
       if( copyy <= PB8 & copyy >= PB8-5 & copyx >= PA8-9 & copyx <= PA8+2 &  ENEMIGO[7]== 1){
    ENEMIGO[7]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB8 & copyy2 >= PB8-5 & copyx2 >= PA8-9 & copyx2 <= PA8+2 &  ENEMIGO[7]== 1 ){
    ENEMIGO[7]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }
//------------------------------------------------------------------------------------- morada 1
  if(escuadron[2]!= 0 & ATAQUE[2]==0){  // ESTATICOS 
  if( copyy <= PB9 & copyy >= PB9-5 & copyx >= PA9-9 & copyx <= PA9+2 &  ENEMIGO[8]== 1 ){
    ENEMIGO[8]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB9 & copyy2 >= PB9-5 & copyx2 >= PA9-9 & copyx2 <= PA9+2 &  ENEMIGO[8]== 1){
    ENEMIGO[8]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ morada 2
    if( copyy <= PB10 & copyy >= PB10-5 & copyx >= PA10-9 & copyx <= PA10+2 &  ENEMIGO[9]== 1 ){
    ENEMIGO[9]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB10 & copyy2 >= PB10-5 & copyx2 >= PA10-9 & copyx2 <= PA10+2 &  ENEMIGO[9]== 1){
    ENEMIGO[9]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- morada 3
       if( copyy <= PB11 & copyy >= PB11-5 & copyx >= PA11-9 & copyx <= PA11+2 &  ENEMIGO[10]== 1){
    ENEMIGO[10]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB11 & copyy2 >= PB11-5 & copyx2 >= PA11-9 & copyx2 <= PA11+2 &  ENEMIGO[10]== 1){
    ENEMIGO[10]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- morada 4
       if( copyy <= PB12 & copyy >= PB12-5 & copyx >= PA12-9 & copyx <= PA12+2 &  ENEMIGO[11]== 1){
    ENEMIGO[11]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB12 & copyy2 >= PB12-5 & copyx2 >= PA12-9 & copyx2 <= PA12+2 &  ENEMIGO[11]== 1 ){
    ENEMIGO[11]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }
  
  //------------------------------------------------------------------------------------- morado 5
  if(escuadron[3]!=0 & ATAQUE[3]==0){  // ESTATICOS 
  if( copyy <= PB13 & copyy >= PB13-5 & copyx >= PA13-9 & copyx <= PA13+2 &  ENEMIGO[12]== 1){
    ENEMIGO[12]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
  if( copyy2 <= PB13 & copyy2 >= PB13-5 & copyx2 >= PA13-9 & copyx2 <= PA13+2 &  ENEMIGO[12]== 1){
    ENEMIGO[12]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ morado 6
    if( copyy <= PB14 & copyy >= PB14-5 & copyx >= PA14-9 & copyx <= PA14+2 &  ENEMIGO[13]== 1){
    ENEMIGO[13]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB14 & copyy2 >= PB14-5 & copyx2 >= PA14-9 & copyx2 <= PA14+2 &  ENEMIGO[13]== 1){
    ENEMIGO[13]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- morado7
       if( copyy <= PB15 & copyy >= PB15-5 & copyx >= PA15-9 & copyx <= PA15+2 &  ENEMIGO[14]== 1){
    ENEMIGO[14]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB15 & copyy2 >= PB15-5 & copyx2 >= PA15-9 & copyx2 <= PA15+2 &  ENEMIGO[14]== 1){
    ENEMIGO[14]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- morado 8
       if( copyy <= PB16 & copyy >= PB16-5 & copyx >= PA16-9 & copyx <= PA16+2 &  ENEMIGO[15]== 1 ){
    ENEMIGO[15]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB16 & copyy2 >= PB16-5 & copyx2 >= PA16-9 & copyx2 <= PA16+2 &  ENEMIGO[15]== 1){
    ENEMIGO[15]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }
 //------------------------------------------------------------------------------------- azul 1
  if(escuadron[4]!=0 & ATAQUE[4]==0){  // ESTATICOS 
  if( copyy <= PB17 & copyy >= PB17-5 & copyx >= PA17-9 & copyx <= PA17+2 &  ENEMIGO[16]== 1){
    ENEMIGO[16]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB17 & copyy2 >= PB17-5 & copyx2 >= PA17-9 & copyx2 <= PA17+2 &  ENEMIGO[16]== 1){
    ENEMIGO[16]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ azul 2
    if( copyy <= PB18 & copyy >= PB18-5 & copyx >= PA18-9 & copyx <= PA18+2 &  ENEMIGO[17]== 1){
    ENEMIGO[17]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB18 & copyy2 >= PB18-5 & copyx2 >= PA18-9 & copyx2 <= PA18+2 &  ENEMIGO[17]== 1 ){
    ENEMIGO[17]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- azul 3
       if( copyy <= PB19 & copyy >= PB19-5 & copyx >= PA19-9 & copyx <= PA19+2 &  ENEMIGO[18]== 1){
    ENEMIGO[18]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB19 & copyy2 >= PB19-5 & copyx2 >= PA19-9 & copyx2 <= PA19+2 &  ENEMIGO[18]== 1){
    ENEMIGO[18]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 4
       if( copyy <= PB20 & copyy >= PB20-5 & copyx >= PA20-9 & copyx <= PA20+2 &  ENEMIGO[19]== 1){
    ENEMIGO[19]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB20 & copyy2 >= PB20-5 & copyx2 >= PA20-9 & copyx2 <= PA20+2 &  ENEMIGO[19]== 1){
    ENEMIGO[19]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

//------------------------------------------------------------------------------------- azul 5
  if(escuadron[5]!=0 & ATAQUE[5]==0){  // ESTATICOS 
  if( copyy <= PB21 & copyy >= PB21-5 & copyx >= PA21-9 & copyx <= PA21+2 &  ENEMIGO[20]== 1 ){
    ENEMIGO[20]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB21 & copyy2 >= PB21-5 & copyx2 >= PA21-9 & copyx2 <= PA21+2 &  ENEMIGO[20]== 1){
    ENEMIGO[20]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ azul 6
    if( copyy <= PB22 & copyy >= PB22-5 & copyx >= PA22-9 & copyx <= PA22+2 &  ENEMIGO[21]== 1 ){
    ENEMIGO[21]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB22 & copyy2 >= PB22-5 & copyx2 >= PA22-9 & copyx2 <= PA22+2 &  ENEMIGO[21]== 1){
    ENEMIGO[21]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- azul 7
       if( copyy <= PB23 & copyy >= PB23-5 & copyx >= PA23-9 & copyx <= PA23+2 &  ENEMIGO[22]== 1 ){
    ENEMIGO[22]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB23 & copyy2 >= PB23-5 & copyx2 >= PA23-9 & copyx2 <= PA23+2 &  ENEMIGO[22]== 1 ){
    ENEMIGO[22]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 8
       if( copyy <= PB24 & copyy >= PB24-5 & copyx >= PA24-9 & copyx <= PA24+2 &  ENEMIGO[23]== 1){
    ENEMIGO[23]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB24 & copyy2 >= PB24-5 & copyx2 >= PA24-9 & copyx2 <= PA24+2 &  ENEMIGO[23]== 1){
    ENEMIGO[23]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }
       if( copyy <= PB25 & copyy >= PB25-5 & copyx >= PA25-9 & copyx <= PA25+2 &  ENEMIGO[24]== 1){   // azul 9
    ENEMIGO[24]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB25 & copyy2 >= PB25-5 & copyx2 >= PA25-9 & copyx2 <= PA25+2 &  ENEMIGO[24]== 1){   
    ENEMIGO[24]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
                                                                                      // azul 10
         if( copyy <= PB26 & copyy >= PB26-5 & copyx >= PA26-9 & copyx <= PA26+2 &  ENEMIGO[25]== 1){
    ENEMIGO[25]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB26 & copyy2 >= PB26-5 & copyx2 >= PA26-9 & copyx2 <= PA26+2 &  ENEMIGO[25]== 1){
    ENEMIGO[25]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }

//------------------------------------------------------------------------------------- azul 11
  if(escuadron[6]!=0 & ATAQUE[6]==0){  // ESTATICOS 
  if( copyy <= PB27 & copyy >= PB27-5 & copyx >= PA27-9 & copyx <= PA27+2 &  ENEMIGO[26]== 1){
    ENEMIGO[26]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB27 & copyy2 >= PB27-5 & copyx2 >= PA27-9 & copyx2 <= PA27+2 &  ENEMIGO[26]== 1){
    ENEMIGO[26]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ azul 12
    if( copyy <= PB28 & copyy >= PB28-5 & copyx >= PA28-9 & copyx <= PA28+2 &  ENEMIGO[27]== 1){
    ENEMIGO[27]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB28 & copyy2 >= PB28-5 & copyx2 >= PA28-9 & copyx2 <= PA28+2 &  ENEMIGO[27]== 1){
    ENEMIGO[27]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- azul 13
       if( copyy <= PB29 & copyy >= PB29-5 & copyx >= PA29-9 & copyx <= PA29+2 &  ENEMIGO[28]== 1){
    ENEMIGO[28]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB29 & copyy2 >= PB29-5 & copyx2 >= PA29-9 & copyx2 <= PA29+2 &  ENEMIGO[28]== 1){
    ENEMIGO[28]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 14
       if( copyy <= PB30 & copyy >= PB30-5 & copyx >= PA30-9 & copyx <= PA30+2 &  ENEMIGO[29]== 1){
    ENEMIGO[29]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB30 & copyy2 >= PB30-5 & copyx2 >= PA30-9 & copyx2 <= PA30+2 &  ENEMIGO[29]== 1){
    ENEMIGO[29]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  //------------------------------------------------------------------------------------- azul 15
  if(escuadron[7]!=0 & ATAQUE[7]==0){  // ESTATICOS 
  if( copyy <= PB31 & copyy >= PB31-5 & copyx >= PA31-9 & copyx <= PA31+2 &  ENEMIGO[30]== 1){
    ENEMIGO[30]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB31 & copyy2 >= PB31-5 & copyx2 >= PA31-9 & copyx2 <= PA31+2 &  ENEMIGO[30]== 1){
    ENEMIGO[30]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ azul 16
    if( copyy <= PB32 & copyy >= PB32-5 & copyx >= PA32-9 & copyx <= PA32+2 &  ENEMIGO[31]== 1){
    ENEMIGO[31]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB32 & copyy2 >= PB32-5 & copyx2 >= PA32-9 & copyx2 <= PA32+2 &  ENEMIGO[31]== 1){
    ENEMIGO[31]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- azul 17
       if( copyy <= PB33 & copyy >= PB33-5 & copyx >= PA33-9 & copyx <= PA33+2 &  ENEMIGO[32]== 1){
    ENEMIGO[32]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB33 & copyy2 >= PB33-5 & copyx2 >= PA33-9 & copyx2 <= PA33+2 &  ENEMIGO[32]== 1){
    ENEMIGO[32]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 18
       if( copyy <= PB34 & copyy >= PB34-5 & copyx >= PA34-9 & copyx <= PA34+2 &  ENEMIGO[33]== 1){
    ENEMIGO[33]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB34 & copyy2 >= PB34-5 & copyx2 >= PA34-9 & copyx2 <= PA34+2 &  ENEMIGO[33]== 1){
    ENEMIGO[33]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }
  //----------------------------------------------------------------------------------------- azul 19
       if( copyy <= PB35 & copyy >= PB35-5 & copyx >= PA35-9 & copyx <= PA35+2 &  ENEMIGO[34]== 1){
    ENEMIGO[34]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB35 & copyy2 >= PB35-5 & copyx2 >= PA35-9 & copyx2 <= PA35+2 &  ENEMIGO[34]== 1){
    ENEMIGO[34]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 20
       if( copyy <= PB36 & copyy >= PB36-5 & copyx >= PA36-9 & copyx <= PA36+2 &  ENEMIGO[35]== 1){
    ENEMIGO[35]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB36 & copyy2 >= PB36-5 & copyx2 >= PA36-9 & copyx2 <= PA36+2 &  ENEMIGO[35]== 1){
    ENEMIGO[35]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }

//------------------------------------------------------------------------------------- azul 21
  if(escuadron[8]!=0 & ATAQUE[8]==0){  // ESTATICOS 
  if( copyy <= PB37 & copyy >= PB37-5 & copyx >= PA37-9 & copyx <= PA37+2 &  ENEMIGO[36]== 1 ){
    ENEMIGO[36]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB37 & copyy2 >= PB37-5 & copyx2 >= PA37-9 & copyx2 <= PA37+2 &  ENEMIGO[36]== 1 ){
    ENEMIGO[36]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ azul 22
    if( copyy <= PB38 & copyy >= PB38-5 & copyx >= PA38-9 & copyx <= PA38+2 &  ENEMIGO[37]== 1 ){
    ENEMIGO[37]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB38 & copyy2 >= PB38-5 & copyx2 >= PA38-9 & copyx2 <= PA38+2 &  ENEMIGO[37]== 1){
    ENEMIGO[37]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- azul 23
       if( copyy <= PB39 & copyy >= PB39-5 & copyx >= PA39-9 & copyx <= PA39+2 &  ENEMIGO[38]== 1 ){
    ENEMIGO[38]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB39 & copyy2 >= PB39-5 & copyx2 >= PA39-9 & copyx2 <= PA39+2 &  ENEMIGO[38]== 1){
    ENEMIGO[38]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 24
       if( copyy <= PB40 & copyy >= PB40-5 & copyx >= PA40-9 & copyx <= PA40+2 &  ENEMIGO[39]== 1){
    ENEMIGO[39]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB40 & copyy2 >= PB40-5 & copyx2 >= PA40-9 & copyx2 <= PA40+2 &  ENEMIGO[39]== 1){
    ENEMIGO[39]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  //------------------------------------------------------------------------------------- azul 25
  if(escuadron[9]!=0 & ATAQUE[9]==0){  // ESTATICOS 
  if( copyy <= PB41 & copyy >= PB41-5 & copyx >= PA41-9 & copyx <= PA41+2 &  ENEMIGO[40]== 1){
    ENEMIGO[40]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB41 & copyy2 >= PB41-5 & copyx2 >= PA41-9 & copyx2 <= PA41+2 &  ENEMIGO[40]== 1){
    ENEMIGO[40]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
//------------------------------------------------------------------------------------------ azul 26
    if( copyy <= PB42 & copyy >= PB42-5 & copyx >= PA42-9 & copyx <= PA42+2 &  ENEMIGO[41]== 1){
    ENEMIGO[41]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB42 & copyy2 >= PB42-5 & copyx2 >= PA42-9 & copyx2 <= PA42+2 &  ENEMIGO[41]== 1 ){
    ENEMIGO[41]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //----------------------------------------------------------------------------------------- azul 27
       if( copyy <= PB43 & copyy >= PB43-5 & copyx >= PA43-9 & copyx <= PA43+2 &  ENEMIGO[42]== 1){
    ENEMIGO[42]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB43 & copyy2 >= PB43-5 & copyx2 >= PA43-9 & copyx2 <= PA43+2 &  ENEMIGO[42]== 1 ){
    ENEMIGO[42]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 28
       if( copyy <= PB44 & copyy >= PB44-5 & copyx >= PA44-9 & copyx <= PA44+2 &  ENEMIGO[43]== 1 ){
    ENEMIGO[43]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB44 & copyy2 >= PB44-5 & copyx2 >= PA44-9 & copyx2 <= PA44+2 &  ENEMIGO[43]== 1){
    ENEMIGO[43]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  //----------------------------------------------------------------------------------------- azul 29
       if( copyy <= PB45 & copyy >= PB45-5 & copyx >= PA45-9 & copyx <= PA45+2 &  ENEMIGO[44]== 1){
    ENEMIGO[44]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB45 & copyy2 >= PB45-5 & copyx2 >= PA45-9 & copyx2 <= PA45+2 &  ENEMIGO[44]== 1){
    ENEMIGO[44]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //----------------------------------------------------------------------------------------- azul 30
       if( copyy <= PB46 & copyy >= PB46-5 & copyx >= PA46-9 & copyx <= PA46+2 &  ENEMIGO[45]== 1){
    ENEMIGO[45]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= PB46 & copyy2 >= PB46-5 & copyx2 >= PA46-9 & copyx2 <= PA46+2 &  ENEMIGO[45]== 1){
    ENEMIGO[45]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }










  //-------------------------------------------------------------------------------------- EN ATAQUE 
    if(escuadron[0]!=0 & ATAQUE[0]==1){                                                 // AMARILLO 1
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[0]== 1){
    ENEMIGO[0]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[0]== 1){
    ENEMIGO[0]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- ROJO 1
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[2]== 1){
    ENEMIGO[2]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[2]== 1){
    ENEMIGO[2]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- ROJO 2
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[3]== 1){
    ENEMIGO[3]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[3]== 1){
    ENEMIGO[3]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- ROJO 3
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[4]== 1){
    ENEMIGO[4]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[4]== 1){
    ENEMIGO[4]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  if(escuadron[1]!=0 & ATAQUE[1]==1){                                                 // AMARILLO 2
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[1]== 1){
    ENEMIGO[1]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[1]== 1){
    ENEMIGO[1]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- ROJO 4
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[5]== 1){
    ENEMIGO[5]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[5]== 1){
    ENEMIGO[5]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- ROJO 5
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[6]== 1){
    ENEMIGO[6]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[6]== 1){
    ENEMIGO[6]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- ROJO 6
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[7]== 1){
    ENEMIGO[7]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[7]== 1){
    ENEMIGO[7]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  if(escuadron[2]!=0 & ATAQUE[2]==1){                                                 // morado 1
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[8]== 1){
    ENEMIGO[8]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[8]== 1){
    ENEMIGO[8]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- morado 2
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[9]== 1){
    ENEMIGO[9]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[9]== 1){
    ENEMIGO[9]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- morado 3
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[10]== 1){
    ENEMIGO[10]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[10]== 1){
    ENEMIGO[10]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- morado 4
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[11]== 1){
    ENEMIGO[11]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[11]== 1){
    ENEMIGO[11]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  if(escuadron[3]!=0 & ATAQUE[3]==1){                                                 // morado 5
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[12]== 1){
    ENEMIGO[12]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[12]== 1){
    ENEMIGO[12]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- morado 6
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[13]== 1){
    ENEMIGO[13]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[13]== 1){
    ENEMIGO[13]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- morado 7
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[14]== 1){
    ENEMIGO[14]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[14]== 1){
    ENEMIGO[14]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- morado 8
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[15]== 1){
    ENEMIGO[15]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[15]== 1){
    ENEMIGO[15]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  if(escuadron[4]!=0 & ATAQUE[4]==1){                                                 // azul 1
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[16]== 1){
    ENEMIGO[16]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[16]== 1){
    ENEMIGO[16]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- azul 2
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[17]== 1){
    ENEMIGO[17]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[17]== 1){
    ENEMIGO[17]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 3
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[18]== 1){
    ENEMIGO[18]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[18]== 1){
    ENEMIGO[18]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 4
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[19]== 1){
    ENEMIGO[19]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[19]== 1){
    ENEMIGO[19]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }


if(escuadron[5]!=0 & ATAQUE[5]==1){                                                 // azul 5
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[20]== 1 ){
    ENEMIGO[20]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[20]== 1){
    ENEMIGO[20]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- azul 6
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[21]== 1){
    ENEMIGO[21]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[21]== 1){
    ENEMIGO[21]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 7
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[22]== 1){
    ENEMIGO[22]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[22]== 1){
    ENEMIGO[22]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 8
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[23]== 1){
    ENEMIGO[23]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[23]== 1){
    ENEMIGO[23]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

if(escuadron[6]!=0 & ATAQUE[6]==1){                                                 // azul 11
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[26]== 1){
    ENEMIGO[26]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[26]== 1){
    ENEMIGO[26]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- azul 12
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[27]== 1){
    ENEMIGO[27]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[27]== 1){
    ENEMIGO[27]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 13
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[28]== 1){
    ENEMIGO[28]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[28]== 1){
    ENEMIGO[28]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 14
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[29]== 1){
    ENEMIGO[29]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[29]== 1){
    ENEMIGO[29]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  if(escuadron[7]!=0 & ATAQUE[7]==1){                                                 // aazul 15
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[30]== 1){
    ENEMIGO[30]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[30]== 1){
    ENEMIGO[30]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- azul 16
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[31]== 1){
    ENEMIGO[31]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[31]== 1){
    ENEMIGO[31]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 17
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[32]== 1){
    ENEMIGO[32]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[32]== 1){
    ENEMIGO[32]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 18
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[33]== 1){
    ENEMIGO[33]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[33]== 1){
    ENEMIGO[33]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

  if(escuadron[8]!=0 & ATAQUE[8]==1){                                                 // azul 21
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[36]== 1){
    ENEMIGO[36]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[36]== 1){
    ENEMIGO[36]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- azul 22
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[37]== 1){
    ENEMIGO[37]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[37]== 1){
    ENEMIGO[37]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 23
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[38]== 1){
    ENEMIGO[38]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[38]== 1){
    ENEMIGO[38]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 24
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[39]== 1){
    ENEMIGO[39]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[39]== 1){
    ENEMIGO[39]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }

if(escuadron[9]!=0 & ATAQUE[9]==1){                                                 // azul 25
  if( copyy <= yy1 & copyy >= yy1-5 & copyx >= xx1-9 & copyx <= xx1+2 &  ENEMIGO[40]== 1){
    ENEMIGO[40]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy1 & copyy2 >= yy1-5 & copyx2 >= xx1-9 & copyx2 <= xx1+2 &  ENEMIGO[40]== 1){
    ENEMIGO[40]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  //------------------------------------------------------------------------------------------- azul 26
    if( copyy <= yy2 & copyy >= yy2-5 & copyx >= xx2-9 & copyx <= xx2+2 &  ENEMIGO[41]== 1){
    ENEMIGO[41]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy2 & copyy2 >= yy2-5 & copyx2 >= xx2-9 & copyx2 <= xx2+2 &  ENEMIGO[41]== 1){
    ENEMIGO[41]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 27
    if( copyy <= yy3 & copyy >= yy3-5 & copyx >= xx3-9 & copyx <= xx3+2 &  ENEMIGO[42]== 1){
    ENEMIGO[42]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy3 & copyy2 >= yy3-5 & copyx2 >= xx3-9 & copyx2 <= xx3+2 &  ENEMIGO[42]== 1){
    ENEMIGO[42]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
    //------------------------------------------------------------------------------------------- azul 28
    if( copyy <= yy4 & copyy >= yy4-5 & copyx >= xx4-9 & copyx <= xx4+2 &  ENEMIGO[43]== 1){
    ENEMIGO[43]=0; 
    misil = 0;
    copyy = 200;
    enable_copy=1;
    digitalWrite(LEDV,HIGH);
  }
    if( copyy2 <= yy4 & copyy2 >= yy4-5 & copyx2 >= xx4-9 & copyx2 <= xx4+2 &  ENEMIGO[43]== 1){
    ENEMIGO[43]=0; 
    misil2 = 0;
    copyy2 = 200;
    enable_copy2=1;
    digitalWrite(LEDA,HIGH);
  }
  }




  
  return;
}

//*********************************************************************************************************************************

void DISPARO1(void){
 
  if(misil == 1 & enable_copy == 1){
    copyx=x;
    enable_copy=0;
  }
       
if( misil == 1){
  copyy--;
  LCD_Bitmap(copyx+6,copyy, 7, 7, MISIL1);
 
  if(copyy==10){
  FillRect(copyx+6, 10, 7,7, 0x00);
  misil=0;
  copyy=200;
  enable_copy=1;
  digitalWrite(LEDV,HIGH);
 }
}

  return;
}
//*********************************************************************************************************************************
void DISPARO2(void){
  
if(misil2 == 1 & enable_copy2 == 1){
    copyx2=x2;
    enable_copy2=0;
  }
       
if( misil2 == 1){
  copyy2--;
  LCD_Bitmap(copyx2+6,copyy2, 7, 7, MISIL1);
 
  if(copyy2==10){
  FillRect(copyx2+6, 10, 7,7, 0x00);
  misil2=0;
  copyy2=200;
  enable_copy2=1;
  digitalWrite(LEDA,HIGH);
 }
}

  return;
}
//**********************************************************************************************************************************************************
void MUERTE_ENEMIGO(void){
  if(ATAQUE[0]==0){
  if(ENEMIGO[0] == 0 & LIMPIEZA[0] != 0 ){            // amarillo
  LIMPIEZA[0]--;
      LCD_Sprite(PA1, PB1, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
 
  }
    if(ENEMIGO[2] == 0 & LIMPIEZA[2] != 0 ){          // rojo 1
    LIMPIEZA[2]--;
      LCD_Sprite(PA3, PB3, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
      if(ENEMIGO[3] == 0 & LIMPIEZA[3] != 0){        // rojo 2
    LIMPIEZA[3]--;
      LCD_Sprite(PA4, PB4, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
         
  }
      if(ENEMIGO[4] == 0 & LIMPIEZA[4] != 0){        // rojo 3
    LIMPIEZA[4]--;
      LCD_Sprite(PA5, PB5, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
   
  }
  }

  if(ATAQUE[1]==0){
  if(ENEMIGO[1] == 0 & LIMPIEZA[1] != 0 ){            
  LIMPIEZA[1]--;
      LCD_Sprite(PA2, PB2, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
    if(ENEMIGO[5] == 0 & LIMPIEZA[5] != 0 ){         
    LIMPIEZA[5]--;
      LCD_Sprite(PA6, PB6, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
      if(ENEMIGO[6] == 0 & LIMPIEZA[6] != 0){        
    LIMPIEZA[6]--;
      LCD_Sprite(PA7, PB7, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
       
  }
      if(ENEMIGO[7] == 0 & LIMPIEZA[7] != 0){        
    LIMPIEZA[7]--;
      LCD_Sprite(PA8, PB8, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
         
  }
  }

  if(ATAQUE[2]==0){
  if(ENEMIGO[8] == 0 & LIMPIEZA[8] != 0 ){           
  LIMPIEZA[8]--;
      LCD_Sprite(PA9, PB9, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
    if(ENEMIGO[9] == 0 & LIMPIEZA[9] != 0 ){          
    LIMPIEZA[9]--;
      LCD_Sprite(PA10, PB10, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
      if(ENEMIGO[10] == 0 & LIMPIEZA[10] != 0){        
    LIMPIEZA[10]--;
      LCD_Sprite(PA11, PB11, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
      
  }
      if(ENEMIGO[11] == 0 & LIMPIEZA[11] != 0){        
    LIMPIEZA[11]--;
      LCD_Sprite(PA12, PB12, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
  }
  if(ATAQUE[3]==0){
  if(ENEMIGO[12] == 0 & LIMPIEZA[12] != 0 ){            
  LIMPIEZA[12]--;
      LCD_Sprite(PA13, PB13, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
         
  }
    if(ENEMIGO[13] == 0 & LIMPIEZA[13] != 0 ){         
    LIMPIEZA[13]--;
      LCD_Sprite(PA14, PB14, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
        
  }
      if(ENEMIGO[14] == 0 & LIMPIEZA[14] != 0){        
    LIMPIEZA[14]--;
      LCD_Sprite(PA15, PB15, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
      
  }
      if(ENEMIGO[15] == 0 & LIMPIEZA[15] != 0){        
    LIMPIEZA[15]--;
      LCD_Sprite(PA16, PB16, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
         
  }
  }
  
  if(ATAQUE[4]==0){
  if(ENEMIGO[16] == 0 & LIMPIEZA[16] != 0 ){            
  LIMPIEZA[16]--;
      LCD_Sprite(PA17, PB17, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
    if(ENEMIGO[17] == 0 & LIMPIEZA[17] != 0 ){         
    LIMPIEZA[17]--;
      LCD_Sprite(PA18, PB18, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
        
  }
      if(ENEMIGO[18] == 0 & LIMPIEZA[18] != 0){        
    LIMPIEZA[18]--;
      LCD_Sprite(PA19, PB19, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
       
  }
      if(ENEMIGO[19] == 0 & LIMPIEZA[19] != 0){        
    LIMPIEZA[19]--;
      LCD_Sprite(PA20, PB20, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
  }
  if(ATAQUE[5]==0){
  if(ENEMIGO[20] == 0 & LIMPIEZA[20] != 0 ){            
  LIMPIEZA[20]--;
      LCD_Sprite(PA21, PB21, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
        
  }
    if(ENEMIGO[21] == 0 & LIMPIEZA[21] != 0 ){         
    LIMPIEZA[21]--;
      LCD_Sprite(PA22, PB22, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
         
  }
      if(ENEMIGO[22] == 0 & LIMPIEZA[22] != 0){        
    LIMPIEZA[22]--;
      LCD_Sprite(PA23, PB23, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
      if(ENEMIGO[23] == 0 & LIMPIEZA[23] != 0){        
    LIMPIEZA[23]--;
      LCD_Sprite(PA24, PB24, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
  }
  if(ATAQUE[6]==0){
  if(ENEMIGO[26] == 0 & LIMPIEZA[26] != 0 ){            
  LIMPIEZA[26]--;
      LCD_Sprite(PA27, PB27, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
       
  }
    if(ENEMIGO[27] == 0 & LIMPIEZA[27] != 0 ){         
    LIMPIEZA[27]--;
      LCD_Sprite(PA28, PB28, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
        
  }
      if(ENEMIGO[28] == 0 & LIMPIEZA[28] != 0){        
    LIMPIEZA[28]--;
      LCD_Sprite(PA29, PB29, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
       
  }
      if(ENEMIGO[29] == 0 & LIMPIEZA[29] != 0){        
    LIMPIEZA[29]--;
      LCD_Sprite(PA30, PB30, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
  }

  if(ATAQUE[7]==0){
  if(ENEMIGO[30] == 0 & LIMPIEZA[30] != 0 ){            
  LIMPIEZA[30]--;
      LCD_Sprite(PA31, PB31, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
      
  }
    if(ENEMIGO[31] == 0 & LIMPIEZA[31] != 0 ){         
    LIMPIEZA[31]--;
      LCD_Sprite(PA32, PB32, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
        
  }
      if(ENEMIGO[32] == 0 & LIMPIEZA[32] != 0){        
    LIMPIEZA[32]--;
      LCD_Sprite(PA33, PB33, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
      if(ENEMIGO[33] == 0 & LIMPIEZA[33] != 0){        
    LIMPIEZA[33]--;
      LCD_Sprite(PA34, PB34, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
       
  }
  }
  
  if(ATAQUE[8]==0){
  if(ENEMIGO[36] == 0 & LIMPIEZA[36] != 0 ){            
  LIMPIEZA[36]--;
      LCD_Sprite(PA37, PB37, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
    if(ENEMIGO[37] == 0 & LIMPIEZA[37] != 0 ){         
    LIMPIEZA[37]--;
      LCD_Sprite(PA38, PB38, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
      if(ENEMIGO[38] == 0 & LIMPIEZA[38] != 0){        
    LIMPIEZA[38]--;
      LCD_Sprite(PA39, PB39, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
   
  }
      if(ENEMIGO[39] == 0 & LIMPIEZA[39] != 0){        
    LIMPIEZA[39]--;
      LCD_Sprite(PA40, PB40, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
       
  }
  }
  if(ATAQUE[9]==0){
  if(ENEMIGO[40] == 0 & LIMPIEZA[40] != 0 ){            
  LIMPIEZA[40]--;
      LCD_Sprite(PA41, PB41, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
    if(ENEMIGO[41] == 0 & LIMPIEZA[41] != 0 ){         
    LIMPIEZA[41]--;
      LCD_Sprite(PA42, PB42, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
      if(ENEMIGO[42] == 0 & LIMPIEZA[42] != 0){        
    LIMPIEZA[42]--;
      LCD_Sprite(PA43, PB43, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
      if(ENEMIGO[43] == 0 & LIMPIEZA[43] != 0){        
    LIMPIEZA[43]--;
      LCD_Sprite(PA44, PB44, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
  }


  if(ENEMIGO[24] == 0 & LIMPIEZA[24] != 0 ){            
  LIMPIEZA[24]--;
      LCD_Sprite(PA25, PB25, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
       
  }
    if(ENEMIGO[25] == 0 & LIMPIEZA[25] != 0 ){         
    LIMPIEZA[25]--;
      LCD_Sprite(PA26, PB26, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
   
  }
      if(ENEMIGO[34] == 0 & LIMPIEZA[34] != 0){        
    LIMPIEZA[34]--;
      LCD_Sprite(PA35, PB35, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
        
  }
      if(ENEMIGO[35] == 0 & LIMPIEZA[35] != 0){        
    LIMPIEZA[35]--;
      LCD_Sprite(PA36, PB36, 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
  
      if(ENEMIGO[44] == 0 & LIMPIEZA[44] != 0){        
    LIMPIEZA[44]--;
      LCD_Sprite(PA45, PB45, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
         
  }
      if(ENEMIGO[45] == 0 & LIMPIEZA[45] != 0){        
    LIMPIEZA[45]--;
      LCD_Sprite(PA46, PB46, 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
         
  }

  
  if(ATAQUE[0]==1){
    if(ENEMIGO[0] == 0 & LIMPIEZA[0] != 0 ){            // amarillo
  LIMPIEZA[0]--;
      LCD_Sprite(ATAMUERTEX[0], ATAMUERTEY[0], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
    if(ENEMIGO[2] == 0 & LIMPIEZA[2] != 0){          // rojo 1
    LIMPIEZA[2]--;
      LCD_Sprite(ATAMUERTEX[2], ATAMUERTEY[2], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
       
  }
      if(ENEMIGO[3] == 0 & LIMPIEZA[3] != 0){        // rojo 2
    LIMPIEZA[3]--;
      LCD_Sprite(ATAMUERTEX[3], ATAMUERTEY[3], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
      if(ENEMIGO[4] == 0 & LIMPIEZA[4] != 0){        // rojo 3
    LIMPIEZA[4]--;
      LCD_Sprite(ATAMUERTEX[4], ATAMUERTEY[4], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
        
  }
  }

   if(ATAQUE[1]==1){
      if(ENEMIGO[1] == 0 & LIMPIEZA[1] != 0 ){            // amarillo 2
  LIMPIEZA[1]--;
      LCD_Sprite(ATAMUERTEX[1], ATAMUERTEY[1], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

      
  }
    if(ENEMIGO[5] == 0 & LIMPIEZA[5] != 0){          // rojo 4
    LIMPIEZA[5]--;
      LCD_Sprite(ATAMUERTEX[5], ATAMUERTEY[5], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

        
  }
      if(ENEMIGO[6] == 0 & LIMPIEZA[6] != 0){        // rojo 5
    LIMPIEZA[6]--;
      LCD_Sprite(ATAMUERTEX[6], ATAMUERTEY[6], 11, 11, REDBUGDEAD,4, anim1, 0, 0);
 
         
  }
      if(ENEMIGO[7] == 0 & LIMPIEZA[7] != 0){        // rojo 6
    LIMPIEZA[7]--;
      LCD_Sprite(ATAMUERTEX[7], ATAMUERTEY[7], 11, 11, REDBUGDEAD,4, anim1, 0, 0);
 
         
  }
  }

  if(ATAQUE[2]==1){
      if(ENEMIGO[8] == 0 & LIMPIEZA[8] != 0 ){            
  LIMPIEZA[8]--;
      LCD_Sprite(ATAMUERTEX[8], ATAMUERTEY[8], 11, 11, REDBUGDEAD,4, anim1, 0, 0);

        
  }
    if(ENEMIGO[9] == 0 & LIMPIEZA[9] != 0){         
    LIMPIEZA[9]--;
      LCD_Sprite(ATAMUERTEX[9], ATAMUERTEY[9], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
 
        
  }
      if(ENEMIGO[10] == 0 & LIMPIEZA[10] != 0){        
    LIMPIEZA[10]--;
      LCD_Sprite(ATAMUERTEX[10], ATAMUERTEY[10], 11, 11, REDBUGDEAD,4, anim1, 0, 0);
  
      
  }
      if(ENEMIGO[11] == 0 & LIMPIEZA[11] != 0){        
    LIMPIEZA[11]--;
      LCD_Sprite(ATAMUERTEX[11], ATAMUERTEY[11], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 

        
  }
  }
  if(ATAQUE[3]==1){
      if(ENEMIGO[12] == 0 & LIMPIEZA[12] != 0 ){            
  LIMPIEZA[12]--;
      LCD_Sprite(ATAMUERTEX[12], ATAMUERTEY[12], 11, 11, REDBUGDEAD,4, anim1, 0, 0);
   
      
  }
    if(ENEMIGO[13] == 0 & LIMPIEZA[13] != 0){          
    LIMPIEZA[13]--;
      LCD_Sprite(ATAMUERTEX[13], ATAMUERTEY[13], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 

        
  }
      if(ENEMIGO[14] == 0 & LIMPIEZA[14] != 0){        
    LIMPIEZA[14]--;
      LCD_Sprite(ATAMUERTEX[14], ATAMUERTEY[14], 11, 11, REDBUGDEAD,4, anim1, 0, 0);
 
       
  }
      if(ENEMIGO[15] == 0 & LIMPIEZA[15] != 0){        
    LIMPIEZA[15]--;
      LCD_Sprite(ATAMUERTEX[15], ATAMUERTEY[15], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
  
     
  }
  }
  
  if(ATAQUE[4]==1){
        if(ENEMIGO[16] == 0 & LIMPIEZA[16] != 0 ){            
  LIMPIEZA[16]--;
      LCD_Sprite(ATAMUERTEX[16], ATAMUERTEY[16], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

      
  }
    if(ENEMIGO[17] == 0 & LIMPIEZA[17] != 0){          
    LIMPIEZA[17]--;
      LCD_Sprite(ATAMUERTEX[17], ATAMUERTEY[17], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

      
  }
      if(ENEMIGO[18] == 0 & LIMPIEZA[18] != 0){        
    LIMPIEZA[18]--;
      LCD_Sprite(ATAMUERTEX[18], ATAMUERTEY[18], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
 
  }
      if(ENEMIGO[19] == 0 & LIMPIEZA[19] != 0){        
    LIMPIEZA[19]--;
      LCD_Sprite(ATAMUERTEX[19], ATAMUERTEY[19], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

   
  }
  }
  if(ATAQUE[5]==1){
        if(ENEMIGO[20] == 0 & LIMPIEZA[20] != 0 ){            
  LIMPIEZA[20]--;
      LCD_Sprite(ATAMUERTEX[20], ATAMUERTEY[20], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

       
  }
    if(ENEMIGO[21] == 0 & LIMPIEZA[21] != 0){          
    LIMPIEZA[21]--;
      LCD_Sprite(ATAMUERTEX[21], ATAMUERTEY[21], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

       
  }
      if(ENEMIGO[22] == 0 & LIMPIEZA[22] != 0){        
    LIMPIEZA[22]--;
      LCD_Sprite(ATAMUERTEX[22], ATAMUERTEY[22], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
 
        
  }
      if(ENEMIGO[23] == 0 & LIMPIEZA[23] != 0){        
    LIMPIEZA[23]--;
      LCD_Sprite(ATAMUERTEX[23], ATAMUERTEY[23], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 

         
  }
  }
  if(ATAQUE[6]==1){
        if(ENEMIGO[26] == 0 & LIMPIEZA[26] != 0 ){            
  LIMPIEZA[26]--;
      LCD_Sprite(ATAMUERTEX[26], ATAMUERTEY[26], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
 
        
  }
    if(ENEMIGO[27] == 0 & LIMPIEZA[27] != 0){          
    LIMPIEZA[27]--;
      LCD_Sprite(ATAMUERTEX[27], ATAMUERTEY[27], 11, 11, REDBUGDEAD,4, anim1, 0, 0);
   
  }
      if(ENEMIGO[28] == 0 & LIMPIEZA[28] != 0){        
    LIMPIEZA[28]--;
      LCD_Sprite(ATAMUERTEX[28], ATAMUERTEY[28], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

        
  }
      if(ENEMIGO[29] == 0 & LIMPIEZA[29] != 0){        
    LIMPIEZA[29]--;
      LCD_Sprite(ATAMUERTEX[29], ATAMUERTEY[29], 11, 11, REDBUGDEAD,4, anim1, 0, 0);

          
  }
  }

  if(ATAQUE[7]==1){
        if(ENEMIGO[30] == 0 & LIMPIEZA[30] != 0 ){            
  LIMPIEZA[30]--;
      LCD_Sprite(ATAMUERTEX[30], ATAMUERTEY[30], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
  
         
  }
    if(ENEMIGO[31] == 0 & LIMPIEZA[31] != 0){          
    LIMPIEZA[31]--;
      LCD_Sprite(ATAMUERTEX[31], ATAMUERTEY[31], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
 
        
  }
      if(ENEMIGO[32] == 0 & LIMPIEZA[32] != 0){        
    LIMPIEZA[32]--;
      LCD_Sprite(ATAMUERTEX[32], ATAMUERTEY[32], 11, 11, REDBUGDEAD,4, anim1, 0, 0);

          
  }
      if(ENEMIGO[33] == 0 & LIMPIEZA[33] != 0){        
    LIMPIEZA[33]--;
      LCD_Sprite(ATAMUERTEX[33], ATAMUERTEY[33], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  

        
  }
  }
  
  if(ATAQUE[8]==1){
    if(ENEMIGO[36] == 0 & LIMPIEZA[36] != 0 ){            
  LIMPIEZA[36]--;
      LCD_Sprite(ATAMUERTEX[36], ATAMUERTEY[36], 11, 11, REDBUGDEAD,4, anim1, 0, 0);
 
          
  }
    if(ENEMIGO[37] == 0 & LIMPIEZA[37] != 0){          
    LIMPIEZA[37]--;
      LCD_Sprite(ATAMUERTEX[37], ATAMUERTEY[37], 11, 11, REDBUGDEAD,4, anim1, 0, 0);

          
  }
      if(ENEMIGO[38] == 0 & LIMPIEZA[38] != 0){        
    LIMPIEZA[38]--;
      LCD_Sprite(ATAMUERTEX[38], ATAMUERTEY[38], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
  
         
  }
      if(ENEMIGO[39] == 0 & LIMPIEZA[39] != 0){        
    LIMPIEZA[39]--;
      LCD_Sprite(ATAMUERTEX[39], ATAMUERTEY[39], 11, 11, REDBUGDEAD,4, anim1, 0, 0);  
 
        
  }
  }
  if(ATAQUE[9]==1){
      if(ENEMIGO[40] == 0 & LIMPIEZA[40] != 0 ){            
  LIMPIEZA[40]--;
      LCD_Sprite(ATAMUERTEX[40], ATAMUERTEY[40], 11, 11, REDBUGDEAD,4, anim1, 0, 0);


  }
    if(ENEMIGO[41] == 0 & LIMPIEZA[41] != 0){          
    LIMPIEZA[41]--;
      LCD_Sprite(ATAMUERTEX[41], ATAMUERTEY[41], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 
 
 
  }
      if(ENEMIGO[42] == 0 & LIMPIEZA[42] != 0){        
    LIMPIEZA[42]--;
      LCD_Sprite(ATAMUERTEX[42], ATAMUERTEY[42], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 


  }
      if(ENEMIGO[43] == 0 & LIMPIEZA[43] != 0){        
    LIMPIEZA[43]--;
      LCD_Sprite(ATAMUERTEX[43], ATAMUERTEY[43], 11, 11, REDBUGDEAD,4, anim1, 0, 0); 


  }
  }


  return;
}


//***********************************************************************************************************************************************************  
  void CONTROLES(void){
     // read the state of the pushbutton value:
  BS1 = digitalRead(BP1);
  BS2 = digitalRead(BP2);
  BS3 = digitalRead(BP3);
  BS4 = digitalRead(BP4);
  BS5 = digitalRead(BP5);
  BS6 = digitalRead(BP6);

if(PLAYERA==1){
//-------------------------------------------------------------PRIMER JUGADOR--------------------------------------------------------------//
  
//---------------------------------DISPARO P1----------------------------------//
  if (BS1 == LOW){
    AR1 = 1;
    digitalWrite(LP3, LOW);
  }
  if (BS1 == HIGH & AR1 == 1) {   
  //if (BS1 == HIGH) {  
    // turn LED on:    
    digitalWrite(LP3, HIGH);
    digitalWrite(LEDV,LOW);
    misil=1;
    delay(40);
    AR1 = 0; 
  } 
  else {
    // turn LED off:
    digitalWrite(LP3, LOW);
    //digitalWrite(LEDV,LOW);
    delay(5); 
  }

//---------------------------MOVIMIENTO DERECHA & IZQUIERDA P1-------------------------//   

  //if (BS2 == HIGH & AR1 == 1) {   
  if (BS2 == HIGH) {  
    // turn LED on:    
  //  digitalWrite(LP2, HIGH);
    x = x+1;
    //AR1 = 0;  
  } 
  else {
    // turn LED off:
   // digitalWrite(LP2, LOW); 
  }

  //if (BS3 == HIGH & AR1 == 1) {   
  if (BS3 == HIGH) {  
    // turn LED on:    
   // digitalWrite(LP3, HIGH);
    
    x = x-1;
    //AR1 = 0;  
  } 
  else {
    // turn LED off:
  //  digitalWrite(LP3, LOW);
    
  }
}
if(PLAYERB==1){
//-------------------------------------------------------------SEGUNDO JUGADOR--------------------------------------------------------------//
  
//---------------------------------DISPARO P2----------------------------------//
    if (BS4 == LOW){
    AR2 = 1;
    digitalWrite(LP2, LOW);
  }
  if (BS4 == HIGH & AR2 == 1) {     
    // turn LED on:    
    digitalWrite(LP2, HIGH);
    digitalWrite(LEDA,LOW);
    delay(40);
    AR2 = 0; 
    misil2=1;
  } 
  else {
    // turn LED off:
    digitalWrite(LP2, LOW);
    //digitalWrite(LEDA,LOW);
    delay(5); 
  }

//---------------------------MOVIMIENTO DERECHA & IZQUIERDA P2-------------------------//   
  if (BS5 == HIGH) {  
    // turn LED on:    
   // digitalWrite(LP5, HIGH);
   x2=x2+1;
  } 
  else {
    // turn LED off:
   // digitalWrite(LP5, LOW); 
  }

  
  if (BS6 == HIGH) {  
    // turn LED on:    
   // digitalWrite(LP6, HIGH);
    x2=x2-1;
    //AR1 = 0;  
  } 
  else {
    // turn LED off:
    //digitalWrite(LP6, LOW); 
  }
 
  }
  }
//**********************************************************************************************************************************************************
void ANIMACIOON(void){
   animacion++;
     anim1 = (animacion/10)%2;
     anim2 = (animacion/20)%2; 
    return;
}

//***********************************************************************************************************************************************************
void ATAQUE_ENEMIGO1(int referencia_1,int referencia_2, int referencia_3, int referencia_4,int ataquee,int squad,int casee, int xxx1, int xxx2, int xxx3, int xxx4, int yyy1, int yyy2, int yyy3, int yyy4, int pa1, int pa2, int pa3, int pa4, int pb1,int pb2, int pb3, int pb4 ){

if(copy == 1){
  xx1 = xxx1;
  xx2 = xxx2;
  xx3 = xxx3;
  xx4 = xxx4;
  yy1 = yyy1;
  yy2 = yyy2;
  yy3 = yyy3;
  yy4 = yyy4;
  copy = 0;
}
if(squad==0){
      CONTADOR = 0;
    ATAQUE[0] = 0;    
    ATAQUE[1] = 0;
    ATAQUE[2] = 0;    
    ATAQUE[3] = 0;
    ATAQUE[4] = 0;    
    ATAQUE[5] = 0;
    ATAQUE[6] = 0;    
    ATAQUE[7] = 0;
    ATAQUE[8] = 0;    
    ATAQUE[9] = 0;
    enablee = 0;
    copy = 1;
    deploy++;
    if(deploy==10){
      deploy=0;
    }
}


if(squad!=0 & ataquee == 1 ){

if(CONTADOR == 0){

if(xx1!= 50){
  xx1 = xx1 - 1;
}
if(xx2!= 30){
  xx2 = xx2 - 1;
}
if(xx3!= 50){
  xx3 = xx3 - 1;
}
if(xx4!= 70){
  xx4 = xx4 - 1;
}

if(yy1!= 30){
  yy1= yy1-1;
}
if(yy2!= 45){
  yy2= yy2-1;
}
if(yy3!= 45){
  yy3= yy3-1;
}
if(yy4!= 45){
  yy4= yy4-1;
}
  
    
    
   if(xx1 == 50 & xx2==30 & xx3==50 & xx4==70 & yy1 == 30 & yy2==45 & yy3 == 45 & yy4 == 45){
    CONTADOR = 1;
   }
}

if(CONTADOR == 1){

 if(xx1!= 30){
  xx1 = xx1 - 1;
}
if(xx2!= 10){
  xx2 = xx2 - 1;
}
if(xx3!= 30){
  xx3 = xx3 - 1;
}
if(xx4!= 50){
  xx4 = xx4 - 1;
}
if(yy1!= 120){
  yy1= yy1+1;
}
if(yy2!= 135){
  yy2= yy2+1;
}
if(yy3!= 135){
  yy3= yy3+1;
}
if(yy4!= 135){
  yy4= yy4+1;
}

   if(xx1 == 30 & xx2==10 & xx3==30 & xx4==50 & yy1 == 120 & yy2==135 & yy3 == 135 & yy4 == 135){
    CONTADOR = 2;
   }
}

if(CONTADOR == 2){

  if(xx1!= 250){
  xx1 = xx1 + 1;
}
if(xx2!= 230){
  xx2 = xx2 + 1;
}
if(xx3!= 250){
  xx3 = xx3 + 1;
}
if(xx4!= 270){
  xx4 = xx4 + 1;
}
if(yy1!= 160){
  yy1= yy1+1;
}
if(yy2!= 175){
  yy2= yy2+1;
}
if(yy3!= 175){
  yy3= yy3+1;
}
if(yy4!= 175){
  yy4= yy4+1;
}



   if(xx1 == 250 & xx2==230 & xx3==250 & xx4==270 & yy1 == 160 & yy2==175 & yy3 == 175 & yy4 == 175){
    CONTADOR = 3;
   }
}

if(CONTADOR == 3){
if(yy1 != 70){
  yy1 = yy1 - 1;
}
if(yy2!= 85){
  yy2= yy2-1;
}
if(yy3!= 85){
  yy3= yy3-1;
}
if(yy4!= 85){
  yy4= yy4-1;
}
if(xx1 != 260){
  xx1 = xx1 +1;
}
if(xx2!= 240){
  xx2 = xx2 + 1;
}
if(xx3!= 260){
  xx3 = xx3 + 1;
}
if(xx4!= 280){
  xx4 = xx4 + 1;
}

   if(yy1 == 70 & yy2==85 & yy3 == 85 & yy4 == 85 & xx2==240 & xx3==260 & xx4==280 & xx1 == 260){
    CONTADOR = 4;
   }
}

if(CONTADOR == 4){

if(xx1 != pa1){
  xx1 = xx1-1;
}
if(xx2 != pa2){
  xx2 = xx2-1;
}
if(xx3 != pa3){
  xx3 = xx3-1;
}
if(xx4 != pa4){
  xx4 = xx4-1;
}
if(yy1 != 40){
  yy1 = yy1-1;
}
if(yy2 != 55){
  yy2 = yy2-1;
}
if(yy3 != 55){
  yy3 = yy3-1;
}
if(yy4 != 55){
  yy4 = yy4-1;
}


   if(xx1 == pa1& xx2==pa2 & xx3 == pa3 & xx4==pa4 & yy1 == 40 & yy2 == 55 & yy3 == 55 & yy4 == 55 ){
    CONTADOR = 5;
   }
}
  if(CONTADOR == 5){
 if ( yy1 != pb1){
  yy1 = yy1 +1;
 }
 if( yy2 != pb2 ){
  yy2 = yy2 +1;
 }
 if( yy3 != pb3){
  yy3 = yy3 +1;
 }
 if( yy4 != pb4){
  yy4 = yy4 +1;
 }
   if(yy1 == pb1 & yy2 == pb2 & yy3 == pb3 & yy4 == pb4){
    CONTADOR = 0;
    ATAQUE[0] = 0;    
    ATAQUE[1] = 0;
    ATAQUE[2] = 0;    
    ATAQUE[3] = 0;
    ATAQUE[4] = 0;    
    ATAQUE[5] = 0;
    ATAQUE[6] = 0;    
    ATAQUE[7] = 0;
    ATAQUE[8] = 0;    
    ATAQUE[9] = 0;
    enablee = 0;
    copy = 1;
    deploy++;
    if(deploy==10){
      deploy=0;
    }
   }
}

 H_line(xx2,yy1-4, 50, 0x00);
 H_line(xx2-10,yy1-6, 70, 0x00);
 H_line(xx2,yy3+10, 50, 0x00);
 H_line(xx2-10,yy3+18, 70, 0x00);
 V_line(xx2-5, yy2-17, 25, 0x00);
 V_line(xx2-8, yy2-25, 40, 0x00);
 V_line(xx4+15,yy4-17, 25, 0x00);
 V_line(xx4+17,yy4-25, 40, 0x00);
 V_line(xx2+12,yy1, 25, 0x00);
 V_line(xx1+12,yy1, 25, 0x00);











switch(casee){
//*******************************************************************  escuadron 1
 case 1:
 if(CONTADOR != 5){
  if(ENEMIGO[0]==1){
 LCD_Bitmap(xx1, yy1,alto_amarillo, ancho_amarillo,YELLOW);
 ATAMUERTEX[0]=xx1;
 ATAMUERTEY[0]=yy1;
  }
  if(ENEMIGO[2]==1){
 LCD_Sprite(xx2, yy2, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
 ATAMUERTEX[2]=xx2;
 ATAMUERTEY[2]=yy2;
 if(xx2==180 & valana == 1 & CONTADOR==2){
  misilito1=1;
  valana=0;
}
 if(xx2==50 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
  }
 if (ENEMIGO[3]==1){
 LCD_Sprite(xx3, yy3, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
 ATAMUERTEX[3]=xx3;
 ATAMUERTEY[3]=yy3;
 if(xx3==250 & valana2 == 1 & CONTADOR ==2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
 }
 if(ENEMIGO[4]==1){
 LCD_Sprite(xx4, yy4, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0); 
 ATAMUERTEX[4]=xx4;
 ATAMUERTEY[4]=yy4;
 
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
 }
 }
  if(CONTADOR == 5){
    if(ENEMIGO[0]==1){
 LCD_Bitmap(referencia_1, yy1,alto_amarillo, ancho_amarillo,YELLOW);
     ATAMUERTEX[0]=referencia_1;
     ATAMUERTEY[0]=yy1;
    }
   if(ENEMIGO[2]==1){
 LCD_Sprite(referencia_2, yy2, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
     ATAMUERTEX[2]=referencia_2;
     ATAMUERTEY[2]=yy2;
   }
   if(ENEMIGO[3]==1){
 LCD_Sprite(referencia_3, yy3, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
     ATAMUERTEX[3]=referencia_3;
     ATAMUERTEY[3]=yy3;
   }
   if(ENEMIGO[4]==1){
 LCD_Sprite(referencia_4, yy4, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0); 
      ATAMUERTEX[4]=referencia_4;
      ATAMUERTEY[4]=yy4;
   }
 }
 break; 
//*******************************************************************  escuadron 2
 case 2:
 if (CONTADOR != 5){
  if(ENEMIGO[1]==1){
  LCD_Bitmap(xx1, yy1, ancho_amarillo, alto_amarillo, YELLOW);
      ATAMUERTEX[1]=xx1;
      ATAMUERTEY[1]=yy1;
  }
  if(ENEMIGO[5]==1){
  LCD_Sprite(xx2, yy2, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
      ATAMUERTEX[5]=xx2;
      ATAMUERTEY[5]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR ==2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
      misilito1=1;
      valana=0;
}
  }
  if(ENEMIGO[6]==1){
  LCD_Sprite(xx3, yy3, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0); 
      ATAMUERTEX[6]=xx3;
      ATAMUERTEY[6]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
  }
  if(ENEMIGO[7]==1){
  LCD_Sprite(xx4, yy4, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0); 
      ATAMUERTEX[7]=xx4;
      ATAMUERTEY[7]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
  }
 }
   if(CONTADOR == 5){
  if(ENEMIGO[1]==1){
  LCD_Bitmap(referencia_1, yy1, ancho_amarillo, alto_amarillo, YELLOW);
      ATAMUERTEX[1]=referencia_1;
      ATAMUERTEY[1]=yy1;
  }
  if(ENEMIGO[5]==1){
  LCD_Sprite(referencia_2, yy2, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0);
      ATAMUERTEX[5]=referencia_2;
      ATAMUERTEY[5]=yy2;
  }
  if(ENEMIGO[6]==1){
  LCD_Sprite(referencia_3, yy3, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0); 
      ATAMUERTEX[6]=referencia_3;
      ATAMUERTEY[6]=yy3;
  }
  if(ENEMIGO[7]==1){
  LCD_Sprite(referencia_4, yy4, ancho_bicho, alto_bicho, REDBUG,2, 0, 0, 0); 
      ATAMUERTEX[7]=referencia_4;
      ATAMUERTEY[7]=yy4;
  }
 }
 break; 
//*******************************************************************  escuadron 3
 case 3: 
 if(CONTADOR != 5){
   if(ENEMIGO[8]==1){
   LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[8]=xx1;
      ATAMUERTEY[8]=yy1;
   }
   if(ENEMIGO[9]==1){
   LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[9]=xx2;
      ATAMUERTEY[9]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
      misilito1=1;
      valana=0;
}
   }
   if(ENEMIGO[10]==1){
   LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[10]=xx3;
      ATAMUERTEY[10]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
   }
   if(ENEMIGO[11]==1){
   LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[11]=xx4;
      ATAMUERTEY[11]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
   }
 }
 if(CONTADOR == 5){
   if(ENEMIGO[8]==1){
   LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[8]=referencia_1;
      ATAMUERTEY[8]=yy1;
   }
   if(ENEMIGO[9]==1){
   LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[9]=referencia_2;
      ATAMUERTEY[9]=yy2;
   }
   if(ENEMIGO[10]==1){
   LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[10]=referencia_3;
      ATAMUERTEY[10]=yy3;
      if(xx3==250 & valana2 == 1){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1){
  misilito2=1;
  valana2=0;
}
   }
   if(ENEMIGO[11]==1){
   LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[11]=referencia_4;
      ATAMUERTEY[11]=yy4;
   }
 }
 
 break;
//*******************************************************************
case 4:
if(CONTADOR != 5){
   if(ENEMIGO[12]==1){
   LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[12]=xx1;
      ATAMUERTEY[12]=yy1;
   }
   if(ENEMIGO[13]==1){
   LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[13]=xx2;
      ATAMUERTEY[13]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
       misilito1=1;
       valana=0;
}
   }
   if(ENEMIGO[14]==1){
   LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[14]=xx3;
      ATAMUERTEY[14]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
   }
   if(ENEMIGO[15]==1){
   LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[15]=xx4;
      ATAMUERTEY[15]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
   }
 }
 if(CONTADOR == 5){
   if(ENEMIGO[12]==1){
   LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[12]=referencia_1;
      ATAMUERTEY[12]=yy1;
   }
   if(ENEMIGO[13]==1){
   LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[13]=referencia_2;
      ATAMUERTEY[13]=yy2;
   }
   if(ENEMIGO[14]==1){
   LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[14]=referencia_3;
      ATAMUERTEY[14]=yy3;
   }
   if(ENEMIGO[15]==1){
   LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, PURPLEBUG,2, 0, 0, 0);
      ATAMUERTEX[15]=referencia_4;
      ATAMUERTEY[15]=yy4;
   }
 }
 
break;
//*******************************************************************
case 5:
if(CONTADOR != 5){
  if(ENEMIGO[16]==1){
LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[16]=xx1;
      ATAMUERTEY[16]=yy1;
  }
  if(ENEMIGO[17]==1){  
LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);  
      ATAMUERTEX[17]=xx2;
      ATAMUERTEY[17]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
      misilito1=1;
      valana=0;
}
  }
  if(ENEMIGO[18]==1){
LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[18]=xx3;
      ATAMUERTEY[18]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
  }
  if(ENEMIGO[19]==1){
LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[19]=xx4;
      ATAMUERTEY[19]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
  }
}
 if(CONTADOR == 5){
  if(ENEMIGO[16]==1){
LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[16]=referencia_1;
      ATAMUERTEY[16]=yy1;
  }
  if(ENEMIGO[17]==1){  
LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);  
      ATAMUERTEX[17]=referencia_2;
      ATAMUERTEY[17]=yy2;
  }
  if(ENEMIGO[18]==1){
LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[18]= referencia_3;
      ATAMUERTEY[18]=yy3;
  }
  if(ENEMIGO[19]==1){
LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[19]=referencia_4;
      ATAMUERTEY[19]=yy4;
  }
 } 
break;
//*******************************************************************
case 6:
if(CONTADOR != 5){
  if(ENEMIGO[20]==1){
LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[20]=xx1;
      ATAMUERTEY[20]=yy1;
  }
  if(ENEMIGO[21]==1){  
LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[21]=xx2;
      ATAMUERTEY[21]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
      misilito1=1;
      valana=0;
} 
  }
  if(ENEMIGO[22]==1){
LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[22]=xx3;
      ATAMUERTEY[22]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
  }
  if(ENEMIGO[23]==1){
LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[23]=xx4;
      ATAMUERTEY[23]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
  }
}
 if(CONTADOR == 5){
  if(ENEMIGO[20]==1){
LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[20]=referencia_1;
      ATAMUERTEY[20]=yy1;
  }
  if(ENEMIGO[21]==1){  
LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[21]=referencia_2;
      ATAMUERTEY[21]=yy2;  
  }
  if(ENEMIGO[22]==1){
LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[22]=referencia_3;
      ATAMUERTEY[22]=yy3;
  }
  if(ENEMIGO[23]==1){
LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[23]=referencia_4;
      ATAMUERTEY[23]=yy4;
  } 
 } 
 
break;
//*******************************************************************
case 7:
if(CONTADOR != 5){
  if(ENEMIGO[26]==1){
LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[26]=xx1;
      ATAMUERTEY[26]=yy1;
  }
  if(ENEMIGO[27]==1){  
LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);  
      ATAMUERTEX[27]=xx2;
      ATAMUERTEY[27]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
      misilito1=1;
      valana=0;
}
  }
  if(ENEMIGO[28]==1){
LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[28]=xx3;
      ATAMUERTEY[28]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
  }
  if(ENEMIGO[29]==1){
LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[29]=xx4;
      ATAMUERTEY[29]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
  }
}
 if(CONTADOR == 5){
  if(ENEMIGO[26]==1){
LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[26]=referencia_1;
      ATAMUERTEY[26]=yy1;
  }
  if(ENEMIGO[27]==1){  
LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);  
      ATAMUERTEX[27]=referencia_2;
      ATAMUERTEY[27]=yy2;
  }
  if(ENEMIGO[28]==1){
LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[28]=referencia_3;
      ATAMUERTEY[28]=yy3;
  }
  if(ENEMIGO[29]==1){
LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[1]=referencia_4;
      ATAMUERTEY[1]=yy4;
  }
 }  
break;
//*******************************************************************
case 8:
if(CONTADOR != 5){
  if(ENEMIGO[30]==1){
LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[30]=xx1;
      ATAMUERTEY[30]=yy1;
  }  
  if(ENEMIGO[31]==1){
LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[31]=xx2;
      ATAMUERTEY[31]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
      misilito1=1;
      valana=0;
}
  }  
  if(ENEMIGO[32]==1){
LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[32]=xx3;
      ATAMUERTEY[32]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
  }
  if(ENEMIGO[33]==1){
LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[33]=xx4;
      ATAMUERTEY[33]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
  }
}
 if(CONTADOR == 5){
  if(ENEMIGO[30]==1){
LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[30]=referencia_1;
      ATAMUERTEY[30]=yy1;
  }  
  if(ENEMIGO[31]==1){
LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[31]=referencia_2;
      ATAMUERTEY[31]=yy2;
  }  
  if(ENEMIGO[32]==1){
LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[32]=referencia_3;
      ATAMUERTEY[32]=yy3;
  }
  if(ENEMIGO[33]==1){
LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[33]=referencia_4;
      ATAMUERTEY[33]=yy4;
  }
 } 
break;
//*******************************************************************
case 9:
if(CONTADOR != 5){
  if(ENEMIGO[36]==1){
LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[36]=xx1;
      ATAMUERTEY[36]=yy1; 
  }
  if(ENEMIGO[37]==1){
LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[37]=xx2;
      ATAMUERTEY[37]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
       misilito1=1;
       valana=0;
} 
  }
  if(ENEMIGO[38]==1){
LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[38]=xx3;
      ATAMUERTEY[38]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
  }
  if(ENEMIGO[39]==1){
LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[39]=xx4;
      ATAMUERTEY[39]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
  }
}
 if(CONTADOR == 5){
  if(ENEMIGO[36]==1){
LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);  
      ATAMUERTEX[36]=referencia_1;
      ATAMUERTEY[36]=yy1;
  }
  if(ENEMIGO[37]==1){
LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[37]=referencia_2;
      ATAMUERTEY[37]=yy2;  
  }
  if(ENEMIGO[38]==1){
LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[38]=referencia_3;
      ATAMUERTEY[38]=yy3;
  }
  if(ENEMIGO[39]==1){
LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[39]=referencia_4;
      ATAMUERTEY[39]=yy4;
  }
 } 
break;

//*********************************************************************************
case 10:
if(CONTADOR != 5){
  if(ENEMIGO[40]==1){
LCD_Sprite(xx1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[40]=xx1;
      ATAMUERTEY[40]=yy1;  
  }
  if(ENEMIGO[41]==1){
LCD_Sprite(xx2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);  
      ATAMUERTEX[41]=xx2;
      ATAMUERTEY[41]=yy2;
      if(xx2==180 & valana == 1 & CONTADOR == 2){
  misilito1=1;
  valana=0;
}
      if(xx2==50 & valana == 1 & CONTADOR == 2){
       misilito1=1;
       valana=0;
}
  }
  if(ENEMIGO[42]==1){
LCD_Sprite(xx3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[42]=xx3;
      ATAMUERTEY[42]=yy3;
      if(xx3==250 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
if(xx3==110 & valana2 == 1 & CONTADOR == 2){
  misilito2=1;
  valana2=0;
}
  }
  if(ENEMIGO[43]==1){
LCD_Sprite(xx4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[43]=xx4;
      ATAMUERTEY[43]=yy4;
      
if(xx4==170 & valana3 == 1 & CONTADOR == 2){
  misilito3=1;
  valana3 = 0;
}
  }
}
 if(CONTADOR == 5){
  if(ENEMIGO[40]==1){
LCD_Sprite(referencia_1,yy1, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);  
      ATAMUERTEX[40]=referencia_1;
      ATAMUERTEY[40]=yy1;
  }
  if(ENEMIGO[41]==1){
LCD_Sprite(referencia_2,yy2, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[41]=referencia_2;
      ATAMUERTEY[41]=yy2; 
  }
  if(ENEMIGO[42]==1){
LCD_Sprite(referencia_3,yy3, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0);
      ATAMUERTEX[42]=referencia_3;
      ATAMUERTEY[42]=yy3;
  }
  if(ENEMIGO[43]==1){
LCD_Sprite(referencia_4,yy4, ancho_bicho, alto_bicho, BICHOA,2,0, 0, 0); 
      ATAMUERTEX[43]=referencia_4;
      ATAMUERTEY[43]=yy4;
  } 
 }  
break;
}
//*********************************************************************************
}
  return;
}
//***********************************************************************************************************************************************************
void TIEMPOS(void){
     
  if(z==0){
    z2++;
    if(z2==6){ 
    y=y-1;
  digitalWrite(MUX1,LOW);
  digitalWrite(MUX2,LOW);
  digitalWrite(MUX3,LOW);
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
  digitalWrite(MUX1,LOW);
  digitalWrite(MUX2,LOW);
  digitalWrite(MUX3,LOW);  
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
//------------------------------------------------------------------------------ amarillo 1
    if(ENEMIGO[0] == 1 & LIMPIEZA[0] == 15 & ATAQUE[0] == 0){
  
    LCD_Bitmap(PX1=130+y,PY1=65,alto_amarillo, ancho_amarillo, YELLOW);
    PA1 = PX1;
    PB1 = PY1;
}   
  if(ENEMIGO[0] == 0 & LIMPIEZA[0] == 0){
    if(REMOVE[0] == 1){
      if(ATAQUE[0]==0){
    FillRect(PA1,PB1, 11, 11,0x00);
      }
    if(ATAQUE[0]==1){
    FillRect(ATAMUERTEX[0],ATAMUERTEY[0], 11, 11,0x00);
      }
    REMOVE[0] = 0;
    }
    PX1=y+130;
    PY1 =65;
    
    
  }
//------------------------------------------------------------------------------------ amarillo 2

  if(ENEMIGO[1] == 1 & LIMPIEZA[1] == 15 & ATAQUE[1] == 0){
    
  
   LCD_Bitmap(PX2=y+190, PY2=65, ancho_amarillo, alto_amarillo, YELLOW);
    PA2 = PX2;
    PB2 = PY2;  
}
  if(ENEMIGO[1] == 0 & LIMPIEZA[1] == 0){
    if(REMOVE[1] == 1){
      if(ATAQUE[1]==0){
    FillRect(PA2,PB2, 11, 11,0x00);
      }
    if(ATAQUE[1]==1){
    FillRect(ATAMUERTEX[1],ATAMUERTEY[1], 11, 11,0x00);
      }
    REMOVE[1] = 0;
    }
    PX2 =y+190; 
    PY2 =65;
    
  }
//-------------------------------------------------------------------------------------------- rojo 1
if(ENEMIGO[2] == 1 & LIMPIEZA[2] == 15 & ATAQUE[0] == 0){
  
    LCD_Sprite(PX3=y+110, PY3=80, ancho_bicho, alto_bicho, REDBUG,2, anim1, 0, 0);     
    PA3 = PX3;
    PB3 = PY3; 
}
  if(ENEMIGO[2] == 0 & LIMPIEZA[2] == 0){
    if(REMOVE[2] == 1){
if(ATAQUE[0]==0){
    FillRect(PA3,PB3, 11, 11,0x00);
      }
    if(ATAQUE[0]==1){
    FillRect(ATAMUERTEX[2],ATAMUERTEY[2], 11, 11,0x00);
      }
    REMOVE[2] = 0;
    }
    PX3=y+110; 
    PY3=80; 
    
  }
//-------------------------------------------------------------------------------------------- rojo 2
if(ENEMIGO[3] == 1 & LIMPIEZA[3] == 15 & ATAQUE[0] == 0){
    LCD_Sprite(PX4=y+130, PY4=80, ancho_bicho, alto_bicho, REDBUG,2, anim1, 0, 0);     
    PA4 = PX4;
    PB4 = PY4; 
}
  if(ENEMIGO[3] == 0 & LIMPIEZA[3] == 0){
    if(REMOVE[3] == 1){
if(ATAQUE[0]==0){
    FillRect(PA4,PB4, 11, 11,0x00);
      }
    if(ATAQUE[0]==1){
    FillRect(ATAMUERTEX[3],ATAMUERTEY[3], 11, 11,0x00);
      }
    REMOVE[3] = 0;
    }
    PX4=y+130; PY4=80;
   
  }
//-------------------------------------------------------------------------------------------- rojo 3
if(ENEMIGO[4] == 1 & LIMPIEZA[4] == 15 & ATAQUE[0] == 0){
    LCD_Sprite(PX5=y+150, PY5=80, ancho_bicho, alto_bicho, REDBUG,2, anim1, 0, 0);     
    PA5 = PX5;
    PB5 = PY5; 
}
  if(ENEMIGO[4] == 0 & LIMPIEZA[4] == 0){
    if(REMOVE[4] == 1){
   if(ATAQUE[0]==0){
    FillRect(PA5,PB5, 11, 11,0x00);
      }
    if(ATAQUE[0]==1){
    FillRect(ATAMUERTEX[4],ATAMUERTEY[4], 11, 11,0x00);
      }
    REMOVE[4] = 0;
    }
    PX5=y+150; PY5=80; 
    
  }
//-------------------------------------------------------------------------------------------- rojo 4
if(ENEMIGO[5] == 1 & LIMPIEZA[5] == 15 & ATAQUE[1] == 0){
  
    LCD_Sprite(PX6=y+170, PY6=80, ancho_bicho, alto_bicho, REDBUG,2, anim2, 0, 0);    
    PA6 = PX6;
    PB6 = PY6;
  
}

  if(ENEMIGO[5] == 0 & LIMPIEZA[5] == 0){
    if(REMOVE[5] == 1){
   if(ATAQUE[1]==0){
    FillRect(PA6,PB6, 11, 11,0x00);
      }
    if(ATAQUE[1]==1){
    FillRect(ATAMUERTEX[5],ATAMUERTEY[5], 11, 11,0x00);
      }
    REMOVE[5] = 0;
    }
    PX6=y+170; PY6=80; 
    
  }
//-------------------------------------------------------------------------------------------- rojo 5
if(ENEMIGO[6] == 1 & LIMPIEZA[6] == 15 & ATAQUE[1] == 0){
  
    LCD_Sprite(PX7=y+190, PY7=80, ancho_bicho, alto_bicho, REDBUG,2, anim1, 0, 0);     
    PA7 = PX7;
    PB7 = PY7;
  
}

  if(ENEMIGO[6] == 0 & LIMPIEZA[6] == 0){
    if(REMOVE[6] == 1){
   if(ATAQUE[1]==0){
    FillRect(PA7,PB7, 11, 11,0x00);
      }
    if(ATAQUE[1]==1){
    FillRect(ATAMUERTEX[6],ATAMUERTEY[6], 11, 11,0x00);
      }
    REMOVE[6] = 0;
    }
    PX7=y+190; PY7=80;
  
  }
//-------------------------------------------------------------------------------------------- rojo 6
if(ENEMIGO[7] == 1 & LIMPIEZA[7] == 15 & ATAQUE[1] == 0){
  
    LCD_Sprite(PX8=y+210, PY8=80, ancho_bicho, alto_bicho, REDBUG,2, anim2, 0, 0);     
    PA8 = PX8;
    PB8 = PY8;
  
}

  if(ENEMIGO[7] == 0 & LIMPIEZA[7] == 0){
    if(REMOVE[7] == 1){
   if(ATAQUE[1]==0){
    FillRect(PA8,PB8, 11, 11,0x00);
      }
    if(ATAQUE[1]==1){
    FillRect(ATAMUERTEX[7],ATAMUERTEY[7], 11, 11,0x00);
      }
    REMOVE[7] = 0;
    }
    PX8=y+210; PY8=80;
    
  }
//--------------------------------------------------------------------------------------------morado 1
if(ENEMIGO[8] == 1 & LIMPIEZA[8] == 15 & ATAQUE[2] == 0){
  
    LCD_Sprite(PX9=y+90,PY9=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);    
    PA9 = PX9;
    PB9 = PY9; 
}
  if(ENEMIGO[8] == 0 & LIMPIEZA[8] == 0){
    if(REMOVE[8] == 1){
   if(ATAQUE[2]==0){
    FillRect(PA9,PB9, 11, 11,0x00);
      }
    if(ATAQUE[2]==1){
    FillRect(ATAMUERTEX[8],ATAMUERTEY[8], 11, 11,0x00);
      }
    REMOVE[8] = 0;
    }
    PX9=y+90; PY9=90;
    
  }
//-------------------------------------------------------------------------------------------- morado 2
if(ENEMIGO[9] == 1 & LIMPIEZA[9] == 15 & ATAQUE[2] == 0){
  
    LCD_Sprite(PX10=y+110, PY10=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);     
    PA10 = PX10;
    PB10 = PY10;
  
}

  if(ENEMIGO[9] == 0 & LIMPIEZA[9] == 0){
    if(REMOVE[9] == 1){
   if(ATAQUE[2]==0){
    FillRect(PA10,PB10, 11, 11,0x00);
      }
    if(ATAQUE[2]==1){
    FillRect(ATAMUERTEX[9],ATAMUERTEY[9], 11, 11,0x00);
      }
    REMOVE[9] = 0;
    }
    PX10=y+110; PY10=90;
    
  }
//-------------------------------------------------------------------------------------------- morado 3
if(ENEMIGO[10] == 1 & LIMPIEZA[10] == 15 & ATAQUE[2] == 0){
  
    LCD_Sprite(PX11=y+130, PY11=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);    
    PA11 = PX11;
    PB11 = PY11;
  
}

  if(ENEMIGO[10] == 0 & LIMPIEZA[10] == 0){
    if(REMOVE[10] == 1){
    if(ATAQUE[2]==0){
    FillRect(PA11,PB11, 11, 11,0x00);
      }
    if(ATAQUE[2]==1){
    FillRect(ATAMUERTEX[10],ATAMUERTEY[10], 11, 11,0x00);
      }
    REMOVE[10] = 0;
    }
    PX11=y+130; PY11=90;
    
  }
//-------------------------------------------------------------------------------------------- morado 4
if(ENEMIGO[11] == 1 & LIMPIEZA[11] == 15 & ATAQUE[2] == 0){
  
     LCD_Sprite(PX12=y+150, PY12=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);     
    PA12 = PX12;
    PB12 = PY12;
  
}

  if(ENEMIGO[11] == 0 & LIMPIEZA[11] == 0){
    if(REMOVE[11] == 1){
     if(ATAQUE[2]==0){
    FillRect(PA12,PB12, 11, 11,0x00);
      }
    if(ATAQUE[2]==1){
    FillRect(ATAMUERTEX[11],ATAMUERTEY[11], 11, 11,0x00);
      }
    REMOVE[11] = 0;
    }
    PX12=y+150; PY12=90;
    
  }
//-------------------------------------------------------------------------------------------- morado 5
if(ENEMIGO[12] == 1 & LIMPIEZA[12] == 15 & ATAQUE[3] == 0){
  
    LCD_Sprite(PX13=y+170, PY13=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);     
    PA13 = PX13;
    PB13 = PY13;
  
}

  if(ENEMIGO[12] == 0 & LIMPIEZA[12] == 0){
    if(REMOVE[12] == 1){
   if(ATAQUE[3]==0){
    FillRect(PA13,PB13, 11, 11,0x00);
      }
    if(ATAQUE[3]==1){
    FillRect(ATAMUERTEX[12],ATAMUERTEY[12], 11, 11,0x00);
      }
    REMOVE[12] = 0;
    }
    PX13=y+170; 
    PY13=90;
    
  }
//-------------------------------------------------------------------------------------------- morado 6
if(ENEMIGO[13] == 1 & LIMPIEZA[13] == 15 & ATAQUE[3] == 0){
  
   LCD_Sprite(PX14=y+190, PY14=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);     
    PA14 = PX14;
    PB14 = PY14;
  
}

  if(ENEMIGO[13] == 0 & LIMPIEZA[13] == 0){
    if(REMOVE[13] == 1){
   if(ATAQUE[3]==0){
    FillRect(PA14,PB14, 11, 11,0x00);
      }
    if(ATAQUE[3]==1){
    FillRect(ATAMUERTEX[13],ATAMUERTEY[13], 11, 11,0x00);
      }
    REMOVE[13] = 0;
    }
    PX14=y+190; 
    PY14=90; 
    
  }
//-------------------------------------------------------------------------------------------- morado 7
if(ENEMIGO[14] == 1 & LIMPIEZA[14] == 15 & ATAQUE[3] == 0){
  
     LCD_Sprite(PX15=y+210, PY15=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim1, 0, 0);   
       
    PA15 = PX15;
    PB15 = PY15;
  
}

  if(ENEMIGO[14] == 0 & LIMPIEZA[14] == 0){
    if(REMOVE[14] == 1){
    if(ATAQUE[3]==0){
    FillRect(PA15,PB15, 11, 11,0x00);
      }
    if(ATAQUE[3]==1){
    FillRect(ATAMUERTEX[14],ATAMUERTEY[14], 11, 11,0x00);
      }
    REMOVE[14] = 0;
    }
    PX15=y+210; 
    PY15=90;
    
  }
//-------------------------------------------------------------------------------------------- morado 8
if(ENEMIGO[15] == 1 & LIMPIEZA[15] == 15 & ATAQUE[3] == 0){
  
    LCD_Sprite(PX16=y+230, PY16=90, ancho_bicho, alto_bicho, PURPLEBUG,2, anim2, 0, 0);     
    PA16 = PX16;
    PB16 = PY16;
  
}

  if(ENEMIGO[15] == 0 & LIMPIEZA[15] == 0){
    if(REMOVE[15] == 1){
    if(ATAQUE[3]==0){
    FillRect(PA16,PB16, 11, 11,0x00);
      }
    if(ATAQUE[3]==1){
    FillRect(ATAMUERTEX[15],ATAMUERTEY[15], 11, 11,0x00);
      }
    REMOVE[15] = 0;
    }
    PX16=y+230; 
    PY16=90;
   
  }
//-------------------------------------------------------------------------------------------- azul 1
if(ENEMIGO[16] == 1 & LIMPIEZA[16] == 15 & ATAQUE[4] == 0){
  
    LCD_Sprite(PX17=y+70, PY17=100, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);       
    PA17 = PX17;
    PB17 = PY17; 
}
  if(ENEMIGO[16] == 0 & LIMPIEZA[16] == 0){
    if(REMOVE[16] == 1){
   
    if(ATAQUE[4]==0){
    FillRect(PA17,PB17, 11, 11,0x00);
      }
    if(ATAQUE[4]==1){
    FillRect(ATAMUERTEX[16],ATAMUERTEY[16], 11, 11,0x00);
      }
    REMOVE[16] = 0;
    }
    PX17=y+70; PY17=100;
    
  }
//-------------------------------------------------------------------------------------------- azul 2

if(ENEMIGO[17] == 1 & LIMPIEZA[17] == 15 & ATAQUE[4] == 0){
     
    LCD_Sprite(PX18=y+90, PY18=100, ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);    
      
    PA18 = PX18;
    PB18 = PY18;
  
}

  if(ENEMIGO[17] == 0 & LIMPIEZA[17] == 0){
    if(REMOVE[17] == 1){
    if(ATAQUE[4]==0){
    FillRect(PA18,PB18, 11, 11,0x00);
      }
    if(ATAQUE[4]==1){
    FillRect(ATAMUERTEX[17],ATAMUERTEY[17], 11, 11,0x00);
      }
    REMOVE[17] = 0;
    }
    PX18=y+90; PY18=100;
    
  }
//-------------------------------------------------------------------------------------------- azul 3
if(ENEMIGO[18] == 1 & LIMPIEZA[18] == 15 & ATAQUE[4] == 0){
  
LCD_Sprite(PX19=y+110, PY19=100, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);      
    PA19 = PX19;
    PB19 = PY19;
}
  if(ENEMIGO[18] == 0 & LIMPIEZA[18] == 0){
    if(REMOVE[18] == 1){

    if(ATAQUE[4]==0){
    FillRect(PA19,PB19, 11, 11,0x00);
      }
    if(ATAQUE[4]==1){
    FillRect(ATAMUERTEX[18],ATAMUERTEY[18], 11, 11,0x00);
      }
    REMOVE[18] = 0;
    }
    PX19=y+110; PY19=100;
    
  }
//-------------------------------------------------------------------------------------------- azul 4
if(ENEMIGO[19] == 1 & LIMPIEZA[19] == 15 & ATAQUE[4] == 0){
  
 LCD_Sprite(PX20=y+130, PY20=100, ancho_bicho, alto_bicho, BICHOA,2,anim2, 0, 0);          
    PA20 = PX20;
    PB20 = PY20; 
}
  if(ENEMIGO[19] == 0 & LIMPIEZA[19] == 0){
    if(REMOVE[19] == 1){
    
    if(ATAQUE[4]==0){
    FillRect(PA20,PB20, 11, 11,0x00);
      }
    if(ATAQUE[4]==1){
    FillRect(ATAMUERTEX[19],ATAMUERTEY[19], 11, 11,0x00);
      }
    REMOVE[19] = 0;
    }
    PX20=y+130; PY20=100;
    
  }
//-------------------------------------------------------------------------------------------- azul 5
if(ENEMIGO[20] == 1 & LIMPIEZA[20] == 15 & ATAQUE[5] == 0){
  LCD_Sprite(PX21=y+150, PY21=100,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);       
  PA21 = PX21;
  PB21 = PY21; 
}
  if(ENEMIGO[20] == 0 & LIMPIEZA[20] == 0){
    if(REMOVE[20] == 1){
    if(ATAQUE[5]==0){
    FillRect(PA21,PB21, 11, 11,0x00);
      }
    if(ATAQUE[5]==1){
    FillRect(ATAMUERTEX[20],ATAMUERTEY[20], 11, 11,0x00);
      }
    REMOVE[20] = 0;
    }
    PX21=y+150; PY21=100;
    
  }
//-------------------------------------------------------------------------------------------- azul 6
if(ENEMIGO[21] == 1 & LIMPIEZA[21] == 15 & ATAQUE[5] == 0){
    LCD_Sprite(PX22=y+170, PY22=100,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);       
    PA22 = PX22;
    PB22 = PY22;
}
  if(ENEMIGO[21] == 0 & LIMPIEZA[21] == 0){
    if(REMOVE[21] == 1){
    if(ATAQUE[5]==0){
    FillRect(PA22,PB22, 11, 11,0x00);
      }
    if(ATAQUE[5]==1){
    FillRect(ATAMUERTEX[21],ATAMUERTEY[21], 11, 11,0x00);
      }
    REMOVE[21] = 0;
    }
    PX22=y+170; PY22=100;
    
  }
//-------------------------------------------------------------------------------------------- azul 7
if(ENEMIGO[22] == 1 & LIMPIEZA[22] == 15 & ATAQUE[5] == 0){
  LCD_Sprite(PX23=y+190, PY23=100,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);       
  PA23 = PX23;
  PB23 = PY23;
}
  if(ENEMIGO[22] == 0 & LIMPIEZA[22] == 0){
    if(REMOVE[22] == 1){
    if(ATAQUE[5]==0){
    FillRect(PA23,PB23, 11, 11,0x00);
      }
    if(ATAQUE[5]==1){
    FillRect(ATAMUERTEX[22],ATAMUERTEY[22], 11, 11,0x00);
      }
    REMOVE[22] = 0;
    }
    PX23=y+190; PY23=100;
   
  }
//-------------------------------------------------------------------------------------------- azul 8
if(ENEMIGO[23] == 1 & LIMPIEZA[23] == 15 & ATAQUE[5] == 0){
    LCD_Sprite(PX24=y+210, PY24=100,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);        
    PA24 = PX24;
    PB24 = PY24;  
}
  if(ENEMIGO[23] == 0 & LIMPIEZA[23] == 0){
    if(REMOVE[23] == 1){
    if(ATAQUE[5]==0){
    FillRect(PA24,PB24, 11, 11,0x00);
      }
    if(ATAQUE[5]==1){
    FillRect(ATAMUERTEX[23],ATAMUERTEY[23], 11, 11,0x00);
      }
    REMOVE[23] = 0;
    }
    PX24=y+210; PY24=100;
   
  }
//-------------------------------------------------------------------------------------------- azul 9
if(ENEMIGO[24] == 1 & LIMPIEZA[24] == 15 ){
    LCD_Sprite(PX25=y+230, PY25=100, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);        
    PA25 = PX25;
    PB25 = PY25;
}
  if(ENEMIGO[24] == 0 & LIMPIEZA[24] == 0){
    if(REMOVE[24] == 1){
    FillRect(PA25,PB25, 11, 11,0x00);
    REMOVE[24] = 0;
    }
    PX25=y+230; PY25=100;
   
  }
//-------------------------------------------------------------------------------------------- azul 10
if(ENEMIGO[25] == 1 & LIMPIEZA[25] == 15 ){
    LCD_Sprite(PX26=y+250, PY26=100,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);        
    PA26 = PX26;
    PB26 = PY26;
}
  if(ENEMIGO[25] == 0 & LIMPIEZA[25] == 0){
    if(REMOVE[25] == 1){
    FillRect(PA26,PB26, 11, 11,0x00);
    REMOVE[25] = 0;
    }
    PX26=y+250; PY26=100;
   
  }
//-------------------------------------------------------------------------------------------- azul 11
if(ENEMIGO[26] == 1 & LIMPIEZA[26] == 15 & ATAQUE[6] == 0){
    LCD_Sprite(PX27=y+70, PY27=110, ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);      
    PA27 = PX27;
    PB27 = PY27; 
}
  if(ENEMIGO[26] == 0 & LIMPIEZA[26] == 0){
    if(REMOVE[26] == 1){

    if(ATAQUE[6]==0){
    FillRect(PA27,PB27, 11, 11,0x00);
      }
    if(ATAQUE[6]==1){
    FillRect(ATAMUERTEX[26],ATAMUERTEY[26], 11, 11,0x00);
      }
    REMOVE[26] = 0;
    }
    PX27=y+70; PY27=110;
   
  }
//-------------------------------------------------------------------------------------------- azul 12
if(ENEMIGO[27] == 1 & LIMPIEZA[27] == 15 & ATAQUE[6] == 0){
    LCD_Sprite(PX28=y+90, PY28=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);             
    PA28 = PX28;
    PB28 = PY28;
}
  if(ENEMIGO[27] == 0 & LIMPIEZA[27] == 0){
    if(REMOVE[27] == 1){

    if(ATAQUE[6]==0){
    FillRect(PA28,PB28, 11, 11,0x00);
      }
    if(ATAQUE[6]==1){
    FillRect(ATAMUERTEX[27],ATAMUERTEY[27], 11, 11,0x00);
      }
    REMOVE[27] = 0;
    }
    PX28=y+90; PY28=110;
    
  }
//-------------------------------------------------------------------------------------------- azul 13
if(ENEMIGO[28] == 1 & LIMPIEZA[28] == 15 & ATAQUE[6] == 0){
    LCD_Sprite(PX29=y+110, PY29=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);      
    PA29 = PX29;
    PB29 = PY29;  
}
  if(ENEMIGO[28] == 0 & LIMPIEZA[28] == 0){
    if(REMOVE[28] == 1){

    if(ATAQUE[6]==0){
    FillRect(PA29,PB29, 11, 11,0x00);
      }
    if(ATAQUE[6]==1){
    FillRect(ATAMUERTEX[28],ATAMUERTEY[28], 11, 11,0x00);
      }
    REMOVE[28] = 0;
    }
    PX29=y+110; PY29=110;
   
  }
//-------------------------------------------------------------------------------------------- azul 14
if(ENEMIGO[29] == 1 & LIMPIEZA[29] == 15 & ATAQUE[6] == 0){
  LCD_Sprite(PX30=y+130, PY30=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);       
  PA30 = PX30;
  PB30 = PY30;
}
  if(ENEMIGO[29] == 0 & LIMPIEZA[29] == 0){
    if(REMOVE[29] == 1){
      
    if(ATAQUE[6]==0){
    FillRect(PA30,PB30, 11, 11,0x00);
      }
    if(ATAQUE[6]==1){
    FillRect(ATAMUERTEX[29],ATAMUERTEY[29], 11, 11,0x00);
      }
    REMOVE[29] = 0;
    }
    PX30=y+130; PY30=110;
   
  }
//-------------------------------------------------------------------------------------------- azul 15
if(ENEMIGO[30] == 1 & LIMPIEZA[30] == 15 & ATAQUE[7] == 0){
  LCD_Sprite(PX31=y+150, PY31=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);        
  PA31 = PX31;
  PB31 = PY31;
}
  if(ENEMIGO[30] == 0 & LIMPIEZA[30] == 0){
    if(REMOVE[30] == 1){

    if(ATAQUE[7]==0){
    FillRect(PA31,PB31, 11, 11,0x00);
      }
    if(ATAQUE[7]==1){
    FillRect(ATAMUERTEX[30],ATAMUERTEY[30], 11, 11,0x00);
      }
    REMOVE[30] = 0;
    }
    PX31=y+150; PY31=110;
    
  }
//-------------------------------------------------------------------------------------------- azul 16
if(ENEMIGO[31] == 1 & LIMPIEZA[31] == 15 & ATAQUE[7] == 0){
    LCD_Sprite(PX32=y+170, PY32=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    PA32 = PX32;
    PB32 = PY32;
}
  if(ENEMIGO[31] == 0 & LIMPIEZA[31] == 0){
    if(REMOVE[31] == 1){

    if(ATAQUE[7]==0){
    FillRect(PA32,PB32, 11, 11,0x00);
      }
    if(ATAQUE[7]==1){
    FillRect(ATAMUERTEX[31],ATAMUERTEY[31], 11, 11,0x00);
      }
    REMOVE[31] = 0;
    }
    PX32=y+170; PY32=110;
    
  }
//-------------------------------------------------------------------------------------------- azul 17
if(ENEMIGO[32] == 1 & LIMPIEZA[32] == 15 & ATAQUE[7] == 0){           
    LCD_Sprite(PX33=y+190, PY33=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0); 
    PA33 = PX33;
    PB33 = PY33; 
}
  if(ENEMIGO[32] == 0 & LIMPIEZA[32] == 0){
    if(REMOVE[32] == 1){

    if(ATAQUE[7]==0){
    FillRect(PA33,PB33, 11, 11,0x00);
      }
    if(ATAQUE[7]==1){
    FillRect(ATAMUERTEX[32],ATAMUERTEY[32], 11, 11,0x00);
      }
    REMOVE[32] = 0;
    }
    PX33=y+190; PY33=110;
   
  }
//-------------------------------------------------------------------------------------------- azul 18
if(ENEMIGO[33] == 1 & LIMPIEZA[33] == 15 & ATAQUE[7] == 0){
    LCD_Sprite(PX34=y+210, PY34=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    PA34 = PX34;
    PB34 = PY34;
}
  if(ENEMIGO[33] == 0 & LIMPIEZA[33] == 0){
    if(REMOVE[33] == 1){
    
    if(ATAQUE[7]==0){
    FillRect(PA34,PB34, 11, 11,0x00);
      }
    if(ATAQUE[7]==1){
    FillRect(ATAMUERTEX[33],ATAMUERTEY[33], 11, 11,0x00);
      }
    REMOVE[33] = 0;
    }
    PX34=y+210; PY34=110;
  
  }
//-------------------------------------------------------------------------------------------- azul 19
if(ENEMIGO[34] == 1 & LIMPIEZA[34] == 15 ){
    LCD_Sprite(PX35=y+230, PY35=110,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0); 
    PA35 = PX35;
    PB35 = PY35; 
}
  if(ENEMIGO[34] == 0 & LIMPIEZA[34] == 0){
    if(REMOVE[34] == 1){
    FillRect(PA35,PB35, 11, 11,0x00);
    REMOVE[34] = 0;
    }
    PX35=y+230; PY35=110;
    
  }
//-------------------------------------------------------------------------------------------- azul 20
if(ENEMIGO[35] == 1 & LIMPIEZA[35] == 15 ){
    LCD_Sprite(PX36=y+250, PY36=110,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    PA36 = PX36;
    PB36 = PY36;
}
  if(ENEMIGO[35] == 0 & LIMPIEZA[35] == 0){
    if(REMOVE[35] == 1){
    FillRect(PA36,PB36, 11, 11,0x00);
    REMOVE[35] = 0;
    }
    PX36=y+250; PY36=110;
   
  }
//-------------------------------------------------------------------------------------------- azul 21
if(ENEMIGO[36] == 1 & LIMPIEZA[36] == 15 & ATAQUE[8] == 0){
    LCD_Sprite(PX37=y+70, PY37=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
    PA37 = PX37;
    PB37 = PY37;
}
  if(ENEMIGO[36] == 0 & LIMPIEZA[36] == 0){
    if(REMOVE[36] == 1){

    if(ATAQUE[8]==0){
    FillRect(PA37,PB37, 11, 11,0x00);
      }
    if(ATAQUE[8]==1){
    FillRect(ATAMUERTEX[36],ATAMUERTEY[36], 11, 11,0x00);
      }
    REMOVE[36] = 0;
    }
    PX37=y+70; PY37=120;
    
  }
//-------------------------------------------------------------------------------------------- azul 22
if(ENEMIGO[37] == 1 & LIMPIEZA[37] == 15 & ATAQUE[8] == 0){
    LCD_Sprite(PX38=y+90, PY38=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    PA38 = PX38;
    PB38 = PY38;
}
  if(ENEMIGO[37] == 0 & LIMPIEZA[37] == 0){
    if(REMOVE[37] == 1){

    if(ATAQUE[8]==0){
    FillRect(PA38,PB38, 11, 11,0x00);
      }
    if(ATAQUE[8]==1){
    FillRect(ATAMUERTEX[37],ATAMUERTEY[37], 11, 11,0x00);
      }
    REMOVE[37] = 0;
    }
    PX38=y+90; PY38=120;
   
  }
//-------------------------------------------------------------------------------------------- azul 23
if(ENEMIGO[38] == 1 & LIMPIEZA[38] == 15 & ATAQUE[8] == 0){
     LCD_Sprite(PX39=y+110, PY39=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);
     PA39 = PX39;
     PB39 = PY39;
}
  if(ENEMIGO[38] == 0 & LIMPIEZA[38] == 0){
    if(REMOVE[38] == 1){

    if(ATAQUE[8]==0){
    FillRect(PA39,PB39, 11, 11,0x00);
      }
    if(ATAQUE[8]==1){
    FillRect(ATAMUERTEX[38],ATAMUERTEY[38], 11, 11,0x00);
      }
    REMOVE[38] = 0;
    }
    PX39=y+110; PY39=120;
   
  }
//-------------------------------------------------------------------------------------------- azul 24
if(ENEMIGO[39] == 1 & LIMPIEZA[39] == 15 & ATAQUE[8] == 0){
    LCD_Sprite(PX40=y+130, PY40=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0); 
    PA40 = PX40;
    PB40 = PY40;
}
  if(ENEMIGO[39] == 0 & LIMPIEZA[39] == 0){
    if(REMOVE[39] == 1){

    if(ATAQUE[8]==0){
    FillRect(PA40,PB40, 11, 11,0x00);
      }
    if(ATAQUE[8]==1){
    FillRect(ATAMUERTEX[39],ATAMUERTEY[39], 11, 11,0x00);
      }
    REMOVE[39] = 0;
    }
    PX40=y+130; PY40=120;
    
  }
//-------------------------------------------------------------------------------------------- azul 25
if(ENEMIGO[40] == 1 & LIMPIEZA[40] == 15 & ATAQUE[9] == 0){
    LCD_Sprite(PX41=y+150, PY41=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);      
    PA41 = PX41;
    PB41 = PY41;
}
  if(ENEMIGO[40] == 0 & LIMPIEZA[40] == 0){
    if(REMOVE[40] == 1){

    if(ATAQUE[9]==0){
    FillRect(PA41,PB41, 11, 11,0x00);
      }
    if(ATAQUE[9]==1){
    FillRect(ATAMUERTEX[40],ATAMUERTEY[40], 11, 11,0x00);
      }
    REMOVE[40] = 0;
    }
    PX41=y+150; PY41=120;
    
  }
//-------------------------------------------------------------------------------------------- azul 26
if(ENEMIGO[41] == 1 & LIMPIEZA[41] == 15 & ATAQUE[9] == 0){
    LCD_Sprite(PX42=y+170, PY42=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);
    PA42 = PX42;
    PB42 = PY42;
}
  if(ENEMIGO[41] == 0 & LIMPIEZA[41] == 0){
    if(REMOVE[41] == 1){

    if(ATAQUE[9]==0){
    FillRect(PA42,PB42, 11, 11,0x00);
      }
    if(ATAQUE[9]==1){
    FillRect(ATAMUERTEX[41],ATAMUERTEY[41], 11, 11,0x00);
      }
    REMOVE[41] = 0;
    }
    PX42=y+170; PY42=120;
    
  }
//-------------------------------------------------------------------------------------------- azul 27
if(ENEMIGO[42] == 1 & LIMPIEZA[42] == 15 & ATAQUE[9] == 0){
    LCD_Sprite(PX43=y+190, PY43=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0); 
    PA43 = PX43;
    PB43 = PY43; 
}
  if(ENEMIGO[42] == 0 & LIMPIEZA[42] == 0){
    if(REMOVE[42] == 1){

    if(ATAQUE[42]==0){
    FillRect(PA43,PB43, 11, 11,0x00);
      }
    if(ATAQUE[42]==1){
    FillRect(ATAMUERTEX[42],ATAMUERTEY[42], 11, 11,0x00);
      }
    REMOVE[42] = 0;
    }
    PX43=y+190; PY43=120;
    
  }
//-------------------------------------------------------------------------------------------- azul 28
if(ENEMIGO[43] == 1 & LIMPIEZA[43] == 15 & ATAQUE[9] == 0){
    LCD_Sprite(PX44=y+210, PY44=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);   
    PA44 = PX44;
    PB44 = PY44;  
}
  if(ENEMIGO[43] == 0 & LIMPIEZA[43] == 0){
    if(REMOVE[43] == 1){
 
    if(ATAQUE[9]==0){
    FillRect(PA44,PB44, 11, 11,0x00);
      }
    if(ATAQUE[9]==1){
    FillRect(ATAMUERTEX[43],ATAMUERTEY[43], 11, 11,0x00);
      }
    REMOVE[43] = 0;
    }
    PX44=y+210; PY44=120;
    
  }
//-------------------------------------------------------------------------------------------- azul 29
if(ENEMIGO[44] == 1 & LIMPIEZA[44] == 15 ){
    LCD_Sprite(PX45=y+230, PY45=120,  ancho_bicho, alto_bicho, BICHOA,2, anim1, 0, 0);         
    PA45 = PX45;
    PB45 = PY45;  
}
  if(ENEMIGO[44] == 0 & LIMPIEZA[44] == 0){
    if(REMOVE[44] == 1){
    FillRect(PA45,PB45, 11, 11,0x00);
    REMOVE[44] = 0;
    }
    PX45=y+230; PY45=120;
    
  }
//-------------------------------------------------------------------------------------------- azul 30  
  if(ENEMIGO[45] == 1 & LIMPIEZA[45] == 15 ){
    LCD_Sprite(PX46=y+250, PY46=120,  ancho_bicho, alto_bicho, BICHOA,2, anim2, 0, 0);             
    PA46 = PX46;
    PB46 = PY46;
  }
  if(ENEMIGO[45] == 0 & LIMPIEZA[45] == 0){
    if(REMOVE[45] == 1){
    FillRect(PA46,PB46, 11, 11,0x00);
    REMOVE[45] = 0;
    }
    PX46=y+250; PY46=120;
    
  }

//-------------------------------------------------------------------------------------------------------------------------
    
   
     
  
   
     
   
  return;
}
//***********************************************************************************************************************************************************

void TIEMPOS_DE_ATAQUE(void){
  segundos++;
  
  if (segundos == 150 ){
      enablee = 1;
      if(CONTADOR==0){
  digitalWrite(MUX1,LOW);    // NAVES ATACANDO
  digitalWrite(MUX2,HIGH);
  digitalWrite(MUX3,LOW);
      }
      segundos = 0;
  }
  
     if (enablee == 1 & deploy == 0 ){
     ATAQUE[0] = 1;
     ATAQUE_ENEMIGO1(PX11,PX10,PX11,PX12,ATAQUE[0],escuadron[0],1, PX1, PX3, PX4, PX5, PY1, PY3, PY4, PY5, PA1, PA3, PA4, PA5, PB1, PB3, PB4, PB5 );
     
     }

     if(enablee == 1 & deploy == 1){
     ATAQUE[1] = 1;
     ATAQUE_ENEMIGO1(PX14,PX13,PX14,PX15,ATAQUE[1],escuadron[1],2, PX2, PX6, PX7, PX8, PY2, PY6, PY7, PY8, PA2, PA6, PA7, PA8, PB2, PB6, PB7, PB8 );
     
     }
     if(enablee == 1 & deploy == 2){
     ATAQUE[2] = 1;
     ATAQUE_ENEMIGO1(PX18,PX19,PX20,PX21,ATAQUE[2],escuadron[2],3, PX9, PX10, PX11, PX12, PY9, PY10, PY11, PY12, PA9, PA10, PA11, PA12, PB9, PB10, PB11, PB12 );
     
     }
     if(enablee == 1 & deploy == 3){
     ATAQUE[3] = 1;
     ATAQUE_ENEMIGO1(PX22,PX23,PX24,PX25,ATAQUE[3],escuadron[3],4, PX13, PX14, PX15, PX16, PY13, PY14, PY15, PY16, PA13, PA14, PA15, PA16, PB13, PB14, PB15, PB16 );
     }
     if(enablee == 1 & deploy == 4){
     ATAQUE[4] = 1;
     ATAQUE_ENEMIGO1(PX27,PX28,PX29,PX30,ATAQUE[4],escuadron[4],5, PX17, PX18, PX19, PX20, PY17, PY18, PY19, PY20, PA17, PA18, PA19, PA20, PB17, PB18, PB19, PB20 );
     }
     if(enablee == 1 & deploy == 5){
     ATAQUE[5] = 1;
     ATAQUE_ENEMIGO1(PX31,PX32,PX33,PX34,ATAQUE[5],escuadron[5],6, PX21, PX22, PX23, PX24, PY21, PY22, PY23, PY24, PA21, PA22, PA23, PA24, PB21, PB22, PB23, PB24 );
     }
     if(enablee == 1 & deploy == 6){
     ATAQUE[6] = 1;
     ATAQUE_ENEMIGO1(PX17,PX18,PX19,PX20,ATAQUE[6],escuadron[6],7, PX27, PX28, PX29, PX30, PY27, PY28, PY29, PY30, PA27, PA28, PA29, PA30, PB27, PB28, PB29, PB30 );
     }
     if(enablee == 1 & deploy == 7){
     ATAQUE[7] = 1;
     ATAQUE_ENEMIGO1(PX21,PX22,PX23,PX24,ATAQUE[7],escuadron[7],8, PX31, PX32, PX33, PX34, PY31, PY32, PY33, PY34, PA31, PA32, PA33, PA34, PB31, PB32, PB33, PB34 );
     }
          if(enablee == 1 & deploy == 8){
     ATAQUE[8] = 1;
     ATAQUE_ENEMIGO1(PX27,PX28,PX29,PX30,ATAQUE[8],escuadron[8],9, PX37, PX38, PX39, PX40, PY37, PY38, PY39, PY40, PA37, PA38, PA39, PA40, PB37, PB38, PB39, PB40 );
     }
          if(enablee == 1 & deploy == 9){
     ATAQUE[9] = 1;
     ATAQUE_ENEMIGO1(PX31,PX32,PX33,PX34,ATAQUE[9],escuadron[9],10, PX41, PX42, PX43, PX44, PY41, PY42, PY43, PY44, PA41, PA42, PA43, PA44, PB41, PB42, PB43, PB44 );
     }


  return;
}





   


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
