#include "object.h"

Object::Object() : m_diffSq(0.0),m_isCollide(false) {

}

Object::~Object() {}


void Object::setPoint(double point) {
	m_diffSq = point;
	m_isCollide = true;
}

double Object::getPoint() {
		return m_diffSq;
}

bool Object::getIsCollide() {
	return m_isCollide;
}

void Object::reset() {
	m_diffSq = 0.0;
	m_isCollide = false;
}




