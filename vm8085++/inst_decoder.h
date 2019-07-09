#include "vm_include.h"
#include"reg8bit.h"
#include"reg16bit.h"
#include"ram.h"
#include"stack85.h"
#include"port.h"
#include"flag.h"

#ifndef __INSTRUCTIONDECODER__
#define __INSTRUCTIONDECODER__

namespace mpu
{
  class Inst_Decoder
  {
  public:
    Inst_Decoder ();
    ~Inst_Decoder ();

    void Execute_Instruction();

    void set_reg(Reg8Bit* _reg[]);
    void set_ram(Ram * _ram);
    void set_stck(Stack * _stck);
    void set_port_a(Port * _port_b);
    void set_port_b(Port * _port_b);
    void set_flag(Flag * _flag);
    void set_pc(Reg16Bit * _pc);
    void set_sp(Reg16Bit * _sp);

    bool halted() const;
    int ram_idx;
    int stack_idx;
    static int prog_loc;
  protected:
    Reg8Bit *reg[7];
    enum
	   {A, B, C, D, E, H, L};
    Reg16Bit *pc,*sp;
    Ram *ram;
    Stack *stck;
    Port *port_a;
    Port *port_b;
    Flag *flag;

    bool halt;
#ifndef DISPLAY
    void display();
#endif
  };

}

#endif				/* __INSTRUCTIONDECODER__ */
