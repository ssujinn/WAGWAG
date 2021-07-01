#include "waterline.h"
#include "ofApp.h"

waterline::waterline()
{
}

waterline::waterline(int lnum, struct line *l)
{
	water_color.set(0, 118, 190);

	num_of_line = lnum;
	Line = new struct line[num_of_line];
	path = new struct dot[100];
	for (int i = 0; i < num_of_line; i++) {
		Line[i].x1 = l[i].x1;
		Line[i].x2 = l[i].x2;
		Line[i].y1 = l[i].y1;
		Line[i].y2 = l[i].y2;
		Line[i].slope = l[i].slope;
	}

	next_x = rand() % 1000 + 20;
	next_y = rand() % 500 + 50;
}

waterline::~waterline()
{
}

void waterline::waterline_computation()
{
	x = next_x;
	y = next_y;
	next_x = rand() % 1000 + 20;
	next_y = rand() % 500 + 50;

	for (int i = 0; i < 100; i++) {
		path[i].x1 = 0;
		path[i].y1 = 0;
	}
	path[0].x1 = x;
	path[0].y1 = y;
	int find_flag = 0;
	int min = 1000;
	int j = 0;

	while (1) {
		find_flag = 0;
		min = 1000;
		for (int i = 0; i < num_of_line; i++) {
			if (path[j].x1 >= Line[i].x1 &&  path[j].x1 <= Line[i].x2) {
				if (path[j].y1 < (Line[i].slope * (path[j].x1 - Line[i].x1) + Line[i].y1)) {
					int tmp = Line[i].y1 + (path[j].x1 - Line[i].x1) * Line[i].slope;
					if (tmp < min) {
						path[j + 1].x1 = path[j].x1;
						path[j + 1].y1 = Line[i].y1 + (path[j + 1].x1 - Line[i].x1) * Line[i].slope;
						if (Line[i].slope > 0) {
							path[j + 2].x1 = Line[i].x2;
							path[j + 2].y1 = Line[i].y2;
						}
						else {
							path[j + 2].x1 = Line[i].x1;
							path[j + 2].y1 = Line[i].y1;
						}
						min = tmp;
						find_flag = 1;
					}
				}
			}
		}

		if (!find_flag) {
			path[j + 1].x1 = path[j].x1;
			path[j + 1].y1 = 767;
			path_cnt = j + 2;
			break;
		}
		j += 2;
	}

}

void waterline::draw()
{

	for (int i = 0; i < path_cnt - 1; i++) 
	{
		int numcircle = 3;
		int div = 10;
		if (path_cnt == 2 || path_cnt == 3) div = 20;
		else div = 10;
		for (int j = 0; j <= div; j++) 
		{
			int xOffset = (int)((((float)j/(float)div)*(float)(path[i+1].x1)+ ((float)(div- j) / (float)div)*(float)(path[i].x1)));
			int yOffset = (int)((((float)j / (float)div)*(float)(path[i+1].y1) + ((float)(div - j) / (float)div)*(float)(path[i].y1)));

			for (int k = 0; k < 5; k++)
			{
				if(k == 0) ofSetColor(141, 189, 232);
				else if (k == 1) ofSetColor(28, 93, 199);
				else if (k == 2) ofSetColor(135, 206, 235);
				else if (k == 3) ofSetColor(153, 255, 252);
				else if (k == 4) ofSetColor(0, 102, 204);

				float width = ofRandom(1, 5);
				float height = ofRandom(1, 7);
				float deltaX = ofRandom(-8, 8);
				float deltaY = ofRandom(-10, 20);
				ofDrawCircle(xOffset+deltaX, yOffset+deltaY, width, height);
			}

		} 
	}

	ofSetColor(255, 0, 0);
	ofDrawCircle(x, y, 8);
	ofDrawCircle(next_x, next_y, 8);
	ofSetColor(255, 255, 255);
	ofDrawCircle(next_x, next_y, 6);
}
