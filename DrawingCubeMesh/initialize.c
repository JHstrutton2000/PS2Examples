

void init_gs(framebuffer_t* frame, zbuffer_t* z) {
	frame->width = 640;
	frame->height = 512;
	frame->mask = 0;
	frame->psm = GS_PSM_32;
	frame->address = graph_vram_allocate(frame->width, frame->height, frame->psm, GRAPH_ALIGN_PAGE);

	z->enable = DRAW_ENABLE;
	z->mask = 0;
	z->method = ZTEST_METHOD_GREATER_EQUAL;
	z->zsm = GS_ZBUF_32;
	z->address = graph_vram_allocate(frame->width, frame->height, z->zsm, GRAPH_ALIGN_PAGE);

	graph_initialize(frame->address, frame->width, frame->height, frame->psm, 0, 0);
}

void init_drawing_environment(framebuffer_t* frame, zbuffer_t* z) {
	packet_t* packet = packet_init(16, PACKET_NORMAL);

	qword_t* q = packet->data;

	q = draw_setup_environment(q, 0, frame, z);
	q = draw_primitive_xyoffset(q, 0, (2048 - 320), (2048 - 256));
	q = draw_finish(q);

	dma_channel_send_normal(DMA_CHANNEL_GIF, packet->data, q - packet->data, 0, 0);
	dma_wait_fast();

	packet_free(packet);
}
