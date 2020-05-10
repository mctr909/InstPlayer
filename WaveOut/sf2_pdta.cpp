#pragma once
#include <math.h>
#include "sf2_struct.h"
#include "sf2_pdta.h"

using SF2::PDTA;

double __EnvelopeSpeed = 12.0;
double __DeltaTime = 0.0;

PDTA::PDTA(FILE *fp, DWORD size, DWORD sampleRate) : RiffChunk() {
    __DeltaTime = 1.0 / sampleRate;
    Loop(fp, size);
    SetPresetList();
    SetInstList();
}

void
PDTA::LoadChunk(FILE *fp, char *chunkType, DWORD chunkSize) {
    if (0 == strcmp(chunkType, "phdr")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_PHDR)) {
            CH_PHDR data;
            fread_s(&data, sizeof(CH_PHDR), sizeof(CH_PHDR), 1, fp);
            mPHDR.push_back(data);
        }
        return;
    }
    if (0 == strcmp(chunkType, "pbag")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_BAG)) {
            CH_BAG data;
            fread_s(&data, sizeof(CH_BAG), sizeof(CH_BAG), 1, fp);
            mPBAG.push_back(data);
        }
        return;
    }
    if (0 == strcmp(chunkType, "pmod")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_MOD)) {
            CH_MOD data;
            fread_s(&data, sizeof(CH_MOD), sizeof(CH_MOD), 1, fp);
            mPMOD.push_back(data);
        }
        return;
    }
    if (0 == strcmp(chunkType, "pgen")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_GEN)) {
            CH_GEN data;
            fread_s(&data, sizeof(CH_GEN), sizeof(CH_GEN), 1, fp);
            mPGEN.push_back(data);
        }
        return;
    }

    if (0 == strcmp(chunkType, "inst")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_INST)) {
            CH_INST data;
            fread_s(&data, sizeof(CH_INST), sizeof(CH_INST), 1, fp);
            mINST.push_back(data);
        }
        return;
    }
    if (0 == strcmp(chunkType, "ibag")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_BAG)) {
            CH_BAG data;
            fread_s(&data, sizeof(CH_BAG), sizeof(CH_BAG), 1, fp);
            mIBAG.push_back(data);
        }
        return;
    }
    if (0 == strcmp(chunkType, "imod")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_MOD)) {
            CH_MOD data;
            fread_s(&data, sizeof(CH_MOD), sizeof(CH_MOD), 1, fp);
            mIMOD.push_back(data);
        }
        return;
    }
    if (0 == strcmp(chunkType, "igen")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_GEN)) {
            CH_GEN data;
            fread_s(&data, sizeof(CH_GEN), sizeof(CH_GEN), 1, fp);
            mIGEN.push_back(data);
        }
        return;
    }

    if (0 == strcmp(chunkType, "shdr")) {
        for (int pos = 0; pos < chunkSize; pos += sizeof(CH_SHDR)) {
            CH_SHDR data;
            fread_s(&data, sizeof(CH_SHDR), sizeof(CH_SHDR), 1, fp);
            mSHDR.push_back(data);
        }
        return;
    }
}

void
PDTA::SetPresetList() {
    for (int i = 0; i < mPHDR.size(); i++) {
        auto preset = mPHDR[i];
        int bagCount;
        if (i < mPHDR.size() - 1) {
            bagCount = mPHDR[i + 1].bagIndex - preset.bagIndex;
        } else {
            bagCount = mPBAG.size() - preset.bagIndex;
        }

        auto global = LAYER();
        auto layerList = std::vector<LAYER>();
        for (int ib = 0, bagIdx = preset.bagIndex; ib < bagCount; ib++, bagIdx++) {
            if (mPBAG.size() <= bagIdx) {
                break;
            }
            auto bag = mPBAG[bagIdx];
            int genCount;
            if (bagIdx < mPBAG.size() - 1) {
                genCount = mPBAG[bagIdx + 1].genIndex - bag.genIndex;
            } else {
                genCount = mPGEN.size() - bag.genIndex;
            }
            auto v = GetPresetGen(global, bag.genIndex, genCount);
            if (v.instId < 0) {
                global = v;
            } else {
                layerList.push_back(v);
            }
        }

        auto pre = PRESET();
        pre.id.isDrum = (byte)(0 < (preset.bank & 0x80) ? 1 : 0);
        pre.id.bankMSB = (byte)(preset.bank & 0x7F);
        pre.id.progNum = (byte)preset.presetno;
        strcpy_s(pre.name, sizeof(pre.name), (const char*)preset.name);

        auto iLayerList = layerList.begin();
        for (; iLayerList < layerList.end(); iLayerList++) {
            pre.layer.push_back(*iLayerList);
        }

        mPresetList.push_back(pre);
        layerList.clear();
    }

    mPHDR.clear();
    mPBAG.clear();
    mPGEN.clear();
    mPMOD.clear();
}

void
PDTA::SetInstList() {
    for (int i = 0; i < mINST.size(); i++) {
        auto inst = mINST[i];
        int bagCount;
        if (i < mINST.size() - 1) {
            bagCount = mINST[i + 1].bagIndex - inst.bagIndex;
        } else {
            bagCount = mIBAG.size() - inst.bagIndex;
        }

        auto global = RANGE();
        auto rangeList = std::vector<RANGE>();
        for (int ib = 0, bagIdx = inst.bagIndex; ib < bagCount; ib++, bagIdx++) {
            if (mIBAG.size() <= bagIdx) {
                break;
            }
            auto bag = mIBAG[bagIdx];
            int genCount;
            if (bagIdx < mIBAG.size() - 1) {
                genCount = mIBAG[bagIdx + 1].genIndex - bag.genIndex;
            } else {
                genCount = mIGEN.size() - bag.genIndex;
            }
            auto v = GetInstGen(global, bag.genIndex, genCount);
            if (v.sampleId < 0) {
                global = v;
            } else {
                rangeList.push_back(v);
            }
        }

        auto tmp = INST();
        strcpy_s(tmp.name, sizeof(tmp.name), (const char*)inst.name);

        auto iRangeList = rangeList.begin();
        for (; iRangeList < rangeList.end(); iRangeList++) {
            tmp.range.push_back(*iRangeList);
        }

        mInstList.push_back(tmp);
        rangeList.clear();
    }

    mINST.clear();
    mIBAG.clear();
    mIGEN.clear();
    mIMOD.clear();
}

PDTA::LAYER
PDTA::GetPresetGen(LAYER global, DWORD begin, DWORD count) {
    auto v = LAYER();

    /**** initialize ****/
    {
        v.keyLo = 0;
        v.keyHi = 127;
        v.velLo = 0;
        v.velHi = 127;
        v.instId = -1;

        v.gain = 0.0;
        v.pan = 0.0;
        v.coarseTune = 0.0;
        v.fineTune = 0.0;
        v.rootKey = -1;

        v.env.deltaA = 0.0;
        v.env.deltaD = 0.0;
        v.env.levelS = -1.0;
        v.env.deltaR = 0.0;
        v.env.hold = -1.0;
    }

    /**** set value ****/
    for (int i = 0, genIdx = begin; i < count; i++, genIdx++) {
        if (mPGEN.size() <= genIdx) {
            break;
        }
        auto g = mPGEN[genIdx];

        switch (g.genOper) {
        case E_OPER::KEY_RANGE:
            v.keyLo = (byte)(g.genAmount & 0x7F);
            v.keyHi = (byte)((g.genAmount >> 8) & 0x7F);
            break;
        case E_OPER::VEL_RANGE:
            v.velLo = (byte)(g.genAmount & 0x7F);
            v.velHi = (byte)((g.genAmount >> 8) & 0x7F);
            break;
        case E_OPER::INSTRUMENT:
            v.instId = g.genAmount;
            break;

        case E_OPER::INITIAL_ATTENUATION:
            v.gain = pow(10.0, -g.genAmount / 200.0);
            break;
        case E_OPER::PAN:
            v.pan = (short)g.genAmount / 500.0;
            break;
        case E_OPER::COARSE_TUNE:
            v.coarseTune = pow(2.0, (short)g.genAmount / 120.0);
            break;
        case E_OPER::FINETUNE:
            v.fineTune = pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::OVERRIDING_ROOTKEY:
            v.rootKey = g.genAmount;
            break;

        case E_OPER::ENV_VOL__ATTACK:
            v.env.deltaA = __EnvelopeSpeed * __DeltaTime / pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::ENV_VOL__HOLD:
            v.env.hold = pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::ENV_VOL__DECAY:
            v.env.deltaD = __EnvelopeSpeed * __DeltaTime / pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::ENV_VOL__SUSTAIN:
            v.env.levelS = pow(10.0, -g.genAmount / 200.0);
            break;
        case E_OPER::ENV_VOL__RELEASE:
            v.env.deltaR = __EnvelopeSpeed * __DeltaTime / pow(2.0, (short)g.genAmount / 1200.0);
            break;

        default:
            break;
        }
    }

    /**** set global value ****/
    if (0 <= v.instId) {
        if (v.gain == 0.0) {
            v.gain = global.gain;
        }
        if (v.coarseTune == 0.0) {
            v.coarseTune = global.coarseTune;
        }
        if (v.fineTune == 0.0) {
            v.fineTune = global.fineTune;
        }
        if (v.rootKey < 0) {
            v.rootKey = global.rootKey;
        }

        if (v.env.deltaA == 0.0) {
            v.env.deltaA = global.env.deltaA;
        }
        if (v.env.deltaD == 0.0) {
            v.env.deltaD = global.env.deltaD;
        }
        if (v.env.levelS < 0.0) {
            v.env.levelS = global.env.levelS;
        }
        if (v.env.deltaR == 0.0) {
            v.env.deltaR = global.env.deltaR;
        }
        if (v.env.hold < 0.0) {
            v.env.hold = global.env.hold;
        }
    }

    /**** set default value ****/
    {
        if (v.gain == 0.0) {
            v.gain = 1.0;
        }
        if (v.coarseTune == 0.0) {
            v.coarseTune = 1.0;
        }
        if (v.fineTune == 0.0) {
            v.fineTune = 1.0;
        }

        if (v.env.deltaA == 0.0) {
            v.env.deltaA = 1000 * __DeltaTime;
        }
        if (v.env.deltaD == 0.0) {
            v.env.deltaD = 1000 * __DeltaTime;
        }
        if (v.env.levelS < 0.0) {
            v.env.levelS = 1.0;
        }
        if (v.env.deltaR == 0.0) {
            v.env.deltaR = 1000 * __DeltaTime;
        }
        if (v.env.hold < 0.0) {
            v.env.hold = 0.0;
        }
        
        v.env.hold += __EnvelopeSpeed * __DeltaTime / v.env.deltaA;
    }

    return v;
}

PDTA::RANGE
PDTA::GetInstGen(RANGE global, DWORD begin, DWORD count) {
    auto v = RANGE();

    /**** initialize ****/
    {
        v.keyLo = 0;
        v.keyHi = 127;
        v.velLo = 0;
        v.velHi = 127;
        v.sampleId = -1;

        v.gain = 0.0;
        v.pan = 0.0;
        v.coarseTune = 0.0;
        v.fineTune = 0.0;
        v.rootKey = -1;

        v.waveBegin = 0xFFFFFFFF;
        v.waveEnd = 0xFFFFFFFF;
        v.waveLoopBegin = 0xFFFFFFFF;
        v.waveLoopEnd = 0xFFFFFFFF;
        v.loopEnable = 0xFF;

        v.env.deltaA = 0.0;
        v.env.deltaD = 0.0;
        v.env.levelS = -1.0;
        v.env.deltaR = 0.0;
        v.env.hold = -1.0;
    }

    /**** set value ****/
    for (int i = 0, genIdx = begin; i < count; i++, genIdx++) {
        if (mIGEN.size() <= genIdx) {
            break;
        }
        auto g = mIGEN[genIdx];

        switch (g.genOper) {
        case E_OPER::KEY_RANGE:
            v.keyLo = (byte)(g.genAmount & 0x7F);
            v.keyHi = (byte)((g.genAmount >> 8) & 0x7F);
            break;
        case E_OPER::VEL_RANGE:
            v.velLo = (byte)(g.genAmount & 0x7F);
            v.velHi = (byte)((g.genAmount >> 8) & 0x7F);
            break;
        case E_OPER::SAMPLE_ID:
            v.sampleId = g.genAmount;
            break;

        case E_OPER::INITIAL_ATTENUATION:
            v.gain = pow(10.0, -g.genAmount / 200.0);
            break;
        case E_OPER::PAN:
            v.pan = (short)g.genAmount / 500.0;
            break;
        case E_OPER::COARSE_TUNE:
            v.coarseTune = pow(2.0, (short)g.genAmount / 120.0);
            break;
        case E_OPER::FINETUNE:
            v.fineTune = pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::OVERRIDING_ROOTKEY:
            v.rootKey = g.genAmount;
            break;

        case E_OPER::OFFSET_ADDRS__START_LSB:
            v.waveBegin |= g.genAmount;
            break;
        case E_OPER::OFFSET_ADDRS__START_MSB:
            v.waveBegin |= (DWORD)(g.genAmount << 16);
            break;
        case E_OPER::OFFSET_ADDRS__END_LSB:
            v.waveEnd |= g.genAmount;
            break;
        case E_OPER::OFFSET_ADDRS__END_MSB:
            v.waveEnd |= (DWORD)(g.genAmount << 16);
            break;

        case E_OPER::OFFSET_ADDRS__LOOP_START_LSB:
            v.waveLoopBegin |= g.genAmount;
            break;
        case E_OPER::OFFSET_ADDRS__LOOP_START_MSB:
            v.waveLoopBegin |= (DWORD)(g.genAmount << 16);
            break;
        case E_OPER::OFFSET_ADDRS__LOOP_END_LSB:
            v.waveLoopEnd |= g.genAmount;
            break;
        case E_OPER::OFFSET_ADDRS__LOOP_END_MSB:
            v.waveLoopEnd |= (DWORD)(g.genAmount << 16);
            break;
        case E_OPER::SAMPLE_MODES:
            v.loopEnable = 0 < (g.genAmount & 1);
            break;

        case E_OPER::ENV_VOL__ATTACK:
            v.env.deltaA = __EnvelopeSpeed * __DeltaTime / pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::ENV_VOL__HOLD:
            v.env.hold = pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::ENV_VOL__DECAY:
            v.env.deltaD = __EnvelopeSpeed * __DeltaTime / pow(2.0, (short)g.genAmount / 1200.0);
            break;
        case E_OPER::ENV_VOL__SUSTAIN:
            v.env.levelS = pow(10.0, -g.genAmount / 200.0);
            break;
        case E_OPER::ENV_VOL__RELEASE:
            v.env.deltaR = __EnvelopeSpeed * __DeltaTime / pow(2.0, (short)g.genAmount / 1200.0);
            break;
        default:
            break;
        }
    }

    /**** set global value ****/
    if (0 <= v.sampleId) {
        if (v.gain == 0.0) {
            v.gain = global.gain;
        }
        if (v.coarseTune == 0.0) {
            v.coarseTune = global.coarseTune;
        }
        if (v.fineTune == 0.0) {
            v.fineTune = global.fineTune;
        }
        if (v.rootKey < 0) {
            v.rootKey = global.rootKey;
        }

        if (v.waveBegin == 0xFFFFFFFF) {
            v.waveBegin = global.waveBegin;
        }
        if (v.waveEnd == 0xFFFFFFFF) {
            v.waveEnd = global.waveEnd;
        }
        if (v.waveLoopBegin == 0xFFFFFFFF) {
            v.waveLoopBegin = global.waveLoopBegin;
        }
        if (v.waveLoopEnd == 0xFFFFFFFF) {
            v.waveLoopEnd = global.waveLoopEnd;
        }
        if (v.loopEnable == 0xFF) {
            v.loopEnable = global.loopEnable;
        }

        if (v.env.deltaA <= 0.0) {
            v.env.deltaA = global.env.deltaA;
        }
        if (v.env.deltaD <= 0.0) {
            v.env.deltaD = global.env.deltaD;
        }
        if (v.env.deltaR <= 0.0) {
            v.env.deltaR = global.env.deltaR;
        }
        if (v.env.hold < 0.0) {
            v.env.hold = global.env.hold;
        }
        if (v.env.levelS < 0.0) {
            v.env.levelS = global.env.levelS;
        }
        if (0.0 < v.env.deltaA) {
            if (v.env.hold < 0.0) {
                v.env.hold = __EnvelopeSpeed * __DeltaTime / v.env.deltaA;
            } else {
                v.env.hold += __EnvelopeSpeed * __DeltaTime / v.env.deltaA;
            }
        }
    }

    return v;
}
