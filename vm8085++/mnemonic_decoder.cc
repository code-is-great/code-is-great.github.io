#include"mnemonic_decoder.h"

using namespace mpu;

#ifdef __MNEMONICDECODER__

Mnemonic_Decoder::Mnemonic_Decoder ()
{
// MAP which contains intelligence to convert mnemonics to hex

  intelligence[std::string ("ACI")] = 0xCE;
  intelligence[std::string ("ADCA")] = 0x8F;
  intelligence[std::string ("ADCB")] = 0x88;
  intelligence[std::string ("ADCC")] = 0x89;
  intelligence[std::string ("ADCD")] = 0x8A;
  intelligence[std::string ("ADCE")] = 0x8B;
  intelligence[std::string ("ADCH")] = 0x8C;
  intelligence[std::string ("ADCL")] = 0x8D;
  intelligence[std::string ("ADCM")] = 0x8E;
  intelligence[std::string ("ADDA")] = 0x87;
  intelligence[std::string ("ADDB")] = 0x80;
  intelligence[std::string ("ADDC")] = 0x81;
  intelligence[std::string ("ADDD")] = 0x82;
  intelligence[std::string ("ADDE")] = 0x83;
  intelligence[std::string ("ADDH")] = 0x84;
  intelligence[std::string ("ADDL")] = 0x85;
  intelligence[std::string ("ADDM")] = 0x86;
  intelligence[std::string ("ADI")] = 0xC6;
  intelligence[std::string ("ANAA")] = 0xA7;
  intelligence[std::string ("ANAB")] = 0xA0;
  intelligence[std::string ("ANAC")] = 0xA1;
  intelligence[std::string ("ANAD")] = 0xA2;
  intelligence[std::string ("ANAE")] = 0xA3;
  intelligence[std::string ("ANAH")] = 0xA4;
  intelligence[std::string ("ANAL")] = 0xA5;
  intelligence[std::string ("ANAM")] = 0xA6;
  intelligence[std::string ("ANI")] = 0xE6;
  intelligence[std::string ("CALL")] = 0xCD;
  intelligence[std::string ("CC")] = 0xDC;
  intelligence[std::string ("CM")] = 0xFC;
  intelligence[std::string ("CMA")] = 0x2F;
  intelligence[std::string ("CMC")] = 0x3F;
  intelligence[std::string ("CMPA")] = 0xBF;
  intelligence[std::string ("CMPB")] = 0xB8;
  intelligence[std::string ("CMPC")] = 0xB9;
  intelligence[std::string ("CMPD")] = 0xBA;
  intelligence[std::string ("CMPE")] = 0xBB;
  intelligence[std::string ("CMPH")] = 0xBC;
  intelligence[std::string ("CMPL")] = 0xBD;
  intelligence[std::string ("CMPM")] = 0xBE;
  intelligence[std::string ("CNC")] = 0xD4;
  intelligence[std::string ("CNZ")] = 0xC4;
  intelligence[std::string ("CP")] = 0xF4;
  intelligence[std::string ("CPE")] = 0xEC;
  intelligence[std::string ("CPI")] = 0xFE;
  intelligence[std::string ("CPO")] = 0xE4;
  intelligence[std::string ("CZ")] = 0xCC;
  intelligence[std::string ("DAA")] = 0x27;
  intelligence[std::string ("DADB")] = 0x09;
  intelligence[std::string ("DADD")] = 0x19;
  intelligence[std::string ("DADH")] = 0x29;
  intelligence[std::string ("DADSP")] = 0x39;
  intelligence[std::string ("DCRA")] = 0x3D;
  intelligence[std::string ("DCRB")] = 0x05;
  intelligence[std::string ("DCRC")] = 0x0D;
  intelligence[std::string ("DCRD")] = 0x15;
  intelligence[std::string ("DCRE")] = 0x1D;
  intelligence[std::string ("DCRH")] = 0x25;
  intelligence[std::string ("DCRL")] = 0x2D;
  intelligence[std::string ("DCRM")] = 0x35;
  intelligence[std::string ("DCXB")] = 0x0B;
  intelligence[std::string ("DCXD")] = 0x1B;
  intelligence[std::string ("DCXH")] = 0x2B;
  intelligence[std::string ("DCXSP")] = 0x3B;
  intelligence[std::string ("DI")] = 0xF3;
  intelligence[std::string ("EI")] = 0xFB;
  intelligence[std::string ("HLT")] = 0x76;
  intelligence[std::string ("IN")] = 0xDB;
  intelligence[std::string ("INRA")] = 0x3C;
  intelligence[std::string ("INRB")] = 0x04;
  intelligence[std::string ("INRC")] = 0x0C;
  intelligence[std::string ("INRD")] = 0x14;
  intelligence[std::string ("INRE")] = 0x1C;
  intelligence[std::string ("INRH")] = 0x24;
  intelligence[std::string ("INRL")] = 0x2C;
  intelligence[std::string ("INRM")] = 0x34;
  intelligence[std::string ("INXB")] = 0x03;
  intelligence[std::string ("INXD")] = 0x13;
  intelligence[std::string ("INXH")] = 0x23;
  intelligence[std::string ("INXSP")] = 0x33;
  intelligence[std::string ("JC")] = 0xDA;
  intelligence[std::string ("JM")] = 0xFA;
  intelligence[std::string ("JMP")] = 0xC3;
  intelligence[std::string ("JNC")] = 0xD2;
  intelligence[std::string ("JNZ")] = 0xC2;
  intelligence[std::string ("JP")] = 0xF2;
  intelligence[std::string ("JPE")] = 0xEA;
  intelligence[std::string ("JPO")] = 0xE2;
  intelligence[std::string ("JZ")] = 0xCA;
  intelligence[std::string ("LDA")] = 0x3A;
  intelligence[std::string ("LDAXB")] = 0x0A;
  intelligence[std::string ("LDAXD")] = 0x1A;
  intelligence[std::string ("LHLD")] = 0x2A;
  intelligence[std::string ("LXIB")] = 0x01;
  intelligence[std::string ("LXID")] = 0x11;
  intelligence[std::string ("LXIH")] = 0x21;
  intelligence[std::string ("LXISP")] = 0x31;
  intelligence[std::string ("MOVAA")] = 0x7F;
  intelligence[std::string ("MOVAB")] = 0x78;
  intelligence[std::string ("MOVAC")] = 0x79;
  intelligence[std::string ("MOVAD")] = 0x7A;
  intelligence[std::string ("MOVAE")] = 0x7B;
  intelligence[std::string ("MOVAH")] = 0x7C;
  intelligence[std::string ("MOVAL")] = 0x7D;
  intelligence[std::string ("MOVAM")] = 0x7E;
  intelligence[std::string ("MOVBA")] = 0x47;
  intelligence[std::string ("MOVBB")] = 0x40;
  intelligence[std::string ("MOVBC")] = 0x41;
  intelligence[std::string ("MOVBD")] = 0x42;
  intelligence[std::string ("MOVBE")] = 0x43;
  intelligence[std::string ("MOVBH")] = 0x44;
  intelligence[std::string ("MOVBL")] = 0x45;
  intelligence[std::string ("MOVBM")] = 0x46;
  intelligence[std::string ("MOVCA")] = 0x4F;
  intelligence[std::string ("MOVCB")] = 0x48;
  intelligence[std::string ("MOVCC")] = 0x49;
  intelligence[std::string ("MOVCD")] = 0x4A;
  intelligence[std::string ("MOVCE")] = 0x4B;
  intelligence[std::string ("MOVCH")] = 0x4C;
  intelligence[std::string ("MOVCL")] = 0x4D;
  intelligence[std::string ("MOVCM")] = 0x4E;
  intelligence[std::string ("MOVDA")] = 0x57;
  intelligence[std::string ("MOVDB")] = 0x50;
  intelligence[std::string ("MOVDC")] = 0x51;
  intelligence[std::string ("MOVDD")] = 0x52;
  intelligence[std::string ("MOVDE")] = 0x53;
  intelligence[std::string ("MOVDH")] = 0x54;
  intelligence[std::string ("MOVDL")] = 0x55;
  intelligence[std::string ("MOVDM")] = 0x56;
  intelligence[std::string ("MOVEA")] = 0x5F;
  intelligence[std::string ("MOVEB")] = 0x58;
  intelligence[std::string ("MOVEC")] = 0x59;
  intelligence[std::string ("MOVED")] = 0x5A;
  intelligence[std::string ("MOVEE")] = 0x5B;
  intelligence[std::string ("MOVEH")] = 0x5C;
  intelligence[std::string ("MOVEL")] = 0x5D;
  intelligence[std::string ("MOVEM")] = 0x5E;
  intelligence[std::string ("MOVHA")] = 0x67;
  intelligence[std::string ("MOVHB")] = 0x60;
  intelligence[std::string ("MOVHC")] = 0x61;
  intelligence[std::string ("MOVHD")] = 0x62;
  intelligence[std::string ("MOVHE")] = 0x63;
  intelligence[std::string ("MOVHH")] = 0x64;
  intelligence[std::string ("MOVHL")] = 0x65;
  intelligence[std::string ("MOVHM")] = 0x66;
  intelligence[std::string ("MOVLA")] = 0x6F;
  intelligence[std::string ("MOVLB")] = 0x68;
  intelligence[std::string ("MOVLC")] = 0x69;
  intelligence[std::string ("MOVLD")] = 0x6A;
  intelligence[std::string ("MOVLE")] = 0x6B;
  intelligence[std::string ("MOVLH")] = 0x6C;
  intelligence[std::string ("MOVLL")] = 0x6D;
  intelligence[std::string ("MOVLM")] = 0x6E;
  intelligence[std::string ("MOVMA")] = 0x77;
  intelligence[std::string ("MOVMB")] = 0x70;
  intelligence[std::string ("MOVMC")] = 0x71;
  intelligence[std::string ("MOVMD")] = 0x72;
  intelligence[std::string ("MOVME")] = 0x73;
  intelligence[std::string ("MOVMH")] = 0x74;
  intelligence[std::string ("MOVML")] = 0x75;
  intelligence[std::string ("MVIA")] = 0x3E;
  intelligence[std::string ("MVIB")] = 0x06;
  intelligence[std::string ("MVIC")] = 0x0E;
  intelligence[std::string ("MVID")] = 0x16;
  intelligence[std::string ("MVIE")] = 0x1E;
  intelligence[std::string ("MVIH")] = 0x26;
  intelligence[std::string ("MVIL")] = 0x2E;
  intelligence[std::string ("MVIM")] = 0x36;
  intelligence[std::string ("NOP")] = 0x00;
  intelligence[std::string ("ORAA")] = 0xB7;
  intelligence[std::string ("ORAB")] = 0xB0;
  intelligence[std::string ("ORAC")] = 0xB1;
  intelligence[std::string ("ORAD")] = 0xB2;
  intelligence[std::string ("ORAE")] = 0xB3;
  intelligence[std::string ("ORAH")] = 0xB4;
  intelligence[std::string ("ORAL")] = 0xB5;
  intelligence[std::string ("ORAM")] = 0xB6;
  intelligence[std::string ("ORI")] = 0xF6;
  intelligence[std::string ("OUT")] = 0xD3;
  intelligence[std::string ("PCHL")] = 0xE9;
  intelligence[std::string ("POPB")] = 0xC1;
  intelligence[std::string ("POPD")] = 0xD1;
  intelligence[std::string ("POPH")] = 0xE1;
  intelligence[std::string ("POPPSW")] = 0xF1;
  intelligence[std::string ("PUSHB")] = 0xC5;
  intelligence[std::string ("PUSHD")] = 0xD5;
  intelligence[std::string ("PUSHH")] = 0xE5;
  intelligence[std::string ("PUSHPSW")] = 0xF5;
  intelligence[std::string ("RAL")] = 0x17;
  intelligence[std::string ("RAR")] = 0x1F;
  intelligence[std::string ("RC")] = 0xD8;
  intelligence[std::string ("RET")] = 0xC9;
  intelligence[std::string ("RIM")] = 0x20;
  intelligence[std::string ("RLC")] = 0x07;
  intelligence[std::string ("RM")] = 0xF8;
  intelligence[std::string ("RNC")] = 0xD0;
  intelligence[std::string ("RNZ")] = 0xC0;
  intelligence[std::string ("RP")] = 0xF0;
  intelligence[std::string ("RPE")] = 0xE8;
  intelligence[std::string ("RPO")] = 0xE0;
  intelligence[std::string ("RRC")] = 0x0F;
  intelligence[std::string ("RST0")] = 0xC7;
  intelligence[std::string ("RST1")] = 0xCF;
  intelligence[std::string ("RST2")] = 0xD7;
  intelligence[std::string ("RST3")] = 0xDF;
  intelligence[std::string ("RST4")] = 0xE7;
  intelligence[std::string ("RST5")] = 0xEF;
  intelligence[std::string ("RST6")] = 0xF7;
  intelligence[std::string ("RST7")] = 0xFF;
  intelligence[std::string ("RZ")] = 0xC8;
  intelligence[std::string ("SBBA")] = 0x9F;
  intelligence[std::string ("SBBB")] = 0x98;
  intelligence[std::string ("SBBC")] = 0x99;
  intelligence[std::string ("SBBD")] = 0x9A;
  intelligence[std::string ("SBBE")] = 0x9B;
  intelligence[std::string ("SBBH")] = 0x9C;
  intelligence[std::string ("SBBL")] = 0x9D;
  intelligence[std::string ("SBBM")] = 0x9E;
  intelligence[std::string ("SBI")] = 0xDE;
  intelligence[std::string ("SHLD")] = 0x22;
  intelligence[std::string ("SIM")] = 0x30;
  intelligence[std::string ("SPHL")] = 0xF9;
  intelligence[std::string ("STA")] = 0x32;
  intelligence[std::string ("STAXB")] = 0x02;
  intelligence[std::string ("STAXD")] = 0x12;
  intelligence[std::string ("STC")] = 0x37;
  intelligence[std::string ("SUBA")] = 0x97;
  intelligence[std::string ("SUBB")] = 0x90;
  intelligence[std::string ("SUBC")] = 0x91;
  intelligence[std::string ("SUBD")] = 0x92;
  intelligence[std::string ("SUBE")] = 0x93;
  intelligence[std::string ("SUBH")] = 0x94;
  intelligence[std::string ("SUBL")] = 0x95;
  intelligence[std::string ("SUBM")] = 0x96;
  intelligence[std::string ("SUI")] = 0xD6;
  intelligence[std::string ("XCHG")] = 0xEB;
  intelligence[std::string ("XRAA")] = 0xAF;
  intelligence[std::string ("XRAB")] = 0xA8;
  intelligence[std::string ("XRAC")] = 0xA9;
  intelligence[std::string ("XRAD")] = 0xAA;
  intelligence[std::string ("XRAE")] = 0xAB;
  intelligence[std::string ("XRAH")] = 0xAC;
  intelligence[std::string ("XRAL")] = 0xAD;
  intelligence[std::string ("XRAM")] = 0xAE;
  intelligence[std::string ("XRI")] = 0xEE;
  intelligence[std::string ("XTHL")] = 0xE3;


//cout<<"MAP and Sets initialized\n";

}

// Function to convert string input to hex using Map intelligence

int
Mnemonic_Decoder::
decode_for_hex (std::map < std::string, int >&_intelligence, std::string word)
{
	std::map < std::string, int >::iterator it;
  it = _intelligence.find (word);

  return (*it).second;

}

void
Mnemonic_Decoder::decode (std::vector < std::string > mnemonic_vector, int addr)
{
// set of all mnemonics in which only one word is required for decoding to hex

	std::set < std::string > one_word_decoder;

  static std::string str1[27] =
    { "CMA", "CMC", "DAA", "DI", "EJ", "HLT", "NOP", "PCHL", "RAL", "RAR", "RC",
    "RET", "RIM", "RLC", "RM", "RNC", "RNZ", "RP", "RPE", "RPO", "RRC", "RZ",
    "SIM", "SPHL", "STC", "XCHG", "XTHL" };

  copy (str1, str1 + 27,
	inserter (one_word_decoder, one_word_decoder.begin ()));

//cout<<"One_word_decoder initialized\n";


// set of all mnemonics in which one word is required for decoding and next word
// is an 8 bit memory word

  std::set < std::string > one_word_decoder_extra_8bit;

  static std::string str2[10] =
    { "ACI", "ADI", "ANI", "CPI", "IN", "SBI", "SUI", "XRI", "ORI", "OUT" };

  copy (str2, str2 + 10,
	inserter (one_word_decoder_extra_8bit,
		  one_word_decoder_extra_8bit.begin ()));

//cout<<"one_word_decoder_extra_8bit initialized\n";

// set of all mnemonics in which one  word is required for decoding and next word
// is a 16 bit memory word


  std::set < std::string > one_word_decoder_extra_16bit;

  static std::string str3[22] =
    { "CALL", "CC", "CM", "CNC", "CNZ", "CP", "CPE", "CPO", "CZ", "JC", "JM",
    "JMP", "JNC", "JNZ", "JP", "JPE", "JPO", "JZ", "LDA", "LHLD", "SHLD",
    "STA"
  };

  copy (str3, str3 + 22,
	inserter (one_word_decoder_extra_16bit,
		  one_word_decoder_extra_16bit.begin ()));


//cout<< "one_word_decoder_extra_16bit initialized\n";

// set of all Jump Mnemonics

  std::set<std::string> jumps;

static std::string jump[9]={"JMP","JC","JNC","JP","JM","JPE","JPO","JZ","JNZ"};

copy (jump, jump+9, inserter(jumps, jumps.begin()));


// set of all call mnemonics

std::set<std::string> calls;

static std::string call[9] = {"CALL", "CC", "CNC", "CP", "CM", "CPE", "CPO",
			"CZ", "CNZ"};

copy (call, call+9, inserter(calls, calls.begin()));

// set of all mnemonics in which two words are required for decoding

std::set < std::string > two_word_decoder;

  static std::string str4[18] =
    { "ADC", "ADD", "ANA", "CMP", "DAD", "DCR", "DCX", "INR", "INX", "LDAX",
    "ORA", "POP", "PUSH", "RST", "SBB", "STAX", "SUB", "XRA"
  };

  copy (str4, str4 + 18,
	inserter (two_word_decoder, two_word_decoder.begin ()));

//cout<<"two_word_decoder initialized\n";

// set of all mnemonics in which two words are required for decoding and the
// third word is an 8 bit memory word

  std::set < std::string > two_word_decoder_extra_8bit;

  static std::string str5[1] = { "MVI" };

  copy (str5, str5 + 1,
	inserter (two_word_decoder_extra_8bit,
		  two_word_decoder_extra_8bit.begin ()));

//cout<<"two_word_decoder_extra_8bit initialized\n";


// set of all mnemonics in which two words are required for decoding and the
// third word is a 16 bit memory word

  std::set < std::string > two_word_decoder_extra_16bit;

  static std::string str6[1] = { "LXI" };

  copy (str6, str6 + 1,
	inserter (two_word_decoder_extra_16bit,
		  two_word_decoder_extra_16bit.begin ()));

//cout<<"two_word_decoder_extra_16bit initialized\n";

// set of all mnemonics in which three words are required for decoding

  std::set < std::string > three_word_decoder;

  static std::string str7[1] = { "MOV" };

  copy (str7, str7 + 1,
	inserter (three_word_decoder, three_word_decoder.begin ()));

//cout<<"Three_word_decoder initialized\n";

  std::vector < std::string >::iterator iter = mnemonic_vector.begin ();
  std::string word;
  int hexword;
  std::map<std::string,  int > :: iterator lbl_iter;

  for (; iter != mnemonic_vector.end (); iter++)
    {
      word = *iter;

      if (one_word_decoder.count (word))
	{

	  hexword = decode_for_hex (intelligence, word);
	  hex_vector.push_back (hexword);
	  continue; 
	}
      if (one_word_decoder_extra_8bit.count (word))
	{

	  hexword = decode_for_hex (intelligence, word);
	  hex_vector.push_back (hexword);
	  iter++;
	  word = *iter;
	  hexword = 0xFF & (int)strtol(word.c_str (), 0, 16);
	  hex_vector.push_back (hexword);
	  continue; 
	}
      if (one_word_decoder_extra_16bit.count (word))
	{

	  hexword = decode_for_hex (intelligence, word);
	  hex_vector.push_back (hexword);
	  if((jumps.count(word)) || (calls.count(word)))
	  {
	  	iter++;
		word=*iter;
		if(label_location.count(word))
		{
      	  		lbl_iter = label_location.find(word);
      	  		int hex1, hex2, position;

      	  		position=(*lbl_iter).second;
	  		hex1=position+addr;
	  		hex2=hex1 & 255;
			hex_vector.push_back(hex2);
	  		hex1>>=8;
	  		hex1 &= 255;
			hex_vector.push_back(hex1);
		}
		else
		{
			label_location[word]=hex_vector.end()-hex_vector.begin();
			hex_vector.push_back(0);
			hex_vector.push_back(0);
		}
	  }
	  else
	  {
	  	iter++;
	  	word = *iter;
	  	hexword = 0xFF & (int)strtol (word.c_str (), 0, 16);
	  	hex_vector.push_back (hexword);
	  	hexword = ((int)strtol (word.c_str (), 0, 16) >> 8) & 0xFF;
	  	hex_vector.push_back (hexword);
	  }
	  continue;
	}
      if (two_word_decoder.count (word))
	{
	  //cout<<"Two word decoder loop entered\n";
		std::string second_word, new_word;
	  iter++;
	  second_word = *iter;
	  new_word = word + second_word;
	  hexword = decode_for_hex (intelligence, new_word);
	  hex_vector.push_back (hexword);
	  continue;
	}
      if (two_word_decoder_extra_8bit.count (word))
	{
	  //cout<<"two word extra decoder 8 bit loop entered\n";
		std::string second_word, new_word;
	  iter++;
	  second_word = *iter;
	  new_word = word + second_word;
	  hexword = decode_for_hex (intelligence, new_word);
	  hex_vector.push_back (hexword);
	  iter++;
	  word = *iter;
	  hex_vector.push_back ((int)strtol (word.c_str (), 0, 16));
	  continue;
	}
      if (two_word_decoder_extra_16bit.count (word))
	{
	  //cout<<"two word extra decoder 16 bit loop entered\n";
		std::string second_word, new_word;
	  iter++;
	  second_word = *iter;
	  new_word = word + second_word;
	  hexword = decode_for_hex (intelligence, new_word);
	  hex_vector.push_back (hexword);
	  iter++;
	  word = *iter;
	  hexword = 0xFF & (int)strtol (word.c_str (), 0, 16);
	  hex_vector.push_back (hexword);
	  hexword = ((int)strtol (word.c_str (), 0, 16) >> 8) & 0xFF;
	  hex_vector.push_back (hexword);
	  continue;
	}
      if (three_word_decoder.count (word))
	{
		std::string second_word, third_word, new_word;
	  iter++;
	  second_word = *iter;
	  iter++;
	  third_word = *iter;
	  new_word = word + second_word + third_word;
	  hexword = decode_for_hex (intelligence, new_word);
	  hex_vector.push_back (hexword);
	  continue;
	}
      if(label_location.count(word))
      {
      	  lbl_iter = label_location.find(word);
      	  int hex1, hex2, position;

      	  position=(*lbl_iter).second;
	  hex1=(hex_vector.end()-hex_vector.begin())+addr;
	  hex2=hex1 & 255;
	  hex1>>=8;
	  hex1 &= 255;
	  hex_vector[position+1]=hex1;
	  hex_vector[position]=hex2;
	  continue;
      }
      if(!label_location.count(word))
      {
      	 label_location[word]=hex_vector.end() - hex_vector.begin();
	 continue;
      }
    }

  /*std::vector < int >::iterator it_int = hex_vector.begin ();
     cout << "The Decoded vector in hex code is:" << "\n";
     for (; it_int != hex_vector.end (); it_int++)
     {
     cout.setf(ios::showbase);
     cout.setf(ios::hex, ios::basefield);
     cout << *it_int << "\n";
     cout.unsetf(ios::showbase);
     cout.unsetf(ios::hex);
     } */
}

#endif /* __MNEMONICDECODER__ */
