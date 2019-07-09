// Mnemonic_decoder.h

#include "vm_include.h"

#ifndef __MNEMONICDECODER__
#define __MNEMONICDECODER__

namespace mpu
{
  class Mnemonic_Decoder
  {
  private:
	  std::map < std::string, int > intelligence;
	  std::map < std::string, int > label_location;  
	  std::vector<int>:: iterator hex_iter;
    int decode_for_hex (std::map < std::string, int >&_intelligence, std::string word);

  public:
      Mnemonic_Decoder ();
     ~Mnemonic_Decoder ()
    {
    };

     std::vector < int >hex_vector;
    void decode (std::vector < std::string >, int);

  };
}

#endif /* __MNEMONICDECODER__ */
