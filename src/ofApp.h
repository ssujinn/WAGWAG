#pragma once

#include "ofMain.h"
#include "stdlib.h"
#include "waterline.h"
#include "ball.h"

typedef struct line {
	int x1;
	int y1;
	int x2;
	int y2;
	float slope;
	float m;
}ln;

typedef struct dot {
	int x1;
	int y1;
}dt;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	/*Ball and bucket related variables Regions*/
	ball Ball;
	ln *sortedLine;

	/* WaterFall-related member variables Regions */
	// flag variables
	int draw_flag;
	int load_flag;
	int water_flag;
	int iter_flag;
	int select_num;
	int modi_flag;
	int game_over;
	int stop_flag;

	struct line *Line;
	struct dot Dot[2];
	// Line segment and dot related variables
	int num_of_line, num_of_dot;
	float dot_diameter;
	int index = 0;
	int water_num = 5;

	waterline wl[5];
	ofTrueTypeFont myfont;
	ofTrueTypeFont assit;
	ofImage over;
	ofImage selka;
	ofImage wagwag;

	/* WaterFall-related member functions */

	void processOpenFileSelection();
	void initializeWaterLines();
	void draw_map();
	void saveLineToBall();
	void gameOver();
};
