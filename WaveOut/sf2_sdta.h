#pragma once
#include "RiffChunk.h"
#include "sf2_struct.h"

namespace SF2 {
    class SDTA : RiffChunk {
    private:
        const char *mWaveFilePath;
    public:
        SDTA(FILE *fp, DWORD size, const char *waveFilePath) : mWaveFilePath(waveFilePath), RiffChunk() {
            Loop(fp, size);
        }
    protected:
        void LoadChunk(FILE *fp, char *chunkType, DWORD chunkSize) override {
            if (0 == strcmp(chunkType, "smpl")) {
                FILE *fpData = NULL;
                fopen_s(&fpData, mWaveFilePath, "wb");
                BYTE tmp[4096];
                DWORD pos = 0;
                while (pos < chunkSize - sizeof(tmp)) {
                    fread_s(&tmp, sizeof(tmp), sizeof(tmp), 1, fp);
                    fwrite(&tmp, sizeof(tmp), 1, fpData);
                    pos += sizeof(tmp);
                }
                auto restSize = (int)chunkSize - (int)pos;
                if (0 < restSize) {
                    fread_s(&tmp, restSize, restSize, 1, fp);
                    fwrite(&tmp, restSize, 1, fpData);
                }
                fclose(fpData);
            }
        }
    };
};
