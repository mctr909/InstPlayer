#pragma once
#include <Windows.h>
#include "RiffChunk.h"
#include "sf2_struct.h"
#include "sf2_pdta.h"
#include "sf2_sdta.h"
#include "channel.h"

#include <vector>

class PDTA;
class SDTA;
struct SF2::PDTA::PRESET;
struct INST_ID;

namespace SF2 {
    class SF2 : RiffChunk {
    private:
        PDTA *mPdta;
        SDTA *mSdta;
        DWORD mSampleRate;
    public:
        const char *mWaveFilePath;
    public:
        SF2(char *path, char *waveFilePath, DWORD sampleRate);
    public:
        PDTA::PRESET GetPreset(INST_ID id);
        std::vector<PDTA::RANGE> GetRange(PDTA::PRESET preset, BYTE noteNum, BYTE vel);
    protected:
        bool CheckFileType(char *fileType, DWORD fileSize);
        void LoadList(FILE *fp, char *listType, DWORD listSize);
    };
}
