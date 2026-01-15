#ifndef RENDERER_H
#define RENDERER_H
#include "Camera.h"
#include "Scene.h"
#include "Resolution.h"
#include "Geometry.h"
class Renderer{
    private: 
        Camera camera;
        Scene& scene;
        Resolution resolution;
        Point_Light light;
    public: 
        Renderer();
        Renderer(Camera camera, Scene& scene, Point_Light light);
        void render();

};

#endif