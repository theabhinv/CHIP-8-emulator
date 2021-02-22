#include "chip8.h"

int main(int argc, char* argv[])
{
  Chip8* chip = new Chip8();
  delete chip;
  return 0;
}