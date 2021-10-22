#include "OPL2/OPL2.cpp"
#include "OPL2/instruments.h"
#include "teclado_read/teclado_read.cpp"

#define ENVELOP_FLAG_NONE 0
#define ENVELOP_FLAG_ATTACK 1
#define ENVELOP_FLAG_SUSTAIN 2
#define ENVELOP_FLAG_RELEASE 3

OPL2 opl2;
uint64_t hitKeysMap = 0x0;
uint8_t volume = MAX_OPL_VOL;
uint8_t attack = MAX_OPL_ENV;
uint8_t sustain = MAX_OPL_ENV;
uint8_t release = MAX_OPL_ENV;
uint8_t envelopFlag = 0x0;
uint8_t octave = 4;

int8_t channels[OPL2_NUM_CHANNELS] = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; // 9 Canais livres


void setAllChannelsInstrument(Instrument i) {
  opl2.setInstrument(0, i);
  opl2.setInstrument(1, i);
  opl2.setInstrument(2, i);
  opl2.setInstrument(3, i);
  opl2.setInstrument(4, i);
  opl2.setInstrument(5, i);
  opl2.setInstrument(6, i);
  opl2.setInstrument(7, i);
  opl2.setInstrument(8, i);
}

void setAllChannelsVolume(byte vol) {
  opl2.setVolume(0, 1, vol);
  opl2.setVolume(1, 1, vol);
  opl2.setVolume(2, 1, vol);
  opl2.setVolume(3, 1, vol);
  opl2.setVolume(4, 1, vol);
  opl2.setVolume(5, 1, vol);
  opl2.setVolume(6, 1, vol);
  opl2.setVolume(7, 1, vol);
  opl2.setVolume(8, 1, vol);
}

void setAllChannelsAttack(byte val) {
  opl2.setAttack(0, 1, val);
  opl2.setAttack(1, 1, val);
  opl2.setAttack(2, 1, val);
  opl2.setAttack(3, 1, val);
  opl2.setAttack(4, 1, val);
  opl2.setAttack(5, 1, val);
  opl2.setAttack(6, 1, val);
  opl2.setAttack(7, 1, val);
  opl2.setAttack(8, 1, val);
}


void setAllChannelsSustain(byte val) {
  opl2.setSustain(0, 1, val);
  opl2.setSustain(1, 1, val);
  opl2.setSustain(2, 1, val);
  opl2.setSustain(3, 1, val);
  opl2.setSustain(4, 1, val);
  opl2.setSustain(5, 1, val);
  opl2.setSustain(6, 1, val);
  opl2.setSustain(7, 1, val);
  opl2.setSustain(8, 1, val);
}

void setAllChannelsRelease(byte val) {
  opl2.setRelease(0, 1, val);
  opl2.setRelease(1, 1, val);
  opl2.setRelease(2, 1, val);
  opl2.setRelease(3, 1, val);
  opl2.setRelease(4, 1, val);
  opl2.setRelease(5, 1, val);
  opl2.setRelease(6, 1, val);
  opl2.setRelease(7, 1, val);
  opl2.setRelease(8, 1, val);
}


void setup() {
  initTecladoPins();

  opl2.init();
  Instrument piano = opl2.loadInstrument(INSTRUMENT_PIANO1);
  setAllChannelsInstrument(piano);
  setAllChannelsVolume(0x00);
}

void loop() {
  updateKeysPressed();


  for(uint8_t i = 0; i < sizeBufferKeysPressed; i++) {
    key_t tecla = bufferKeysPressed[i];

    if((hitKeysMap & (1ULL << tecla)) == 0) {                         // A tecla antes estava solta e agora foi apertada

      switch(tecla) {
        case KEY_VOL_PLUS:
          if(volume < MAX_OPL_VOL) {
            volume++;
          }
          setAllChannelsVolume(MAX_OPL_VOL-volume);
          break;
        case KEY_VOL_MINUS:                                        // Diminuir volume
          if(volume > 0) {
            volume--;
          }
          setAllChannelsVolume(MAX_OPL_VOL-volume);
          break;
        case KEY_RED_0:                                            // Editar Attack
          envelopFlag = ENVELOP_FLAG_ATTACK;
          break;
        case KEY_RED_1:                                            // Editar Sustain
          envelopFlag = ENVELOP_FLAG_SUSTAIN;
          break;
        case KEY_RED_2:                                            // Editar Release
          envelopFlag = ENVELOP_FLAG_RELEASE;
          break;
        case KEY_RED_3:                                            // Editar Oitavo
          envelopFlag = ENVELOP_FLAG_NONE;
          break;
        case KEY_TEMPO_PLUS:                                       // Aumentar algum envelope ou o oitavo
          switch(envelopFlag) {
            case ENVELOP_FLAG_ATTACK:
              if(attack < MAX_OPL_ENV) {
                attack++;
              }
              setAllChannelsAttack(MAX_OPL_ENV-attack);
              break;
            case ENVELOP_FLAG_SUSTAIN:
              if(sustain < MAX_OPL_ENV) {
                sustain++;
              }
              setAllChannelsSustain(MAX_OPL_ENV-sustain);
              break;
            case ENVELOP_FLAG_RELEASE:
              if(release < MAX_OPL_ENV) {
                release++;
              }
              setAllChannelsRelease(MAX_OPL_ENV-release);
              break;
            case ENVELOP_FLAG_NONE:
              // O teclado cobre 3 oitavos
              if(octave <= NUM_OCTAVES-3) {
                octave++;
              }
              break;
          }
          break;
        case KEY_TEMPO_MINUS:                                     // Diminuir algum envelope ou o oitavo
          switch(envelopFlag) {
            case ENVELOP_FLAG_ATTACK:
              if(attack > 0) {
                attack--;
              }
              setAllChannelsAttack(MAX_OPL_ENV-attack);
              break;
            case ENVELOP_FLAG_SUSTAIN:
              if(sustain > 0) {
                sustain--;
              }
              setAllChannelsSustain(MAX_OPL_ENV-sustain);
              break;
            case ENVELOP_FLAG_RELEASE:
              if(release > 0) {
                release--;
              }
              setAllChannelsRelease(MAX_OPL_ENV-release);
              break;
            case ENVELOP_FLAG_NONE:
              if(octave > 0) {
                octave--;
              }
              break;
          }
          break;
        case KEY_PIANO:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_PIANO1));
          break;
        case KEY_ORGAN:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_ORGAN1));
          break;
        case KEY_VIOLIN:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_VIOLIN1));
          break;
        case KEY_TRUMPET:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_TRUMPET1));
          break;
        case KEY_MANDOLIN:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_CELESTA));
          break;
        case KEY_BELL:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_BELLS));
          break;
        case KEY_MUSIC_BOX:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_PIANOBEL));
          break;
        case KEY_GUITAR:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_GUITAR1));
          break;
        case KEY_SLOW_ROCK:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_BASS1));
          break;
        case KEY_ROCK:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_ELGUIT1));
          break;
        case KEY_NEW:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_TRIANGLE));
          break;
        case KEY_DISCO:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_WAVE));
          break;
        case KEY_MARCH:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_MARIMBA1));
          break;
        case KEY_WALTZ:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_ACCORDN));
          break;
        case KEY_SAMBA:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_POPBASS1));
          break;
        case KEY_BLUES:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_SNAKEFL));
          break;
        case KEY_0 ... KEY_36:
          int shiftOctave = tecla / 12;
          int note = tecla % 12;
          bool found = false;
          for(uint8_t i = 0; i < OPL2_NUM_CHANNELS && !found; i++) {
            if(channels[i] == -1) {
              opl2.playNote(i, octave+shiftOctave, note);
              channels[i] = tecla;
              found = true;
            }
          }
          break;
      } // Switch tecla
    } // if tecla não estava apertada
  } // for cada tecla apertada


  for(key_t tecla = KEY_0; tecla <= KEY_36; tecla = (key_t)(tecla + 1)) {
    bool found = false;
    for(uint8_t i = 0; i < sizeBufferKeysPressed && !found; i++) {
      if(bufferKeysPressed[i] == tecla) {
        found = true;
      }
    }

    if(
      !found &&                 // A tecla não está apertada agora
      hitKeysMap & (1ULL << tecla) // Mas estava antes
    ) {
      bool foundChannel = false;
      for(uint8_t i = 0; i < OPL2_NUM_CHANNELS && !foundChannel; i++) {
        if(channels[i] == tecla) {
          channels[i] = -1;
          opl2.setKeyOn(i, false);
          foundChannel = true;
        }
      }
    }
  }


  hitKeysMap = 0x0;
  for(uint8_t i = 0; i < sizeBufferKeysPressed; i++) {
    hitKeysMap |= 1ULL << bufferKeysPressed[i];
  }
}
