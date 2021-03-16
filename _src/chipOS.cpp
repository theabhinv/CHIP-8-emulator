#include "chipOS.h"

File* ChipOS::currentFile = NULL;
std::fstream* ChipOS::disk = new std::fstream();

ChipOS::ChipOS()
{
    disk->open(FilePath, std::ios::in | std::ios::out | std::ios::binary);
   
    if(!disk->is_open())
    {
        std::cout << "COULD NOT FIND DISK DRIVE :" << FilePath << std::endl;
        std::cout << "CREATING DISK DRIVE :" << FilePath << std::endl;
    
        disk->open(FilePath, std::ios::out | std::ios::binary);
    
        std::cout << "CREATING START SIGNATURE" << std::endl;
    
        disk->write(&StartSignature[0], 16);
    
        std::cout << "START SIGNATURE CREATED" << std::endl;
        std::cout << "CREATING EMPTY FILESPACE " << std::endl;
    
        disk->seekp(DISK_SIZE - 16);
    
        std::cout << "EMPTY FILESPACE CREATED" << std::endl;
        std::cout << "CREATING END SIGNATURE" << std::endl;
    
        disk->write(&EndSignature[0], 16);
    
        std::cout << "END SIGNATURE CREATED" << std::endl;
        std::cout << FilePath << " HAS BEEN CREATED" << std::endl;

        File f;
        f.fileName = "src";
        f.parent = &f;
    
        std::cout << sizeof(f) << std::endl;
        
        disk->seekp(16);
        disk->write((char *)&f, sizeof(f));
        disk->close();
        disk->open(FilePath, std::ios::in | std::ios::out | std::ios::binary);
    }

    std::cout << "DISK LOADED" << std::endl;
        

    char StartSig[16];
    char EndSig[16];
    File f;
    disk->seekg(0);
    disk->read(&StartSig[0], 16);
    disk->read((char*)&f, sizeof(f));  
    currentFile = &f;    
    disk->seekg(DISK_SIZE - 16);
    disk->read(&EndSig[0], 16);

    int i = 0;
    for(i = 0; i < 16; i++)
    {
        if((StartSignature[i] != StartSig[i]) || (EndSignature[i] != EndSig[i]))
            break;  
    }
    delete StartSig;
    delete EndSig;

    if(i == 16)
    {
        std::cout << "SIGNATURE MATCHED" << std::endl;
    }
    else
    {
        std::cout << "SIGNATURE DID NOT MATCH" << std::endl;
        std::cout << "PLEASE DELETE " << FilePath << " AND RESTART THE APPLICATION"<< std::endl;
        std::cin.get();
        return;
    }

    disk->seekg(16);
    
    isRunning = true;
    Cycle();
}

void ChipOS::Cycle()
{
    system("cls");
    while(isRunning)
    {
        std::cout << currentFile->fileName << " >> ";
        std::string input;
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){return std::tolower(c);});
        std::vector<std::string> args;
        std::string word;
        std::stringstream s(input);
        while(std::getline(s, word, ' '))
        {
            args.push_back(word);
        }
        if(args[0] == "quit")
        {
            isRunning = false;
        }
        else if(args[0] == "clear")
        {
            system("cls");
        }
        else if(args[0] == "run")
        {
            if(args.size() < 2)
            {
                std::cout << "'run' TAKES TWO ARGUMENTS" << std::endl;
                continue;
            }
            Run(args[1]);
        }
        else
        {
            std::cout << "COMMAND NOT FOUND: " << args[0] << std::endl;
        }
    }
}

void ChipOS::Run(std::string filename)
{
    Chip8* chip8 = new Chip8();
    delete chip8;
}
ChipOS::~ChipOS()
{

}