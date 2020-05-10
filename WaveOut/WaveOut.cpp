#include <iostream>
#include <windows.h> 
#include <mmsystem.h> 
#include "WaveOut.h"
#include "sf2.h"

#pragma comment(lib, "winmm.lib")

HMIDIIN midi_in_handle = 0;
Channel **ppCh = 0;
CHANNEL_PARAM *ppChParam[16] = { 0 };
unsigned char **ppKeyboard = 0;
SYSTEM_VAL sysVal;

/**************************************************************/
void CALLBACK midiInProc(
    HMIDIIN midi_in_handle,
    UINT wMsg,
    DWORD dwInstance,
    DWORD dwParam1,
    DWORD dwParam2
);
void noteOn(int chNum, int noteNum, int velo);
void noteOff(int chNum, int noteNum);
void setChannels();

/**************************************************************/
void WINAPI
waveout_midiOpen(unsigned int devNum) {
    if (0 != midi_in_handle) {
        midiInReset(midi_in_handle);
        midiInStop(midi_in_handle);
        midiInClose(midi_in_handle);
        midi_in_handle = 0;
    }
    MMRESULT res = midiInOpen(&midi_in_handle, devNum, (DWORD_PTR)midiInProc, 0, CALLBACK_FUNCTION);
    if (res != MMSYSERR_NOERROR) {
        return;
    }

    auto sf2 = new SF2::SF2(
        (char*)"C:\\Users\\owner\\source\\repos\\InstPlayer\\InstPlayer\\bin\\Debug\\gm.sf2",
        (char*)"C:\\Users\\owner\\source\\repos\\InstPlayer\\InstPlayer\\bin\\Debug\\wave.dat", 
        44100);

    auto id = INST_ID();
    auto preset = sf2->GetPreset(id);
    auto range = sf2->GetRange(preset, 60, 127);

    res = midiInStart(midi_in_handle);
}

CHANNEL_PARAM** WINAPI
waveout_getChannelParamPtr() {
    setChannels();
    return ppChParam;
}

unsigned char** WINAPI
waveout_getKeyboardPtr() {
    setChannels();
    if (0 == ppKeyboard) {
        ppKeyboard = (unsigned char**)malloc(sizeof(unsigned char*) * 16);
        for (int i = 0; i < 16; i++) {
            ppKeyboard[i] = ppCh[i]->GetKeyboardPtr();
        }
    }
    return ppKeyboard;
}

/**************************************************************/
void CALLBACK
midiInProc(
    HMIDIIN midi_in_handle,
    UINT wMsg,
    DWORD dwInstance,
    DWORD dwParam1,
    DWORD dwParam2
) {
    switch (wMsg) {
    case MIM_OPEN:
        break;
    case MIM_CLOSE:
        break;
    case MIM_DATA:
    {
        if (0 == ppCh) {
            return;
        }

        unsigned char chNum = dwParam1 & 0xF;
        unsigned char type = dwParam1 & 0xF0;
        unsigned char v1 = (dwParam1 & 0xFF00) >> 8;
        unsigned char v2 = (dwParam1 & 0xFF0000) >> 16;

        switch (type) {
        case 0x80:
            noteOff(chNum, v1);
            break;
        case 0x90:
            noteOn(chNum, v1, v2);
            break;
        case 0xA0:
            break;
        case 0xB0:
            ppCh[chNum]->CtrlChg((CTRL_TYPE)v1, v2);
            break;
        case 0xC0:
            ppCh[chNum]->ProgChg(v1);
            break;
        case 0xD0:
            break;
        case 0xE0:
            ppCh[chNum]->Pitch(v1, v2);
            break;
        case 0xF0:
            break;
        default:
            break;
        }
    }
    break;
    case MIM_LONGDATA:
    case MIM_ERROR:
    case MIM_LONGERROR:
    case MIM_MOREDATA:
        break;
    default:
        break;
    }
}

void
noteOn(int chNum, int noteNum, int velo) {
    if (0 == ppCh) {
        return;
    }
    auto pKeyboard = ppCh[chNum]->mKeyboard;
    if (0 == velo) {
        noteOff(chNum, noteNum);
        return;
    }
    for (int i = 0; i < 127; i++) {
        if (i == noteNum) {
            pKeyboard[i] = 1;
            break;
        }
    }
}

void
noteOff(int chNum, int noteNum) {
    if (0 == ppKeyboard) {
        return;
    }
    auto pKeyboard = ppCh[chNum]->mKeyboard;
    for (int i = 0; i < 127; i++) {
        if (i == noteNum) {
            pKeyboard[i] = 0;
            break;
        }
    }
}

void
setChannels() {
    if (0 == ppCh) {
        ppCh = (Channel**)malloc(sizeof(Channel*) * 16);
        for (int i = 0; i < 16; i++) {
            ppCh[i] = new Channel(&sysVal, i);
        }
        for (int i = 0; i < 16; i++) {
            ppChParam[i] = ppCh[i]->GetParamPtr();
        }
    }
}