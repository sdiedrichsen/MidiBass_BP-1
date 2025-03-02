

#define NUM_NOTES 13
#define READ_PIN 14
#define BASIC_NOTE 36

char state[13];

void setup()  
{
   for(int n = 0; n < NUM_NOTES; n++)
   {
      pinMode(n, OUTPUT);
      state[n] = 0;
   }
   
   pinMode(READ_PIN, INPUT_PULLDOWN);   
   pinMode(LED_BUILTIN, OUTPUT);

   digitalWrite(LED_BUILTIN, HIGH);
}

void loop() 
{
   for(int n = 0; n < NUM_NOTES; n++)
   {
      digitalWrite(n, HIGH);
      int reading1 = digitalRead(READ_PIN);
      delay(1);
      int reading2 = digitalRead(READ_PIN);

      if(reading1 == reading2)
      {
         if((state[n] == 0) && (reading2 > 0)) 
         {
            usbMIDI.sendNoteOn(BASIC_NOTE + n, 96, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
            state[n] = 1;
            digitalWrite(LED_BUILTIN, HIGH);
         }
         else
         if((state[n] == 1) && (reading2 == 0))
         {
            usbMIDI.sendNoteOff(BASIC_NOTE + n, 0, 1);     // Stop the note
            state[n] = 0;
            digitalWrite(LED_BUILTIN, LOW);
         }
      }
      digitalWrite(n, LOW);
   }
   // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
  }
}
