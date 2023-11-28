#pragma once

#include <string>
#include <vector>
#include <map>

struct espConfig {
	bool state = false;
	bool checkSpotted;

	bool boundBox;
	float boundBoxThickness = 1.f;
	float spottedColours[3] = { 1.f,1.f,1.f };
	float notSpottedColours[3] = { 1.f,1.f,1.f };
	float width = 2.5f;

	bool isPawnName;
	std::string pawnName;



	bool isHealthBar;
	bool hpCounter;
	float health[3];

	float attributeColours[3] = { 1.f,1.f,1.f };

	bool skeleton;
	float skeletonColours[3] = { 1.f,1.f,1.f };



	bool distance;
};
inline espConfig espConf = {};



enum bones : int {
	head = 6,
	neck = 5,
	chest = 4,
	shoulderRight = 8,
	shoulderLeft = 13,
	elbowRight = 9,
	elbowLeft = 14,
	handRight = 11,
	handLeft = 16,
	crotch = 0,
	kneeRight = 23,
	kneeLeft = 26,
	ankleRight = 24,
	ankleLeft = 27,
};


inline namespace boneGroups {
	inline std::vector<int> mid = {bones::head,bones::neck,bones::chest,bones::crotch};
	inline std::vector<int> leftArm = { bones::neck,bones::shoulderLeft,bones::elbowLeft,bones::handLeft};
	inline std::vector<int> righttArm = { bones::neck,bones::shoulderRight,bones::elbowRight,bones::handRight };
	inline std::vector<int> leftLeg = {bones::crotch,bones::kneeLeft,bones::ankleLeft};
	inline std::vector<int> rightLeg = { bones::crotch,bones::kneeRight,bones::ankleRight};
	inline std::vector<std::vector<int>> allGroups = {mid,leftArm,righttArm,leftLeg,rightLeg};
};