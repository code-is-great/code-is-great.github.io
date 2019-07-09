#include "ram.h"

using namespace mpu;

#ifdef __RAM__

Ram::Ram ()
{
  resize (0xffff);
}

Ram::~Ram ()
{
}

void
Ram::load (std::vector < int >_value, int _prog_loc)
{
  clear();
  copy (_value.begin (), _value.end (), begin () + _prog_loc);
  prog_loc = _prog_loc;
#ifdef DISPLAY
  std::vector< int >::iterator i;
  int j = _prog_loc;
  g_hex->reset();
  for(i = _value.begin(); i < _value.end(); i++)
  {
  	g_hex->load((*i),j++);
  }
#else
  display();
#endif
}

int
Ram::inst_at (int loc)
{
  return (*this)[loc].get ();
}

void
Ram::write_at(int loc, Byte data)
{
  (*this)[loc] = Byte(data.get() & 0xff);
}

#ifdef DISPLAY
void
Ram::set_mp_sheet(display::Mp_Sheet * _g_hex)
{
	g_hex = _g_hex;
}
#else
void Ram::display()
{
	int ram_idx = prog_loc;
	int stack_idx = 0xffff - 9;
	std::cout << "---------------------------------------------------------------" << std::endl;
	printf("\t\t\t       >0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	printf("Program Counter : 0x%04x", prog_loc);
	printf("\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	printf("Stack Pointer   : 0xffff");
	printf("\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	std::cout << "------------------------";
	printf("\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	printf("\t\t\t\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	printf("RegA : 0x00");
	printf("\t\t\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	printf("RegB : 0x00\tRegC : 0x00 ");
	printf("\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	printf("RegD : 0x00\tRegE : 0x00 ");
	printf("\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	printf("RegH : 0x00\tRegL : 0x00 ");
	printf("\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("\t0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	std::cout << "Flag : 00000000";
	printf("\t\t\t0x%04x : 0x%02x", ram_idx++, inst_at(ram_idx));
	printf("  >0x%04x : 0x%02x\n", stack_idx++, inst_at(stack_idx));
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "Status : STOP\t\t\tPROGRAM\t\tSTACK\n";
}
#endif /* DISPLAY */

#endif /* __RAM__ */
