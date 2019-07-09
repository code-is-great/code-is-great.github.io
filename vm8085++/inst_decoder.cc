#include "inst_decoder.h"

using namespace mpu;

#ifdef __INSTRUCTIONDECODER__

int Inst_Decoder::prog_loc = 0;

Inst_Decoder::Inst_Decoder ()
{
	halt = false;
}

Inst_Decoder::~Inst_Decoder ()
{
}

void Inst_Decoder::Execute_Instruction()
{
	int hexvalue, ramvalue, hval, lval, temp =0 ;
	int newtemp = 255, LR = 0, HR = 0, aggregation = 0;
	int d0bit, d7bit, M, tmp_flag, tmp_reg;
	int lsb = 0, msb = 0;

	if(ram_idx == pc->get())
	{
		flag->put(0);
		reg[A]->put(0);
		reg[B]->put(0);
		reg[C]->put(0);
		reg[D]->put(0);
		reg[E]->put(0);
		reg[H]->put(0);
		reg[L]->put(0);
	}
	hexvalue=ram->inst_at(pc->get());

	switch (hexvalue)
	{
		case 0xCE: //ACI 
			   (*pc)++;
			   hexvalue=ram->inst_at(pc->get());
			   if(flag->carry())
			   	*reg[A]=*reg[A]+hexvalue+1;
			    else
			   	*reg[A]=*reg[A]+hexvalue;
			    break;	

		case 0x88:// ADC B 
			   if(flag->carry())
			   	*reg[A]+=*reg[B]+1;
			   else
			   	*reg[A]+=*reg[B];
			   break;
		case 0x89:// ADC C 
			   if(flag->carry())
			   	*reg[A]+=*reg[C]+1;
			   else
			   	*reg[A]+=*reg[C];
			   break;
		case 0x8A:// ADC D 
			   if(flag->carry())
			   	*reg[A]+=*reg[D]+1;
			   else
			   	*reg[A]+=*reg[D];
			   break;
		case 0x8C:// ADC H 
			   if(flag->carry())
			   	*reg[A]+=*reg[H]+1;
			   else
			   	*reg[A]+=*reg[H];
			   break;
		case 0x8D:// ADC L 
			   if(flag->carry())
			   	*reg[A]+=*reg[L]+1;
			   else
			   	*reg[A]+=*reg[L];
			   break;
		case 0x8E:// ADC M 
			   	   	
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue= ram->inst_at(hval);
			    if(flag->carry())
			    	*reg[A]+=ramvalue+1;
			    else
			    	*reg[A]+=ramvalue;
			    break;
			
		case 0x8F:// ADC A 
			   if(flag->carry())
			   	*reg[A]+=*reg[A]+1;
			   else
			   	*reg[A]+=*reg[A];
			   break;
		case 0x80: // ADD B
			   *reg[A]+=*reg[B];
			   break;
		case 0x81: // ADD C
			   *reg[A]+=*reg[C];
			   break;
		case 0x82: // ADD D
			   *reg[A]+=*reg[D];
			   break;
		case 0x83: // ADD E
			   *reg[A]+=*reg[E];
			   break;
		case 0x84: // ADD H
			   *reg[A]+=*reg[H];
			   break;
		case 0x85: // ADD L
			   *reg[A]+=*reg[L];
			   break;
		case 0x86: // ADD M
				
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue= ram->inst_at(hval);
			    *reg[A]+=ramvalue;
			    break;
		case 0x87: // ADD A
			   *reg[A]+=*reg[A];
			   break;
		case 0xC6: //ADI
			   (*pc)++;
			   hexvalue=ram->inst_at(pc->get());
			   *reg[A]+=hexvalue;
			   break;
		case 0xA0: //ANA B 
			   *reg[A]&=*reg[B];
			   break;
		case 0xA1: // ANA C
			   *reg[A]&=*reg[C];
			   break;
		case 0xA2: // ANA D
			   *reg[A]&=*reg[D];
			   break;
		case 0xA3: // ANA E
			   *reg[A]&=*reg[E];
			   break;
		case 0xA4: // ANA H
			   *reg[A]&=*reg[H];
			   break;
		case 0xA5: // ANA L
			   *reg[A]&=*reg[L];
			   break;
		case 0xA6: // ANA M
			   
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue= ram->inst_at(hval);
			    *reg[A]&=ramvalue;
			    break;
		case 0xA7: // ANA A
			   *reg[A]&=*reg[A];
			   break;
		case 0xE6: // ANI
			   (*pc)++;
			   hexvalue=ram->inst_at(pc->get());
			   *reg[A]&=hexvalue;
			   break;
		case 0x2F: // CMA
			    *reg[A]=!*reg[A];
			    break;
		case 0x3F: // CMC
			   if(flag->carry())
			   	flag->reset_carry();
			   else
			   	flag->set_carry();
			   
			   break;
		case 0xB8: // CMP B
			   if(*reg[A]<*reg[B])
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==*reg[B])
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>*reg[B])
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xB9: // CMP C
			   if(*reg[A]<*reg[C])
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==*reg[C])
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>*reg[C])
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xBA: // CMP D
			   if(*reg[A]<*reg[D])
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==*reg[D])
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>*reg[D])
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xBB: // CMP E
			   if(*reg[A]<*reg[E])
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==*reg[E])
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>*reg[E])
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xBC: // CMP H
			   if(*reg[A]<*reg[H])
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==*reg[H])
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>*reg[H])
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xBD: // CMP L
			   if(*reg[A]<*reg[L])
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==*reg[L])
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>*reg[L])
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xBE: // CMP M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue= ram->inst_at(hval);
			   if(*reg[A]<ramvalue)
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==ramvalue)
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>ramvalue)
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xBF: // CMP A
			   if(*reg[A]<*reg[A])
			   {
			   	flag->set_carry();
				flag->reset_zero();
			   }
			   if(*reg[A]==*reg[A])
			   {
			   	flag->reset_carry();
				flag->set_zero();
			   }
			   if(*reg[A]>*reg[A])
			   {
			   	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
		case 0xFE: // CPI
		 	    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    if(*reg[A]<hexvalue)
			    {
			    	flag->set_carry();
				flag->reset_zero();
			    }
			    if(*reg[A]==hexvalue)
			    {
			    	flag->reset_carry();
				flag->set_zero();
			    }
			    if(*reg[A]>hexvalue)
			    {
			    	flag->reset_carry();
				flag->reset_zero();
			    }
			    break;
	       	case 0x09: // DAD B
			    aggregation=reg[B]->get();
			    aggregation<<=8;
			    temp=reg[C]->get();
			    aggregation|=temp;			
			    HR=reg[H]->get();
			    LR=reg[L]->get();
			    HR<<=8;
			    HR|=LR;
			    temp=aggregation+HR;
			    if(temp>pow(2,16))
			    	flag->set_carry();
			    newtemp&=temp;
			    reg[L]->put(newtemp);
			    temp>>=8;
			    newtemp=255;
			    newtemp&=temp;
			    reg[H]->put(newtemp);
			    break;
	       	case 0x19: // DAD D
			    aggregation=reg[D]->get();
			    aggregation<<=8;
			    temp=reg[E]->get();
			    aggregation|=temp;			
			    HR=reg[H]->get();
			    LR=reg[L]->get();
			    HR<<=8;
			    HR|=LR;
			    temp=aggregation+HR;
			    if(temp>pow(2,16))
			    	flag->set_carry();
			    newtemp&=temp;
			    reg[L]->put(newtemp);
			    temp>>=8;
			    newtemp=255;
			    newtemp&=temp;
			    reg[H]->put(newtemp);
			    break;
	       	case 0x29: // DAD H
			    aggregation=reg[H]->get();
			    aggregation<<=8;
			    temp=reg[L]->get();
			    aggregation|=temp;			
			    HR=reg[H]->get();
			    LR=reg[L]->get();
			    HR<<=8;
			    HR|=LR;
			    temp=aggregation+HR;
			    if(temp>pow(2,16))
			    	flag->set_carry();
			    newtemp&=temp;
			    reg[L]->put(newtemp);
			    temp>>=8;
			    newtemp=255;
			    newtemp&=temp;
			    reg[H]->put(newtemp);
			    break;
	       	case 0x39: // DAD SP
			    aggregation=sp->get();
			    HR=reg[H]->get();
			    LR=reg[L]->get();
			    HR<<=8;
			    HR|=LR;
			    temp=aggregation+HR;
			    if(temp>pow(2,16))
			    	flag->set_carry();
			    newtemp&=temp;
			    reg[L]->put(newtemp);
			    temp>>=8;
			    newtemp=255;
			    newtemp&=temp;
			    reg[H]->put(newtemp);
			    break;
		case 0x06: // MVI B
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    reg[B]->put(hexvalue);
			    break;
		case 0x0E: // MVI C
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    reg[C]->put(hexvalue);
			    break;
		case 0x16: // MVI D
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    reg[D]->put(hexvalue);
			    break;
		case 0x1E: // MVI E
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    reg[E]->put(hexvalue);
			    break;
		case 0x26: // MVI H
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    reg[H]->put(hexvalue);
			    break;
		case 0x2E: // MVI L
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    reg[L]->put(hexvalue);
			    break;
		case 0x36: // MVI M
			     (*pc)++;
			     hexvalue=ram->inst_at(pc->get());
			     hval=reg[H]->get();
			     lval=reg[L]->get();
			     hval<<=8;
			     hval|=lval;
			     ram->write_at(hval,hexvalue);
			     break;
		case 0x3E: // MVI A
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    reg[A]->put(hexvalue);
			    break;
                case 0x00: // NOP
			    break;
	    	case 0xB0: // ORA B
			    *reg[A]|=*reg[B];
			    break;
	    	case 0xB1: // ORA C
			    *reg[A]|=*reg[C];
			    break;
	    	case 0xB2: // ORA D 
			    *reg[A]|=*reg[D];
			    break;
	    	case 0xB3: // ORA E 
			    *reg[A]|=*reg[E];
			    break;
	    	case 0xB4: // ORA H
			    *reg[A]|=*reg[H];
			    break;
	    	case 0xB5: // ORA L
			    *reg[A]|=*reg[L];
			    break;
	    	case 0xB6: // ORA M
			    break;
	    	case 0xB7: // ORA A
			    *reg[A]|=*reg[A];
			    break;
		case 0xF6: // ORI
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    *reg[A]|=hexvalue;
			    break;
		case 0xD3: // OUT
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    if(port_a->get_addr()==hexvalue)
			    	port_a->put(reg[A]->get());
			    else
			    	port_b->put(reg[B]->get());
			    break;
		case 0xE9: // PCHL
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    pc->put(hval);
			    break;
		case 0x17: // RAL
			    temp=128;
			    if(temp&=(reg[A]->get()))
			    	d7bit=1;
			    else
			    	d7bit=0;

			    *reg[A]<<=1;
			    if(flag->carry())
			    	*reg[A]|=1;
			    else
			    	{
				    int invert;

				    invert=!(reg[A]->get());
				    invert|=1;
				    *reg[A]=!invert;
				 }

			     if(d7bit)
			     	flag->set_carry();
			     else
			     	flag->reset_carry();

			     break;
		case 0x1F: // RAR
			    temp=1;
			    if(temp&=(reg[A]->get()))
			    	d0bit=1;
			    else
			    	d0bit=0;

			    *reg[A]>>=1;
			    if(flag->carry())
			    	*reg[A]|=128;
			    else
			    	{
				    int invert;

				    invert=!(reg[A]->get());
				    invert|=128;
				    (*reg[A])=!invert;
				 }

			     if(d0bit)
			     	flag->set_carry();
			     else
			     	flag->reset_carry();

				break;

		 case 0x07: // RLC
		 	     
			    temp=128;
			    if(temp&=(reg[A]->get()))
			    	d7bit=1;
			    else
			    	d7bit=0;

			    *reg[A]<<=1;
			    if(d7bit)
			    {
			    	*reg[A]|=1;
				flag->set_carry();
			    }
			    else
			    	{
				    int invert;

				    invert=!(reg[A]->get());
				    invert|=1;
				    *reg[A]=!invert;
				    flag->reset_carry();
				 }

			     break;
			     
		case 0x0F : // RRC
			   
			    temp=1;
			    if(temp&=(reg[A]->get()))
			    	d0bit=1;
			    else
			    	d0bit=0;

			    *reg[A]>>=1;
			    if(d0bit)
			    {
			    	*reg[A]|=128;
				flag->set_carry();
			     }
			    else
			    	{
				    int invert;

				    invert=!(reg[A]->get());
				    invert|=128;
				    *reg[A]=!invert;
				    flag->reset_carry();
				 }

				break;

		case 0x40: // MOV B,B

			    *reg[B]=*reg[B];
			    break;
		case 0x41: // MOV B,C

			    *reg[B]=*reg[C];
			    break;
		case 0x42: // MOV B,D

			    *reg[B]=*reg[D];
			    break;
		case 0x43: // MOV B,E

			    *reg[B]=*reg[E];
			    break;
		case 0x44: // MOV B,H

			    *reg[B]=*reg[H];
			    break;
		case 0x45: // MOV B,L

			    *reg[B]=*reg[L];
			    break;
		case 0x46: // MOV B,M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue=ram->inst_at(hval);
			    reg[B]->put(ramvalue);
			    break;
		case 0x47: // MOV B,A

			    *reg[B]=*reg[A];
			    break;
		case 0x48: // MOV C,B

			    *reg[C]=*reg[B];
			    break;
		case 0x49: // MOV C,C

			    *reg[C]=*reg[C];
			    break;
		case 0x4A: // MOV C,D

			    *reg[C]=*reg[D];
			    break;
		case 0x4B: // MOV C,E

			    *reg[C]=*reg[E];
			    break;
		case 0x4C: // MOV C,H

			    *reg[C]=*reg[H];
			    break;
		case 0x4D: // MOV C,L

			    *reg[C]=*reg[L];
			    break;
		case 0x4E: // MOV C,M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue=ram->inst_at(hval);
			    reg[C]->put(ramvalue);
			    break;
		case 0x4F: // MOV C,A

			    *reg[C]=*reg[A];
			    break;
		case 0x50: // MOV D,B

			    *reg[D]=*reg[B];
			    break;
		case 0x51: // MOV D,C

			    *reg[D]=*reg[C];
			    break;
		case 0x52: // MOV D,D

			    *reg[D]=*reg[D];
			    break;
		case 0x53: // MOV D,E

			    *reg[D]=*reg[E];
			    break;
		case 0x54: // MOV D,H

			    *reg[D]=*reg[H];
			    break;
		case 0x55: // MOV D,L

			    *reg[D]=*reg[L];
			    break;
		case 0x56: // MOV D,M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue=ram->inst_at(hval);
			    reg[D]->put(ramvalue);
			    break;
		case 0x57: // MOV D,A

			    *reg[D]=*reg[A];
			    break;
		case 0x58: // MOV E,B

			    *reg[E]=*reg[B];
			    break;
		case 0x59: // MOV E,C

			    *reg[E]=*reg[C];
			    break;
		case 0x5A: // MOV E,D

			    *reg[E]=*reg[D];
			    break;
		case 0x5B: // MOV E,E

			    *reg[E]=*reg[E];
			    break;
		case 0x5C: // MOV E,H

			    *reg[E]=*reg[H];
			    break;
		case 0x5D: // MOV E,L

			    *reg[E]=*reg[L];
			    break;
		case 0x5E: // MOV E,M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue=ram->inst_at(hval);
			    reg[E]->put(ramvalue);
			    break;
		case 0x5F: // MOV E,A

			    *reg[E]=*reg[A];
			    break;
		case 0x60: // MOV H,B

			    *reg[H]=*reg[B];
			    break;
		case 0x61: // MOV H,C

			    *reg[H]=*reg[C];
			    break;
		case 0x62: // MOV H,D

			    *reg[H]=*reg[D];
			    break;
		case 0x63: // MOV H,E

			    *reg[H]=*reg[E];
			    break;
		case 0x64: // MOV H,H

			    *reg[H]=*reg[H];
			    break;
		case 0x65: // MOV H,L

			    *reg[H]=*reg[L];
			    break;
		case 0x66: // MOV H,M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue=ram->inst_at(hval);
			    reg[H]->put(ramvalue);
			    break;
		case 0x67: // MOV H,A

			    *reg[H]=*reg[A];
			    break;
		case 0x68: // MOV L,B

			    *reg[L]=*reg[B];
			    break;
		case 0x69: // MOV L,C

			    *reg[L]=*reg[C];
			    break;
		case 0x6A: // MOV L,D

			    *reg[L]=*reg[D];
			    break;
		case 0x6B: // MOV L,E

			    *reg[L]=*reg[E];
			    break;
		case 0x6C: // MOV L,H

			    *reg[L]=*reg[H];
			    break;
		case 0x6D: // MOV L,L

			    *reg[L]=*reg[L];
			    break;
		case 0x6E: // MOV L,M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue=ram->inst_at(hval);
			    reg[L]->put(ramvalue);
			    break;
		case 0x6F: // MOV L,A

			    *reg[L]=*reg[A];
			    break;
		case 0x70: // MOV M,B
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ram->write_at(hval,*reg[B]);
			    break;
		case 0x71: // MOV M,C
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ram->write_at(hval,*reg[C]);
			    break;
		case 0x72: // MOV M,D
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ram->write_at(hval,*reg[D]);
			    break;
		case 0x73: // MOV M,E
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ram->write_at(hval,*reg[E]);
			    break;
		case 0x74: // MOV M,H
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ram->write_at(hval,*reg[H]);
			    break;
		case 0x75: // MOV M,L
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ram->write_at(hval,*reg[L]);
			    break;
		case 0x77: // MOV M,A
			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ram->write_at(hval,*reg[A]);
			    break;
		case 0x78: // MOV A,B

			    *reg[A]=*reg[B];
			    break;
		case 0x79: // MOV A,C

			    *reg[A]=*reg[C];
			    break;
		case 0x7A: // MOV A,D

			    *reg[A]=*reg[D];
			    break;
		case 0x7B: // MOV A,E

			    *reg[A]=*reg[E];
			    break;
		case 0x7C: // MOV A,H

			    *reg[A]=*reg[H];
			    break;
		case 0x7D: // MOV A,L

			    *reg[A]=*reg[L];
			    break;
		case 0x7E: // MOV A,M

			    hval=reg[H]->get();
			    hval<<=8;
			    lval=reg[L]->get();
			    hval|=lval;
			    ramvalue=ram->inst_at(hval);
			    reg[A]->put(ramvalue);
			    break;
		case 0x7F: // MOV A,A

			    *reg[A]=*reg[A];
			    break;
		case 0xC3: // JMP 
			    
			    (*pc)++;
			    hexvalue=ram->inst_at(pc->get());
			    (*pc)++;
			    ramvalue=ram->inst_at(pc->get());
			    ramvalue<<=8;
			    ramvalue|=hexvalue;
			    pc->put(ramvalue-1);
			    break;
		case 0xDA: // JC
			
			    if(flag->carry())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue-1);
			    }
			    	break;
			    
		case 0xD2: // JNC

			    if(!flag->carry())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue-1);
			    }
			    break;
		case 0xF2: // JP

			    if(!flag->sign())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue - 1);
			    }
			    break;
		case 0xFA: // JM

			    if(flag->sign())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue - 1);
			    }
			    break;
		case 0xEA: // JPE

			    if(flag->parity())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue - 1);
			    }
			    break;
		case 0xE2: // JPO

			    if(!flag->parity())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue - 1);
			     }
			    break;
		case 0xCA: // JZ

			    if(flag->zero())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue - 1);
			    }
			    break;
		case 0xC2: // JNZ

			    if(!flag->zero())
			    {
			    	(*pc)++;
			    	hexvalue=ram->inst_at(pc->get());
			    	(*pc)++;
			    	ramvalue=ram->inst_at(pc->get());
			    	ramvalue<<=8;
			    	ramvalue|=hexvalue;
			    	pc->put(ramvalue - 1);
			    }
			    break;
		case 0xF9: // SPHL
			    sp->put(((reg[H]->get())<<8)|(reg[L]->get()));
			    stck->set_stack(sp->get());
			    break;
		case 0xC5: // PUSH B
			    stck->push(*reg[B]);
			    stck->push(*reg[C]);
			    break;
		case 0xD5: // PUSH D
			    stck->push(*reg[D]);
			    stck->push(*reg[E]);
			    break;
		case 0xE5: // PUSH H
			    stck->push(*reg[H]);
			    stck->push(*reg[L]);
			    break;
		case 0xF5: // PUSH PSW
			    stck->push(*reg[A]);
			    stck->push(*flag);
			    break;
		case 0xC1: // POP B
			    reg[C]->put((stck->pop()).get());
			    reg[B]->put((stck->pop()).get());
			    break;
		case 0xD1: // POP D
			    reg[E]->put((stck->pop()).get());
			    reg[D]->put((stck->pop()).get());
			    break;
		case 0xE1: // POP H
			    reg[L]->put((stck->pop()).get());
			    reg[H]->put((stck->pop()).get());
			    break;
		case 0xF1: // POP PSW
			    flag->put((stck->pop()).get());
			    reg[A]->put((stck->pop()).get());
			    break;
		case 0x3D: // DCR A
		 	    (*reg[A])--;
			    break;
		case 0x05: // DCR B
		 	    (*reg[B])--;
			    break;
		case 0x0D: // DCR C
		 	    (*reg[C])--;
			    break;
		case 0x15: // DCR D
		 	    (*reg[D])--;
			    break;
		case 0x1D: // DCR E
		 	    (*reg[E])--;
			    break;
		case 0x25: // DCR H
		 	    (*reg[H])--;
			    break;
		case 0x2D: // DCR L
		 	    (*reg[L])--;
			    break;
		case 0x35: // DCR M
			    tmp_flag = (0x01 & flag->get());
			    tmp_reg = reg[A]->get();
			    M = (((reg[H]->get())<<8)|(reg[L]->get()));
			    reg[A]->put(ram->inst_at(M));
			    --(*reg[A]);
			    ram->write_at(M, reg[A]->get());
			    reg[A]->put(tmp_reg);
			    flag->put(((flag->get()) & 0xfe) | tmp_flag);
			    break;
		case 0x0B: // DCX B
			    M = (((reg[B]->get())<<8)|(reg[C]->get()));
			    M--;
			    reg[C]->put(M & 0x00ff);
			    reg[B]->put((M &= 0xff00)>>8);
			    break;
		case 0x1B: // DCX D
			    M = (((reg[D]->get())<<8)|(reg[E]->get()));
			    M--;
			    reg[E]->put(M & 0x00ff);
			    reg[D]->put((M &= 0xff00)>>8);
			    break;
		case 0x2B: // DCX H
			    M = (((reg[H]->get())<<8)|(reg[L]->get()));
			    M--;
			    reg[L]->put(M & 0x00ff);
			    reg[H]->put((M &= 0xff00)>>8);
			    break;
		case 0x3B: // DCX SP
			    sp->put((sp->get()) - 1);
			    break;
		case 0x3C: // INR A
		 	    (*reg[A])++;
			    break;
		case 0x04: // INR B
		 	    (*reg[B])++;
			    break;
		case 0x0C: // INR C
		 	    (*reg[C])++;
			    break;
		case 0x14: // INR D
		 	    (*reg[D])++;
			    break;
		case 0x1C: // INR E
		 	    (*reg[E])++;
			    break;
		case 0x24: // INR H
		 	    (*reg[H])++;
			    break;
		case 0x2C: // INR L
		 	    (*reg[L])++;
			    break;
		case 0x34: // INR M
			    tmp_flag = (0x01 & flag->get());
			    tmp_reg = reg[A]->get();
			    M = (((reg[H]->get())<<8)|(reg[L]->get()));
			    reg[A]->put(ram->inst_at(M));
			    ++(*reg[A]);
			    ram->write_at(M, reg[A]->get());
			    reg[A]->put(tmp_reg);
			    flag->put(((flag->get()) & 0xfe) | tmp_flag);
			    break;
		case 0x03: // INX B
			    M = (((reg[B]->get())<<8)|(reg[C]->get()));
			    M++;
			    reg[C]->put(M & 0x00ff);
			    reg[B]->put((M &= 0xff00)>>8);
			    break;
		case 0x13: // INX D
			    M = (((reg[D]->get())<<8)|(reg[E]->get()));
			    M++;
			    reg[E]->put(M & 0x00ff);
			    reg[D]->put((M &= 0xff00)>>8);
			    break;
		case 0x23: // INX H
			    M = (((reg[H]->get())<<8)|(reg[L]->get()));
			    M++;
			    reg[L]->put(M & 0x00ff);
			    reg[H]->put((M &= 0xff00)>>8);
			    break;
		case 0x33: // INX SP
			    sp->put((sp->get()) - 1);
			    break;
		case 0xCD: // CALL

			     (*pc)++;
			     lsb=ram->inst_at(pc->get());
			     (*pc)++;
			     msb=ram->inst_at(pc->get());
			     (*pc)++;
			     ramvalue = pc->get();
			     newtemp &= ramvalue;
			     ramvalue>>=8;
			     stck->push(Byte(ramvalue));
			     stck->push(Byte(newtemp));
			     msb<<=8;
			     msb|=lsb;
			     pc->put(msb-1);

			     break;

		case 0xDC: // CC 

			    if( flag->carry())
			    {
			    	 (*pc)++;
			       	lsb=ram->inst_at(pc->get());
			    	 (*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
				msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			     }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }
			     	break;
			     

		case 0xD4: // CNC

			     if(!flag->carry())
			     {
			     	(*pc)++;
			     	lsb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
			     	msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			      }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }

			     break;

		case 0xF4: // CP

			     if(!flag->sign())
			     {
			     	(*pc)++;
			     	lsb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
			     	msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			      }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }

			      break;

		 case 0xFC: // CM
		 

			     if(flag->sign())
			     {
			     	(*pc)++;
			     	lsb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
			     	msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			      }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }

			      break;

		 case 0xEC: // CPE
		 

			     if(flag->parity())
			     {
			     	(*pc)++;
			     	lsb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
			     	msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			      }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }

			       break;

		 case 0xE4: // CPO
		 

			     if(!flag->parity())
			     {
			     	(*pc)++;
			     	lsb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
			     	msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			      }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }

			      break;

		 case 0xCC: // CZ
		 

			     if(flag->zero())
			     {
			     	(*pc)++;
			     	lsb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
			     	msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			      }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }

			      break;

		 case 0xC4: // CNZ
		 

			     if(!flag->zero())
			     {
			     	(*pc)++;
			     	lsb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	msb=ram->inst_at(pc->get());
			     	(*pc)++;
			     	ramvalue = pc->get();
			     	newtemp &= ramvalue;
			     	ramvalue>>=8;
			     	stck->push(Byte(ramvalue));
			     	stck->push(Byte(newtemp));
			     	msb<<=8;
			     	msb|=lsb;
			     	pc->put(msb-1);
			      }
			     else
			     {
			     	(*pc)++;
			     	(*pc)++;
			     }

			      break;

		 case 0xC9: // RET

		 	      lsb = (stck->pop()).get();
			      msb = (stck->pop()).get();
			      msb<<=8;
			      msb|=lsb;
			      pc->put(msb-1);

			      break;
		case 0xD8:    // RC

			      if(flag->carry())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			      break;
			      
		case 0xD0:    // RNC

			      if(!flag->carry())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			      break;

		case 0xF0:    // RP

			      if(!flag->sign())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			      break;

		case 0xF8:    // RM

			      if(flag->sign())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			       break;

		case 0xE8:    // RPE

			      if(flag->parity())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			       break;

		case 0xE0:    // RPO

			      if(!flag->parity())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			       break;

		case 0xC8:    // RZ

			      if(flag->zero())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			       break;

		case 0xC0:    // RNZ

			      if(!flag->zero())
			      {
		 	      	lsb = (stck->pop()).get();
			      	msb = (stck->pop()).get();
			      	msb<<=8;
			      	msb|=lsb;
			      	pc->put(msb-1);
			       }

			       break;
		case 0x76:
			    halt = true;
			    break;
	}

	if(ram_idx == prog_loc) 
		halt = false;
	if(hexvalue!=0x76)
		(*pc)++;
#ifndef DISPLAY
	display();
#endif
    }

			    
void Inst_Decoder::set_reg(Reg8Bit* _reg[])
{
	reg[0] = _reg[0];
	reg[1] = _reg[1];
	reg[2] = _reg[2];
	reg[3] = _reg[3];
	reg[4] = _reg[4];
	reg[5] = _reg[5];
	reg[6] = _reg[6];
}

void Inst_Decoder::set_ram(Ram * _ram)
{
	ram = _ram;
}

void Inst_Decoder::set_stck(Stack * _stck)
{
	stck = _stck;
}

void Inst_Decoder::set_port_a(Port * _port_a)
{
	port_a = _port_a;
}

void Inst_Decoder::set_port_b(Port * _port_b)
{
	port_b = _port_b;
}

void Inst_Decoder::set_flag(Flag * _flag)
{
	flag = _flag;
}

void Inst_Decoder::set_pc(Reg16Bit * _pc)
{
	pc = _pc;
}

void Inst_Decoder::set_sp(Reg16Bit * _sp)
{
	sp = _sp;
}

bool Inst_Decoder::halted() const
{
	return halt;
}

#ifndef DISPLAY
void Inst_Decoder::display()
{
	if(!((pc->get()) < (prog_loc + 10)))
		ram_idx = (pc->get()) - 9;
	else
		ram_idx = prog_loc;
	if(!((sp->get()) > (0xffff - 10)))
		stack_idx = (sp->get());
	else
		stack_idx = 0xffff - 9;
	std::cout << "---------------------------------------------------------------" << std::endl;
	printf("\t\t\t\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	printf("Program Counter : 0x%04x", pc->get());
	if((pc->get()) == ram_idx)
	printf("       >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	printf("Stack Pointer   : 0x%04x", sp->get());
	if((pc->get()) == ram_idx)
	printf("       >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	std::cout << "------------------------";
	if((pc->get()) == ram_idx)
	printf("       >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	if((pc->get()) == ram_idx)
	printf("\t\t\t       >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t\t\t\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	printf("RegA : 0x%02x",reg[A]->get());
	if((pc->get()) == ram_idx)
	printf("\t\t       >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t\t\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	printf("RegB : 0x%02x\tRegC : 0x%02x ", reg[B]->get(), reg[C]->get());
	if((pc->get()) == ram_idx)
	printf("   >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	printf("RegD : 0x%02x\tRegE : 0x%02x ", reg[D]->get(), reg[E]->get());
	if((pc->get()) == ram_idx)
	printf("   >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	printf("RegH : 0x%02x\tRegL : 0x%02x ", reg[H]->get(), reg[L]->get());
	if((pc->get()) == ram_idx)
	printf("   >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	std::cout << "Flag : "; flag->print_bin();
	if((pc->get()) == ram_idx)
	printf("\t\t       >0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	else
	printf("\t\t\t0x%04x : 0x%02x", ram_idx++, ram->inst_at(ram_idx));
	if((sp->get()) == stack_idx)
	printf("  >0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	else
	printf("\t0x%04x : 0x%02x\n", stack_idx++, ram->inst_at(stack_idx));
	std::cout << "---------------------------------------------------------------" << std::endl;
	if(!halted())
		std::cout << "Status : RUNNING";
	else
		std::cout << "Status : HALTED ";
	std::cout << "\t\tPROGRAM\t\tSTACK\n";
}
#endif	/* DISPLAY */

#endif /* __INSTRUCTIONDECODER__ */
