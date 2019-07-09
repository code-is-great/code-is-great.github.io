// PARSER.H
#include "vm_include.h"
#include "mnemonic_decoder.h"
#include "ram.h"
#include "reg16bit.h"

#ifndef __PARSER__
#define __PARSER__

namespace mpu
{
  class Parser
  {
  private:
    Reg16Bit *pc;
    std::vector < std::string > all_words;

    void get_word (std::string);
    void get_text (std::string);

    Mnemonic_Decoder * decoder;
    Ram *memory;
  public:
      Parser ()
    {
    };
     ~Parser ()
    {
    };
    void read (std::string, int);
    void set_ram (Ram * _memory);
    void set_decoder (Mnemonic_Decoder * _decoder);
    void set_pc (Reg16Bit * _pc);

  };
}

#endif /* __PARSER__ */
