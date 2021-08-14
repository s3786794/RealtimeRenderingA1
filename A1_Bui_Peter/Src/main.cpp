//-----------------------------------------------------------------------------
// main.cpp
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include "RTRApp.h"
#include "RTRSceneOne.h"
#include "RTRSceneTwo.h"
#include "RTRSceneThree.h"
#include "RTRSceneFour.h"
#include "RTRSceneFive.h"
#include "RTRSceneSix.h"
#include "Camera.h"

#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class AssignmentApp : public RTRApp
{
public:
    AssignmentApp(const char* title, bool fullscreen = false, int width = 1024, int height = 768)
        : RTRApp(title, fullscreen, width, height) {}
    int Init();
    void Done();
    bool Tick(unsigned int td_milli);

private:
    bool m_QuitApp = false;

    bool m_ShowOSD = true;
    int m_CurrSceneNum = 1;
    float m_ResolutionRate = 0;
    float m_RefreshRate = 0;
    float m_FPS = 0;
    float m_VertexData = 0;
    int m_NumOfLights = 1;

    RTRSceneBase* ListOfScenes[6] = {};
    RTRSceneBase* m_CurrScene = nullptr;

    /*float* VertexPointsAndColours[100] = {};*/

    Camera* camera = new Camera();

    float deltaX = 0.0f;
    float deltaY = 0.0f;

    void CheckInput();
    void UpdateState(unsigned int td_milli);
    void RenderFrame();
    void RenderOSD();
};

bool AssignmentApp::Tick(unsigned int td_milli)
{
    m_QuitApp = false;
    CheckInput();
    UpdateState(td_milli);
    RenderFrame();
    return m_QuitApp;
}

void AssignmentApp::CheckInput()
{
    SDL_Event event;
    SDL_WaitEvent(&event);
    /*SDL_PollEvent(&event);*/

    glm::vec3 cameraPos = *camera->GetCameraPos();
    glm::vec3 cameraFront = *camera->GetCameraFront();
    glm::vec3 cameraUp = *camera->GetCameraUp();
    float cameraDeltaTime = *camera->GetDeltaTime();
    const float cameraSpeed = *camera->GetCameraSpeed() * cameraDeltaTime;

    switch (event.type) {
    case SDL_MOUSEMOTION:
        camera->Mouse_Callback(m_SDLWindow, event.motion.x, event.motion.y);
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            m_QuitApp = true;
            break;

            // Changing scenes 1...6
        case SDLK_1:
            m_CurrSceneNum = 1;
            break;
        case SDLK_2:
            m_CurrSceneNum = 2;
            break;
        case SDLK_3:
            m_CurrSceneNum = 3;
            break;
        case SDLK_4:
            m_CurrSceneNum = 4;
            break;
        case SDLK_5:
            m_CurrSceneNum = 5;
            break;
        case SDLK_6:
            m_CurrSceneNum = 6;
            break;

            // Camera Controls
        case SDLK_w:
            cameraPos -= cameraSpeed * cameraFront;
            camera->SetCameraPos(cameraPos);
            break;

        case SDLK_s:
            cameraPos += cameraSpeed * cameraFront;
            camera->SetCameraPos(cameraPos);
            break;

        case SDLK_a:
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            camera->SetCameraPos(cameraPos);
            break;

        case SDLK_d:
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            camera->SetCameraPos(cameraPos);
            break;

            // Increment/Decrement Subdivision
        case SDLK_EQUALS:
            ListOfScenes[m_CurrSceneNum - 1]->IncrementSubdivision();
            break;
        case SDLK_KP_PLUS:
            ListOfScenes[m_CurrSceneNum - 1]->IncrementSubdivision();
            break;

        case SDLK_MINUS:
            if (*ListOfScenes[m_CurrSceneNum - 1]->GetSubdivisions() > 1) {
                ListOfScenes[m_CurrSceneNum - 1]->DecrementSubdivision();
                break;
            }
            else {
                break;
            }
        case SDLK_KP_MINUS:
            if (*ListOfScenes[m_CurrSceneNum - 1]->GetSubdivisions() > 1) {
                ListOfScenes[m_CurrSceneNum - 1]->DecrementSubdivision();
                break;
            }
            else {
                break;
            }

            // Showing OSD
        case SDLK_h:
            m_ShowOSD = !m_ShowOSD;
            break;

            // Toggle Lighting
        case SDLK_l:
            ListOfScenes[m_CurrSceneNum - 1]->ToggleLighting();
            break;

            // Increment/Decrement # of Lights
        case SDLK_PERIOD:
            m_NumOfLights += 1;
            break;

        case SDLK_COMMA:
            if (m_NumOfLights > 1) {
                m_NumOfLights -= 1;
                break;
            }
            else {
                break;
            }

            // Toggle Depth Buffering
        case SDLK_z:
            ListOfScenes[m_CurrSceneNum - 1]->ToggleDepthBuffer();
            break;

            // Toggle Backface Culling
        case SDLK_c:
            ListOfScenes[m_CurrSceneNum - 1]->ToggleBackface();
            break;
        }
    }
}

void AssignmentApp::UpdateState(unsigned int td_milli)
{
    // This is where we will do all our model updating, physics, etc...
}

// Render On-Screen Display
void AssignmentApp::RenderOSD()
{
    // Scene name, display, fps, subdivisions, vertices, faces, data, lighting, depth, backface
    GLTtext* scene_num = gltCreateText();
    GLTtext* display_rates = gltCreateText();
    GLTtext* fps_rates = gltCreateText();
    GLTtext* subdivision_num = gltCreateText();
    GLTtext* vertices_num = gltCreateText();
    GLTtext* faces_num = gltCreateText();
    GLTtext* data_num = gltCreateText();
    GLTtext* lights_on = gltCreateText();
    GLTtext* depth_on = gltCreateText();
    GLTtext* backface_on = gltCreateText();

    std::string sceneNumText = "Scene: " + std::to_string(m_CurrSceneNum);
    std::string displayText = "Resolution: " + std::to_string(m_ResolutionRate) +
        " Refresh: " + std::to_string(m_RefreshRate);
    std::string fpsText = "FPS: " + std::to_string(m_FPS);
    std::string subdivisionText = "# of Subdivisions: " + std::to_string(
        *ListOfScenes[m_CurrSceneNum - 1]->GetSubdivisions());
    std::string verticesText = "# of Vertices: " + std::to_string(
        *ListOfScenes[m_CurrSceneNum - 1]->GetVertices());
    std::string facesText = "# of Faces: " + std::to_string(
        *ListOfScenes[m_CurrSceneNum - 1]->GetFaces());
    std::string vertexDataText = "Vertex Data: " + std::to_string(m_VertexData);
    std::string lightsOnText = "";
    std::string depthOnText = "";
    std::string backfaceOnText = "";

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetLighting()) {
        lightsOnText = "Lights On";
    }
    else {
        lightsOnText = "Lights Off";
    }

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetDepthBuffer()) {
        depthOnText = "Buffer On";
    }
    else {
        depthOnText = "Buffer Off";
    }

    if (*ListOfScenes[m_CurrSceneNum - 1]->GetBackface()) {
        backfaceOnText = "Backface On";
    }
    else {
        backfaceOnText = "Backface Off";
    }

    gltSetText(scene_num, sceneNumText.c_str());
    gltSetText(display_rates, displayText.c_str());
    gltSetText(fps_rates, fpsText.c_str());
    gltSetText(subdivision_num, subdivisionText.c_str());
    gltSetText(vertices_num, verticesText.c_str());
    gltSetText(faces_num, facesText.c_str());
    gltSetText(data_num, vertexDataText.c_str());
    gltSetText(lights_on, lightsOnText.c_str());
    gltSetText(depth_on, depthOnText.c_str());
    gltSetText(backface_on, backfaceOnText.c_str());

    gltBeginDraw();
    gltColor(0.0f, 1.0f, 0.0f, 1.0f);
    gltDrawText2D(scene_num, 10, 10, 2.0);
    gltDrawText2D(display_rates, 10, 60, 2.0);
    gltDrawText2D(fps_rates, 10, 110, 2.0);
    gltDrawText2D(subdivision_num, 10, 160, 2.0);
    gltDrawText2D(vertices_num, 10, 210, 2.0);
    gltDrawText2D(faces_num, 10, 260, 2.0);
    gltDrawText2D(data_num, 10, 310, 2.0);
    gltDrawText2D(lights_on, 10, 360, 2.0);
    gltDrawText2D(depth_on, 10, 410, 2.0);
    gltDrawText2D(backface_on, 10, 460, 2.0);
    gltEndDraw();
    glUseProgram(0);

    gltDeleteText(scene_num);
    gltDeleteText(display_rates);
    gltDeleteText(fps_rates);
    gltDeleteText(subdivision_num);
    gltDeleteText(vertices_num);
    gltDeleteText(faces_num);
    gltDeleteText(data_num);
    gltDeleteText(lights_on);
    gltDeleteText(depth_on);
    gltDeleteText(backface_on);
}

void AssignmentApp::RenderFrame()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_WindowWidth, m_WindowHeight);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_CurrScene = ListOfScenes[m_CurrSceneNum - 1];
    m_CurrScene->Init();
    m_CurrScene->DrawAll();

    if (m_CurrSceneNum == 1) {
        camera->ImmediateCamera();
    }
    else {
        camera->ModernCamera();
    }

    if (m_ShowOSD) {
        RenderOSD();
    }


    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("Error");

    SDL_GL_SwapWindow(m_SDLWindow);
}

int AssignmentApp::Init()
{
    if (int err = RTRApp::Init() != 0) {
        return err;
    }

    /*SDL_ShowCursor(SDL_DISABLE);*/

    /*SDL_SetRelativeMouseMode(SDL_TRUE);*/

    gltInit();

    // Instantiate all 6 scenes in an array/data struct
    RTRSceneBase* sceneOne = new RTRSceneOne(m_WindowWidth, m_WindowHeight);
    RTRSceneBase* sceneTwo = new RTRSceneTwo(m_WindowWidth, m_WindowHeight);
    RTRSceneBase* sceneThree = new RTRSceneThree(m_WindowWidth, m_WindowHeight);
    RTRSceneBase* sceneFour = new RTRSceneFour(m_WindowWidth, m_WindowHeight);
    RTRSceneBase* sceneFive = new RTRSceneFive(m_WindowWidth, m_WindowHeight);
    RTRSceneBase* sceneSix = new RTRSceneSix(m_WindowWidth, m_WindowHeight);

    ListOfScenes[0] = sceneOne;
    ListOfScenes[1] = sceneTwo;
    ListOfScenes[2] = sceneThree;
    ListOfScenes[3] = sceneFour;
    ListOfScenes[4] = sceneFive;
    ListOfScenes[5] = sceneSix;

    return 0;
}

void AssignmentApp::Done()
{
    gltTerminate();

    RTRApp::Done();

    ListOfScenes[0] = nullptr;
    ListOfScenes[1] = nullptr;
    ListOfScenes[2] = nullptr;
    ListOfScenes[3] = nullptr;
    ListOfScenes[4] = nullptr;
    ListOfScenes[5] = nullptr;
    m_CurrScene = nullptr;
    camera = nullptr;
}


static const char* MAIN_WINDOW_TITLE = "COSC1226 - Assignment 1";

int main(int argc, char** argv)
{
    AssignmentApp* app = new AssignmentApp(MAIN_WINDOW_TITLE, true);
    if (int err = app->Init() != 0) {
        std::cout << "RTR:ERROR: Failed to initialise application. Please see error messages for details..." << std::endl;
        return -1;
    };
    app->Run();
    app->Done();
    return 0;
}