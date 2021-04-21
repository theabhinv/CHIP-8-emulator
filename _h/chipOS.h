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
    File* children[21]{};
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
        static std::fstream* disk;
        bool isRunning;

        size_t METADATA_CURRENT;
        size_t DATA_CURRENT;

    public:
        ChipOS();
        ~ChipOS();       
        void Cycle();

        void Run(std::string filename); // run
        void ShowDirectory(); // sd
        void MoveDirectory(std::string destination); // md
        void LoadFile(std::string filename); // load 
        void MoveFile(std::string filename, std::string destination); // mf
        void EditFile(std::string filename); // ef
        void DeleteFile(std::string filename); // rm
        void RenameFile(std::string filename, std::string newname); // rn
        void DefragDisk(); // defrag
        void Initialize();
        void CheckFreeSize();
        void Shutdown();

        char* getFileData(File* f);
};

#endif