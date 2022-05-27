/*
 * FortunaGenerator.cpp
 *
 *  Created on: 20.04.2011
 *      Author: chkarg
 */

#include <iostream>
#include <fstream>
#include "filters.h"
#include "sha.h"
#include "aes.h"
#include "modes.h"
#include "hex.h"
#include "files.h"
#include "FortunaGenerator.h"

using namespace std;

FortunaGenerator::FortunaGenerator() {
	for (int i = 0; i < sizeof(key); i++) {
		key[i] = 0;
	}

	for (int i = 0; i < sizeof(cntr); i++) {
		cntr[i] = 0;
	}
	seeded = false;
	last_reseed=0;
}

bool FortunaGenerator::incCntr() {
    if((last_reseed + 1) >= sizeof(cntr)) {
        //cntr[] = cntr[ ]; keine Ahnung an welcher stelle
        return true;
    }
    return false;
}

void FortunaGenerator::reseed(byte* seed, unsigned int size) {
    byte skey[sizeof(key) + size];
    for (int i = 0; i < sizeof(key); ++i) {
        skey[i] = key[i];
        if(i < size){
            skey[sizeof(key + i)] = seed[i];
        }
    }
    SHA256 hash;
    ArraySource(skey, true ,new HashFilter(hash,//dem Filter HashFilter wird zur berechnung der Prüfsumme eine geeignete Hashfunktion übergeben
                                               new ArraySink(key, 32)));
    this->incCntr();
}  //keine Ahnung ob das stimmt

bool FortunaGenerator::getBit() {
    //s = s*s mod n, return s mod 2
}

byte FortunaGenerator::getByte() {
}

void FortunaGenerator::generateBlocks(byte* buffer, unsigned int n) {
    if(cntr == 0)
    {
        //PRNG wurde nicht korrekt initialisiert
    }
    else //if(seeded == false && (getTimeStamp() - last_reseed) > 500) eventuell die abfrage für g
    {
        byte r[16 * n];
        for (int i = 0; i < n; i++) {
            CTR_Mode<AES>::Decryption ctr_dec;//Betriebsmodus des Kryptosystems AES auf Entschlüsselung
            ArraySource(key, true,
                         new HexDecoder(new ArraySink(r, 16)));
        }
    }
}
            //???????????????????????
void FortunaGenerator::getBlock(byte* buffer, unsigned int n) {
    for (int i = 0; i < n; ++i) {
        buffer[i] = this->getByte();
    }
}

uint32_t FortunaGenerator::getTimeStamp() const {
	struct timeval  tv;

	gettimeofday(&tv,NULL);
	return tv.tv_sec*1000 + tv.tv_usec/1000;
}

