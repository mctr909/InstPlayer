#pragma once
#include <windows.h>
#include "channel.h"

#ifdef __cplusplus
extern "C" {
#endif
    __declspec(dllexport) void WINAPI waveout_midiOpen(unsigned int devNum);
    __declspec(dllexport) CHANNEL_PARAM** WINAPI waveout_getChannelParamPtr();
    __declspec(dllexport) unsigned char** WINAPI waveout_getKeyboardPtr();
#ifdef __cplusplus
}
#endif
