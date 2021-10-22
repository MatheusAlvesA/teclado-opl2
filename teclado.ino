#include "OPL2/OPL2.cpp"
#include "OPL2/midi_instruments.h"

#define SIG_VER "mte:1.0" // Assinatura da versão dessa biblioteca

OPL2 opl2;

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

void setAllChannelsDecay(byte val) {
  opl2.setDecay(0, 1, val);
  opl2.setDecay(1, 1, val);
  opl2.setDecay(2, 1, val);
  opl2.setDecay(3, 1, val);
  opl2.setDecay(4, 1, val);
  opl2.setDecay(5, 1, val);
  opl2.setDecay(6, 1, val);
  opl2.setDecay(7, 1, val);
  opl2.setDecay(8, 1, val);
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
  Serial.begin(9600);

  opl2.init();
  Instrument piano = opl2.loadInstrument(INSTRUMENT_PIANO1);      // Load a piano instrument.
  setAllChannelsInstrument(piano);
  setAllChannelsVolume(0x00);
}

void loop() {
  while(!Serial.available());
  String cmd = Serial.readStringUntil(';');

  unsigned int splitPoint = 0;
  while(cmd[splitPoint] != ':' && splitPoint < cmd.length()) {
    splitPoint++;
  }
  if(splitPoint >= cmd.length()) {
    return; // Não foi possível ler o comando
  }
  String cmdName = cmd.substring(0, splitPoint);
  String cmdParam = cmd.substring(splitPoint+1);

  if(cmdName.equals("ver")) {
      Serial.print(SIG_VER);
      return;
  }

  if(cmdName.equals("ping")) {
      Serial.print("pong");
      return;
  }

  if(cmdName.equals("volume")) {
      int v = cmdParam.toInt();
      v = constrain(v, 0, 100);
      int vNormalized = ((float(v)/100)*63);

      setAllChannelsVolume(63-vNormalized);
      return;
  }

  if(cmdName.equals("attack")) {
      int v = cmdParam.toInt();
      v = constrain(v, 0, 15);

      setAllChannelsAttack(15-v);
      return;
  }

  if(cmdName.equals("decay")) {
      int v = cmdParam.toInt();
      v = constrain(v, 0, 15);

      setAllChannelsDecay(15-v);
      return;
  }

  if(cmdName.equals("sustain")) {
      int v = cmdParam.toInt();
      v = constrain(v, 0, 15);

      setAllChannelsSustain(15-v);
      return;
  }

  if(cmdName.equals("release")) {
      int v = cmdParam.toInt();
      v = constrain(v, 0, 15);

      setAllChannelsRelease(15-v);
      return;
  }

  if(cmdName.equals("playNote")) {
      unsigned int splitPoint = 0;
      while(cmdParam[splitPoint] != '_' && splitPoint < cmdParam.length()) {
        splitPoint++;
      }
      if(splitPoint >= cmdParam.length()) {
        return; // Não foi possível ler o comando
      }
      int channel = cmdParam.substring(0, splitPoint).toInt();
      int note = cmdParam.substring(splitPoint+1).toInt();
      if(note < 0) {
        note = 0;
      }

      int octave = note / 12;
      note = note % 12;

      channel = constrain(channel, 0, 8);
      opl2.playNote(channel, octave, note);
      return;
  }

  if(cmdName.equals("playNoteVel")) {
      unsigned int splitPoint = 0;
      while(cmdParam[splitPoint] != '_' && splitPoint < cmdParam.length()) {
        splitPoint++;
      }
      if(splitPoint >= cmdParam.length()) {
        return; // Não foi possível ler o comando
      }
      int channel = cmdParam.substring(0, splitPoint).toInt();

      splitPoint++;
      unsigned int secondSplitPoint = splitPoint;
      while(cmdParam[secondSplitPoint] != '_' && secondSplitPoint < cmdParam.length()) {
        secondSplitPoint++;
      }
      if(secondSplitPoint >= cmdParam.length()) {
        return; // Não foi possível ler o comando
      }
      int note = cmdParam.substring(splitPoint, secondSplitPoint).toInt();
      int vel = cmdParam.substring(secondSplitPoint+1).toInt();
      if(note < 0) {
        note = 0;
      }

      int octave = note / 12;
      note = note % 12;

      channel = constrain(channel, 0, 8);
      vel = 63-constrain(vel, 0, 63);

      opl2.setVolume(channel, 0, vel);
      opl2.setVolume(channel, 1, vel);
      opl2.playNote(channel, octave, note);
      return;
  }

  if(cmdName.equals("releaseNote")) {
      int channel = cmdParam.toInt();
      channel = constrain(channel, 0, 8);
      opl2.setKeyOn(channel, false);
      return;
  }

  if(cmdName.equals("instrument")) {
      int v = cmdParam.toInt();

      switch(v) {
        case 0:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_PIANO1));
          break;
       case 1:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_PIANO2));
          break;
       case 2:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_TINKLBEL));
          break;
       case 3:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_CELESTA));
          break;

        default:
          setAllChannelsInstrument(opl2.loadInstrument(INSTRUMENT_PIANO1));
      }
      return;
  }

  if(cmdName.equals("instrument_midi")) {
      unsigned int splitPoint = 0;
      while(cmdParam[splitPoint] != '_' && splitPoint < cmdParam.length()) {
        splitPoint++;
      }
      if(splitPoint >= cmdParam.length()) {
        return; // Não foi possível ler o comando
      }
      int channel = cmdParam.substring(0, splitPoint).toInt();
      channel = constrain(channel, 0, 8);
      int inst = cmdParam.substring(splitPoint+1).toInt();
      inst = constrain(inst, 0, 127);

      opl2.setInstrument(channel, opl2.loadInstrument(midiInstruments[inst]));
      return;
  }

}
