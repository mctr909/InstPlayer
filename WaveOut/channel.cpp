#include <stdlib.h>
#include <math.h>
#include "channel.h"

Channel::Channel(SYSTEM_VAL *pSysVal, int num) {
    int buffSize = sizeof(double)*pSysVal->buffLength;
    mpSysVal = pSysVal;
    mNum = num;
    mpWave = (double*)malloc(buffSize);
    mpDelTapL = (double*)malloc(buffSize);
    mpDelTapR = (double*)malloc(buffSize);
}

Channel::~Channel() {
    free(mpWave);
    free(mpDelTapL);
    free(mpDelTapR);
}

void
Channel::AllReset() {
    mParam.vol = 100;
    mParam.exp = 100;
    mParam.pan = 64;
    mAmp = 100 / 127.0 * 100 / 127.0;
    mPanL = 1.0;
    mPanR = 1.0;

    mParam.rev = 0;
    mParam.cho = 0;
    mParam.del = 0;
    mChoSend = 0.0;
    mChoRate = 0.2 * mpSysVal->deltaTime;
    mDelSend = 0.0;
    mDelTime = 0;

    mParam.fc = 64;
    mParam.fq = 64;
    mParam.mod = 0;

    mParam.bendRange = 2;
    mParam.pitch = 0;
    mPitch = 1.0;

    mParam.rpnLsb = 255;
    mParam.rpnMsb = 255;
}

void
Channel::Pitch(unsigned char lsb, unsigned char msb) {
    mParam.pitch = (msb << 7) | lsb - 8192;
    mPitch = pow(2.0, mParam.bendRange * mParam.pitch / 98304.0);
}

void
Channel::CtrlChg(CTRL_TYPE type, unsigned char val) {
    switch (type) {
    case CTRL_TYPE::BANK_LSB:
        mParam.id.bankLSB = val;
        break;
    case CTRL_TYPE::BANK_MSB:
        mParam.id.bankMSB = val;
        break;

    case CTRL_TYPE::VOL:
        mParam.vol = val;
        mAmp = mParam.vol / 127.0 * mParam.exp / 127.0;
        break;
    case CTRL_TYPE::EXP:
        mParam.exp = val;
        mAmp = mParam.vol / 127.0 * mParam.exp / 127.0;
        break;
    case CTRL_TYPE::PAN:
        mParam.pan = val;
        mPanL = 1.0;
        mPanR = 1.0;
        break;

    case CTRL_TYPE::REV:
        mParam.rev = val;
        break;
    case CTRL_TYPE::CHO:
        mParam.cho = val;
        break;
    case CTRL_TYPE::DEL:
        mParam.del = val;
        break;

    case CTRL_TYPE::CUTOFF:
        mParam.fc = val;
        break;
    case CTRL_TYPE::RESO:
        mParam.fq = val;
        break;
    case CTRL_TYPE::MODURATION:
        mParam.mod = val;
        break;

    case CTRL_TYPE::RPN_LSB:
        mParam.rpnLsb = val;
        break;
    case CTRL_TYPE::RPN_MSB:
        mParam.rpnMsb = val;
        break;
    case CTRL_TYPE::DATA:
        if (mParam.rpnLsb == 0 && mParam.rpnMsb == 0) {
            mParam.bendRange = val;
        }
        break;

    default:
        break;
    }
}

void
Channel::ProgChg(unsigned char val) {
    mParam.id.progNum = val;
}

inline void
Channel::Output() {

}
