#include "RTRSceneOne.h"

RTRSceneOne::RTRSceneOne(float windowWidth, float windowHeight, std::vector<GLfloat> vertexAndNormals, 
	std::vector<int> faces, Lighting* lighting)
{
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
	m_DepthState = false;
	m_BackfaceState = false;
	m_LightingState = false;
	m_Subdivisions = 1;
	m_Vertices = 8;
	m_Faces = 6;
	m_NumLights = 0;
	m_VertexData = 0.0f;

	amountOfVertices.push_back(m_Vertices);
	amountOfFaces.push_back(m_Faces);

	geom = new Geometry;
	cube = new Cube(0.0f, 0.0f, 0.0f, 1.0f);
	Cubes.push_back(*cube);
	sceneLighting = lighting;

	facesCopy = faces;
	std::vector<std::vector<GLfloat>> placeholder;
	placeholder.push_back(vertexAndNormals);
	listOfVertexes.push_back(placeholder);
	listOfMidVertexes.push_back(vertexAndNormals);
}

void RTRSceneOne::Init() {
}

void RTRSceneOne::End() {
	geom = nullptr;
	cube = nullptr;
	sceneLighting = nullptr;
	facesCopy.clear();

	for (auto tier1 : listOfVertexes) {
		for (auto tier2 : tier1) {
			tier2.clear();
		}
	}
	listOfVertexes.clear();
}

void RTRSceneOne::DrawAll(Camera* camera) {
	int currSubdivision = m_Subdivisions - 1;
	geom->DrawCubeWithPointsImmediate(listOfVertexes.at(currSubdivision), facesCopy, m_LightingState);
	camera->ImmediateCamera(m_WindowWidth, m_WindowHeight);
	m_VertexData = listOfVertexes.at(currSubdivision).size() * 
		listOfVertexes.at(currSubdivision).at(0).size() * sizeof(GLfloat);
}

void RTRSceneOne::CreateCubes()
{
	int currCalSubdivision = m_Subdivisions - 1;

	if (listOfVertexes.size() == m_Subdivisions) {
		std::vector<Cube> newCube;

		for (Cube currCube : Cubes) {
			std::vector<Cube> createdCube = currCube.CalculateCube();
			newCube.insert(newCube.end(), createdCube.begin(), createdCube.end());
		}

		this->Cubes = newCube;

		std::vector<std::vector<GLfloat>> newVertexPositions;
		std::vector<GLfloat> currVector = listOfMidVertexes.at(currCalSubdivision);

		for (auto& currCube : Cubes) {
			std::vector<GLfloat> newPositions = cube->CalculateNewPositionsImmediate(currCube, currVector);
			newVertexPositions.push_back(newPositions);
		}

		listOfVertexes.push_back(newVertexPositions);

		int totalFaces = 6 * newVertexPositions.size();
		int totalVertices = 8 * newVertexPositions.size();

		amountOfFaces.push_back(totalFaces);
		amountOfVertices.push_back(totalVertices);

		// calculate middle cube position
		cube->CalculateNewRadius();

		std::vector<GLfloat> storingNewMidVector = cube->CalculateNewPositionsImmediate(*cube, currVector);
		listOfMidVertexes.push_back(storingNewMidVector);
	}
}

bool* RTRSceneOne::GetDepthBuffer()
{
	bool* state = &m_DepthState;
	return state;
}

bool* RTRSceneOne::GetBackface()
{
	bool* state = &m_BackfaceState;
	return state;
}

bool* RTRSceneOne::GetLighting()
{
	bool* state = &m_LightingState;
	return state;
}

int* RTRSceneOne::GetNumLights()
{
	int* number = &m_NumLights;
	return number;
}

void RTRSceneOne::ToggleDepthBuffer()
{
	m_DepthState = !m_DepthState;
}

void RTRSceneOne::ToggleBackface()
{
	m_BackfaceState = !m_BackfaceState;
}

void RTRSceneOne::ToggleLighting()
{
	m_LightingState = !m_LightingState;
}

int* RTRSceneOne::GetSubdivisions()
{
	int* number = &m_Subdivisions;
	return number;
}

int* RTRSceneOne::GetVertices()
{
	int currSubdivision = m_Subdivisions - 1;
	int* number = &amountOfVertices.at(currSubdivision);
	return number;
}

int* RTRSceneOne::GetFaces()
{
	int currSubdivision = m_Subdivisions - 1;
	int* number = &amountOfFaces.at(currSubdivision);
	return number;
}

float* RTRSceneOne::GetVertexData()
{
	float* number = &m_VertexData;
	return number;
}

void RTRSceneOne::IncrementSubdivision()
{
	m_Subdivisions += 1;
}

void RTRSceneOne::DecrementSubdivision()
{
	m_Subdivisions -= 1;
}

void RTRSceneOne::IncrementLights()
{
	if (m_NumLights < 8) {
		m_NumLights += 1;
	}
}

void RTRSceneOne::DecrementLights()
{
	m_NumLights -= 1;
}

