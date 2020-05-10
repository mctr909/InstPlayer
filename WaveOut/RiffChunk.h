#pragma once
#include <stdio.h>
#include <Windows.h>

class RiffChunk {
protected:
    RiffChunk() {}
    RiffChunk(FILE *fp, DWORD size);

protected:
    void Load(char *path);

protected:
    virtual bool CheckFileType(char *type, DWORD size) { return false; }
    virtual void LoadChunk(FILE *fp, char *chunkType, DWORD size) {}
    virtual void LoadList(FILE *fp, char *listType, DWORD size) {}
    virtual void LoadInfo(FILE *fp, char *infoType, DWORD size) {}

protected:
    void Loop(FILE *fp, DWORD size);

private:
    void infoLoop(FILE *fp, DWORD size);
};
