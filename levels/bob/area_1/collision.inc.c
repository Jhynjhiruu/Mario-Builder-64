const Collision bob_area_1_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(4),
	COL_VERTEX(-150, -2000, 9450),
	COL_VERTEX(9450, -2000, 9450),
	COL_VERTEX(9450, -2000, -150),
	COL_VERTEX(-150, -2000, -150),
	COL_TRI_INIT(SURFACE_DEATH_PLANE, 2),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI_STOP(),
	COL_END()
};
