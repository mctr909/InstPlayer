#pragma once

typedef struct SYSTEM_VAL {
    unsigned char *pWaveData;
    unsigned char *pInstData;
    int buffLength;
    int buffCount;
    int sampleRate;
    double deltaTime;
} SYSTEM_VAL;

#pragma pack(push, 4)
typedef struct INST_ID {
    unsigned char isDrum;
    unsigned char progNum;
    unsigned char bankMSB;
    unsigned char bankLSB;
} INST_ID;
#pragma pack(pop)

#pragma pack(push, 4)
typedef struct CHANNEL_PARAM {
    INST_ID id;

    unsigned char vol;
    unsigned char exp;
    unsigned char pan;
    unsigned char rev;

    unsigned char cho;
    unsigned char del;
    unsigned char fq;
    unsigned char fc;

    unsigned char mod;
    unsigned char reserved;
    unsigned char attack;
    unsigned char release;

    unsigned char hold;
    unsigned char rpnMsb;
    unsigned char rpnLsb;
    unsigned char bendRange;

    int pitch;
} CHANNEL_PARAM;
#pragma pack(pop)

enum struct CTRL_TYPE {
    BANK_MSB = 0,
    MODURATION = 1,
    POLTA_TIME = 5,
    VOL = 7,
    PAN = 10,
    EXP = 11,
    BANK_LSB = 32,
    DATA = 38,
    HOLD = 64,
    POLTA_SW = 65,
    SOSTENUTO = 66,
    RESO = 71,
    RELEASE = 72,
    ATTACK = 73,
    CUTOFF = 74,
    REV = 91,
    CHO = 93,
    DEL = 94,
    RPN_LSB = 98,
    RPN_MSB = 99,
    ALL_RESET = 121
};

class Channel {
private:
    SYSTEM_VAL *mpSysVal = 0;
    CHANNEL_PARAM mParam;

    double *mpDelTapL = 0;
    double *mpDelTapR = 0;
    double mDelSend;
    double mDelTime;
    double mDelIndex;
    double mChoLfoU;
    double mChoLfoV;
    double mChoLfoW;
    double mChoRate;
    double mChoSend;
    double mAmp;
    double mPanL;
    double mPanR;

public:
    int mNum;
    double mPitch;
    double *mpWave = 0;
    unsigned char mKeyboard[128] = { 0 };

public:
    Channel(SYSTEM_VAL *pSysVal, int num);
    ~Channel();

public:
    CHANNEL_PARAM *GetParamPtr() { AllReset(); return &mParam; }
    unsigned char *GetKeyboardPtr() { return &mKeyboard[0]; }

    void AllReset();
    void Pitch(unsigned char lsb, unsigned char msb);
    void CtrlChg(CTRL_TYPE type, unsigned char val);
    void ProgChg(unsigned char val);

    inline void Output();
};
