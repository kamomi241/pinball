#include "Input.h"
#include "DxLib.h"

#include "Vector2D.h"

using namespace DxLib;

Input* Input::m_instance = 0;

Input::Input():
	m_mousePoint(0.0f,0.0f),
	m_mouseState(0),
	m_intMouseX(0),
	m_intMouseY(0),
	m_oldMouseState(0)
{
	GetHitKeyStateAll(m_keyState);
	GetHitKeyStateAll(m_oldKeyState);
}

Input::~Input() {}

Input* Input::instance() {
	return m_instance;
}

void Input::create() {
	if (!m_instance) {
		m_instance = new Input();
	}
}

void Input::destroy() {
	delete m_instance;
}

void Input::keyboardCheck() {
	memcpy(m_oldKeyState, m_keyState, sizeof(m_keyState) );
	GetHitKeyStateAll(m_keyState);
}

void Input::mouseCheck() {
	GetMousePoint(&m_intMouseX, &m_intMouseY);
	m_mousePoint.x = (double)m_intMouseX;
	m_mousePoint.y = (double)m_intMouseY;

	m_oldMouseState = m_mouseState;
	m_mouseState = GetMouseInput();
}

void Input::inputStatsReset() {
	m_oldMouseState = 0;
	for (int i = 0; i < 256; i++)
	{
		m_oldKeyState[i] = 0;
	}
}


bool Input::isKeyPressed(unsigned char key) const
{
	if (m_keyState[key] == 1 && m_oldKeyState[key] == 0) return TRUE;
	return FALSE;
}
bool Input::isKeyReleased(unsigned char key) const
{
	if (m_keyState[key] == 0 && m_oldKeyState[key] == 1) return TRUE;
	return FALSE;
}
bool Input::isKeyDown(unsigned char key) const
{
	if (m_keyState[key] == 1) return TRUE;
	return FALSE;
}
bool Input::isKeyUp(unsigned char key) const
{
	if (m_keyState[key] == 0) return TRUE;
	return FALSE;
}

bool Input::isKeyKeepPressing(unsigned char key) const
{
	if (m_keyState[key] == 1 && m_oldKeyState[key] == 1) return TRUE;
	return FALSE;
}


bool Input::isMousePressed(char button) const
{
	if ((m_mouseState & button) && !(m_oldMouseState & button))
		return TRUE;
	return FALSE;
}
bool Input::isMouseReleased(char button) const 
{
	if ((m_oldMouseState & button) && !(m_mouseState & button))
		return TRUE;
	return FALSE;
}
bool Input::isMouseDown(char button) const
{
	if (m_mouseState & button)
		return TRUE;
	return FALSE;
}
bool Input::isMouseUp(char button) const
{
	if (m_mouseState & button)
		return FALSE;
	return TRUE;
}

bool Input::isMouseKeepPressing(char button) const
{
	if ((m_oldMouseState & button) && (m_mouseState & button))
		return TRUE;
	return FALSE;
}

double Input::getMouseX() const
{
	return m_mousePoint.x;
}
double Input::getMouseY() const
{
	return m_mousePoint.y;
}


bool Input::isClickedRect(int x1, int y1, int x2, int y2, char button) const
{
	if ((m_mouseState & button) && (m_oldMouseState ^ button))
	{
		if (((x1 > m_mousePoint.x && x2 < m_mousePoint.x) || (x1 < m_mousePoint.x && x2 > m_mousePoint.x)) && 
			((y1 > m_mousePoint.y && y2 < m_mousePoint.y) || (y1 < m_mousePoint.y && y2 > m_mousePoint.y)))
			return TRUE;
	}
	return FALSE;
}

bool Input::isOnRect(int x1, int y1, int x2, int y2) const
{
	if (((x1 > m_mousePoint.x && x2 < m_mousePoint.x) || (x1 < m_mousePoint.x && x2 > m_mousePoint.x)) && 
		((y1 > m_mousePoint.y && y2 < m_mousePoint.y) || (y1 < m_mousePoint.y && y2 > m_mousePoint.y)))
		return TRUE;
	return FALSE;
}

Vector2D Input::getMouseVector() const
{
	return m_mousePoint;
}
