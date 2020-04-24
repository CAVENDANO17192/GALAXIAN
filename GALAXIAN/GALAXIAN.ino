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
const int buttonPin1 = PUSH1;     // the number of the pushbutton pin
const int ledPinBLUE =  BLUE_LED;      // the number of the LED pin
int buttonState1 = 0;
const int buttonPin2 = PUSH2;     // the number of the pushbutton pin
const int ledPinGREEN =  GREEN_LED;      // the number of the LED pin
int buttonState2 = 0;
int x = 90;
int y = 0;
int z = 1;
int z2 = 0;
int animacion=0;
int azul1 = 0;
int azul2 = 0;
int azul3 = 0;
int azul4 = 0;
int azul5 = 0;
int azul6 = 0;
int azul7 = 0;
int azul8 = 0;
int azul9 = 0;
int azul10 = 0;
int azul11 = 0;
int azul12 = 0;
int azul13 = 0;
int azul14 = 0;
int azul15 = 0;
int azul16 = 0;
int azul17 = 0;
int azul18 = 0;
int azul19 = 0;
int azul20 = 0;
int azul21 = 0;
int azul22 = 0;
int azul23 = 0;
int azul24 = 0;
int azul25 = 0;
int azul26 = 0;
int azul27 = 0;
int azul28 = 0;
int azul29 = 0;
int azul30 = 0;
int morado1= 0;
int morado2= 0;
int morado3= 0;
int morado4= 0;
int morado5= 0;
int morado6= 0;
int morado7= 0;
int morado8= 0;
int rojo1  = 0;
int rojo2  = 0;
int rojo3  = 0;
int rojo4  = 0;
int rojo5  = 0;
int rojo6  = 0;
int lider1 = 1;
int lider2 = 0;
int x1;
int x2;
int x3;
int x4;
int x5;
int x6;
int x7;
int x8;
int x9;
int x10;
int x11;
int x12;
int x13;
int x14;
int x15;
int x16;
int x17;
int x18;
int x19;
int x20;
int x21;
int x22;
int x23;
int x24;
int x25;
int x26;
int x27;
int x28;
int x29;
int x30;
int x31;
int x32;
int x33;
int x34;
int x35;
int x36;
int x37;
int x38;
int x39;
int x40;
int x41;
int x42;
int x43;
int x44;
int x45;
int x46;
int LIMPIEZA = 15;
int POSICION = 0;
int POSICIONX=0;
int POSICIONY=0;
int REMOVE =1;
int ATAQUE = 0;
int LIDER1X = 0;
int LIDER1Y = 0;

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
  LCD_Bitmap(20, 20, 12, 8, MUERTITO);
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

  
    animacion++;
    int anim1 = (animacion/10)%6;
    int anim2 = (animacion/20)%6; 
    
   
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
  buttonState1 = digitalRead(buttonPin1);
if (buttonState1 == LOW) {     
    // turn LED on:   
    x = x-1;
    lider1=0;
    delay(15);
    
    digitalWrite(ledPinBLUE, HIGH); 
    LCD_Bitmap(x, 200, 20, 20, PLAYER1); 
   
}
buttonState2 = digitalRead(buttonPin2);
if (buttonState2 == LOW) {     
    // turn LED on:   
    x = x+1;
    lider1= 1;
    delay(15);
    
    digitalWrite(ledPinGREEN, HIGH); 
     
   
}
  if (buttonState1 == HIGH) {digitalWrite(ledPinBLUE, LOW); }
  if (buttonState2 == HIGH) {digitalWrite(ledPinGREEN, LOW); }
  
   // LCD_Bitmap(20, 150, 60, 8, BICHOA);
  // V_line(186+y, 65, 100, 0x421b);
  //V_line(187+y, 65, 100, 0x421b);
   // LCD_Sprite(20, 160, 12, 8, PURPLEBUG,6, 0, 0, 0);
    //LCD_Sprite(40, 160, 12, 8, REDBUG,6, 0, 0, 0);
    //V_line( x -1, 100, 20, 0x421b);
    //FillRect(y+128, 65, 3, 10, 0x421b);

if(lider1 == 1 & LIMPIEZA == 15 & ATAQUE == 0){
  
    LCD_Bitmap(y+130, 65, 11, 11, YELLOW);
    POSICION = y+130;
    POSICIONX = y+130;
    POSICIONY = 65;
}

  
   
  

if(lider1 == 0 & LIMPIEZA != 0){
  LIMPIEZA--;
      LCD_Sprite(POSICION, 65, 11, 11, REDBUGDEAD,4, anim1, 0, 0);
      
  }
  if(lider1 == 0 & LIMPIEZA == 0){
    if(REMOVE == 1){
    FillRect(POSICION,65,11,11,0x00);
    REMOVE = 0;
    }
    FillRect(y+130, 65, 10, 11, 0x00);
  }
    
    
    

    
    LCD_Bitmap(y+190, 65, 11, 11, YELLOW);
  //  LCD_Bitmap(20, 20, 12, 8, MUERTITO);
 
    LCD_Sprite(y+110, 80, 12, 8, REDBUG,6, anim1, 0, 0);     
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO); 
    
    LCD_Sprite(y+130, 80, 12, 8, REDBUG,6, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
       
    LCD_Sprite(y+150, 80, 12, 8, REDBUG,6, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+170, 80, 12, 8, REDBUG,6, anim2, 0, 0);
//LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+190, 80, 12, 8, REDBUG,6, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(y+210, 80, 12, 8, REDBUG,6, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+90, 90, 12, 8, PURPLEBUG,6, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+110, 90, 12, 8, PURPLEBUG,6, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+130, 90, 12, 8, PURPLEBUG,6, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+150, 90, 12, 8, PURPLEBUG,6, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+170, 90, 12, 8, PURPLEBUG,6, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+190, 90, 12, 8, PURPLEBUG,6, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+210, 90, 12, 8, PURPLEBUG,6, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+230, 90, 12, 8, PURPLEBUG,6, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+70, 100, 12, 8, BICHOA,4, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+90, 100, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);

    LCD_Sprite(y+110, 100, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+130, 100, 12, 8, BICHOA,4,anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+150, 100, 12, 8, BICHOA,4, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(y+170, 100, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(y+190, 100, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+210, 100, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+230, 100, 12, 8, BICHOA,4, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+250, 100, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+70, 110, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+90, 110, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+110, 110, 12, 8, BICHOA,4, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(y+130, 110, 12, 8, BICHOA,4, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+150, 110, 12, 8, BICHOA,4, anim1, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+170, 110, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+190, 110, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+210, 110, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+230, 110, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
   
    LCD_Sprite(y+250, 110, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+70, 120, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+90, 120, 12, 8, BICHOA,4, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+110, 120, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+130, 120, 12, 8, BICHOA,4, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+150, 120, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+170, 120, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+190, 120, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+210, 120, 12, 8, BICHOA,4, anim2, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+230, 120, 12, 8, BICHOA,4, anim1, 0, 0);
   // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
    
    LCD_Sprite(y+250, 120, 12, 8, BICHOA,4, anim2, 0, 0);
    //LCD_Bitmap(y+250, 120, 12, 8, MUERTITO);
   
     
     LCD_Bitmap(x, 200, 20, 20, PLAYER1);
    // LCD_Bitmap(20, 20, 12, 8, MUERTITO);
     LCD_Bitmap(185, 200, 20, 20, PLAYER2);
   //  LCD_Bitmap(20, 20, 12, 8, MUERTITO);
     
    /*
    //LCD_Bitmap(x, 100, 32, 32, prueba);
    
    int anim = (x/11)%8;
    

    int anim3 = (x/11)%4;
    
    LCD_Sprite(x, 20, 16, 32, mario,8, anim,1, 0);
    V_line( x -1, 20, 32, 0x421b);
 
    //LCD_Sprite(x,100,32,32,bowser,4,anim3,0,1);
    //V_line( x -1, 100, 32, 0x421b);
 
 
    LCD_Sprite(x, 140, 16, 16, enemy,2, anim2,1, 0);
    V_line( x -1, 140, 16, 0x421b);
  
    LCD_Sprite(x, 175, 16, 32, luigi,8, anim,1, 0);
    V_line( x -1, 175, 32, 0x421b);
  }
  for(int x = 320-32; x >0; x--){
    delay(5);
    int anim = (x/11)%8;
    int anim2 = (x/11)%2;
    
    LCD_Sprite(x,100,16,24,planta,2,anim2,0,0);
    V_line( x + 16, 100, 24, 0x421b);
    
    //LCD_Bitmap(x, 100, 32, 32, prueba);
    
    //LCD_Sprite(x, 140, 16, 16, enemy,2, anim2,0, 0);
    //V_line( x + 16, 140, 16, 0x421b);
    
    //LCD_Sprite(x, 175, 16, 32, luigi,8, anim,0, 0);
    //V_line( x + 16, 175, 32, 0x421b);

    //LCD_Sprite(x, 20, 16, 32, mario,8, anim,0, 0);
    //V_line( x + 16, 20, 32, 0x421b);
    */
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
