#include "AABB.h"
#include <iostream>
#include <vector>

const glm::vec2 rect_vert = glm::vec2(-1,0);
const glm::vec2 rect_horz = glm::vec2(0,1);

float dotProduct(const glm::vec2& A, const glm::vec2& B) {
	return A.x * B.x + A.y * B.y;
}

glm::vec2 normal(const glm::vec2& vec) {
	return glm::vec2(-vec.y, vec.x);
}

glm::vec2 AABB::getPoint(int num) {
	switch (num) {
	case 0:
		return centerPoint();
	case 1:
		return topLeft();
	case 2:
		return bottomLeft();
	case 3:
		return bottomRight();
	case 4:
		return topRight();
	default:
		std::cout << "[ERROR]: Invalid Point Number - getPoint() in AABB.cpp" << std::endl;
		return glm::vec2(0,0);
	}
}

void findMinMax(float& minProj, float& maxProj, const std::vector<glm::vec2>& box, glm::vec2 axis) {
	if (box.size() <= 0) {
		std::cout << "[ERROR]: In AABB.cpp, function 'findMinAndMax', has an error" << std::endl;
	}
	
	//Find the min and max projections
	//We start at [1] because [0] is the center point
	float minProj1 = dotProduct(box[1], axis);
	float maxProj1 = dotProduct(box[1], axis);

	for (int i = 2; i < box.size(); i++) {
		float currProj1 = dotProduct(box[i], axis);

		//Pick the min projection
		if (currProj1 < minProj1) {
			minProj1 = currProj1;
		}

		//Pick the max projection
		if (currProj1 > maxProj1) {
			maxProj1 = currProj1;
		}
	}
}

bool AABB::intersects(AABB* box) {

	//Get the points
	std::vector<glm::vec2> box1;
	std::vector<glm::vec2> box2;

	for (int i = 0; i < 5; i++) {
		box1.push_back(this->getPoint(i));
		box2.push_back(box->getPoint(i));
	}
	
	float p1_min, p1_max,
		p2_min, p2_max,
		q1_min, q1_max,
		q2_min, q2_max;

	// You owuld need to copy this again to check the normals of the other rectangle if stuff was rotated
	findMinMax(p1_min, p1_max, box1, rect_vert);
	findMinMax(p2_min, p2_max, box2, rect_vert);
	findMinMax(q1_min, q1_max, box1, rect_horz);
	findMinMax(q2_min, q2_max, box2, rect_horz);

	//Check for seperation
	bool p = p1_max < p2_min || p2_max < p1_min;
	bool q = q1_max < q2_min || q2_max < q1_min;

	bool isSeperated = p || q;

	return false;

	//return !isSeperated;
}