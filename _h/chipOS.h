#ifndef CHIP_OS
#define CHIP_OS

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "chip8.h"

struct File
{
    File* parent;
    File* children[21];
    
    char* fileName;
    size_t position;
    size_t size;
};

class ChipOS
{
    private:
        //static ChipOS* Instance;
        const size_t DISK_SIZE = 1 * 1024 * 1024;
        const size_t DATA_STARTING = 0x2720;
        const char* StartSignature = "AbhiShubbzCereal";
        const char* EndSignature   = "LaerecZbbuhsIhba";
        const std::string FilePath = "DiskDrive.fat";
        static File* currentFile;
        static File* allFiles[100];
        static std::fstream* disk;
        bool isRunning;
    public:
        ChipOS();
        ~ChipOS();       
        void Cycle();

        void Run(std::string filename);
        void ShowDirectory();
        void MoveDirectory(std::string destination);
        void MoveFile(std::string filename, std::string destination);
        void EditFile(std::string filename);
        void DeleteFile(std::string filename);
        void RenameFile(std::string filename, std::string newname);
        void DefragDisk();
        void ParseInstruction(std::string line);
        void Initialize();
        void CheckFreeSize();
        void Shutdown();

        char* getFileData(File* f);
};

#endif