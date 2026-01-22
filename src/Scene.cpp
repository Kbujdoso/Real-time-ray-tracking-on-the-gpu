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
#include <cmath>
#include <algorithm>
#include "Globals.h"
#include <memory>

Scene::Scene(std::vector<std::unique_ptr<Objects>> objects, 
             std::vector<std::unique_ptr<Light>> lights) 
    : objects(std::move(objects)),
      lights(std::move(lights)) 
{}

Scene::Scene(){
}

std::optional<Intersection_data> Scene::trace(Ray ray) {
    std::optional<Intersection_data> closest_hit = std::nullopt;
    float min_t = std::numeric_limits<float>::max(); 
    for (auto& obj : objects) {

        auto current_hit = obj->intersect(ray);

        if (current_hit) {

            if (current_hit->T() < min_t) {
                min_t = current_hit->T();
                closest_hit = current_hit;
            }
        }
    }

    return closest_hit;
}

void Scene::add_object(std::unique_ptr<Objects> object){
    objects.push_back(std::move(object));
}


void Scene::add_light(std::unique_ptr<Light> light){
    lights.push_back(std::move(light));
}

void Scene::clear_all(){
    objects.clear();
    lights.clear();
}

std::vector<std::unique_ptr<Objects>>& Scene::get_Objects() {
    return objects;
}

