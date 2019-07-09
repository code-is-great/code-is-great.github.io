#include "display.h"
#include "controlunit.h"
#include "port.h"
#include "flag.h"
#include "reg8bit.h"
#include "reg16bit.h"
#include "ram.h"
#include "stack85.h"
#include "parser.h"
#include "mnemonic_decoder.h"
#include "inst_decoder.h"

#ifndef __8085MICROPROCESSOR__
#define __8085MICROPROCESSOR__

namespace mpu
{
  class Processor
  {
  public:
    Processor (int rows);
    ~Processor ();

    void start ();
    static void final (int n);
  private:
#ifdef DISPLAY
      display::Display screen;
      display::Button * button[5];
    enum
    { NOTFOUND, LOAD, START, STOP, NEXT, EXIT, FILE, PROG_LOC };
#else
	int LINES;
#endif
    ControlUnit control;
    Port port_a, port_b;
    Flag flag;
    Reg8Bit reg[7];
    enum
    { A, B, C, D, E, H, L };
    Reg16Bit pc, sp;
    Ram ram;
    Stack stck;
    Parser parser;
    Mnemonic_Decoder decoder;
    Inst_Decoder in_dec;
  };

}

#endif
