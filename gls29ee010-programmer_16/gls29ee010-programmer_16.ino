/*
 * Programs the 17x8 Greenliant GLS29EE010 EEPROM using an Arduino Micro and 3 74HC595 shift registers.
 *
 * The following control signals for the shift registers are hardwired to the Arduino:
 * SHIFT_DATA (SER)
 * SHIFT_CLK (SRCLK)
 * DFF_CLK (RCLK)
 * SHIFT_CLR (SRCLR#)
 *
 * The following control signals for the EEPROM are hardwired to the Arduino:
 * EEPROM_READ_EN (OE#)
 * EEPROM_WRITE_EN (WE#)
 *
 * The shift registers are used for the address. The bottom 17 outputs are used.
 * The top 7 outputs are filled with 0s but not used.
 * Shifts data into the shift registers in LSB first format.
 * The lowest bit (QH on the lowest shift register) is connected to A0 (LSB) on the EEPROM.
 * The highest bit (QH (not QA b/c only need 1 bit) on the highest shift register) is connected to A16 (MSB) on the EEPROM.
 * The highest shift register's QA through QG are not connected to anything.
 *
 * The 8 data lines are hardwired between the Arduino Micro and the EEPROM.
 * Lower Arduino pin number is used for LSB in the EEPROM.
 * Higher Arduino pin number is used for MSB in the EEPROM.
 */

#define EEPROM_D0 40 // data LSB
#define EEPROM_D7 47 // data MSB

#define SHIFT_DATA 53 // data to shift into shift register
#define SHIFT_CLK 53 // pos-edge clock for shift register
#define DFF_CLK 53 // pos-edge clock for DFF to set after filling shift register
#define SHIFT_CLR 53 // active-low async clear for shift registers

#define EEPROM_READ_EN 51 // active-low EEPROM read enable
#define EEPROM_WRITE_EN 50 // active-low EEPROM write enable

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) { delay(10); }

  // *** WRITE THE DATA ***
  pinMode(52, OUTPUT);
  digitalWrite(52, LOW);
  int i;
  for (i = 22; i <= 38; i++)
    pinMode(i, OUTPUT);
  
  setPinsToDefaultForWriting();
  Serial.print("Programming EEPROM");
  Serial.flush();

  // Write the 1st page of data
  bypassSDP();
  for (int i = 0; i < 16; i++) // the first 2-16 bytes written in each page are skipped for some reason, so write 16 useless bytes
    writeEEPROM(0, 0xFF);
  writeEEPROM(0, B01101001); // 0x69
  writeEEPROM(1, B01010101); // 0x55
  writeEEPROM(2, B10101010); // 0xAA
  writeEEPROM(3, B00001101); // 0x0D
  endWriting(); // end the page write

  // Write the 2nd page of data
  bypassSDP();
  for (int i = 0; i < 16; i++) // the first 2-16 bytes written in each page are skipped for some reason, so write 16 useless bytes
    writeEEPROM(128, 0xFF);
  writeEEPROM(128, B10010110); // 0x96
  writeEEPROM(129, B01010101); // 0x55
  writeEEPROM(130, B10101010); // 0xAA
  writeEEPROM(131, B11010000); // 0xD0
  endWriting(); // end the page write
  
  Serial.println(" Done writing");
  Serial.flush();

  // *** CHECK WHAT WAS WRITTEN ***
  setPinsToDefaultForReading();
  print256Bytes();
  Serial.println("Done reading");
  Serial.flush();
}

void loop()
{
}

/*
 * Gets past SDP by sending the appropriate 3-byte code to the appropriate addresses.
 * Does not finish the SDP write by sending EEPROM_WRITE_EN high.
 */
void bypassSDP()
{
  writeEEPROM(0x5555, 0xAA);
  writeEEPROM(0x2AAA, 0x55);
  writeEEPROM(0x5555, 0xA0);
}

/*
 * Sets all the pins for reading from the EEPROM. Don't have to manually handle EEPROM_READ_EN for reading.
 * No delay in this function.
 */
void setPinsToDefaultForReading()
{
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) // for each data pin
  {
    pinMode(pin, INPUT);
  }

  pinMode(EEPROM_READ_EN, OUTPUT);
  digitalWrite(EEPROM_READ_EN, LOW); // always read
  pinMode(EEPROM_WRITE_EN, OUTPUT);
  digitalWrite(EEPROM_WRITE_EN, HIGH);
}

/*
 * Sets all the pins for writing to the EEPROM. Still have to manually handle EEPROM_WRITE_EN for writing.
 * No delay in this function.
 */
void setPinsToDefaultForWriting()
{
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) // for each data pin
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  pinMode(EEPROM_READ_EN, OUTPUT);
  digitalWrite(EEPROM_READ_EN, HIGH);
  pinMode(EEPROM_WRITE_EN, OUTPUT);
  digitalWrite(EEPROM_WRITE_EN, HIGH);
}

/*
 * Sets the shift registers values so they contain the address. Does not clock the DFF H/L to have the shift registers output the address.
 * No delay in this function.
 *
 * Note: CALL setPinsToDefaultForReading() OR setPinsToDefaultForWriting() BEFORE CALLING THIS FUNCTION.
 * This function does not make sure the pins are set properly.
 *
 * Note 2: CALL digitalWrite(DFF_CLK, HIGH) AND digitalWrite(DFF_CLK, LOW) after calling this function.
 * Otherwise the shift registers will still be outputting the previous address.
 */
void shiftAddress(unsigned long address)
{
  // address can have 17 bits of important info, but int is only 16 bits long, so have to use long.
  // long is 32 bits.
  
  int i;
  for (i = 0; i < 17; i++)
    digitalWrite((22+i), LOW);
  for (i = 0; i < 17; i++)
    if (address & (1 << i))
      digitalWrite((22+i), HIGH);
}

/*
 * Reads from the EEPROM. No delay in this function.
 *
 * Note: MAKE SURE YOU CALL setPinsToDefaultForReading() BEFORE CALLING THIS FUNCTION.
 * This function does not make sure the pins are set properly.
 */
byte readEEPROM(unsigned long address)
{
  // Set up the address
  shiftAddress(address);
  digitalWrite(DFF_CLK, HIGH);
  digitalWrite(DFF_CLK, LOW);

  // Perform the read
  byte data = 0;
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin--) // for each data pin in reverse
  {
    data = (data << 1) + digitalRead(pin);
  }

  return data;
}

/*
 * Starts a write to the EEPROM. Does not finish it in order to let either the next writeEEPROM() call
 * or an endWriting() call finish it. No delay in this function.
 *
 * Note: MAKE SURE YOU CALL setPinsToDefaultForWriting() BEFORE CALLING THIS FUNCTION.
 * This function does not make sure the pins are set properly.
 *
 * Note 2: MAKE SURE YOU CALL endWriting() WHEN YOU ARE DONE SETTING THE DATA FOR THE PAGE WRITE.
 * Otherwise only some data will get written (probably nothing or everything except the last piece
 * you put in) and EEPROM_WRITE_EN will stay active (low).
 */
void writeEEPROM(unsigned long address, byte data)
{
  // Set up the address
  shiftAddress(address);

  // End the previous write if there was one
  digitalWrite(EEPROM_WRITE_EN, HIGH);

  // Show the new address to the EEPROM
  digitalWrite(DFF_CLK, HIGH);
  digitalWrite(DFF_CLK, LOW);
  
  // Set up the data
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) // for each data pin
  {
    digitalWrite(pin, data & 1);
    data = data >> 1;
  }

  // Start the write
  digitalWrite(EEPROM_WRITE_EN, LOW);
}

/*
 * Finishes the page write by making EEPROM_WRITE_EN go high and then waiting 20ms for the write to happen.
 * Can start writing a new page once this function is done.
 */
void endWriting()
{
  digitalWrite(EEPROM_WRITE_EN, HIGH);
  delay(20);
}

/*
 * Prints the contents of the EEPROM at the first 256 addresses. No delays in this function.
 *
 * Example output format:
 * 00000: 00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00
 * 00010: 00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00
 * ...
 *
 * Note: MAKE SURE YOU CALL setPinsToDefaultForReading() BEFORE CALLING THIS FUNCTION.
 * This function does not make sure the pins are set properly.
 */
void print256Bytes()
{
  unsigned long baseAddr;

  byte data[16];
  for (baseAddr = 0UL; baseAddr < 256UL; baseAddr += 16UL) // for every 16 addresses in the EEPROM
  {
    for (unsigned int offset = 0U; offset < 16U; offset++) // for each address within the current set of 16 addresses
    {
      data[offset] = readEEPROM(baseAddr + offset);
    }

    char buf[80];
    sprintf(buf, "%05lx: %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
      baseAddr, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10],
      data[11], data[12], data[13], data[14], data[15]);
    // the %05lx above has an L, not a one

    Serial.println(buf);
    Serial.flush();
  }
}
