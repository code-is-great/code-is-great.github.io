#include "8085microprocessor.h"

using namespace mpu;

#ifdef __8085MICROPROCESSOR__

Processor::Processor (int rows)
{
#ifdef DISPLAY
  screen.set_controller (&control);

  display::Element * ptr;
  ptr = screen.get_element ("load");
  assert (ptr != 0);
  button[LOAD] = (display::Button *) ptr;
  ptr = screen.get_element ("start");
  assert (ptr != 0);
  button[START] = (display::Button *) ptr;
  ptr = screen.get_element ("stop");
  assert (ptr != 0);
  button[STOP] = (display::Button *) ptr;
  ptr = screen.get_element ("next");
  assert (ptr != 0);
  button[NEXT] = (display::Button *) ptr;
  ptr = screen.get_element ("exit");
  assert (ptr != 0);
  button[EXIT] = (display::Button *) ptr;

  button[LOAD]->set_controller (&control);
  button[START]->set_controller (&control);
  button[STOP]->set_controller (&control);
  button[NEXT]->set_controller (&control);

  display::Label * label[2];
  ptr = screen.get_element ("file");
  assert (ptr != 0);
  label[FILE] = (display::Label *) ptr;
  ptr = screen.get_element ("prog_loc");
  assert (ptr != 0);
  label[PROG_LOC] = (display::Label *) ptr;
  control.set_label (label);
  ram.set_mp_sheet(screen.get_mp_sheet());
  reg[A].set_label((display::Label*)screen.get_label("regA"));
  reg[B].set_label((display::Label*)screen.get_label("regB"));
  reg[C].set_label((display::Label*)screen.get_label("regC"));
  reg[D].set_label((display::Label*)screen.get_label("regD"));
  reg[E].set_label((display::Label*)screen.get_label("regE"));
  reg[H].set_label((display::Label*)screen.get_label("regH"));
  reg[L].set_label((display::Label*)screen.get_label("regL"));
  flag.set_label((display::Label*)screen.get_label("flag"));
  sp.set_label((display::Label*)screen.get_label("sp"));
  pc.set_label((display::Label*)screen.get_label("pc"));
#else
	LINES = rows;
#endif

  control.set_parser (&parser);
  parser.set_ram (&ram);
  parser.set_decoder (&decoder);
  parser.set_pc (&pc);
  control.set_inst_decoder(&in_dec);
  reg[A].set_accum();
  Reg8Bit * ptrs_reg[7];
  int i = 0;
  for (i = 0; i < 7; i++)
  {
  	ptrs_reg[i] = &reg[i];
	reg[i].set_flag(&flag);
  }
  in_dec.set_reg(ptrs_reg);
  in_dec.set_ram(&ram);
  in_dec.set_stck(&stck);
  in_dec.set_port_a(&port_a);
  in_dec.set_port_b(&port_b);
  in_dec.set_flag(&flag);
  in_dec.set_pc(&pc);
  in_dec.set_sp(&sp);
  sp.put(0xffff);
  stck.set_ram(&ram);
  stck.set_sp(&sp);
}

Processor::~Processor ()
{
}

void
Processor::start ()
{
  int key, key_count = 0;

#ifdef DISPLAY
  int i = 0;
  char _file[9], _prog_loc[5];
  for (i = 0; i < 9; i++)
    _file[i] = '\0';
  for (i = 0; i < 5; i++)
    _prog_loc[i] = '\0';
  i = 0;
#endif

#ifdef DISPLAY

  signal (SIGINT, final);
  keypad (screen.get_ctl_win (), TRUE);
  screen.show ();
  screen.set_focus ("file");

#endif

  for (;;)
    {

#ifndef DISPLAY

      {
	int gap = LINES - 23;
	int idx = 0;
	for(idx = 0; idx < gap;idx++)
		std::cout << "\n";
      }
      std::cout << "________________" << std::endl;
      std::cout << "Select an action" << std::endl;
      std::cout << "----------------" << std::endl;
      std::cout << "1. (L)oad" << std::endl;
      std::cout << "2. (S)tart" << std::endl;
      std::cout << "3. s(T)op" << std::endl;
      std::cout << "4. (N)ext" << std::endl;
      std::cout << "5. (E)xit" << std::endl;
      std::cout << "----------------" << std::endl;
      std::cout << "Your Choice : ";
      key = toupper (getchar ());
      key_count++;
      getchar ();
      switch (key)
	{
	case 'L':
	  control.load ();
	  break;
	case 'S':
	  //control.start ();
	      while(!(in_dec.halted()))
	      {
		control.next();
      		{
			int gap = LINES - 14;
			int idx = 0;
			for(idx = 0; idx < gap;idx++)
				std::cout << "\n";
     	        }
		sleep(1);
	      }
	  break;
	case 'T':
	  control.stop ();
	  break;
	case 'N':
	  control.next ();
	  break;
	case 'Q':
	case 'E':
	  final (0);
	  break;
	default:
	  std::cout << "Invalid Choice" << std::endl;
	  //sleep (1);
	  continue;
	}

#else

      key = wgetch (screen.get_ctl_win ());
      key_count++;
      if (key == 9)
	{
	  screen.next_focus ();
	  i = 0;
	}
      else if (key == 13)
	{
		std::string focussed = screen.focus_on ();
	  if (focussed == "load")
	    {
	      control.set_file ((std::string) _file);
	      control.set_prog_loc ((int)strtol(_prog_loc, 0, 16));
	      if(!button[LOAD]->disabled())
	      button[LOAD]->press ();
	      button[LOAD]->disable();
	      screen.draw_grid();
	      screen.update_labels();
	      i = 0;
	    }
	  else if (focussed == "start")
	    {
	      //button[START]->press ();
	      while(!(in_dec.halted()))
	      {
	      	button[NEXT]->press();
	        screen.update_labels();
		sleep(1);
	      }
	    }
	  else if (focussed == "stop")
	    {
	      button[STOP]->press ();
	    }
	  else if (focussed == "next")
	    {
	      button[NEXT]->press ();
	      screen.update_labels();
	    }
	  else if (focussed == "exit")
	    {
	      final (0);
	    }
	  else if (focussed == "file")
	    {
	      screen.next_focus ();
	      i = 0;
	    }
	  else if (focussed == "prog_loc")
	    {
	      screen.next_focus ();
	      i = 0;
	    }
	}
      else if (((key >= 65) && (key <= 90)) ||
	       ((key >= 97) && (key <= 122)) ||
	       ((key >= 48) && (key <= 57)) || (key == 46) || (key == 263))
	{
		std::string focussed = screen.focus_on ();
	  if (focussed == "file")
	    {
	      button[LOAD]->enable();
	      if (i < 8)
		{
		  if (key != 263)
		    {
		      _file[i++] = key;
		      waddch (screen.get_ctl_win (), key);
		      _file[8] = '\0';
		    }
		  else
		    {
		      if (i > 0)
			{
			  display::Element::backspace (screen.get_ctl_win ());
			  i--;
			}
		    }
		}
	      else if (i == 8)
		{
		  if (key == 263)
		    {
		      display::Element::backspace (screen.get_ctl_win ());
		      i--;
		    }
		}
	    }
	  else if (focussed == "prog_loc")
	    {
	      button[LOAD]->enable();
	      if (i < 4)
		{
		  if (key != 263)
		    {
		      _prog_loc[i++] = key;
		      waddch (screen.get_ctl_win (), key);
		      _prog_loc[4] = '\0';
		    }
		  else
		    {
		      if (i > 0)
			{
			  display::Element::backspace (screen.get_ctl_win ());
			  i--;
			}
		    }
		}
	      else if (i == 4)
		{
		  if (key == 263)
		    {
		      display::Element::backspace (screen.get_ctl_win ());
		      i--;
		    }
		}
	    }
	}
      else if ( key == 258 )
        {
		screen.scroll_down();
	}
      else if ( key == 259 )
        {
		screen.scroll_up();
	}
      else
	{
	  printw ("%d", key);
	  refresh ();
	  //sleep (1);
	}

#endif

    }
}

void
Processor::final (int n)
{
  std::string mesg ("THANK YOU FOR USING THIS SIMULATOR");

#ifndef DISPLAY

  std::cout << mesg << std::endl;
  sleep (1);

#else

  werase (stdscr);
  wrefresh (stdscr);
  wmove (stdscr, LINES / 2, COLS / 2 - mesg.size () / 2);
  if (has_colors ())
    wcolor_set (stdscr, 5, 0);
  wprintw (stdscr, "%s", mesg.c_str ());
  if (has_colors ())
    wcolor_set (stdscr, 7, 0);
  wrefresh (stdscr);
  sleep (1);
  werase (stdscr);
  wrefresh (stdscr);
  endwin ();

#endif

  exit (0);
}

#endif /* __8085MICROPROCESSOR */
