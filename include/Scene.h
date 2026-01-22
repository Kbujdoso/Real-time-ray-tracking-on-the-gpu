#ifndef SCENE_H
#define SCENE_H
#include <iostream>
#include <utility>
#include <vector>
#include <optional>
#include "Geometry.h"
#include "Ray.h"
#include "Resolution.h"
#include "Camera.h"
#include "Light.h"
#include "Objects.h"
#include "Surface.h"
#include <memory>
class Light;
class Scene{
    private: 
        std::vector<std::unique_ptr<Objects>> objects;
        int num_objects;
        std::vector<std::unique_ptr<Light>> lights;
        int num_lights;
    public:
        Scene(std::vector<std::unique_ptr<Objects>> Objects , std::vector<std::unique_ptr<Light>> Lights);
        Scene(); 

        std::optional<Intersection_data> trace(Ray ray); 

        void add_object(std::unique_ptr<Objects> object);
        void remove_object(std::unique_ptr<Objects> object);
        std::vector<std::unique_ptr<Objects>>& get_Objects();

        void add_light(std::unique_ptr<Light> light);
        void remove_light(std::unique_ptr<Light> light);
        std::vector<std::unique_ptr<Light>> get_lights();

        void clear_all();
};



#endif