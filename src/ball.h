#pragma once

#include "ofMain.h"
#include "stdlib.h"
#include "waterline.h"

typedef struct line_ {
	int x1;
	int y1;
	int x2;
	int y2;
	float m;
	float slope;
}lining;

class ball {
public:
	ball();
	~ball();
	lining line[100];
	int line_num = 0;
	int x = 50;
	int y = 50;
	int prev_x = 50;
	int prev_y = 50;
	int square_x = 300;
	int square_y = 300;
	int play_flag = 0;
	int success_flag = 0;
	int game_over = 0;
	int line_idx;
	float diameter = 10;
	float ball_diameter= 15;
	float square_diameter = 60;
	int draw_y;

	ofImage bucket;
	ofImage congrats;

	int move(int st);
	void draw_square();
	int success();
	void draw();
};


