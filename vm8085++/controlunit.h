#include "vm_include.h"
#include "parser.h"
#include "inst_decoder.h"

#ifndef __CONTROLUNIT__
#define __CONTROLUNIT__

#ifdef DISPLAY

#include "label.h"

#endif

namespace mpu
{
  class ControlUnit
  {
  public:
    ControlUnit ();
    ~ControlUnit ();

    void load ();
    void start ();
    void stop ();
    void next ();

    void set_file (std::string _file);
    void set_prog_loc (int _pr_loc);

    void set_parser (Parser * _parser);
    void set_inst_decoder (Inst_Decoder * _in_dec);

#ifdef DISPLAY

    void do_this (std::string lbl);
    void set_label (display::Label * _label[]);

#endif

  private:
      std::string file;
    int pr_loc;

    Parser *parser;
    Inst_Decoder *in_dec;

#ifdef DISPLAY

      display::Label * label[2];
    enum
    { NOTFOUND, LOAD, START, STOP, NEXT, EXIT, FILE, PROG_LOC };

#endif
  };

}

#endif
