#!/usr/bin/env python3

"""
clock.py: a simple clock.
By Guido Gonzato, April 2024.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
"""

from sdl_bgi  import *
from math     import *
from datetime import datetime
from time     import sleep

PI_180 = 3.14159 / 180

initwindow (500, 500)

mx = getmaxx () / 2
my = getmaxy () / 2
r = getmaxx () / 2 - 20
l_hour = getmaxx () / 3 - 40
l_min = getmaxx () / 3 + 30
l_sec = getmaxx () / 3 + 50

# draw the clock

for i in range (10):
    setcolor (COLOR (255 - 10*i, 0, 0))
    circle (mx, my, r + i)

for i in range (0, 360, 30):
    angle = 90 - i
    setcolor (WHITE)
    setlinestyle (SOLID_LINE, COPY_PUT, NORM_WIDTH)
    line (mx + r * cos (angle * PI_180),
	  my - r * sin (angle * PI_180),
	  mx + (r+10) * cos (angle * PI_180),
	  my - (r+10) * sin (angle * PI_180))

setfillstyle (SOLID_FILL, BLACK)

while (0 == kbhit () and (0 == ismouseclick (WM_LBUTTONDOWN))):
    setcolor (BLACK)
    fillellipse (mx, my, r, r)

    # get time
    current_time = datetime.now ()
    tm_hour = current_time.hour
    tm_min = current_time.minute
    tm_sec = current_time.second

    # calculate angle for seconds, minutes, and hours
    second_angle = 90 - (tm_sec * 6)
    minute_angle = 90 - (tm_min * 6)
    hour_angle   = 90 - ((tm_hour % 12) * 30 + tm_min / 2)

    # draw hands
    # seconds
    setcolor (WHITE)
    line (mx, my,
	  mx + l_sec * cos (second_angle * PI_180),
	  my - l_sec * sin (second_angle * PI_180))
    # minutes
    setcolor (YELLOW)
    setlinestyle (SOLID_LINE, COPY_PUT, THICK_WIDTH)
    line (mx, my,
	  mx + l_min * cos (minute_angle * PI_180),
	  my - l_min * sin (minute_angle * PI_180))
    # hours
    setcolor (BLUE)
    line (mx, my,
	  mx + l_hour * cos (hour_angle * PI_180),
	  my - l_hour * sin (hour_angle * PI_180))
    setlinestyle (SOLID_LINE, COPY_PUT, THICK_WIDTH)
    setcolor (WHITE)
    # print time as text
    bar (10, 10, 10 + 8*20, 10 + 8)
    outtextxy (10, 10, current_time.strftime("%H:%M:%S"))
    
    refresh ()
    sleep (1)

closegraph()
