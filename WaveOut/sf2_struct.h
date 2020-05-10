#pragma once
#include <Windows.h>

namespace SF2 {
    enum struct E_OPER : WORD {
        OFFSET_ADDRS__START_LSB = 0,
        OFFSET_ADDRS__START_MSB = 4,
        OFFSET_ADDRS__END_LSB = 1,
        OFFSET_ADDRS__END_MSB = 12,
        OFFSET_ADDRS__LOOP_START_LSB = 2,
        OFFSET_ADDRS__LOOP_START_MSB = 45,
        OFFSET_ADDRS__LOOP_END_LSB = 3,
        OFFSET_ADDRS__LOOP_END_MSB = 50,
        //
        LFO_MOD__TO_PITCH = 5,
        LFO_MOD__TO_FILTER_FC = 10,
        LFO_MOD__TO_VOLUME = 13,
        LFO_MOD__DELAY = 21,
        LFO_MOD__FREQ = 22,
        //
        LFO_VIB__TO_PITCH = 6,
        LFO_VIB__DELAY = 23,
        LFO_VIB__FREQ = 24,
        //
        ENV_MOD__TO_PITCH = 7,
        ENV_MOD__TO_FILTER_FC = 11,
        ENV_MOD__DELAY = 25,
        ENV_MOD__ATTACK = 26,
        ENV_MOD__HOLD = 27,
        ENV_MOD__DECAY = 28,
        ENV_MOD__SUSTAIN = 29,
        ENV_MOD__RELEASE = 30,
        ENV_MOD__KEY_NUM_TO_HOLD = 31,
        ENV_MOD__KEY_NUM_TO_DECAY = 32,
        //
        ENV_VOL__DELAY = 33,
        ENV_VOL__ATTACK = 34,
        ENV_VOL__HOLD = 35,
        ENV_VOL__DECAY = 36,
        ENV_VOL__SUSTAIN = 37,
        ENV_VOL__RELEASE = 38,
        ENV_VOL__KEY_NUM_TO_HOLD = 39,
        ENV_VOL__KEY_NUM_TO_DECAY = 40,
        //
        INITIAL_FILTER__FC = 8,
        INITIAL_FILTER__Q = 9,
        //
        UNUSED1 = 14,
        CHORUS_EFFECTS_SEND = 15,
        REVERB_EFFECTS_SEND = 16,
        PAN = 17,
        UNUSED2 = 18,
        UNUSED3 = 19,
        UNUSED4 = 20,
        //
        INSTRUMENT = 41,
        RESERVED1 = 42,
        KEY_RANGE = 43,
        VEL_RANGE = 44,
        //
        KEYNUM = 46,
        VELOCITY = 47,
        INITIAL_ATTENUATION = 48,
        RESERVED2 = 49,
        //
        COARSE_TUNE = 51,
        FINETUNE = 52,
        SAMPLE_ID = 53,
        SAMPLE_MODES = 54,
        RESERVED3 = 55,
        SCALE_TUNING = 56,
        EXCLUSIVE_CLASS = 57,
        OVERRIDING_ROOTKEY = 58,
        UNUSED5 = 59,
        END_OPER = 60,
    };

#pragma pack(push, 2)
    typedef struct CH_PHDR {
        BYTE  name[20];
        WORD  presetno;
        WORD  bank;
        WORD  bagIndex;
        DWORD library;
        DWORD genre;
        DWORD morph;
    } CH_PHDR;
#pragma pack(pop)

#pragma pack(push, 2)
    typedef struct CH_INST {
        BYTE name[20];
        WORD bagIndex;
    } CH_INST;
#pragma pack(pop)

#pragma pack(push, 2)
    typedef struct CH_SHDR {
        BYTE name[20];
        DWORD start;
        DWORD end;
        DWORD loopStart;
        DWORD loopEnd;
        DWORD sampleRate;
        BYTE originalKey;
        signed char correction;
        WORD sampleLink;
        WORD type;
    } CH_SHDR;
#pragma pack(pop)

#pragma pack(push, 4)
    typedef struct CH_BAG {
        WORD genIndex;
        WORD modIndex;
    } CH_BAG;
#pragma pack(pop)

#pragma pack(push, 2)
    typedef struct CH_MOD {
        WORD   srcOper;
        E_OPER destOper;
        short  modAmount;
        WORD   amtSrcOper;
        WORD   modTransOper;
    } CH_MOD;
#pragma pack(pop)

#pragma pack(push, 4)
    typedef struct CH_GEN {
        E_OPER genOper;
        WORD   genAmount;
    } CH_GEN;
#pragma pack(pop)
};
