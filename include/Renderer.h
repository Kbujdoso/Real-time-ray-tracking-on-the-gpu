#ifndef RENDERER_H
#define RENDERER_H
#include "Camera.h"
#include "Scene.h"
#include "Resolution.h"
#include "Geometry.h"
#include <vector>
#include "GPU_Struct.h"
class Renderer{
    private: 
        Camera camera;
        Scene& scene;
        Resolution resolution;
        Point_Light light;
    public: 
        Renderer();
        Renderer(Camera camera, Scene& scene, Point_Light light);
        std::vector<GPU_Object> prepareSceneForGPU();
        GPU_Camera prepareCameraForGPU();
        GPU_Light prepareLightForGPU();
        void render();

};

#endif