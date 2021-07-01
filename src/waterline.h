#pragma once
#include "ofMain.h"

class waterline {
public:
	waterline();
	waterline(int lnum, struct line *l);
	~waterline();

	void waterline_computation();
	void draw();

	struct line *Line;
	ofColor water_color;
	int end_flag = 0;
	int path_cnt = 0;
	int num_of_line;
	struct dot *path;

	int x, y;
	int next_x, next_y;
};
