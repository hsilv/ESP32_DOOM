#ifndef READ_H
#define READ_H

#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>

void printDirectory(File dir, int numTabs);
void setupSD();

#endif