#include "Geometry.h"

Geometry::Geometry()
{
	sceneShader = nullptr;
}

Geometry::Geometry(RTRShader* shader) {
	sceneShader = shader;
}

void Geometry::DrawCubeWithPointsImmediate(std::vector<std::vector<GLfloat>> vertexAndNormalsHolder, 
	std::vector<int> faces) {
	glBegin(GL_TRIANGLES);
	for (auto& VANVertex : vertexAndNormalsHolder) {
		for (int j = 0; j < VANVertex.size() / 24; j++) {
			for (int i = 0; i < faces.size(); i++) {
				int posVertexX = (faces.at(i) + (faces.at(i) * 5)) + (j * 24);
				int posVertexY = (faces.at(i) + (faces.at(i) * 5) + 1) + (j * 24);
				int posVertexZ = (faces.at(i) + (faces.at(i) * 5) + 2) + (j * 24);

				GLfloat colours = (float)i * 0.15f;
				
				GLfloat ambientArray[] = { 0.6f, 0.6f, 0.6f, 1.0f };
				GLfloat diffuseArray[] = { 0.8f, 0.8f, 0.8f, 1.0f };
				GLfloat specularArray[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				GLfloat shinyArray[] = { 50.0f };

				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientArray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinyArray);

				glColor3f(colours, colours, colours);
				glVertex3f(VANVertex.at(posVertexX),
					VANVertex.at(posVertexY),
					VANVertex.at(posVertexZ));
			}
		}
	}
	glEnd();
	glUseProgram(0);
}

void Geometry::DrawCubeWithPoints(int size) {
	glm::mat4 model = glm::mat4(1.0f);
	sceneShader->SetMat4("model", model);

	int newSize = 36 * size;

	glDrawArrays(GL_TRIANGLES, 0, newSize);
}

void Geometry::DrawMultipleCubes(int currSubdivision, std::vector<Cube> cubePositions, 
	std::vector<glm::vec3> cubePositionsInWorld) {
	std::vector<glm::vec3> cubeRotations = {
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.33f, 0.33f),
		glm::vec3(0.33f, 1.0f, 0.33f),
		glm::vec3(0.33f, 0.33f, 1.0f),
		glm::vec3(1.0f, 0.66f, 0.66f),
		glm::vec3(0.66f, 1.0f, 0.66f),
		glm::vec3(0.66f, 0.66f, 1.0f)
	};

	std::vector<GLfloat> cubeAngles = {
		15.0f, 30.0f, 45.0f, 60.0f, 75.0f,
		-20.0f, -40.0f, -60.0f, -80.0f
	};

	for (int c = 0; c < cubePositionsInWorld.size(); c++) {
		for (int i = 0; i < cubePositions.size(); i++) {
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, cubePositionsInWorld.at(c));
			model = glm::rotate(model, glm::radians(cubeAngles.at(c)) * SDL_GetTicks() / 1000.0f, cubeRotations.at(c));

			glm::vec3 currCubePos = glm::vec3(*cubePositions.at(i).GetPosX(), *cubePositions.at(i).GetPosY(), *cubePositions.at(i).GetPosZ());

			model = glm::translate(model, currCubePos);
			model = glm::scale(model, glm::vec3(pow(0.34f, currSubdivision)));

			sceneShader->SetMat4("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
	}
}

void Geometry::DrawCubeArrayInstanced(int size) {
	int newSize = 36 * size;

	glDrawArraysInstanced(GL_TRIANGLES, 0, newSize, 9);
}
