//      PARSER.CC

#include"parser.h"

using namespace mpu;

#ifdef __PARSER__

void
Parser::get_word (std::string textline)
{
	std::string list_of_delimiters (" ,");
	std::string::size_type position_begin = 0;
	std::string::size_type position_end = 0;
	std::vector < std::string > words;

  //cout << "READ STRING " << textline << "\n";
  while ((position_end =
	  textline.find_first_of (list_of_delimiters,
				  position_end)) != std::string::npos)
    {
      words.push_back (textline.
		       substr (position_begin,
			       position_end - position_begin));
      position_begin = ++position_end;

    }

  int
    size =
    textline.
    size ();
  words.push_back (textline.
		   substr (position_begin, size + 1 - position_begin));

  std::vector < std::string >::iterator it = words.begin ();
  for (; it != words.end (); it++)
  {
#ifndef DISPLAY
    //cout << (*it) << endl;
#endif
    all_words.push_back(*it);
  }
}

void
Parser::get_text (std::string file_name)
{

  std::ifstream infile (file_name.c_str (), std::ios::in);
  assert(infile);
  std::string text_line;


  while (getline (infile, text_line, '\n'))
    {
      get_word (text_line);
    }

}

void
Parser::read (std::string file_name, int addr)
{
  all_words.clear();
  decoder->hex_vector.clear();
  get_text (file_name);
  decoder->decode (all_words, addr);
  memory->load (decoder->hex_vector, addr);
  pc->put(addr);
}

void
Parser::set_ram (Ram * _memory)
{
  memory = _memory;
}

void
Parser::set_decoder (Mnemonic_Decoder * _decoder)
{
  decoder = _decoder;
}

void
Parser::set_pc (Reg16Bit * _pc)
{
  pc = _pc;
}

#endif /* __PARSER__ */
