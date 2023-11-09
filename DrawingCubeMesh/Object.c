struct Obj {
	VECTOR pos;
	VECTOR rot;
	VECTOR vel;
	VECTOR acc;

	color_t color;
	prim_t prim;

	int vertex_count;
	VECTOR* vertices;
	VECTOR* colours;

	int points_count;
	int* points;

} Obj;

//struct Obj ObjInit(VECTOR pos, VECTOR rot) {
//	struct Obj obj;
//
//	memcpy(obj.pos, pos, sizeof(pos));
//	memcpy(obj.rot, rot, sizeof(rot));
//
//	return obj;
//}


//void ObjUpdate(struct Obj* obj) {
//	VECT_Add(obj->pos, obj->vel);
//	VECT_Add(obj->vel, obj->acc);
//	VECT_Reset(obj->acc);
//}
//
//void ObjApplyForce(struct Obj* obj, struct VECTOR* force) {
//	VECT_Add(obj->acc, force);
//}
//
//struct Obj* placeObject() {
//	struct Obj* obj;
//
//	return obj;
//}