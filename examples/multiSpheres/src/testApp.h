#pragma once

#include "ofMain.h"
#include "ofxPolyvox.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofEasyCam cam;
		ofxPolyvox poly;
		ofMesh outMesh;

		vector <Vector3DFloat> centers;
		vector <float> radii;

		int num;
        	int maxDim;
};
