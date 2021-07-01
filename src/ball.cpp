#include "ball.h"

ball::ball()
{
	//printf("\n\nI am ball !!!!\n\n");
}

ball::~ball()
{
}

int ball::move(int st)
{
	if (st == 0)
	{
		if (line_idx > 0)
		{
			prev_x = x;
			prev_y = y;
			line_idx--;
			y = (int)(((float)line[line_idx].y1 + (float)line[line_idx].y2) / 2);
			x = (int)(((float)line[line_idx].x1 + (float)line[line_idx].x2) / 2);
		}
	}//up
	if (st == 1)
	{
		prev_x = x;
		prev_y = y;
		if (x - 10 <= line[line_idx].x1) x = line[line_idx].x1;
		else x -= 10;
		y = (int)(line[line_idx].slope * (float)(x - line[line_idx].x1) + (float)line[line_idx].y1);
	}//left
	if (st == 2)
	{
		prev_x = x;
		prev_y = y;
		if (x + 10 >= line[line_idx].x2) x = line[line_idx].x2;
		else x += 10;
		y = (int)(line[line_idx].slope * (float)(x - line[line_idx].x1) + (float)line[line_idx].y1);
	}//right

	if (st == 3)
	{
		if (line_idx < line_num - 1)
		{
			line_idx++;
			prev_x = x;
			prev_y = y;
			y = (int)(((float)line[line_idx].y1 + (float)line[line_idx].y2) / 2);
			x = (int)(((float)line[line_idx].x1 + (float)line[line_idx].x2) / 2);
		}
	}//down
	return 0;
}

void ball::draw_square()
{
	ofSetColor(255);
	bucket.draw(square_x-square_diameter/2, square_y-square_diameter/2, square_diameter, square_diameter);
}

void ball::draw()
{
	if (square_x - square_diameter/2 <= x && x <= square_x + square_diameter/ 2 && square_y - square_diameter/ 2 <= y && y <= square_y + square_diameter/ 2)
	{
		draw_square();
	}
	ofSetColor(0, ofRandom(100) + 155, 0);
	draw_y = y - ball_diameter / 2 - 10;
	ofDrawCircle(x, draw_y, ball_diameter);///draw ball
	ofSetLineWidth(7);

	ofSetColor(119, 195, 236);
	ofDrawLine(line[line_idx + 1].x1, line[line_idx + 1].y1, line[line_idx + 1].x2, line[line_idx + 1].y2);
	
	ofSetColor(205, 94, 119);
	ofDrawLine(line[line_idx - 1].x1, line[line_idx - 1].y1, line[line_idx - 1].x2, line[line_idx - 1].y2);
}

int ball::success()
{
	if (square_x -5 <= x && x <= square_x + 5 && square_y - 5 <= y && y <= square_y + 5)
	{
		play_flag = 0;
		ofSetColor(255);
		congrats.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2, ofGetHeight() / 2);
		success_flag = 1;
		return 1;
	}
	else
	{
		return 0;
	}
}
