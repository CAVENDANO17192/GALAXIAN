
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;     // the number of the pushbutton pin
const int buttonPin3 = 4;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buzzer = 8;

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;
int buttonState3 = 0;
int x;
int melody1[] = {
 
NOTE_G7,
NOTE_FS7,       //tono repetitivo ataque
NOTE_F7


 
};
int melody2[] = {

NOTE_DS8,
NOTE_D8,
NOTE_CS8,
NOTE_C8,
NOTE_B7,
NOTE_AS7,
NOTE_A7,
NOTE_GS7,   //naves atacando
NOTE_G7,
NOTE_FS7,
NOTE_F7,
NOTE_G7,
NOTE_FS7,
NOTE_F7,
NOTE_G7,
NOTE_FS7,
NOTE_F7,
NOTE_G7,
NOTE_FS7,
NOTE_F7,
NOTE_G7,
NOTE_FS7,
NOTE_F7


 
};
int melody3[] = {

NOTE_A6  ,
 NOTE_AS6 ,           //naves muriendo
 NOTE_B6

};
int melody4[] = {

NOTE_A5,
 NOTE_AS5,       // disparos 
 NOTE_B5
 
};
int melody5[] = {

 NOTE_C8,
 NOTE_CS7,
 NOTE_DS6,
 NOTE_FS4,
 NOTE_DS6,
 NOTE_FS4,      // jugador muere
 NOTE_DS6,
 NOTE_FS4,
 NOTE_F4,
 NOTE_E4,
 NOTE_E4
 

 
};

// The note duration, 8 = 8th note, 4 = quarter note, etc.
int durations1[] = {
  20,20,20  // naves muriendo
 
  };

  int durations2[] = {
  
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15 // naves atacando
  
  };
  int durations3[] = {
 
  15,10,20 // disparos 
  
  };
  int durations4[] = {
  
  8,8,8,5,8,5,8,5,7,7,7 //jugador muere
  };
// determine the length of the arrays to use in the loop iteration
int songLength1 = sizeof(melody1)/sizeof(melody1[0]);
int songLength2 = sizeof(melody2)/sizeof(melody2[0]);
int songLength3 = sizeof(melody3)/sizeof(melody3[0]);
int songLength4 = sizeof(melody4)/sizeof(melody4[0]);
int songLength5 = sizeof(melody5)/sizeof(melody5[0]);



void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //-------------------------------------------------------------------------------------------------------------1 TONO REPETITIVO DE ATAQUE
  if (buttonState1 == HIGH & buttonState2 == LOW &buttonState3 == LOW & x == 0) {
    digitalWrite(buzzer,LOW);
    x = 1;
    // turn LED on:
      for (int thisNote = 0; thisNote < songLength1; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations1[thisNote];
    tone(8, melody1[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(8);
  }
    digitalWrite(ledPin, HIGH);
  } 

  //--------------------------------------------------------------------------------------------------------------2 NAVES ATACANDO 
    if (buttonState1 == LOW & buttonState2 == HIGH & buttonState3 == LOW & x == 0) {
    digitalWrite(buzzer,LOW);
    x = 1;
    // turn LED on:
      for (int thisNote = 0; thisNote < songLength2; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations2[thisNote];
    tone(8, melody2[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(8);
  }
    digitalWrite(ledPin, HIGH);
  } 
  //------------------------------------------------------------------------------------------------------------------3 NAVES MURIENDO 
      if (buttonState1 == HIGH & buttonState2 == HIGH & buttonState3 == LOW & x == 0) {
    digitalWrite(buzzer,LOW);
    x = 1;
    // turn LED on:
      for (int thisNote = 0; thisNote < songLength3; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations1[thisNote];
    tone(8, melody3[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(8);
  }
    digitalWrite(ledPin, HIGH);
  }

    //------------------------------------------------------------------------------------------------------------------4 DISPAROS 
      if (buttonState1 == LOW & buttonState2 == LOW & buttonState3 == HIGH & x == 0) {
    digitalWrite(buzzer,LOW);
    x = 1;
    // turn LED on:
      for (int thisNote = 0; thisNote < songLength4; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations3[thisNote];
    tone(8, melody4[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(8);
  }
    digitalWrite(ledPin, HIGH);
  }

    //------------------------------------------------------------------------------------------------------------------5 JUGADOR MUERE 
      if (buttonState1 == HIGH & buttonState2 == LOW & buttonState3 == HIGH & x == 0) {
    digitalWrite(buzzer,LOW);
    x = 1;
    // turn LED on:
      for (int thisNote = 0; thisNote < songLength5; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations4[thisNote];
    tone(8, melody5[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(8);
  }
    digitalWrite(ledPin, HIGH);
  }

  //--------------------------------------------------------------------------------------------------------------------------

   if(buttonState1 == LOW & buttonState2 == LOW & buttonState2 == LOW & x == 1) {
    // turn LED off:
    x = 0;
    digitalWrite(ledPin, LOW);
     noTone(8);
     digitalWrite(buzzer,HIGH);
  }
}
