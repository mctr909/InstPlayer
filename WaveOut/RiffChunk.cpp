#include <stdio.h>
#include <stdlib.h>
#include "RiffChunk.h"

RiffChunk::RiffChunk(FILE *fp, DWORD size) {
    Loop(fp, size);
}

void RiffChunk::Load(char *path) {
    FILE *fp = NULL;
    fopen_s(&fp, path, "rb");
    fseek(fp, 0, SEEK_SET);

    char riffId[5] = { 0 };
    DWORD riffSize;
    char fileType[5] = { 0 };
    fread_s(&riffId, 4, 4, 1, fp);
    fread_s(&riffSize, sizeof(riffSize), sizeof(riffSize), 1, fp);
    fread_s(&fileType, 4, 4, 1, fp);

    if (0 == strcmp("RIFF", (const char*)&riffId) && CheckFileType(fileType, riffSize)) {
        Loop(fp, riffSize - 4);
    }

    fclose(fp);
}

void RiffChunk::Loop(FILE *fp, DWORD size) {
    DWORD pos = 0;
    while (pos < size) {
        char chunkType[5] = { 0 };
        DWORD chunkSize;
        fread_s(&chunkType, 4, 4, 1, fp);
        fread_s(&chunkSize, sizeof(chunkSize), sizeof(chunkSize), 1, fp);

        pos += 8;
        if (0 == chunkSize) {
            break;
        }

        if (0 == strcmp("LIST", chunkType)) {
            char listType[5] = { 0 };
            fread_s(&listType, 4, 4, 1, fp);
            if (0 == strcmp("INFO", listType)) {
                infoLoop(fp, chunkSize - 4);
            } else {
                fpos_t filePos;
                fgetpos(fp, &filePos);
                LoadList(fp, listType, chunkSize - 4);
                fseek(fp, filePos + chunkSize - 4, SEEK_SET);
            }
        } else {
            fpos_t filePos;
            fgetpos(fp, &filePos);
            LoadChunk(fp, chunkType, chunkSize);
            fseek(fp, filePos + chunkSize, SEEK_SET);
        }

        pos += chunkSize;
    }
}

void RiffChunk::infoLoop(FILE *fp, DWORD size) {
    DWORD pos = 0;
    while (pos < size) {
        char infoType[5] = { 0 };
        DWORD infoSize;
        fread_s(&infoType, 4, 4, 1, fp);
        fread_s(&infoSize, sizeof(infoSize), sizeof(infoSize), 1, fp);

        pos += 8;
        if (0 == infoSize) {
            break;
        }

        fpos_t filePos;
        fgetpos(fp, &filePos);
        LoadInfo(fp, infoType, infoSize);
        fseek(fp, filePos + infoSize, SEEK_SET);

        infoSize += (DWORD)(infoSize % 2 == 0 ? 0 : 1);
        pos += infoSize;
    }
}
