#include "ofApp.h"
using namespace std;


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255);
	ofSetLineWidth(4);
	ofSetBackgroundAuto(true);
	
	Line = new struct line[100];
	sortedLine = new struct line[100];

	draw_flag = 0;
	load_flag = 0;
	water_flag = 0;
	iter_flag = 0;
	modi_flag = 0;
	select_num = 0;
	num_of_line = 0;
	game_over = 0;
	stop_flag = 0;
	Dot[0].x1 = -1;
	Dot[0].y1 = -1;
	Dot[1].x1 = -1;
	Dot[1].y1 = -1;
	myfont.load("arial", 25);
	assit.load("arial", 10);
	dot_diameter = 20.0f;
	////Ball
	Ball.success_flag = 0;
	Ball.bucket.load("bucket.png");
	Ball.congrats.load("congrats.png");
	over.load("game-over.png");
	selka.load("selka.png");
	wagwag.load("wagwag.png");
}

//--------------------------------------------------------------
void ofApp::update() {
	int fnum = ofGetFrameNum();
	if (iter_flag && water_flag == 1) {
		if (fnum % 30 == 0 && water_flag == 1 && stop_flag == 0) {
			//printf("frame number: %d\n", tmp % 10);
			water_flag = 0;
			for (int i = 0; i < water_num; i++) {
				wl[i].waterline_computation();
			}
		}
		water_flag = 1;
	}
	if (select_num == 2 && load_flag == 0) {

		////@@@@@
		//saveLineToBall();

		modi_flag = 0;
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) { // If the left mouse button is pressed...
			int tmp_x = ofGetMouseX();
			int tmp_y = ofGetMouseY();

			if (Dot[0].x1 == -1 && Dot[1].x1 == -1) {
				Dot[0].x1 = tmp_x;
				Dot[0].y1 = tmp_y;
			}
			else if (Dot[0].x1 != -1 && Dot[1].x1 == -1) {
				Dot[1].x1 = tmp_x;
				Dot[1].y1 = tmp_y;
			}

			if (Dot[1].x1 != -1) {
				for (int i = 0; i < num_of_line; i++) {
					if ((Dot[0].x1 - Line[i].x1)*(Dot[0].x1 - Line[i].x1) + (Dot[0].y1 - Line[i].y1)*(Dot[0].y1 - Line[i].y1) < 50) {
						Line[i].x1 = Dot[1].x1;
						Line[i].y1 = Dot[1].y1;
						Line[i].slope = (float)(Line[i].y2 - Line[i].y1) / (Line[i].x2 - Line[i].x1);
						modi_flag = 1;
						Dot[0].x1 = -1;
						Dot[0].y1 = -1;
						Dot[1].x1 = -1;
						Dot[1].y1 = -1;
						break;
					}

					else if ((Dot[0].x1 - Line[i].x2)*(Dot[0].x1 - Line[i].x2) + (Dot[0].y1 - Line[i].y2)*(Dot[0].y1 - Line[i].y2) < 50) {

						Line[i].x2 = Dot[1].x1;
						Line[i].y2 = Dot[1].y1;
						Line[i].slope = (float)(Line[i].y2 - Line[i].y1) / (Line[i].x2 - Line[i].x1);
						modi_flag = 1;
						Dot[0].x1 = -1;
						Dot[0].y1 = -1;
						Dot[1].x1 = -1;
						Dot[1].y1 = -1;
						break;
					}
				}
			}

			if (Dot[0].x1 != -1 && Dot[1].x1 != -1 && modi_flag == 0) {
				draw_map();
			}
			Sleep(200);
		}
	}
	if (Ball.play_flag == 1 && Ball.success_flag == 0) {
		gameOver();
		if (game_over) {
			Ball.play_flag = 0;
			stop_flag = 1;
		}
	}
	if (Ball.success_flag == 1)
		water_flag = 0;
}

//--------------------------------------------------------------
void ofApp::draw() {
	/* 메인 화면 */
	if (!draw_flag) {
		ofSetColor(119, 195, 236);  // Set the drawing color to brown

		// Draw shapes for ceiling and floor
		ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
		ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high

	}
	if (select_num == 0) {
		ofSetColor(50, 50, 50);
		myfont.drawString("0: Move to main\n\n1: Fixed map\n\n2: User made map", 405, 400);
		assit.drawString("MADE BY", 780, 700);
		ofSetColor(255);
		selka.draw(830, 550, 200, 200);
		wagwag.draw(350, 5, ofGetWidth() / 3, ofGetHeight() / 2);
	}

	/* 플레이 화면 */
	ofSetLineWidth(7);
	if (draw_flag) {
		// 맵 만들 때 점 찍은거 표시
		if (select_num == 2 && load_flag == 0) {
			ofDrawCircle(Dot[0].x1, Dot[0].y1, dot_diameter / 2);
			ofDrawCircle(Dot[1].x1, Dot[1].y1, dot_diameter / 2);
		}

		// 맵 선분들
		ofSetColor(164, 130, 106);
		for (int i = 0; i < num_of_line; i++) {
			ofDrawLine(Line[i].x1, Line[i].y1, Line[i].x2, Line[i].y2);
		}

		////Ball
		if (load_flag) {
			// 공이랑 바구니
			Ball.draw();
			Ball.draw_square();

			/* 가이드 */
			// 위
			ofSetColor(205, 94, 119);
			ofDrawRectangle(10, 10, 100, 10);
			ofSetColor(0);
			assit.drawString("UP", 120, 20);
			//아래
			ofSetColor(119, 195, 236);
			ofDrawRectangle(200, 10, 100, 10);
			ofSetColor(0);
			assit.drawString("DOWN", 320, 20);
			// 지금 점
			ofSetColor(255, 0, 0);
			ofDrawCircle(450, 15, 8);
			ofSetColor(0);
			assit.drawString("START POINT", 470, 20);
			// 다음 점
			assit.drawString("NEXT START POINT", 620, 20);
			ofSetColor(255, 0, 0);
			ofDrawCircle(600, 15, 8);
			ofSetColor(255, 255, 255);
			ofDrawCircle(600, 15, 6);

		}

		// 물 그리기
		if (water_flag) {
			ofSetLineWidth(4);
			for (int i = 0; i < water_num; i++) {
				wl[i].draw();
			}
		}

		// 성공
		if (Ball.success_flag) {
			ofSetColor(255);
			Ball.congrats.draw(ofGetWidth() / 4, ofGetHeight() / 4, ofGetWidth() / 2, ofGetHeight() / 2);
		}

		// 실패
		if (game_over) {
			over.draw(400, ofGetHeight() / 3, ofGetWidth() / 4, ofGetHeight() / 4);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'v') {
		// HACK: only needed on windows, when using ofSetAutoBackground(false)
		glReadBuffer(GL_FRONT);
		ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
	}
	if (key == 'q') {
		// Reset flags
		draw_flag = 0;

		// Free the dynamically allocated memory exits.
		delete[] Line;
		delete[] sortedLine;
		cout << "Dynamically allocated memory has been freed." << endl;

		_Exit(0);
	}
	if (key == 'd') {
		if (select_num != 2 || load_flag == 1 || Ball.play_flag) return;
		if (!num_of_line) return;
		load_flag = 1;
		draw_flag = 1;
		saveLineToBall();
		initializeWaterLines();
		Ball.draw_square();
	}
	if (key == 's') {
		if (iter_flag == 0 && draw_flag == 1 && Ball.play_flag == 0 && load_flag == 1) {
			for (int i = 0; i < water_num; i++)
				wl[i].waterline_computation();
			water_flag = 1;
			iter_flag = 1;
			Ball.play_flag = 1;
		}
	}
	if (key == 'e') {
		if (iter_flag == 1 && draw_flag == 1 && water_flag == 1) {
			iter_flag = 0;
			water_flag = 0;
			Ball.success_flag = 0;
			Ball.play_flag = 0;
			game_over = 0;
		}
	}
	///@@@@@@Ball
	if (key == OF_KEY_LEFT)
	{
		if (!Ball.play_flag || Ball.success_flag) return;
		Ball.move(1);
		Ball.success();
	}
	if (key == OF_KEY_RIGHT)
	{
		if (!Ball.play_flag || Ball.success_flag) return;
		Ball.move(2);
		Ball.success();
	}
	if (key == OF_KEY_UP)
	{
		if (!Ball.play_flag || Ball.success_flag) return;
		Ball.move(0);
		Ball.success();
	}
	if (key == OF_KEY_DOWN)
	{
		if (!Ball.play_flag || Ball.success_flag) return;
		Ball.move(3);
		Ball.success();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == '0') {
		if (Line) {
			delete[] Line;
		}
		setup();
	}
	if (key == '1') {
		if (select_num != 0) return;
		select_num = 1;
		// We have a file, so let's check it and process it
		processOpenFileSelection();
		load_flag = 1;
		draw_flag = 1;
	}
	if (key == '2') {
		if (select_num != 0) return;
		select_num = 2;
		draw_flag = 1;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::processOpenFileSelection() {
	//Path to the comma delimited file
	string fileName = "input.txt";

	//string fileName = openFileResult.getName();
	ofFile file(fileName);

	//	if (!file.exists()) cout << "Target file does not exists." << endl;
		//else cout << "We found the target file." << endl;

	ofBuffer buffer(file);

	/* This variable is for indicating which type of input is being received.
	 IF input_type == 0, then work of getting line input is in progress.
	 IF input_type == 1, then work of getting dot input is in progress.
	 */
	int input_type = 0;
	int cnt = 0;
	int countL = 0;
	int countD = 0;


	/* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
	 You must maintain those information. But, currently below code is not complete.
	 Also, note that all of coordinate should not be out of screen size.
	 However, all of coordinate do not always turn out to be the case.
	 So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
	*/


	// Read file line by line
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		string line = *it;

		// Split line into strings
		vector<string> words = ofSplitString(line, " ");

		if (words.size() == 1) {
			if (input_type == 0) { // Input for the number of lines.
				num_of_line = atoi(words[0].c_str());
				//cout << "The number of line is: " << num_of_line << endl;

			}
		}
		else if (words.size() >= 2) {
			int x1, y1, x2, y2;
			if (input_type == 0) { // Input for actual information of lines
				x1 = atoi(words[0].c_str());
				y1 = atoi(words[1].c_str());
				x2 = atoi(words[2].c_str());
				y2 = atoi(words[3].c_str());

				if (x1 < 0 || x1 > ofGetWidth()) {
					return;
				}
				if (x2 < 0 || x2 > ofGetWidth()) {
					return;
				}
				if (y1 < 0 || y1 > ofGetHeight()) {
					return;
				}
				if (y2 < 0 || y2 > ofGetHeight()) {
					return;
				}

				Line[countL].x1 = x1;
				Line[countL].y1 = y1;
				Line[countL].x2 = x2;
				Line[countL].y2 = y2;
				Line[countL].slope = (float)(y2 - y1) / (float)(x2 - x1);
				countL++;
				if (countL == num_of_line) input_type = 1;
			}

		} // End of else if.
	} // End of for-loop (Read file line by line).
	saveLineToBall();
	initializeWaterLines();
}

void ofApp::initializeWaterLines()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < water_num; i++) {
		wl[i] = waterline(num_of_line, Line);
	}
}

void ofApp::draw_map() {
	if (Dot[0].x1 < Dot[1].x1) {
		Line[num_of_line].x1 = Dot[0].x1;
		Line[num_of_line].x2 = Dot[1].x1;
		Line[num_of_line].y1 = Dot[0].y1;
		Line[num_of_line].y2 = Dot[1].y1;
	}
	else {
		Line[num_of_line].x2 = Dot[0].x1;
		Line[num_of_line].x1 = Dot[1].x1;
		Line[num_of_line].y2 = Dot[0].y1;
		Line[num_of_line].y1 = Dot[1].y1;
	}
	Line[num_of_line].slope = (float)(Dot[1].y1 - Dot[0].y1) / (Dot[1].x1 - Dot[0].x1);
	num_of_line++;
	Dot[0].x1 = -1;
	Dot[0].y1 = -1;
	Dot[1].x1 = -1;
	Dot[1].y1 = -1;
}

void ofApp::saveLineToBall()
{
	int i, j;
	int tx1, tx2, ty1, ty2;
	float tm, ts;

	for (i = 0; i < 100; i++) {
		Ball.line[i].x1 = -1;
		Ball.line[i].y1 = -1;
		Ball.line[i].x2 = -1;
		Ball.line[i].y2 = -1;
		Ball.line[i].slope = 0;
	}
	for (i = 0; i < num_of_line; i++)
	{
		sortedLine[i].x1 = Line[i].x1;
		sortedLine[i].x2 = Line[i].x2;
		sortedLine[i].y1 = Line[i].y1;
		sortedLine[i].y2 = Line[i].y2;
		sortedLine[i].m = (float(sortedLine[i].y1) + float(sortedLine[i].y2)) / 2;
		sortedLine[i].slope = float(sortedLine[i].y2 - sortedLine[i].y1) / float(sortedLine[i].x2 - sortedLine[i].x1);
	}
	for (int i = 0; i < num_of_line; i++)
	{
		for (int j = 0; j < num_of_line - i - 1; j++)
		{
			if (sortedLine[j].m > sortedLine[j + 1].m)
			{
				tx1 = sortedLine[j].x1;
				sortedLine[j].x1 = sortedLine[j + 1].x1;
				sortedLine[j + 1].x1 = tx1;
				tx2 = sortedLine[j].x2;
				sortedLine[j].x2 = sortedLine[j + 1].x2;
				sortedLine[j + 1].x2 = tx2;
				ty1 = sortedLine[j].y1;
				sortedLine[j].y1 = sortedLine[j + 1].y1;
				sortedLine[j + 1].y1 = ty1;
				ty2 = sortedLine[j].y2;
				sortedLine[j].y2 = sortedLine[j + 1].y2;
				sortedLine[j + 1].y2 = ty2;
				tm = sortedLine[j].m;
				sortedLine[j].m = sortedLine[j + 1].m;
				sortedLine[j + 1].m = tm;
				ts = sortedLine[j].slope;
				sortedLine[j].slope = sortedLine[j + 1].slope;
				sortedLine[j + 1].slope = ts;
			}
		}
	}//bubble sort / Line-> sortedLine
	Ball.line_num = num_of_line;
	Ball.diameter = dot_diameter;
	Ball.line_idx = num_of_line - 1;
	Ball.square_x = sortedLine[0].x2;
	Ball.square_y = sortedLine[0].y2;
	Ball.y = (int)(((float)sortedLine[num_of_line - 1].y1 + (float)sortedLine[num_of_line - 1].y2) / 2);
	Ball.x = (int)(((float)sortedLine[num_of_line - 1].x1 + (float)sortedLine[num_of_line - 1].x2) / 2);
	for (int i = 0; i < num_of_line; i++)
	{
		Ball.line[i].x1 = sortedLine[i].x1;
		Ball.line[i].x2 = sortedLine[i].x2;
		Ball.line[i].y1 = sortedLine[i].y1;
		Ball.line[i].y2 = sortedLine[i].y2;
		Ball.line[i].m = sortedLine[i].m;
		Ball.line[i].slope = sortedLine[i].slope;
	}

	//initialize Ball

}

void ofApp::gameOver() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < wl[i].path_cnt - 1; j++) {
			if (j % 2) {	// 선분 따라 흐르는 물
				if (Ball.y >= wl[i].path[j].y1 && Ball.y <= wl[i].path[j + 1].y1) {
					int tmpx1, tmpx2;
					tmpx1 = wl[i].path[j].x1;
					tmpx2 = wl[i].path[j + 1].x1;
					if (tmpx1 > tmpx2) {
						if (Ball.x <= tmpx1 && Ball.x >= tmpx2) {
							game_over = 1;
						}
					}
					else {
						if (Ball.x <= tmpx2 && Ball.x >= tmpx1) {
							game_over = 1;
						}
					}

				}
			}
			else {	// 아래로 떨어지는 물
				if (wl[i].path[j].y1 <= Ball.draw_y && wl[i].path[j + 1].y1 >= Ball.draw_y) {
					if (fabs(wl[i].path[j].x1 - Ball.x) < Ball.ball_diameter) {
						game_over = 1;
					}
				}
			}
		}
	}
}