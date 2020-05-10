#include "sf2.h"

SF2::SF2::SF2(char *path, char *waveFilePath, DWORD sampleRate) :
    mWaveFilePath(waveFilePath),
    mSampleRate(sampleRate),
    RiffChunk() {
    Load(path);
}

bool
SF2::SF2::CheckFileType(char *fileType, DWORD fileSize) {
    return 0 == strcmp(fileType, "sfbk");
}

void
SF2::SF2::LoadList(FILE *fp, char *listType, DWORD listSize) {
    if (0 == strcmp(listType, "pdta")) {
        mPdta = new PDTA(fp, listSize, mSampleRate);
        return;
    }
    if (0 == strcmp(listType, "sdta")) {
        mSdta = new SDTA(fp, listSize, mWaveFilePath);
        return;
    }
}

SF2::PDTA::PRESET
SF2::SF2::GetPreset(INST_ID id) {
    auto itr = mPdta->mPresetList.begin();
    for (; itr < mPdta->mPresetList.end(); itr++) {
        if (id.isDrum == itr->id.isDrum &&
            id.bankMSB == itr->id.bankMSB &&
            id.bankLSB == itr->id.bankLSB &&
            id.progNum == itr->id.progNum) {
            return *itr;
        }
    }
    for (; itr < mPdta->mPresetList.end(); itr++) {
        if (id.isDrum == itr->id.isDrum &&
            id.progNum == itr->id.progNum) {
            return *itr;
        }
    }
    for (; itr < mPdta->mPresetList.end(); itr++) {
        if (id.isDrum == itr->id.isDrum) {
            return *itr;
        }
    }
}

std::vector<SF2::PDTA::RANGE>
SF2::SF2::GetRange(PDTA::PRESET preset, BYTE noteNum, BYTE vel) {
    auto list = std::vector<PDTA::RANGE>();
    auto itrLayer = preset.layer.begin();
    for (; itrLayer < preset.layer.end(); itrLayer++) {
        if (itrLayer->keyLo <= noteNum && noteNum <= itrLayer->keyHi &&
            itrLayer->velLo <= vel && vel <= itrLayer->velHi) {
            auto inst = mPdta->mInstList[itrLayer->instId];
            auto itrRange = inst.range.begin();
            for (; itrRange < inst.range.end(); itrRange++) {
                if (itrRange->keyLo <= noteNum && noteNum <= itrRange->keyHi &&
                    itrRange->velLo <= vel && vel <= itrRange->velHi) {
                    list.push_back(*itrRange);
                }
            }
        }
    }
    return list;
}
