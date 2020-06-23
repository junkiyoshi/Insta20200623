#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);

	this->inner_size = 150;
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> outer_vertices = { 
		glm::vec2(0, 0),
		glm::vec2(0, ofGetHeight()),
		glm::vec2(ofGetWidth(), ofGetHeight()),
		glm::vec2(ofGetWidth(), 0)
	};

	vector<glm::vec2> inner_vertices = { 
		glm::vec2(ofGetWidth() * 0.5 - this->inner_size, ofGetHeight() * 0.5 - this->inner_size),
		glm::vec2(ofGetWidth() * 0.5 - this->inner_size, ofGetHeight() * 0.5 + this->inner_size),
		glm::vec2(ofGetWidth() * 0.5 + this->inner_size, ofGetHeight() * 0.5 + this->inner_size),
		glm::vec2(ofGetWidth() * 0.5 + this->inner_size, ofGetHeight() * 0.5 - this->inner_size)
	};


	this->draw_particles(16);

	ofFill();
	ofSetColor(239);
	ofBeginShape();
	ofVertices(outer_vertices);
	ofNextContour(true);
	ofVertices(inner_vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(39);
	ofBeginShape();
	ofVertices(outer_vertices);
	ofNextContour(true);
	ofVertices(inner_vertices);
	ofEndShape(true);

	this->draw_particles(8);
}


//--------------------------------------------------------------
void ofApp::draw_particles(int count) {

	ofSetColor(39);
	for (int i = 0; i < count; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		auto location = glm::vec2();
		vector<glm::vec2> vertices;
		for (int k = 0; k < 15; k++) {

			location = glm::vec2(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + k) * 0.005), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + k) * 0.005), 0, 1, 0, ofGetHeight()));
			vertices.push_back(location);
		}

		ofNoFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		ofFill();
		ofDrawCircle(location, 8);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}