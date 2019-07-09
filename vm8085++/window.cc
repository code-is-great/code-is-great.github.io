#include "window.h"

using namespace display;

#ifdef __WINDOW__

Window::Window ()
{
	std::string init_title ("WINDOW");
  init_title += ((count++) + 48);

  title = new_title = init_title;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;
  width = new_width = COLS;
  height = new_height = LINES;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Window::Window (std::string tl)
{
  count++;

  title = new_title = tl;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;
  width = new_width = COLS;
  height = new_height = LINES;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Window::Window (int x, int y)
{
	std::string init_title ("WINDOW");
  init_title += ((count++) + 48);

  title = new_title = init_title;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;
  width = new_width = COLS;
  height = new_height = LINES;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Window::Window (std::string tl, int x, int y)
{
  count++;

  title = new_title = tl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;
  width = new_width = COLS;
  height = new_height = LINES;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Window::Window (std::string tl, int x, int y, int w, int h)
{
  count++;

  title = new_title = tl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;
  width = new_width = w;
  height = new_height = h;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Window::~Window ()
{
  count--;
  hide ();
  if (!isendwin ())
    endwin ();
}

void
Window::set_title (std::string tl)
{
  new_title = tl;
}

void
Window::set_width (int w)
{
  new_width = w;
}

void
Window::set_height (int h)
{
  new_height = h;
}

int
Window::get_width () const
{
  return width;
}

int
Window::get_height () const
{
  return height;
}

WINDOW *
Window::get_win () const
{
  return win;
}

void
Window::show_title ()
{
  if ((title.size () + 2) % 2)
    wmove (win, 0, (width / 2) - (title.size () / 2));
  else
    wmove (win, 0, (width / 2) - (title.size () / 2) - 1);
  wprintw (win, " %s ", title.c_str ());
  wrefresh (win);
}

void
Window::hide_title ()
{
  wmove (win, 0, 1);
  whline (win, ACS_HLINE, width - 2);
  wrefresh (win);
}

void
Window::draw ()
{
  wborder (win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER,
	   ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  show_title ();
  move (0, 0);
  hidden = false;
  wrefresh (win);
}

void
Window::hide ()
{
  werase (win);
  wrefresh (win);
}

void
Window::update ()
{
  title = new_title;
  x_pos = new_x_pos;
  y_pos = new_y_pos;
  width = new_width;
  height = new_height;
  win = new_win = newwin (height, width, y_pos, x_pos);
  wresize (win, height, width);
}

#endif
