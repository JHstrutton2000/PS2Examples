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

#include <kernel.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <malloc.h>
#include <tamtypes.h>
#include <math3d.h>

#include <packet.h>

#include <dma_tags.h>
#include <gif_tags.h>
#include <gs_psm.h>

#include <dma.h>

#include <graph.h>

#include <draw.h>
#include <draw3d.h>

#include <math.h>

#include "mesh_data.c"

//VECTOR object_position = { 0.00f, 0.00f, 0.00f, 1.00f };
//VECTOR object_rotation = { 0.00f, 0.00f, 0.00f, 1.00f };
//
//VECTOR camera_position = { 0.00f, 0.00f, 100.00f, 1.00f };
//VECTOR camera_rotation = { 0.00f, 0.00f,   0.00f, 1.00f };

#include "VECT.c"

#include "Utility.c"
#include "Object.c"
#include "Cam.c"
#include "Scene.c"

#include "initialize.c"


int main(int argc, char *argv[]) {
	framebuffer_t frame;
	zbuffer_t z;

	dma_channel_initialize(DMA_CHANNEL_GIF,NULL,0);
	dma_channel_fast_waits(DMA_CHANNEL_GIF);

	initScene();

	init_gs(&frame, &z);
	init_drawing_environment(&frame,&z);
	render(&frame,&z);

	SleepThread();

	return 0;
}
