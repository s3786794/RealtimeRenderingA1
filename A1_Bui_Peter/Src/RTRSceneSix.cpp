#include "RTRSceneSix.h"
#include "Geometry.h"

RTRSceneSix::RTRSceneSix(float windowWidth, float windowHeight)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 1;
	m_Faces = 1;
}

void RTRSceneSix::Init() {
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void RTRSceneSix::End() {

}

void RTRSceneSix::DrawAll() {
	Geometry* geom = new Geometry();

	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.0);
	geom->DrawTriangle(0.6, 0.9, -0.2, 0.1, 0.5, 1.0);
	geom->DrawTriangle(-0.6, -0.9, -0.2, 0.1, 1.0, 0.5);

	geom->DrawTriangle(0.4, 0.6, 0.0, 0.0, 0.0, 1.0);
	geom->DrawTriangle(-0.4, -0.6, 0.0, 0.0, 1.0, 0.0);
	glPopMatrix();

	glUseProgram(0);
}

bool* RTRSceneSix::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneSix::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneSix::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

void RTRSceneSix::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneSix::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneSix::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneSix::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneSix::GetVertices()
{
	int* number = &m_Vertices;
	return number;
}

int* RTRSceneSix::GetFaces()
{
	int* number = &m_Faces;
	return number;
}

void RTRSceneSix::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneSix::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneSix::IncrementVertices()
{
	m_Vertices += 1;
}

void RTRSceneSix::DecrementVertices()
{
	m_Vertices -= 1;
}

void RTRSceneSix::IncrementFaces()
{
	m_Faces += 1;
}

void RTRSceneSix::DecrementFaces()
{
	m_Faces -= 1;
}