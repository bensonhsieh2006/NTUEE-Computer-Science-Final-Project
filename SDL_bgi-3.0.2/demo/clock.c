/* clock.c  -*- C -*-
 * 
 * To compile:
 * gcc -o clock clock.c -lSDL_bgi -lSDL2 -lm
 * 
 * Simple clock.
 * By Guido Gonzato, March 2023.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 */

#include <stdio.h>
#include <graphics.h>
#include <time.h>

#define PI_180 3.14159 / 180

int main (int argc, char *argv[]) {

  int
    r,
    mx, my,
    l_hour, l_min, l_sec;

  char
    s[10];

  initwindow (500, 500);

  mx = getmaxx () / 2;
  my = getmaxy () / 2;
  r = getmaxx () / 2 - 20;
  l_hour = getmaxx () / 3 - 40;
  l_min = getmaxx () / 3 + 30;
  l_sec = getmaxx () / 3 + 50;

  // draw the clock
  for (int i = 0; i < 10; i++) {
    setcolor (COLOR (255 - 10*i, 0, 0));
    circle (mx, my, r + i);
  }
  for (int i = 0; i < 360; i += 30) {
    int angle = 90 - i;
    // if (0 == i % 30) {
      setlinestyle (SOLID_LINE, COPY_PUT, THICK_WIDTH);
      setcolor (BLUE);
    // }
    /*
    else {
      setcolor (WHITE);
      setlinestyle (SOLID_LINE, COPY_PUT, NORM_WIDTH);
    }
    */
    line (mx + r * cos (angle * PI_180),
	  my - r * sin (angle * PI_180),
	  mx + (r+10) * cos (angle * PI_180),
	  my - (r+10) * sin (angle * PI_180));
  }

  setfillstyle (SOLID_FILL, BLACK);
  
  while (!kbhit () && (0 == ismouseclick (WM_LBUTTONDOWN))) {

    setcolor (BLACK);
    fillellipse (mx, my, r, r);

    // get time
    time_t current_time = time (NULL);
    struct tm *time_info = localtime (&current_time);
    int sec = time_info->tm_sec;

    // calculate angle for seconds, minutes, and hours
    int second_angle = 90 - (time_info->tm_sec * 6);
    int minute_angle = 90 - (time_info->tm_min * 6);
    int hour_angle   = 90 - ((time_info->tm_hour % 12) * 30 +
			     time_info->tm_min / 2);

    // draw hands
    // seconds
    setcolor (WHITE);
    line (mx, my,
	  mx + l_sec * cos (second_angle * PI_180),
	  my - l_sec * sin (second_angle * PI_180));
    // minutes
    setcolor (YELLOW);
    setlinestyle (SOLID_LINE, COPY_PUT, THICK_WIDTH);
    line (mx, my,
	  mx + l_min * cos (minute_angle * PI_180),
	  my - l_min * sin (minute_angle * PI_180));
    // hours
    setcolor (BLUE);
    line (mx, my,
	  mx + l_hour * cos (hour_angle * PI_180),
	  my - l_hour * sin (hour_angle * PI_180));
    setlinestyle (SOLID_LINE, COPY_PUT, NORM_WIDTH);
    setcolor (WHITE);
    // print time as text
    bar (10, 10, 10 + strlen (s)*8, 10 + 8);
    sprintf (s, "%02d:%02d:%02d",
	     time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    outtextxy (10, 10, s);
    refresh ();

    // wait a second
    do {
      time_t current_time = time (NULL);
      time_info = localtime (&current_time);
      if (kbhit () || ismouseclick (WM_LBUTTONDOWN))
	break;
    } while (sec == time_info->tm_sec);

  }

  closegraph();
  return 0;
}
