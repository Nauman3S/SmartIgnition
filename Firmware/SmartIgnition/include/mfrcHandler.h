#include <SPI.h>
#include <MFRC522.h>
void readingData();
void setupRFID();
void loopRFID();
void printHex(byte *buffer, byte bufferSize);
void printDec(byte *buffer, byte bufferSize);
void readNUID();
String NUIDV = "";

#define SIZE_BUFFER 18
#define MAX_SIZE_BLOCK 16

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
volatile bool bNewInt = false;
byte regVal = 0x7F;
byte nuidPICC[4];

/**
 * Initialize.
 */
void setupRFID()
{

    SPI.begin(); // Init SPI bus

    mfrc522.PCD_Init(); // Init MFRC522 card

    /* read and printout the MFRC522 version (valid values 0x91 & 0x92)*/
    Serial.print(F("Ver: 0x"));
    byte readReg = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
    Serial.println(readReg, HEX);
    Serial.println(F("End setup"));
}

/**
 * Main loop.
 */
void loopRFID()
{
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }
    // Select a card
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }
    // Dump debug info about the card; PICC_HaltA() is automatically called
    //  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));</p><p>  //call menu function and retrieve the desired option
    readingData();
    // int op = menu();

    // if (op == 0)
    // {
    //     readingData();
    // }
    // else if (op == 1)
    // {
    //     //writingData()
    // }
    // else
    // {
    //     Serial.println(F("Incorrect Option!"));
    //     return;
    // }

    //instructs the PICC when in the ACTIVE state to go to a "STOP" state
    mfrc522.PICC_HaltA();
    // "stop" the encryption of the PCD, it must be called after communication with authentication, otherwise new communications can not be initiated
    mfrc522.PCD_StopCrypto1();
}
void readingData()
{
    //prints the technical details of the card/tag
    mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));

    //prepare the key - all keys are set to FFFFFFFFFFFFh
    for (byte i = 0; i < 6; i++)
        key.keyByte[i] = 0xFF;

    //buffer for read data
    byte buffer[SIZE_BUFFER] = {0};

    //the block to operate
    byte block = 4;
    byte size = SIZE_BUFFER;
    //</ p><p>                                                                                             //authenticates the block to operate
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));

        return;
    }

    //read data from block
    status = mfrc522.MIFARE_Read(block, buffer, &size);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));

        return;
    }
    else
    {
    }
    readNUID();
    Serial.print(F("\nData from block ["));
    Serial.print(block);
    Serial.print(F("]: "));

    //prints read data
    for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++)
    {
        Serial.write(buffer[i]);
    }
    Serial.println(" ");
}
void printHex(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], DEC);
    }
}

void readNUID()
{
    NUIDV = "";
    for (byte i = 0; i < 4; i++)
    {
        nuidPICC[i] = mfrc522.uid.uidByte[i];
        NUIDV += String(nuidPICC[i]);
    }

    beepNow(2);
    Serial.print(F("NUID Detected: "));
    Serial.println(NUIDV);
    Serial.println();

    if (checkAccess(NUIDV))
    {
        redArmedLed = JLed(LED_R).Off().DelayBefore(500);   //red led off
        greenLed = JLed(LED_BUILTIN).On().DelayBefore(500); //green led on
        lastCardAllowed=true;
    }
    else
    {
        redArmedLed = JLed(LED_R).Blink(1000, 1000).Repeat(1);
        beepNow(1);
        redArmedLed = JLed(LED_R).Blink(1000, 1000).Forever();
    }
}