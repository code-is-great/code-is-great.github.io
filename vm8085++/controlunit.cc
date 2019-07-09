#include "controlunit.h"

using namespace mpu;

#ifdef __CONTROLUNIT__

ControlUnit::ControlUnit ()
{
}

ControlUnit::~ControlUnit ()
{
}

void
ControlUnit::load ()
{
#ifndef DISPLAY

  std::cout << "Enter program starting location (in HEX): ";
  std::cin >> std::hex >> pr_loc;
  std::cout << "Enter program filename : ";
  std::cin >> file;
  getchar ();
  in_dec->prog_loc = pr_loc;
#else
  label[FILE]->set_value (file);
  char _pr_loc[5];
  sprintf (_pr_loc, "%x", pr_loc);
  _pr_loc[5] = '\0';
  label[PROG_LOC]->set_value ((std::string) _pr_loc);

#endif /* DISPLAY */

  parser->read (file, pr_loc);

}

void
ControlUnit::start ()
{
#ifdef DISPLAY
#else
 // while(!(in_dec->halted()))
  //	next();
#endif
}

void
ControlUnit::stop ()
{
#ifdef DISPLAY
  //sleep (1);
#else
	std::cout << "Stop Pressed" << std::endl;
#endif
}

void
ControlUnit::next ()
{
#ifdef DISPLAY
  //sleep (1);
#else
#endif
  in_dec->Execute_Instruction();
}

void
ControlUnit::set_file (std::string _file)
{
  file = _file;
}

void
ControlUnit::set_prog_loc (int _pr_loc)
{
  pr_loc = _pr_loc;
}

#ifdef DISPLAY

void
ControlUnit::do_this (std::string lbl)
{
  if (lbl == "LOAD")
    load ();
  else if (lbl == "START")
    start ();
  else if (lbl == "STOP")
    stop ();
  else if (lbl == "NEXT")
    next ();
}

void
ControlUnit::set_label (display::Label * _label[])
{
  label[FILE] = _label[FILE];
  label[PROG_LOC] = _label[PROG_LOC];
}

#endif

void
ControlUnit::set_parser (Parser * _parser)
{
  parser = _parser;
}

void 
ControlUnit::set_inst_decoder(Inst_Decoder * _in_dec)
{
	in_dec = _in_dec;
}

#endif /* __CONTROLUNIT__ */
