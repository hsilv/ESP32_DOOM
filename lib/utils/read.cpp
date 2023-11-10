#include "read.h"

void printDirectory(File dir, int numTabs)
{
    while (true)
    {

        File entry = dir.openNextFile();
        if (!entry)
        {
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            Serial.print('\t');
        }
        Serial.print(entry.name());
        if (entry.isDirectory())
        {
            Serial.println("/");
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            Serial.print("\t\tBytes: ");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}

void setupSD()
{
    digitalWrite(15, HIGH);
    digitalWrite(5, HIGH);

    if (!SD.begin(5))
    {
        Serial.println("Montaje de Tarjeta SD Fallido");
        return;
    }
   uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No has insertado ninguna Tarjeta SD");
        return;
    }

    Serial.print("Tipo de Tarjeta SD: ");
    if (cardType == CARD_MMC)
    {
        Serial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
        Serial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    }
    else
    {
        Serial.println("FORMATO DE TARJETA DESCONOCIDO");
    }
 
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("Tamaño de Tarjeta SD: %lluMB\n", cardSize);

    Serial.println("Inicialización de SD completa!"); 

    File root = SD.open("/");

    printDirectory(root, 0);

    Serial.println("Hecho! :D");

    root.close();
    
}