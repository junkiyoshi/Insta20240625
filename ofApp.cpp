#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font_size = 120;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 1.44);

	string word = "JunKiyoshi.com";
	int sample_count = 60;
	vector<glm::vec3> base_location = { glm::vec3() };

	ofColor color;
	for (int k = 0; k < base_location.size(); k++) {

		auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int i = 0; i < word.size(); i++) {

			ofPath chara_path = this->font.getCharacterAsPoints(word[i], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofFill();
			ofSetColor(0);
			for (int radius = 200; radius <= 320; radius += 10) {

				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
					for (auto& vertex : vertices) {

						auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, radius);
						auto rotation = glm::rotate(glm::mat4(), (i * 23.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
						location = glm::vec4(location, 0) * rotation;

						auto noise_location = glm::normalize(location);
						auto angle_x = ofMap(ofNoise(noise_param.x, noise_location.x * 0.5, radius * 0.002 + ofGetFrameNum() * 0.02), 0, 1, -PI * 0.25, PI * 0.25);
						auto angle_y = ofMap(ofNoise(noise_param.x, noise_location.y * 0.5, radius * 0.002 + ofGetFrameNum() * 0.02), 0, 1, -PI * 0.25, PI * 0.25);
						auto angle_z = ofMap(ofNoise(noise_param.x, noise_location.z * 0.5, radius * 0.002 + ofGetFrameNum() * 0.02), 0, 1, -PI * 0.25, PI * 0.25);

						auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
						auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
						auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

						location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;
						location = glm::normalize(location) * radius;
						location += base_location[k];

						ofVertex(location);
					}
				}
				ofEndShape(true);
			}

			ofNoFill();
			for (int radius = 200; radius <= 320; radius += 10) {

				color.setHsb(ofMap(radius, 200, 320, 0, 255), 180, 255);
				ofSetColor(color);

				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
					for (auto& vertex : vertices) {

						auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, radius);
						auto rotation = glm::rotate(glm::mat4(), (i * 23.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
						location = glm::vec4(location, 0) * rotation;

						auto noise_location = glm::normalize(location);
						auto angle_x = ofMap(ofNoise(noise_param.x, noise_location.x * 0.5, radius * 0.002 + ofGetFrameNum() * 0.02), 0, 1, -PI * 0.25, PI * 0.25);
						auto angle_y = ofMap(ofNoise(noise_param.x, noise_location.y * 0.5, radius * 0.002 + ofGetFrameNum() * 0.02), 0, 1, -PI * 0.25, PI * 0.25);
						auto angle_z = ofMap(ofNoise(noise_param.x, noise_location.z * 0.5, radius * 0.002 + ofGetFrameNum() * 0.02), 0, 1, -PI * 0.25, PI * 0.25);

						auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
						auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
						auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

						location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;
						location = glm::normalize(location) * radius;
						location += base_location[k];

						ofVertex(location);
					}
				}
				ofEndShape(true);
			}
		}
	}
	this->cam.end();

	/*
	int start = 225;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}