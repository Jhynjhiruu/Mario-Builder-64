const Collision dslope_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(8),
	COL_VERTEX(150, -150, -150),
	COL_VERTEX(150, 150, 150),
	COL_VERTEX(-150, 150, 150),
	COL_VERTEX(-150, -150, -150),
	COL_VERTEX(-150, 150, -150),
	COL_VERTEX(150, 150, -150),
	COL_VERTEX(150, -101, -150),
	COL_VERTEX(-150, -101, -150),
	COL_TRI_INIT(SURFACE_NOT_SLIPPERY, 8),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(4, 5, 6),
	COL_TRI(4, 6, 7),
	COL_TRI(4, 7, 2),
	COL_TRI(5, 1, 6),
	COL_TRI(4, 2, 1),
	COL_TRI(4, 1, 5),
	COL_TRI_STOP(),
	COL_END()
};
