/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# (c) 2005 Naomi Peori <naomi@peori.ca>
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
*/

 int points_count = 12;

 int points[12] = {
   0, 1, 2,
   1, 2, 3,
   0, 1, 3,
   0, 2, 3
 };

 int vertex_count = 4;

 VECTOR vertices[4] = {
	 {-5,  5,     5},
	 { 5,  20,    10},
	 { 00, -04.1, 5},
	 { 00, -10,   00}
 };

 VECTOR colours[4] = {
  { 255, 000, 000, 1.00f },
  { 000, 255, 000, 1.00f },
  { 000, 000, 255, 1.00f },
  { 255, 255, 255, 1.00f }
 };
