#pragma once
#include "RiffChunk.h"
#include "sf2_struct.h"

#include <vector>

struct CH_PHDR;
struct CH_INST;
struct CH_SHDR;
struct CH_BAG;
struct CH_MOD;
struct CH_GEN;

namespace SF2 {
    class PDTA : RiffChunk {
    public:
        typedef struct INST_ID {
            BYTE isDrum;
            BYTE progNum;
            BYTE bankMSB;
            BYTE bankLSB;
        } INST_ID;

        typedef struct ENVELOPE {
            double deltaA;
            double deltaD;
            double deltaR;
            double levelS;
            double hold;
        } ENVELOPE;

        typedef struct LAYER {
            BYTE   keyLo;
            BYTE   keyHi;
            BYTE   velLo;
            BYTE   velHi;
            int    instId;
            int    rootKey;
            double gain;
            double pan;
            double coarseTune;
            double fineTune;
            ENVELOPE env;
        } LAYER;

        typedef struct RANGE {
            BYTE   keyLo;
            BYTE   keyHi;
            BYTE   velLo;
            BYTE   velHi;
            int    sampleId;
            int    rootKey;
            BYTE   loopEnable;
            DWORD  waveBegin;
            DWORD  waveEnd;
            DWORD  waveLoopBegin;
            DWORD  waveLoopEnd;
            double gain;
            double pan;
            double coarseTune;
            double fineTune;
            ENVELOPE env;
        } RANGE;

        typedef struct PRESET {
            INST_ID id;
            char name[20];
            std::vector<LAYER> layer;
        } PRESET;

        typedef struct INST {
            char name[20];
            std::vector<RANGE> range;
        } INST;

    public:
        std::vector<PRESET> mPresetList;
        std::vector<INST> mInstList;

    private:
        std::vector<CH_PHDR> mPHDR;
        std::vector<CH_BAG> mPBAG;
        std::vector<CH_MOD> mPMOD;
        std::vector<CH_GEN> mPGEN;
        std::vector<CH_INST> mINST;
        std::vector<CH_BAG> mIBAG;
        std::vector<CH_MOD> mIMOD;
        std::vector<CH_GEN> mIGEN;
        std::vector<CH_SHDR> mSHDR;

    public:
        PDTA(FILE *fp, DWORD size, DWORD sampleRate);

    private:
        void SetPresetList();
        void SetInstList();
        LAYER GetPresetGen(LAYER global, DWORD begin, DWORD count);
        RANGE GetInstGen(RANGE global, DWORD begin, DWORD count);

    protected:
        void LoadChunk(FILE *fp, char *chunkType, DWORD chunkSize) override;
    };
}
