#include "mp_sheet.h"

using namespace display;

#ifdef __MP_SHEET__

Mp_Sheet::Mp_Sheet ()
{
  std::string init_title ("HEX-CODE");

  title = new_title = init_title;
  x_pos = new_x_pos = COLS / 2;
  y_pos = new_y_pos = 1;
  width = new_width = COLS / 2 - 1;
  if(LINES % 2)
  height = new_height = LINES - 3;
  else
  height = new_height = LINES - 2;
  rows = new_rows = LINES / 2 - 2;
  cols = new_cols = 4;
  cols_width = new int[cols];
  rows_height = new int[rows];
  new_cols_width = new int[cols];
  new_rows_height = new int[rows];
  int i = 0;
  for (i = 0; i < rows; i++)
    rows_height[i] = height / rows;
  for (i = 0; i < cols; i++)
    cols_width[i] = width / cols;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Mp_Sheet::~Mp_Sheet ()
{
  count--;
  delete[]new_cols_width;
  delete[]new_rows_height;
  delete[]rows_height;
  delete[]cols_width;
  hide ();
  if (!isendwin ())
    endwin ();
}

void
Mp_Sheet::draw ()
{
  int i = 0;
  wborder (win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER,
	   ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  if ((title.size () + 2) % 2)
    wmove (win, 0, (width / 2) - (title.size () / 2));
  else
    wmove (win, 0, (width / 2) - (title.size () / 2) - 1);
  wprintw (win, " %s ", title.c_str ());

  wmove (win, 1, 0);
  whline (win, ACS_LTEE, 1);
  wmove (win, 1, 1);
  whline (win, ACS_HLINE, width - 2);
  wmove (win, 1, width - 1);
  whline (win, ACS_RTEE, 1);

  wmove (win, 1, 4);
  whline (win, ACS_TTEE, 1);
  wmove (win, 1, 9);
  whline (win, ACS_TTEE, 1);
  wmove (win, 1, 13);
  whline (win, ACS_TTEE, 1);

  if (has_colors ())
    wcolor_set (win, 2, 0);
  wmove (win, 2, 1);
  wprintw (win, "PTR");

  wmove (win, 2, 5);
  wprintw (win, "MMRY");

  wmove (win, 2, 10);
  wprintw (win, "HEX");

  wmove (win, 2, 14);
  wprintw (win, "MNEMONICS");
  if (has_colors ())
    wcolor_set (win, 7, 0);

  for (i = 0; i < (2 * rows - 2); i++)
    {
      if ((i % 2))
	{
	  wmove (win, i + 2, 1);
	  whline (win, ACS_HLINE, width - 2);
	  wmove (win, i + 2, 0);
	  whline (win, ACS_LTEE, 1);
	  wmove (win, i + 2, width - 1);
	  whline (win, ACS_RTEE, 1);
	}
      wmove (win, i + 2, 4);
      whline (win, ACS_VLINE, 1);
      if ((i % 2))
	{
	  wmove (win, i + 2, 4);
	  whline (win, ACS_PLUS, 1);
	}
      wmove (win, i + 2, 9);
      whline (win, ACS_VLINE, 1);
      if ((i % 2))
	{
	  wmove (win, i + 2, 9);
	  whline (win, ACS_PLUS, 1);
	}
      wmove (win, i + 2, 13);
      whline (win, ACS_VLINE, 1);
      if ((i % 2))
	{
	  wmove (win, i + 2, 13);
	  whline (win, ACS_PLUS, 1);
	}
    }
  wmove (win, i + 2, 4);
  whline (win, ACS_VLINE, 1);
  wmove (win, i + 2, 9);
  whline (win, ACS_VLINE, 1);
  wmove (win, i + 2, 13);
  whline (win, ACS_VLINE, 1);

  wmove (win, height - 1, 4);
  whline (win, ACS_BTEE, 1);
  wmove (win, height - 1, 9);
  whline (win, ACS_BTEE, 1);
  wmove (win, height - 1, 13);
  whline (win, ACS_BTEE, 1);

  //draw_arrow();

  move (0, 0);
  hidden = false;
  wrefresh (win);
}

void
Mp_Sheet::update ()
{
  int temp_rows_height[rows];
  int temp_cols_width[cols];
  int i;
  for (i = 0; i < rows; i++)
    temp_rows_height[i] = rows_height[i];
  for (i = 0; i < cols; i++)
    temp_cols_width[i] = cols_width[i];
  title = new_title;
  x_pos = new_x_pos;
  y_pos = new_y_pos;
  width = new_width;
  height = new_height;
  win = new_win = newwin (height, width, y_pos, x_pos);
  rows = new_rows;
  cols = new_cols;
  for (i = 0; i < rows; i++)
    rows_height[i] = new_rows_height[i];
  for (i = 0; i < cols; i++)
    cols_width[i] = new_cols_width[i];

  wresize (win, height, width);
}

void
Mp_Sheet::load(int _hex, int loc, ...)
{
	char loc_str[5], hex_str[3];
	int idx = 0;
	if(ptr_loc == 0) ptr_loc = 4;
	sprintf(loc_str, "%04x",loc);
	sprintf(hex_str, "%02x",_hex);
	wmove(win, ptr_loc, 5);
	for(idx = 0;idx < 4;idx++)
	{
		waddch(win, loc_str[idx]);
	}
	wmove(win, ptr_loc, 10);
	for(idx = 0;idx < 2;idx++)
	{
		waddch(win, hex_str[idx]);
	}
	ptr_loc += 2;
}

void 
Mp_Sheet::reset()
{
	ptr_loc = 0;
}

void Mp_Sheet::draw_arrow()
{
  if (has_colors ())
    wcolor_set (win, 3, 0);
  wmove (win, 6, 1);
  whline (win, ACS_RARROW, 3);
  if (has_colors ())
    wcolor_set (win, 7, 0);
}

#endif
