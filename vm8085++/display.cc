#include "display.h"

using namespace display;

#ifdef __DISPLAY__

#ifdef __ELEMENT__

void
Element::init ()
{
  initscr ();
  cbreak ();
  noecho ();
  nonl ();
  intrflush (stdscr, FALSE);
  if (has_colors ())
    {
      start_color ();
      init_pair (1, COLOR_RED, COLOR_BLACK);
      init_pair (2, COLOR_GREEN, COLOR_BLACK);
      init_pair (3, COLOR_YELLOW, COLOR_BLACK);
      init_pair (4, COLOR_BLUE, COLOR_BLACK);
      init_pair (5, COLOR_CYAN, COLOR_BLACK);
      init_pair (6, COLOR_MAGENTA, COLOR_BLACK);
      init_pair (7, COLOR_WHITE, COLOR_BLACK);
      init_pair (8, COLOR_BLACK, COLOR_WHITE);
    }
}

void
Element::backspace (WINDOW * _win)
{
  int y, x;
  getyx (_win, y, x);
  wmove (_win, y, x - 1);
  waddch (_win, 32);
  wmove (_win, y, x - 1);
}

#endif

#ifdef __WINDOW__
int
  Window::count =
  0;
#endif

#ifdef __GRID__
int
  Grid::count =
  0;
#endif

#ifdef __MP_SHEET__
int
  Mp_Sheet::count =
  0;
#endif

#ifdef __LABEL__
int
  Label::count =
  0;
#endif

#ifdef __BUTTON__
int
  Button::count =
  0;
#endif

Display::Display ()
{
  w_main.set_title ("INTEL 8085 SIMULATOR");
  w_main.update ();
  g_reg.set_title ("REGISTERS");
  g_reg.set_xy (1, 1);
  g_reg.set_width (COLS / 2 - 1);
  g_reg.set_height (LINES / 2 - 1);
  g_reg.update ();
  g_ctl.set_title ("CONTROLS");
  g_ctl.set_xy (1, LINES / 2);
  g_ctl.set_width (COLS / 2 - 1);
  g_ctl.set_height (LINES / 2 - 1);
  g_ctl.update ();
  a.set_win (g_reg.get_win ());
  a.set_name ("RegA");
  a.set_value ("00");
  a.update ();
  flag.set_win (g_reg.get_win ());
  flag.set_name ("Flag");
  flag.set_value ("00000000");
  flag.update ();
  b.set_win (g_reg.get_win ());
  b.set_name ("RegB");
  b.set_value ("00");
  b.update ();
  c.set_win (g_reg.get_win ());
  c.set_name ("RegC");
  c.set_value ("00");
  c.update ();
  d.set_win (g_reg.get_win ());
  d.set_name ("RegD");
  d.set_value ("00");
  d.update ();
  e.set_win (g_reg.get_win ());
  e.set_name ("RegE");
  e.set_value ("00");
  e.update ();
  h.set_win (g_reg.get_win ());
  h.set_name ("RegH");
  h.set_value ("00");
  h.update ();
  l.set_win (g_reg.get_win ());
  l.set_name ("RegL");
  l.set_value ("00");
  l.update ();
  pc.set_win (g_reg.get_win ());
  pc.set_name ("PC");
  pc.set_value ("0000");
  pc.update ();
  sp.set_win (g_reg.get_win ());
  sp.set_name ("SP");
  sp.set_value ("0000");
  sp.update ();
  load.set_win (g_ctl.get_win ());
  load.set_label ("LOAD");
  load.update ();
  start.set_win (g_ctl.get_win ());
  start.set_label ("START");
  stop.update ();
  stop.set_win (g_ctl.get_win ());
  stop.set_label ("STOP");
  stop.update ();
  next.set_win (g_ctl.get_win ());
  next.set_label ("NEXT");
  next.update ();
  exit.set_win (g_ctl.get_win ());
  exit.set_label ("EXIT");
  exit.update ();
  file.set_win (g_ctl.get_win ());
  file.set_name ("File ( 8-char )  :");
  file.set_value ("        ");
  file.update ();
  prog_loc.set_win (g_ctl.get_win ());
  prog_loc.set_name ("Program Location :    ");
  prog_loc.set_value ("    ");
  prog_loc.update ();

  space = (g_reg.get_width () - (a.get_width () + flag.get_width ())) / 3;
  a.set_xy (space, 2);
  a.update ();
  flag.set_xy (space, 7);
  flag.update ();
  b.set_xy (space, 3);
  b.update ();
  c.set_xy (2 * space + a.get_width (), 3);
  c.update ();
  d.set_xy (space, 4);
  d.update ();
  e.set_xy (2 * space + a.get_width (), 4);
  e.update ();
  h.set_xy (space, 5);
  h.update ();
  l.set_xy (2 * space + a.get_width (), 5);
  l.update ();
  pc.set_xy (space, g_reg.get_height () - 3);
  pc.update ();
  sp.set_xy (space, g_reg.get_height () - 2);
  sp.update ();
  space = (g_ctl.get_width () - (load.get_width () +
				 start.get_width () + stop.get_width ())) / 4;
  load.set_xy (space, 3);
  load.update ();
  start.set_xy (2 * space + load.get_width (), 3);
  start.update ();
  stop.set_xy (3 * space + load.get_width () + start.get_width (), 3);
  stop.update ();
  next.set_xy (space, 5);
  next.update ();
  exit.set_xy (2 * space + load.get_width (), 5);
  exit.update ();
  file.set_xy (space, g_ctl.get_height () - 3);
  file.update ();
  prog_loc.set_xy (space, g_ctl.get_height () - 2);
  prog_loc.update ();
}

Display::~Display ()
{
  hide ();
}

void
Display::set_focus (std::string element)
{
  remove_focus (focus_on ());
  if (element == "load")
    focus = LOAD;
  else if (element == "start")
    focus = START;
  else if (element == "stop")
    focus = STOP;
  else if (element == "next")
    focus = NEXT;
  else if (element == "exit")
    focus = EXIT;
  else if (element == "file")
    focus = FILE;
  else if (element == "prog_loc")
    focus = PROG_LOC;
  else
    focus = NOTFOUND;
  switch (focus)
    {
    case LOAD:
      load.set_focus ();
      break;
    case START:
      start.set_focus ();
      break;
    case STOP:
      stop.set_focus ();
      break;
    case NEXT:
      next.set_focus ();
      break;
    case EXIT:
      exit.set_focus ();
      break;
    case FILE:
      file.set_focus ();
      break;
    case PROG_LOC:
      prog_loc.set_focus ();
      break;
    default:
      break;
    }
}

void
Display::next_focus ()
{
  std::string now, nxt;
  now = focus_on ();
  if (now == "load")
    nxt = "start";
  else if (now == "start")
    nxt = "stop";
  else if (now == "stop")
    nxt = "next";
  else if (now == "next")
    nxt = "exit";
  else if (now == "exit")
    nxt = "file";
  else if (now == "file")
    nxt = "prog_loc";
  else if (now == "prog_loc")
    nxt = "load";
  else
    nxt = "load";
  set_focus (nxt);
}

std::string Display::focus_on ()
{
	std::string
  me ("notfound");
  if (focus == LOAD)
    me = "load";
  else if (focus == START)
    me = "start";
  else if (focus == STOP)
    me = "stop";
  else if (focus == NEXT)
    me = "next";
  else if (focus == EXIT)
    me = "exit";
  else if (focus == FILE)
    me = "file";
  else if (focus == PROG_LOC)
    me = "prog_loc";
  else
    me = "notfound";
  return me;
}

void
Display::remove_focus (std::string element)
{
  if (element == "load")
    focus = LOAD;
  else if (element == "start")
    focus = START;
  else if (element == "stop")
    focus = STOP;
  else if (element == "next")
    focus = NEXT;
  else if (element == "exit")
    focus = EXIT;
  else if (element == "file")
    focus = FILE;
  else if (element == "prog_loc")
    focus = PROG_LOC;
  else
    focus = NOTFOUND;
  switch (focus)
    {
    case LOAD:
      load.remove_focus ();
      break;
    case START:
      start.remove_focus ();
      break;
    case STOP:
      stop.remove_focus ();
      break;
    case NEXT:
      next.remove_focus ();
      break;
    case EXIT:
      exit.remove_focus ();
      break;
    case FILE:
      file.remove_focus ();
      break;
    case PROG_LOC:
      prog_loc.remove_focus ();
      break;
    default:
      break;
    }
}

void
Display::set_controller (mpu::ControlUnit * _ctl)
{
  ctl = _ctl;
}

void 
Display::scroll_down()
{
	WINDOW * g_win = g_hex.get_win();
	wscrl(g_win, 1);
}

void
Display::scroll_up()
{
	WINDOW * g_win = g_hex.get_win();
	wscrl(g_win, -1);
}

WINDOW *
Display::get_ctl_win ()
{
  return g_ctl.get_win ();
}

Mp_Sheet *
Display::get_mp_sheet()
{
  return (&g_hex);
}

Element *
Display::get_element (std::string element)
{
  Element *ptr;
  if (element == "load")
    focus = LOAD;
  else if (element == "start")
    focus = START;
  else if (element == "stop")
    focus = STOP;
  else if (element == "next")
    focus = NEXT;
  else if (element == "exit")
    focus = EXIT;
  else if (element == "file")
    focus = FILE;
  else if (element == "prog_loc")
    focus = PROG_LOC;
  else if (element == "regA")
    focus = REGA;
  else if (element == "regB")
    focus = REGB;
  else if (element == "regC")
    focus = REGC;
  else if (element == "regD")
    focus = REGD;
  else if (element == "regE")
    focus = REGE;
  else if (element == "regH")
    focus = REGH;
  else if (element == "regL")
    focus = REGL;
  else if (element == "sp")
    focus = SP;
  else if (element == "pc")
    focus = PC;
  else
    focus = NOTFOUND;
  switch (focus)
    {
    case LOAD:
      ptr = &load;
      break;
    case START:
      ptr = &start;
      break;
    case STOP:
      ptr = &stop;
      break;
    case NEXT:
      ptr = &next;
      break;
    case EXIT:
      ptr = &exit;
      break;
    case FILE:
      ptr = &file;
      break;
    case PROG_LOC:
      ptr = &prog_loc;
      break;
    case REGA:
      ptr = &a;
      break;
    case REGB:
      ptr = &b;
      break;
    case REGC:
      ptr = &c;
      break;
    case REGD:
      ptr = &d;
      break;
    case REGE:
      ptr = &e;
      break;
    case REGH:
      ptr = &h;
      break;
    case REGL:
      ptr = &l;
      break;
    case PC:
      ptr = &pc;
      break;
    case SP:
      ptr = &sp;
      break;
    default:
      ptr = 0;
      break;
    }
  return ptr;
}

Label *
Display::get_label (std::string element)
{
  Label *ptr;
  if (element == "regA")
    focus = REGA;
  else if (element == "regB")
    focus = REGB;
  else if (element == "regC")
    focus = REGC;
  else if (element == "regD")
    focus = REGD;
  else if (element == "regE")
    focus = REGE;
  else if (element == "regH")
    focus = REGH;
  else if (element == "regL")
    focus = REGL;
  else if (element == "sp")
    focus = SP;
  else if (element == "pc")
    focus = PC;
  else if (element == "flag")
    focus = FLAG;
  else
    focus = NOTFOUND;
  switch (focus)
    {
    case REGA:
      ptr = &a;
      break;
    case REGB:
      ptr = &b;
      break;
    case REGC:
      ptr = &c;
      break;
    case REGD:
      ptr = &d;
      break;
    case REGE:
      ptr = &e;
      break;
    case REGH:
      ptr = &h;
      break;
    case REGL:
      ptr = &l;
      break;
    case PC:
      ptr = &pc;
      break;
    case SP:
      ptr = &sp;
      break;
    case FLAG:
      ptr = &flag;
      break;
    default:
      ptr = 0;
      break;
    }
  return ptr;
}

void
Display::show ()
{
  w_main.draw ();
  g_reg.draw ();
  g_ctl.draw ();
  g_hex.draw ();
  a.draw ();
  flag.draw ();
  b.draw ();
  c.draw ();
  d.draw ();
  e.draw ();
  h.draw ();
  l.draw ();
  pc.draw ();
  sp.draw ();
  load.draw ();
  start.draw ();
  stop.draw ();
  next.draw ();
  exit.draw ();
  file.draw ();
  prog_loc.draw ();
}

void
Display::hide ()
{
  w_main.hide ();
  g_reg.hide ();
  g_ctl.hide ();
  g_hex.hide ();
  a.hide ();
  flag.hide ();
  b.hide ();
  c.hide ();
  d.hide ();
  e.hide ();
  h.hide ();
  l.hide ();
  pc.hide ();
  sp.hide ();
  load.hide ();
  start.hide ();
  stop.hide ();
  next.hide ();
  exit.hide ();
  file.hide ();
  prog_loc.hide ();
}

void
Display::draw_grid ()
{
  g_hex.draw ();
}

void
Display::update_labels()
{
  a.draw();
  b.draw();
  c.draw();
  d.draw();
  e.draw();
  h.draw();
  l.draw();
  flag.draw();
  pc.draw();
  sp.draw();
}

#endif
