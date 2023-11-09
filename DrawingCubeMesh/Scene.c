struct Scene scene;

struct Scene {
	struct Obj obj;
	struct Cam cam;
} Scene;

void initScene() {
	VECTOR objpos = { 0.00f, 0.00f, 0.00f, 1.00f };
	VECTOR objrot = { 0.00f, 0.00f, 0.00f, 1.00f };

	VECTOR campos = { 0.00f, 0.00f, 100.00f, 1.00f };
	VECTOR camrot = { 0.00f, 0.00f,   0.00f, 1.00f };

	memcpy(scene.obj.pos, objpos, sizeof(objpos));
	memcpy(scene.obj.rot, objrot, sizeof(objrot));

	memcpy(scene.cam.pos, campos, sizeof(campos));
	memcpy(scene.cam.rot, camrot, sizeof(camrot));
}

int render(framebuffer_t* frame, zbuffer_t* z)
{

	int i;
	int context = 0;

	MATRIX local_world;
	MATRIX world_view;
	MATRIX view_screen;
	MATRIX local_screen;

	VECTOR* temp_vertices;

	packet_t* packets[2];
	packet_t* current;
	qword_t* dmatag;

	packets[0] = packet_init(100, PACKET_NORMAL);
	packets[1] = packet_init(100, PACKET_NORMAL);

	temp_vertices = memalign(128, sizeof(VECTOR) * vertex_count);
	
	xyz_t* verts;
	color_t* colors;

	verts = memalign(128, sizeof(vertex_t) * vertex_count);
	colors = memalign(128, sizeof(color_t) * vertex_count);

	prim_t prim;
	color_t color;

	prim.type = PRIM_TRIANGLE;
	prim.shading = PRIM_SHADE_GOURAUD;
	prim.mapping = DRAW_DISABLE;
	prim.fogging = DRAW_DISABLE;
	prim.blending = DRAW_DISABLE;
	prim.antialiasing = DRAW_ENABLE;
	prim.mapping_type = PRIM_MAP_ST;
	prim.colorfix = PRIM_UNFIXED;

	color.r = 0x80;
	color.g = 0x80;
	color.b = 0x80;
	color.a = 0x80;
	color.q = 1.0f;

	create_view_screen(view_screen, graph_aspect_ratio(), -3.00f, 3.00f, -3.00f, 3.00f, 1.00f, 2000.00f);

	dma_wait_fast();

	for (;;)
	{
		qword_t* q;

		current = packets[context];

		/*object_rotation[0] += 0.008f;
		object_rotation[1] += 0.012f;*/

		scene.obj.rot[0] += 0.008f;
		scene.obj.rot[1] += 0.012f;

		create_local_world(local_world, scene.obj.pos, scene.obj.rot);
		create_world_view(world_view, scene.cam.pos, scene.cam.rot);
		create_local_screen(local_screen, local_world, world_view, view_screen);
		calculate_vertices(temp_vertices, vertex_count, vertices, local_screen);

		draw_convert_xyz(verts, 2048, 2048, 32, vertex_count, (vertex_f_t*)temp_vertices);
		draw_convert_rgbq(colors, vertex_count, (vertex_f_t*)temp_vertices, (color_f_t*)colours, 0x80);
		dmatag = current->data;

		q = dmatag;
		q++;

		q = draw_disable_tests(q, 0, z);
		q = draw_clear(q, 0, 2048.0f - 320.0f, 2048.0f - 256.0f, frame->width, frame->height, 0x00, 0x00, 0x00);
		q = draw_enable_tests(q, 0, z);
		q = draw_prim_start(q, 0, &prim, &color);

		for (i = 0; i < points_count; i++)
		{
			q->dw[0] = colors[points[i]].rgbaq;
			q->dw[1] = verts[points[i]].xyz;
			q++;
		}

		q = draw_prim_end(q, 2, DRAW_RGBAQ_REGLIST);
		q = draw_finish(q);

		DMATAG_END(dmatag, (q - current->data) - 1, 0, 0, 0);

		dma_wait_fast();
		dma_channel_send_chain(DMA_CHANNEL_GIF, current->data, q - current->data, 0, 0);

		context ^= 1;

		draw_wait_finish();
		graph_wait_vsync();

	}

	packet_free(packets[0]);
	packet_free(packets[1]);

	return 0;
}